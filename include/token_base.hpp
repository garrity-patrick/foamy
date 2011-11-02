#ifndef _TOKEN_BASE_HPP_
#define _TOKEN_BASE_HPP_

enum TokenType
{
	Error, Type, Reserved, Operator, Symbol, Number, Name
};

class token_base
{
protected:
	TokenType _type;

public:
	token_base(void) : _type(Error) { }
	
	token_base(TokenType t) : _type(t) { }
	
	token_base(const token_base & other) : _type(other._type) { }
	
	virtual ~token_base(void) { }
	
	token_base & operator=(const token_base & other)
	{
		_type = other._type;
		return *this;
	}
	
	TokenType type(void) const { return _type; }
	void set_type(TokenType t) { _type = t; }
};

#endif
