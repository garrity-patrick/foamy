#include "parser.hpp"

parser::parser( const std::vector<token_base *>* tokens ){
	_tokens = *tokens;
	_tokenPos = 0;
}

parser::~parser(){
	//Destroy yourself
};

bool verbose = false;

int parser::tokens_left(){

	return _tokens.size() - _tokenPos;
	
}

//Accessor for _look_ahead, allows for easier throwing of EOF errors.
token_base * parser::cur_token(){
	if( tokens_left() == 0 ){
		std::cout << "Unexpected End Of File" << std::endl;
		exit(1);
	}
	return _tokens[ _tokenPos ];
}

const char * get_type_string(TokenType type){
	switch(type){
		case ErrorToken:		return "'Error'";
		case Type:		return "'Type'";
		case Reserved:	return "'Reserved'";
		case OperatorToken:	return "'Operator'";
		case Symbol:	return "'Symbol'";
		case Number:	return "'Number'";
		case Name:		return "'Name'";
		default: 		return "No-Matching-Type";
	}
}
	
const char * get_operator_string(OperatorType type){
	switch(type){
		case ErrorOperator:	return "'ErrorOperator'";
		case OpEquals:		return "'Equals'";
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
		<< get_symbol_string ( dynamic_cast<const token_symbol *>( cur_token() )->symbol() )
		<< std::endl;
	exit(1);
}

void parser::operator_type_error(OperatorType expected){
	std::cout << "Error.  Expected OperatorType:" << get_operator_string( expected ) << " Received: "
		<< get_operator_string( dynamic_cast<const token_operator *>( cur_token() )->operator_type() )
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
			dynamic_cast<const token_symbol *>( cur_token() )->symbol() == desiredSymbol
		)
		return true;
	return false;
}

bool parser::check_operator( OperatorType desiredOperator ){
	if	( 	check_type( OperatorToken ) && 
			dynamic_cast<const token_operator *>( cur_token() )->operator_type() == desiredOperator
		)
		return true;
	return false;
}


//Functions to parse individual token types
void parser::parse_symbol(SymbolType desiredSymbol){
	if(verbose)
		std::cout << "Parse Symbol" << std::endl;

	if( !check_type( Symbol ) )
		token_type_error( Symbol );
		
	else if( !check_symbol( desiredSymbol ) )
		symbol_type_error(desiredSymbol );
	
	next_token();
}

ftype_t parser::parse_type(){
	if(verbose)
		std::cout << "Parse Type" << std::endl;

	if( !check_type ( Type ) )
		token_type_error( Type );
		
	ftype_t tempType = dynamic_cast<const token_type *>( cur_token() )->ftype();	
	
	next_token();
	
	return tempType;
}

ReservedWord parser::parse_reserved(){
	if(verbose)
		std::cout << "Parse Reserved" << std::endl;

	if( !check_type ( Reserved ) )
		token_type_error( Reserved );
	
	ReservedWord tempWord = dynamic_cast<const token_reserved *>( cur_token() )->word();
	
	next_token();
	
	return tempWord;
}

exp_const * parser::parse_number(){

	if(verbose)
		std::cout << "Parse Number" << std::endl;
	
	if( !check_type( Number ) )
		token_type_error( Number );
		
	exp_const * tempNode = new exp_const();
	
	tempNode->set_val( dynamic_cast<const token_number *>( cur_token() )->number() );
	tempNode->set_ftype( Int );
	
	next_token();
	
	return tempNode;
}

exp_operator * parser::parse_operator( OperatorType desiredOperator ){

	if(verbose)
		std::cout << "Parse Operator" << std::endl;

	if( !check_type( OperatorToken) )
		token_type_error( OperatorToken );
		
	else if( !check_operator( desiredOperator ) )
		operator_type_error( desiredOperator );


	exp_operator * tempNode = new exp_operator();
		
	tempNode->set_optype( dynamic_cast<const token_operator *>( cur_token() )->operator_type() );
	
	//TODO: Need to set l_exp and r_exp still.	Might set in statement after return.	
	
	next_token();
	
	return tempNode;
}


fident_t parser::parse_name(){

	if(verbose)
		std::cout << "Parse Name" << std::endl;

	if( !check_type( Name ) )
		token_type_error( Name );
	
	//TODO:	Add check for reserved words, throw error if found.
	
	fident_t tempIdent = dynamic_cast<const token_name *>( cur_token() )->name();
	
	next_token();
	
	return tempIdent;
}


//Parse Variable Declaration
exp_base * parser::parse_variable_declaration(){

	if(verbose)
		std::cout << "Parse Variable Declaration" << std::endl;

	exp_base * tempNode = new exp_declare();
	dynamic_cast<exp_declare *>( tempNode )->set_ftype( parse_type() );	//int
	parse_symbol( Colon );					//:
	dynamic_cast<exp_declare *>( tempNode )->set_name( parse_name() );		//x
	
	if( !check_symbol( Semicolon ) ){
		parse_operator( OpEquals );
		//Pass the variable declaration as an argument.  It will pass back the exp_assign
		//~	with the declare as the dest and the number as src.
		tempNode->set_next( parse_variable_assignment( dynamic_cast<exp_declare *>(tempNode)->name() ) );
	}
	//No check for semicolon because this function is used with params as well.
	
	return tempNode;//->next();
}
  	
vector <func_arg> * parser::parse_parameter_list(){

	if(verbose)
		std::cout << "Parse Parameter List" << std::endl;

	vector<func_arg> * funcArgs = new vector<func_arg>();
	
	parse_symbol( LParen );
	
	exp_declare * tempDeclare;
	func_arg * tempArg;
	while ( !check_symbol( RParen ) ){
		//TODO: May need to rework this.  Args are variable declarations.
	
		tempDeclare = dynamic_cast<exp_declare *>( parse_variable_declaration() );
		tempArg = new func_arg( tempDeclare->ftype(),tempDeclare->name() );
		funcArgs->push_back( *tempArg );
	}
	
	parse_symbol( RParen );
	
	return funcArgs;
}

exp_call * parser::parse_function_call(fident_t statementName){

	if(verbose)
		std::cout << "Parse Function Call" << std::endl;
	exp_call * ret_var = new exp_call();
		
	dynamic_cast<exp_call *>( ret_var )->set_fident( statementName ); 
	//Maybe change to parse_statement to allow for: return(x + 5);
	//TODO: Change to below line after it's sorted whether to use exp_base * or vector<func_args>
	//dynamic_cast<exp_call *>( tempNode )->set_args( parse_parameter_list() );
	
	//dynamic_cast<exp_call *>( ret_var )->set_args(  );
	parse_parameter_list();
	
	return ret_var;
}

//exp_base for now...I see problems returning a generic type like this...
exp_base * parser::parse_right_assignment(){

	if(verbose)
		std::cout << "Parse Right Assignment" << std::endl;

	exp_base * ret_var;
	exp_base * ret_var2;
	//Will not handle function call for now.
	if( check_type(Name) ){
		fident_t tempIdent = parse_name();
		
		//If it's an LParen, they're doing a function call.
		if( check_symbol( LParen ) ){
			ret_var = parse_function_call(tempIdent);
		}
		else{
			//Assume variable
			ret_var = new exp_var();
			dynamic_cast<exp_var *>( ret_var )->set_name( tempIdent );
		}
	}
	//Otherwise assume it's a number
	else{
		ret_var = parse_number();
		//dynamic_cast<const exp_const *>( ret_var )->set_val( parse_number() );
	}
	
	if( check_symbol(Semicolon) ){
		//Don't actually parse the Semicolon, that happens below.
		return ret_var;
	}
	//Otherwise assume you want a  "+"
	else{
		parse_operator(Plus);
		
		ret_var2 = new exp_operator();
		//Set the left side equal to what we parsed above
		dynamic_cast<exp_operator *>( ret_var2 )->set_lexp( ret_var );
		//Recur on the right side
		dynamic_cast<exp_operator *>( ret_var2 )->set_rexp( parse_right_assignment() );
		
		return ret_var2;
	}
	
}

exp_assign * parser::parse_variable_assignment(fident_t varName){

	if(verbose)
		std::cout << "Parse Variable Assignment" << std::endl;

	exp_assign * tempNode = new exp_assign();

	exp_var * varNode = new exp_var();
	varNode->set_name( varName );
	
	tempNode->set_dest( varNode );
	
	tempNode->set_src( parse_right_assignment() );
	return tempNode;
}

//May need to create separate functions for this to handle exp_call and 
//~	exp_declare
exp_base * parser::parse_name_statement(){

	if(verbose)
		std::cout << "Parse Name Statement" << std::endl;

	exp_base * ret_var = new exp_base();
	
	//Either Function Or Variable Assignment starts with a "Name" token
	fident_t statementName = parse_name();
	
	//If it's a symbol, assume it's a function call.
	if( check_symbol( LParen ) ){
		
		ret_var = parse_function_call(statementName);
	
	}
	//If it's an operator, assume it's an assignment operation.
	else if( check_type( OperatorToken ) ){
		parse_operator( OpEquals );
		ret_var = parse_variable_assignment( statementName );
	}
	else{
		//Otherwise assume you want a semicolon
		parse_symbol(Semicolon);
	}
	
	return ret_var;
	
}

exp_return * parser::parse_reserved_statement(){

	if(verbose)
		std::cout << "Parse Reserved Statement" << std::endl;

	exp_return * tempNode = new exp_return();
	exp_var * tempVar = new exp_var();
	//Only reserved word we have is "return" right now.
	
	parse_reserved();					//return
	parse_symbol(LParen);				//(
	//TODO: Change to allow for parse_statement parsing.
	
	tempVar->set_name( parse_name() );	//[variable]
	tempNode->set_arg( tempVar );
	
	parse_symbol(RParen);				//)
	
	return tempNode;
}

//Return true if "return()" because that would be the last 
//	~statement in the set of statements.  Will have to be more general later,
//	~but for now this will work.
exp_base * parser::parse_statement(){

	if(verbose)
		std::cout << "Parse Statement" << std::endl;

	exp_base * tempNode;
	switch( cur_token()->type() ){
		case Type:
			//exp_base * parentNode = tempNode;
			//For now, only variable definitions will begin with type in a statement
			tempNode = parse_variable_declaration();	//x:int = 5;
			parse_symbol( Semicolon );		//;
			//return false;
			break;
		case Name:
			tempNode = parse_name_statement();			//x = 5;
			parse_symbol( Semicolon );		//;
			//return false;
			break;
		case Reserved:
			tempNode = parse_reserved_statement();		//return(5);
			parse_symbol( Semicolon );
			//return true;
			break;
		default:
			std::cout << "Expected 'Type', 'Name', or 'Reserved Word' at beginning of statement." << 
			"received " << cur_token()->type() << std::endl;
			exit(1);
			break;
	}
	
	return tempNode;
	
}

exp_base * parser::parse_statements(){

	if(verbose)
		std::cout << "Parse Statements" << std::endl;

	exp_base * topNode = new exp_base();
	exp_base * curNode = topNode;

	//As long as we haven't encountered an RBrace yet, keep parsing statements.
	while( !check_symbol( RBrace ) ){
		curNode->set_next( parse_statement() );
		curNode = curNode->next();
		
		//This fixes declaration and assign statement overlap.
		if( curNode->next() != NULL ){
				curNode = curNode->next();
		}
	}
	
	return topNode;
		
}

node_function * parser::parse_function(){

	if(verbose)
		std::cout << "Parse Function" << std::endl;

	exp_declarefunc * tempDec = new exp_declarefunc();
	node_function * tempFunc = new node_function();
							//Example:
	tempFunc->set_rettype( parse_type() );			//	int
	parse_symbol( Colon );	//	:
	tempFunc->set_name( parse_name() );			//	main
	tempFunc->set_args( *parse_parameter_list() );	//	()
	parse_symbol( LBrace );	//	{
	tempFunc->set_body( parse_statements() );		//	return();
	parse_symbol( RBrace );	//	}
	
	
	
	tempDec->set_func( tempFunc );
	
	return tempFunc;
}


node_program * parser::begin_parse(){
	node_program * prog = new node_program();
	node_function * tempFunction;
	
	while( tokens_left() > 0){
		tempFunction = parse_function();
		
		if( tokens_left() > 0 )
			prog->globalsVector().push_back( tempFunction );
		else{
			prog->set_main( tempFunction );
			break;
		}
	}
	
	return prog;
}
  	
