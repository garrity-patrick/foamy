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

void codegen::gen(node_base * tree)
{
	if (tree == 0) return;
	// assert: tree exits.
	
	switch(tree->type())  // all cases except Expression will return from this function
	{
	case NodeError:
		return;
	case Program:
		return;
	case Function:
		return;
	case Expression:
		// For expressions, break out to the next switch statement
		break;
	default:
		return;
	}
	
	// assert: this is an expression node
	exp_base* exp = dynamic_cast<exp_base*>(tree);  // make ourselves an Expression object

	switch(exp->exptype())
	{
	case ExpError:
		break;
		
	case Var:
		break;
		
	case Const:
		break;
		
	case ExpOperator:
		break;
		
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
		
		_vars[var_name] = Alloca;
		gen(exp->next());
		break;
		
	case DeclareFunc:
		break;
		
	case Assign:
		break;
		
	case Call:
		break;
		
	case ExpReturn:
		break;
		
	default:
		break;
	}
}
