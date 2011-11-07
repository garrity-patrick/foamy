// token_type.hpp
// @author Chris Cornelius, Patrick Garrity, Jonathan Sandness                  
// Created 11/07/2011                                                           
// Foamy (toy language project) - ProLang course, Fall 2011   

#ifndef _TOKEN_TYPE_HPP_
#define _TOKEN_TYPE_HPP_

#include "token_base.hpp"

enum Datatype
{
	ErrorType=-1,Void=0,Int=1
};

static const unsigned int DATATYPE_SIZE = 2;
static const char * DATATYPE[] =
{
	"void","int"
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
