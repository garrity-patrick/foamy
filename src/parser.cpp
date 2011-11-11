#include "parser.hpp"
#include <iostream>
#include <cstdlib>

parser::parser( const std::vector<token_base *>* tokens ){
	_tokens = *tokens;
	_tokenPos = 0;
}

parser::~parser(){
	//Destroy yourself
};

//Accessor for _look_ahead, allows for easier throwing of EOF errors.
token_base * parser::cur_token(){
	if( (unsigned int)_tokenPos == _tokens.size() ){
		std::cout << "Unexpected End Of File" << std::endl;
		exit(1);
	}
	return _tokens[ _tokenPos ];
}

const char * get_type_string(TokenType type){
	switch(type){
		case Error:		return "'Error'";
		case Type:		return "'Type'";
		case Reserved:	return "'Reserved'";
		case Operator:	return "'Operator'";
		case Symbol:	return "'Symbol'";
		case Number:	return "'Number'";
		case Name:		return "'Name'";
		default: 		return "No-Matching-Type";
	}
}
	
const char * get_operator_string(OperatorType type){
	switch(type){
		case ErrorOperator:	return "'ErrorOperator'";
		case Equals:		return "'Equals'";
		case Plus:			return "'Plus'";
		default:			return "'No-Matching-Operator'";
	}
}

const char * get_symbol_string(SymbolType type){
	switch(type){
		case ErrorOperator:	return "'ErrorSymbol'";
		case LParen:		return "'LParen'";
		case RParen:		return "'RParen'";
		case LBrace:		return "'LBrace'";
		case RBrace:		return "'RBrace'";
		case Semicolon:		return "'Semicolon'";
		case Colon:			return "'Colon'";
		default:			return "'No-Matching-Symbol'";
	}
}



//Error=-1, Type=0, Reserved=1, Operator=2, Symbol=3, Number=4, Name=5
//Functions used to signal errors
void parser::token_type_error(TokenType expected){
	std::cout << "Token Type Error.  Expected " << get_type_string(expected) << " Received: "
		<< get_type_string( cur_token()->type() ) << std::endl;
	exit(1);
}
//reinterpret_cast<const token_symbol *>( cur_token() )->get_symbol_string()
void parser::symbol_type_error(SymbolType expected ){
	std::cout << "Error.  Expected SymbolType: " << get_symbol_string( expected ) << " Received: "
		<< get_symbol_string ( reinterpret_cast<const token_symbol *>( cur_token() )->symbol() )
		<< std::endl;
	exit(1);
}

void parser::operator_type_error(OperatorType expected){
	std::cout << "Error.  Expected OperatorType:" << get_operator_string( expected ) << " Received: "
		<< get_operator_string( reinterpret_cast<const token_operator *>( cur_token() )->operator_type() )
		<< std::endl;
	exit(1);
}


//Function to advance the token
void parser::next_token(){
	_tokenPos ++;
}

//Functions to check types, not parse
bool parser::check_type( TokenType desiredType ){
	if( cur_token()->type() == desiredType )
		return true;
	return false;
}

bool parser::check_symbol( SymbolType desiredSymbol ){
	if	( 	check_type( Symbol ) &&
			reinterpret_cast<const token_symbol *>( cur_token() )->symbol() == desiredSymbol
		)
		return true;
	return false;
}

bool parser::check_operator( OperatorType desiredOperator ){
	if	( 	check_type( Operator ) && 
			reinterpret_cast<const token_operator *>( cur_token() )->operator_type() == desiredOperator
		)
		return true;
	return false;
}


//Functions to parse individual token types
void parser::parse_symbol(SymbolType desiredSymbol){
	if( !check_type( Symbol ) )
		token_type_error( Symbol );
		
	else if( !check_symbol( desiredSymbol ) )
		symbol_type_error(desiredSymbol );
	
	next_token();
}

void parser::parse_type(){
	if( !check_type ( Type ) )
		token_type_error( Type );
		
	next_token();
}

void parser::parse_reserved(){
	if( !check_type ( Reserved ) )
		token_type_error( Reserved );
		
	next_token();
}

void parser::parse_number(){
	if( !check_type( Number ) )
		token_type_error( Number );
	
	next_token();
}

void parser::parse_operator( OperatorType desiredOperator ){
	if( !check_type( Operator) )
		token_type_error( Operator );
		
	else if( !check_operator( desiredOperator ) )
		operator_type_error( desiredOperator );
		
	next_token();
}


void parser::parse_name(){
	if( !check_type( Name ) )
		token_type_error( Name );
	
	//TODO:	Add check for reserved words, throw error if found.
	
	next_token();
}


//Parse Variable Declaration
void parser::parse_variable_declaration(){
	parse_type();			//int
	parse_symbol( Colon );	//:
	parse_name();			//x
	
	if( !check_symbol( Semicolon ) ){
		parse_operator( Equals );
		parse_number();
	}
	//No check for semicolon because this function is used with params as well.
} 
  	
void parser::parse_parameter_list(){
	parse_symbol( LParen );
	
	while ( !check_symbol( RParen ) )
		parse_variable_declaration();
	
	parse_symbol( RParen );
	
}


void parser::parse_name_statement(){
	//Either Function Or Variable Assignment starts with a "Name" token
	
	parse_name();	//x
	
	//If it's a symbol, assume it's a function call.
	if( check_symbol( LParen ) ){
		
		parse_symbol( LParen );		//	(
		parse_parameter_list();		//	[args]
		parse_symbol( RParen );		//	)
		
	}
	//If it's an operator, assume it's an assignment operation.
	else if( check_type( Operator ) ){
		parse_operator( Equals );
		parse_number();	//Assume we're just doing like: x=5
	}
	
}

void parser::parse_reserved_statement(){
	//Only reserved word we have is "return" right now.
	
	parse_reserved();		//return
	parse_symbol(LParen);	//(
	parse_name();			//[variable]
	parse_symbol(RParen);	//)
	
}

//Return true if "return()" because that would be the last 
//	~statement in the set of statements.  Will have to be more general later,
//	~but for now this will work.
bool parser::parse_statement(){
	switch( cur_token()->type() ){
		case Type:
			//For now, only variable definitions will begin with type in a statement
			parse_variable_declaration();	//x:int = 5;
			parse_symbol( Semicolon );		//;
			return false;
			break;
		case Name:
			parse_name_statement();			//x = 5;
			parse_symbol( Semicolon );		//;
			return false;
			break;
		case Reserved:
			parse_reserved_statement();		//return(5);
			parse_symbol( Semicolon );
			return true;
			break;
		default:
			std::cout << "Expected 'Type', 'Name', or 'Reserved Word' at beginning of statement." << 
			"received " << cur_token()->type() << std::endl;
			exit(1);
			break;
	}
	
}

void parser::parse_statements(){
	bool finished = false;
	//As long as we haven't encountered an RBrace yet, keep parsing statements.
	while( !check_symbol( RBrace ) ){
		finished = parse_statement();
		if( finished )
			break;
	}
		
}

void parser::parse_function(){
							//Example:
	parse_type();			//	int
	parse_symbol( Colon );	//	:
	parse_name();			//	main
	parse_parameter_list();	//	()
	parse_symbol( LBrace );	//	{
	parse_statements();		//	return();
	parse_symbol( RBrace );	//	}
}


void parser::begin_parse(){
	parse_function();
}
  	
