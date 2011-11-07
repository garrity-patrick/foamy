// token_name.hpp
// @author Chris Cornelius, Patrick Garrity, Jonathan Sandness                  
// Created 11/07/2011                                                           
// Foamy (toy language project) - ProLang course, Fall 2011   

#ifndef _TOKEN_NAME_HPP_
#define _TOKEN_NAME_HPP_

#include "token_base.hpp"
#include <string>

class token_name : public token_base
{
private:
	std::string _name;

public:
	token_name(void) { _type = Name; }
	
	token_name(const std::string name) : _name(name) { _type = Name; }
	
	token_name(const token_name & other) :
		_name(other._name)
	{
		_type = Name;
	}
	
	virtual ~token_name(void) { }
	
	token_name & operator=(const token_name & other)
	{
		if (this != &other)
		{
			_name = other._name;
		}
		
		return *this;
	}
	
	const std::string & name(void) const { return _name; }
	
	void set_name(const std::string & name) { _name = name; }
};

#endif
