#ifndef _CODEGEN_HPP_
#define _CODEGEN_HPP_

#include "node_base.hpp"

#include <llvm/Module.h>
#include <llvm/Function.h>
#include <llvm/PassManager.h>
#include <llvm/CallingConv.h>
#include <llvm/Analysis/Verifier.h>
#include <llvm/Assembly/PrintModulePass.h>
#include <llvm/Support/IRBuilder.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/LLVMContext.h>

#include <map>
#include <stack>
#include <pair>

class codegen
{
private:
	node_base * _tree;
	Module * _mod;
	std::string _name;
	
	std::map<std::string, AllocaInst *> _vars;
	std::stack<std::pair<BasicBlock *, IRBuilder<> > > _blocks;

public:
	codegen(void);
	codegen(const std::string & name);
	~codegen(void);
	
	void generate();

private:
	void gen(node_base * tree);
};

#endif
