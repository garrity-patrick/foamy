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

#include <vector>

/*
#include "node_base.hpp"
#include "node_exp.hpp"
#include "node_function.hpp"
#include "node_program.hpp"
#include "node_seqnode.hpp"
*/

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
	
	//Parse an entire function
	void parse_function();
	
	bool check_symbol(SymbolType);
	
	bool check_operator(OperatorType);
	
	bool check_type(TokenType);
	
	
	token_base * cur_token();
	
	//Parse a type token
	void parse_type();
	
	//Parse  a number
	void parse_number();
	
	//Parse a name
  	void parse_name();
  	
  	//Parse a reserved word
  	void parse_reserved();
  	
  	//Check the operator value of _lookAhead against parameter
  	void parse_operator( OperatorType );
  	
  	//Check the symbol value of _lookAhead against parameter
	void parse_symbol(SymbolType);
	
  	//Parse a list of parameters in a function
  	void parse_parameter_list();
  	
  	//Parse a statement that begins with a "name" token
  	void parse_name_statement();
  	
  	//Parse a statement that begins with a reserved word, namely "return"
  	void parse_reserved_statement();
  	
  	//Parse a single statement
  	bool parse_statement();
  	
  	//Parse the statements inside the body of a function
  	void parse_statements();
  	
  	//Parse a variable declaration
  	void parse_variable_declaration();
  	
  	//Throw an error if unexpected result occurs
  	void token_type_error(TokenType);
  	void symbol_type_error(SymbolType);
  	void operator_type_error(OperatorType);
  	
  	
  
};


#endif // _PARSER_H_

>>>>>>> 8c72c2f7454d662b45ad0d0cfebe2abca98c2e9c
