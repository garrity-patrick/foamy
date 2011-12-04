#include "codegen.hpp"

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
	exp_base* exp = dynamic_cast<exp_base*> (tree);  // make ourselves an Expression object

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
