#define _FUNCTABLE_HPP_
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

class func
{
private:
	Function * _llvmfunc;
	ftype_t _type;
	//args

public:
	func(void);
};

#endif
