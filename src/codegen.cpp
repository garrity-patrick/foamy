#include "codegen.hpp"
#include "exp.hpp"
#include "node.hpp"

codegen::codegen()
{
	_tree = 0;
	_name = std::string("default");
	_mod = 0;
}

codegen::codegen(const std::string & name)
{
	_tree = 0;
	_name = name;
	_mod = 0;
}

codegen::~codegen()
{
	if (_mod != 0) delete _mod;
}

void codegen::generate()
{
	if (_mod != 0) delete _mod;
	_mod = gen(_tree);
	
	if (_mod == 0)
	{
		return;
	}
	
	verifyModule(*_mod, PrintMessageAction);
	
	PassManager pm;
	pm.add(createPrintModulePass(&outs()));
	pm.run(*_mod);
	
	delete _mod;
	_mod = 0;
}

Value * codegen::gen(node_base * tree)
{
	if (tree == 0) return;
	// assert: tree exits.
	
	switch(tree->type())  // all cases except Expression will return from this function
	{
	/*--------------------------------------------------------------------------
	Error Node - Something went wrong.
	--------------------------------------------------------------------------*/
	case NodeError:
		return ErrorV("ERROR NODE");
		
	/*--------------------------------------------------------------------------
	Program Node - Defines a program. There should be only one.
	--------------------------------------------------------------------------*/
	case Program:
		return 0;
	
	/*--------------------------------------------------------------------------
	Function Node - Defines a function, including its body.
	--------------------------------------------------------------------------*/
	case Function:
		return 0;
	
	/*--------------------------------------------------------------------------
	Expression Node - This case falls through to the different types of
	expressions. These should always be within a function body.
	--------------------------------------------------------------------------*/
	case Expression:
		// For expressions, break out to the next switch statement
		break;
		
	/*--------------------------------------------------------------------------
	Herp Derp - Something went abnormally wrong.
	--------------------------------------------------------------------------*/
	default:
		return 0;
	}
	
	// assert: this is an expression node
	exp_base* exp = dynamic_cast<exp_base*>(tree);  // make ourselves an Expression object

	switch(exp->exptype())
	{
	/*--------------------------------------------------------------------------
	Error Expression - Something went wrong.
	--------------------------------------------------------------------------*/
	case ExpError:
		return ErrorV("ERROR EXPRESSION");
		
	/*--------------------------------------------------------------------------
	Variable Expression - Get the value of a variable.
	--------------------------------------------------------------------------*/
	case Var:
		exp_var * v = dynamic_cast<exp_var *>(exp);
		std::string vname = v->name();
		
		// Get the variable, searching beginning with the most recent scope.
		var * info = search_var(vname);
		if (info == 0)
		{
			return ErrorV("Unknown variable name.");
		}
		
		// Get the instance of the variable.
		AllocaInst * alloca = info->alloca();
		if (alloca == 0)
		{
			return ErrorV("No alloca associated with variable!");
		}
		
		// Evaluate the next expression.
		gen(exp->next());
		
		// Generate code in the current scope.
		return current_builder().CreateLoad(alloca, vname.c_str());
		
	/*--------------------------------------------------------------------------
	Constant Expression - Does not actually generate code.
	This case is used to get the (LLVM) value of a constant.
	--------------------------------------------------------------------------*/
	case Const:
		exp_const * c = dynamic_cast<exp_const *>(exp);
		
		// Evaluate the next expression.
		gen(exp->next());
		
		// Return the value associated with this constant.
		return ConstantInt::get(getGlobalContext(), APInt(32, c->val(), true));
	
	/*--------------------------------------------------------------------------
	(Binary) Operator Expression - Evaluate a binary expression.
	For example, a+b. This case evaluates the left and right sides.
	--------------------------------------------------------------------------*/
	case ExpOperator:
		exp_operator * oper = dynamic_cast<exp_operator *>(exp);
		
		// Evaluate the left- and- right expressions.
		Value * left = gen(oper->lexp());
		Value * right = gen(oper->rexp());
		
		if (left == 0 || right == 0)
		{
			// Error
			return ErrorV("Could not evaluate operands!");
		}
		
		// Get the builder for the current scope.
		IRBuilder<> builder = current_builder();
		
		// Generate code based on the operator type.
		switch (oper->optype())
		{
		case Plus:
			return builder.CreateAdd(left, right);
		case Minus:
			return builder.CreateSub(left, right);
		case Greater:
			return builder.CreateICmpSGT(left, right);
		case Less:
			return builder.CreateICmpSLT(left, right);
		default:
			return ErrorV("Invalid binary operator.");
		}
		
		break;
		
	/*--------------------------------------------------------------------------
	(Variable) Declaration Expression - Declare a new variable.
	--------------------------------------------------------------------------*/
	case Declare:
		exp_declare * decl = dynamic_cast<exp_declare *>(exp);
		std::string var_name = decl->name();
		
		map<std::string, AllocaInst *>::iterator it = _vars.find(var_name);
		if (it != _vars.end())
		{
			// Trying to re-declare a variable!
			gen(exp->next());
			break;
		}
		
		Value * initial_value = ConstantInt::get(getGlobalContext(), 
												 APInt(32, 0, true));
		
		IRBuilder<> tmp(_blocks.top().first, _blocks.top().first->begin());
		AllocaInst * Alloca = tmp.CreateAlloca(Type::getInt32Ty(
			getGlobalContext()), 0, var_name.c_str());
		
		builder = _blocks.top().second;
		builder.CreateStore(initial_value, Alloca);
		
		var * v = new var();
		v->set_alloca(Alloca);
		v->set_type(decl->ftype());
		_scope.top()->insert_variable(var_name, v);
		
		gen(exp->next());
		
		return initial_value;
		break;
	
	/*--------------------------------------------------------------------------
	(Function) Declaration Expression - Declare a local function.
	--------------------------------------------------------------------------*/	
	case DeclareFunc:
		Value * f = gen(fexp->func());
		gen(exp->next());
		return f;
		
	/*--------------------------------------------------------------------------
	Assignment Expression - Assign a value to a variable.
	--------------------------------------------------------------------------*/
	case Assign:
		// get data on this transaction
		exp_assign* ass = dynamic_cast<exp_assign*> (exp);
		string var_name;
		
		// guard to make sure this expression is well-formed
		if(ass->dest() != 0 && ass->src() != 0)
		{
			var_name = ass->dest()->name();
		}
		else 
		{
			return ErrorV("Badly formed assignment!");
		}
		
		// check if variable is in variable table
		var * info = search_var(var_name);
		if (info == 0)
		{
			return ErrorV("[Assign] Unknown variable name.");
		}
		
		// get the instance for our variable (look up by name, note that we don't have scoping yet)
		AllocaInst * alloca = info->alloca();
		
		// find the value to assign to the variable.
		Value * new_value = gen(ass->src());
		
		// set up the object to generate code
		current_builder().CreateStore(initial_value, Alloca);
		
		// recur to move to next expression
		gen(exp->next());
		return new_value;
		
	/*--------------------------------------------------------------------------
	Call Expression - Call a function. Returns the value of the called function.
	--------------------------------------------------------------------------*/
	case Call:
		break;
		
	/*--------------------------------------------------------------------------
	Return Expression - Return from the current function.
	--------------------------------------------------------------------------*/
	case ExpReturn:
		break;
	
	/*--------------------------------------------------------------------------
	Herp Derp. Something went abnormally wrong.
	--------------------------------------------------------------------------*/	
	default:
		break;
	}
}

var * codegen::search_var(const std::string & name)
{
	list<scope>::iterator rit;
	for (rit = _scope.rbegin(); rit != _scope.rend(); ++rit)
	{
		var * result = (*rit)->get_variable(name);
		if (result != 0) return result;
	}
	
	return 0;
}

func * codegen::search_func(const std::string & name)
{
	list<scope>::iterator rit;
	for (rit = _scope.rbegin(); rit != _scope.rend(); ++rit)
	{
		func * result = (*rit)->get_function(name);
		if (result != 0) return result;
	}
	
	return 0;
}

IRBuilder<> current_builder(void) const
{
	return _scope.top()->get_builder();
}
