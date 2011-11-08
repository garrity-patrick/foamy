// token_type.hpp
// @author Chris Cornelius, Patrick Garrity, Jonathan Sandness                  
// Created 11/07/2011                                                           
// Foamy (toy language project) - ProLang course, Fall 2011   

#ifndef _TOKEN_TYPE_HPP_
#define _TOKEN_TYPE_HPP_

#include "token_base.hpp"
#include "ftype_t.hpp"

class token_type : public token_base
{
private:
	ftype_t _ftype;

public:
	token_type(void) : _ftype(ErrorType) { _type = Type; }
	
	token_type(ftype_t d) : _ftype(d) { _type = Type; }
	
	token_type(const token_type & other) : 
		_ftype(other._ftype)
	{
		_type = Type;
	}
	
	virtual ~token_type(void) { }
	
	token_type & operator=(const token_type & other)
	{
		_ftype = other._ftype;
		return *this;
	}
	
	ftype_t ftype(void) const { return _ftype; }
	
	void set_ftype(const ftype_t d) { _ftype = d; }
};

#endif
