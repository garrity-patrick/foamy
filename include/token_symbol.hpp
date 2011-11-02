#ifndef _TOKEN_SYMBOL_HPP_
#define _TOKEN_SYMBOL_HPP_

#include "token_base.hpp"

enum SymbolType
{
	ErrorSymbol,LParen,RParen,LBrace,RBrace,Semicolon,Colon
};

class token_symbol : public token_base
{
private:
	SymbolType _symbol;

public:
	token_symbol(void) : _symbol(ErrorSymbol) { _type = Symbol; }
	
	token_symbol(SymbolType sym) : _symbol(sym) { _type = Symbol; }
	
	token_symbol(const token_symbol & other) :
		_symbol(other._symbol)
	{
		_type = Symbol;
	}
	
	virtual ~token_symbol(void) { }
	
	token_symbol & operator=(const token_symbol & other)
	{
		_type = other._type;
		_symbol = other._symbol;
		return *this;
	}
	
	SymbolType symbol(void) const { return _symbol; }
	
	void set_symbol(SymbolType sym) { _symbol = sym; }
};

#endif
