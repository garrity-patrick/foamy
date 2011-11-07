// token_operator.hpp
// @author Chris Cornelius, Patrick Garrity, Jonathan Sandness                  
// Created 11/07/2011                                                           
// Foamy (toy language project) - ProLang course, Fall 2011   

#ifndef _TOKEN_OPERATOR_HPP_
#define _TOKEN_OPERATOR_HPP_

#include "token_base.hpp"

enum OperatorType
{
	ErrorOperator=-1,Equals=0,Plus=1
};

class token_operator : public token_base
{
private:
	OperatorType _operator;

public:
	token_operator(void) : _operator(ErrorOperator) { _type = Operator; }
	
	token_operator(OperatorType o) : _operator(o) { _type = Operator; }
	
	token_operator(const token_operator & other) :
		_operator(other._operator)
	{
		_type = Operator;
	}
	
	virtual ~token_operator(void) { }
	
	token_operator & operator=(const token_operator & other)
	{
		_operator = other._operator;
		return *this;
	}
	
	OperatorType operator_type(void) const { return _operator; }
	
	void set_operator_type(OperatorType o) { _operator = o; }
};

#endif
