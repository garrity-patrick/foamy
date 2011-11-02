#ifndef _TOKEN_TYPE_HPP_
#define _TOKEN_TYPE_HPP_

#include "token_base.hpp"

enum Datatype
{
	ErrorType,Void,Int
};

class token_type : public token_base
{
private:
	Datatype _datatype;

public:
	token_type(void) : _datatype(ErrorType) { _type = Type; }
	
	token_type(Datatype d) : _datatype(d) { _type = Type; }
	
	token_type(const token_type & other) : 
		_datatype(other._datatype)
	{
		_type = Type;
	}
	
	virtual ~token_type(void) { }
	
	token_type & operator=(const token_type & other)
	{
		_datatype = other._datatype;
		return *this;
	}
	
	Datatype datatype(void) const { return _datatype; }
	
	void set_datatype(Datatype d) { _datatype = d; }
};

#endif
