#ifndef _FUNCTABLE_HPP_
#define _FUNCTABLE_HPP_

#include "ftype_t.hpp"
#include "node_function.hpp"

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
#include <list>

using namespace llvm;

using std::map;
using std::string;

class func
{
private:
	Function * _llvmfunc;
	ftype_t _type;
	vector<func_arg> _args;

public:
	func(void);
	
	void set_llvmfunc(Function * f) { _llvmfunc = f; }
	void set_type(ftype_t t) { _type = t; }
	void set_args(const vector<func_arg> & args) { _args = args; }
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
