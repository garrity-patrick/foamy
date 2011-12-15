#ifndef _SCOPE_HPP_
#define _SCOPE_HPP_

#include "vartable.hpp"
#include "functable.hpp"

#include <llvm/Module.h>
#include <llvm/Function.h>
#include <llvm/PassManager.h>
#include <llvm/CallingConv.h>
#include <llvm/Analysis/Verifier.h>
#include <llvm/Assembly/PrintModulePass.h>
#include <llvm/Support/IRBuilder.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/LLVMContext.h>

using llvm::BasicBlock;
using llvm::Block;
using llvm::IRBuilder;
using llvm::Value;

#include <string>

class scope
{
private:
	BasicBlock * _block;
	IRBuilder<> _builder;
	vartable * _vars;
	functable * _funcs;

public:
	scope(void)
	{
		_block = 0;
		_vars = 0;
		_funcs = 0;
		_vars = new vartable();
		_funcs = new functable();
	}
	
	scope(const scope & other)
	{
		_block = other._block;
		_builder = other._builder;
		_vars = new vartable(*other._vars);
		_funcs = new functable(*other._funcs);
	}
	
	scope(BasicBlock * b)
	{
		_block = b;
		make_builder();
		_vars = new vartable();
		_funcs = new functable();
	}
	
	~scope(void)
	{
		if (_vars != 0) delete _vars;
		if (_funcs != 0) delete _funcs;
	}
	
	void set_block(Block * b) { _block = b; }
	
	BasicBlock * get_block(void) { return _block; }
	IRBuilder<> get_builder(void) const { return _builder; }
	const vartable * get_vars(void) const { return _vars; }
	const functable * get_funcs(void) const { return _funcs; }
	
	const var * get_variable(const std::string & name) const
	{
		return _vars->get(name);
	}
	
	const func * get_function(const std::string & name) const
	{
		return _funcs->get(name);
	}
	
	void make_builder(void)
	{
		if (_block == 0) return;
		_builder = IRBuilder<>(_block);
	}
	
	void insert_variable(const std::string & name, var * v)
	{
		if (_vars->get(name) != 0)
		{
			_vars->modify(name, v);
		}
		else
		{
			_vars->insert(name, v);
		}
	}
};

#endif
