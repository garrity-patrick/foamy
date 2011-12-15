#ifndef _FUNCTABLE_HPP_
#define _FUNCTABLE_HPP_

#include "ftype_t.hpp"

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
#include <string>

using std::map;
using std::string;

class func
{
private:
	llvm::Function * _llvmfunc;
	ftype_t _type;
	//args

public:
	func(void);
};


class functable {
private:
	map<string, func*> _table;
	
public:
	functable();
	functable(functable&);
	
	~functable();
	
	int modify(const string& func_name, func * v);
	int insert(string func_name, func* v);
	func* get(const string& func_name);
	
};

#endif
