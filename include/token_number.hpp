#ifndef _TOKEN_NUMBER_HPP_
#define _TOKEN_NUMBER_HPP_

#include "token_base.hpp"

class token_number : public token_base
{
private:
	int _number;

public:
	token_number(void) : _number(0) { _type = Number; }
	
	token_number(int n) : _number(n) { _type = Number; }
	
	token_number(const token_number & other) :
		_number(other._number)
	{
		_type = Number;
	}
	
	virtual ~token_number(void) { }
	
	token_number & operator=(const token_number & other)
	{
		_number = other._number;
		return *this;
	}
	
	int number(void) const { return _number; }
	
	void set_number(int n) { _number = n; }
};

#endif
