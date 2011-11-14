// @author Chris Cornelius, Patrick Garrity, Jonathan Sandness                  
// Created 11/07/2011                                                           
// Foamy (toy language project) - ProLang course, Fall 2011

#ifndef _PARSER_H_
#define _PARSER_H_

#include "token_base.hpp"
#include "token_error.hpp"
#include "token_type.hpp"
#include "token_reserved.hpp"
#include "token_operator.hpp"
#include "token_symbol.hpp"
#include "token_number.hpp"
#include "token_name.hpp"
#include "fident_t.hpp"
#include "ftype_t.hpp"

#include <vector>


#include "exp_base.hpp"
#include "exp_assign.hpp"
#include "exp_call.hpp"
#include "exp_const.hpp"
#include "exp_declare.hpp"
#include "exp_declarefunc.hpp"
#include "exp_operator.hpp"
#include "exp_return.hpp"
#include "exp_var.hpp"


class parser
{
protected:
	std::vector<token_base *> _tokens;
	int _tokenPos;
	
public:
	parser(const std::vector<token_base *> * tokens);
	~parser();
	
	//Start the parsing process
	void begin_parse();
	
	//Grab the next token, set _tokenPos equal to it
	void next_token();
	
	bool check_symbol(SymbolType);
	
	bool check_operator(OperatorType);
	
	bool check_type(TokenType);
	
	
	token_base * cur_token();
	
	//Parse a type token
	ftype_t parse_type();
	
	//Parse  a number
	exp_const * parse_number();
	
	//Parse a name
  	fident_t parse_name();
  	
  	//Parse a reserved word
  	fident_t parse_reserved();
  	
  	//Check the operator value of _lookAhead against parameter
  	exp_operator * parse_operator( OperatorType );
  	
  	//Check the symbol value of _lookAhead against parameter
	void parse_symbol(SymbolType);
	
  	//Parse a list of parameters in a function
  	exp_declare ** parse_parameter_list();
  	
  	//Parse a statement that begins with a "name" token
  	exp_base * parse_name_statement();
  	
  	//Parse a statement that begins with a reserved word, namely "return"
  	exp_return * parse_reserved_statement();
  	
  	//Parse a single statement
  	exp_base * parse_statement();
  	
  	//Parse the statements inside the body of a function
  	exp_base ** parse_statements();
  	
  	//Parse an entire function
	exp_declarefunc * parse_function();
  	
  	//Parse a variable declaration
  	exp_declare * parse_variable_declaration();
  	
  	//Throw an error if unexpected result occurs
  	void token_type_error(TokenType);
  	void symbol_type_error(SymbolType);
  	void operator_type_error(OperatorType);
  	
  	
  
};


#endif // _PARSER_H_

