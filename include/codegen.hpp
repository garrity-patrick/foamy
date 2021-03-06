#ifndef _CODEGEN_HPP_
#define _CODEGEN_HPP_

#include "node_base.hpp"
#include "scope.hpp"

#include <llvm/Module.h>
#include <llvm/Function.h>
#include <llvm/PassManager.h>
#include <llvm/CallingConv.h>
#include <llvm/Analysis/Verifier.h>
#include <llvm/Assembly/PrintModulePass.h>
#include <llvm/Support/IRBuilder.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/LLVMContext.h>
#include <llvm/Type.h>
#include <llvm/DerivedTypes.h>

#include <list>
using std::list;
using llvm::Module;
using llvm::IRBuilder;
using llvm::Value;
using llvm::Type;

class codegen
{
private:
	node_base * _tree;
	Module * _mod;
	std::string _name;
	std::list<scope *> _scope;

public:
	codegen(void);
	codegen(const std::string & name);
	~codegen(void);
	
	void set_tree(node_base * derp) { _tree = derp; }
	void generate();

private:
	Value * gen(node_base * tree);
	var * search_var(const std::string & name);
	func * search_func(const std::string & name);
	IRBuilder<> * current_builder(void) const;
};

#endif
