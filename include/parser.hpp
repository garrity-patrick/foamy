<<<<<<< HEAD
#ifndef _PARSER_HPP_
#define _PARSER_HPP_

class parser
{
};

#endif
=======
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

#include "exp_base.hpp"
#include "exp_assign.hpp"
#include "exp_call.hpp"
#include "exp_const.hpp"
#include "exp_declare.hpp"
#include "exp_declarefunc.hpp"
#include "exp_operator.hpp"
#include "exp_return.hpp"
#include "exp_var.hpp"

#include "node_function.hpp"
#include "node_base.hpp"
#include "node_program.hpp"

#include <vector>
#include <iostream>
#include <cstdlib>

class parser
{
protected:
	std::vector<token_base *> _tokens;
	int _tokenPos;
	
public:
	parser(const std::vector<token_base *> * tokens);
	~parser();
	
	//Start the parsing process
	node_program * begin_parse();
	
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
  	ReservedWord parse_reserved();
  	
  	//Check the operator value of _lookAhead against parameter
  	exp_operator * parse_operator( OperatorType );
  	
  	//Check the symbol value of _lookAhead against parameter
	void parse_symbol(SymbolType);
	
  	//Parse a list of parameters in a function
  	vector <func_arg> * parse_parameter_list();
  	
  	
  	//Parse a statement that begins with a "name" token
  	exp_base * parse_name_statement();
  	
  	//Parse a statement that begins with a reserved word, namely "return"
  	exp_return * parse_reserved_statement();
  	
  	//Parse a single statement
  	exp_base * parse_statement();
  	
  	//Parse the statements inside the body of a function
  	exp_base * parse_statements();
  	
  	//Parse an entire function
	node_function * parse_function();
  	
  	//Parse a variable declaration
  	exp_base * parse_variable_declaration();
  	
  	//Do a variable assignment with this exp_declare
  	exp_assign * parse_variable_assignment(fident_t);
  	
  	//Throw an error if unexpected result occurs
  	void token_type_error(TokenType);
  	void symbol_type_error(SymbolType);
  	void operator_type_error(OperatorType);
  	
  	
  
};


#endif // _PARSER_H_

>>>>>>> 8c72c2f7454d662b45ad0d0cfebe2abca98c2e9c
