// token_error.hpp
// @author Chris Cornelius, Patrick Garrity, Jonathan Sandness                  
// Created 11/07/2011                                                           
// Foamy (toy language project) - ProLang course, Fall 2011   

#ifndef _TOKEN_ERROR_HPP_
#define _TOKEN_ERROR_HPP_

#include "token_base.hpp"
#include <string>

class token_error : public token_base
{
private:
	std::string _message;

public:
	token_error(void) { _type = ErrorToken; }
	
	token_error(const std::string & msg) : _message(msg) { _type = ErrorToken; }
	
	token_error(const token_error & other) : 
		_message(other._message)
	{
		_type = ErrorToken;
	}
	
	virtual ~token_error(void) { }
	
	token_error & operator=(const token_error & other)
	{
		if (this != &other)
		{
			_message = other._message;
		}
		
		return *this;
	}
	
	const std::string & message(void) const { return _message; }
	
	void set_message(const std::string & msg) { _message = msg; }
};

#endif
