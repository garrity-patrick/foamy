// foamyc.cpp
// @author Pat Garrity, Chris Cornelius, Jon Sandness
// Backbone compiler for foamy language
// Rough cut from scanner_driver on 12/14/11 at 10pm

#include "scanner.hpp"
#include "parser.hpp"
#include "codegen.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::streamsize;
using std::vector;

void usage(void)
{
	cout << "Usage: foamyc [file]" << endl;
	cout << "" << endl;
}

int main(int argc, char ** argv)
{

	bool verbose = true;
	
	if (argc < 2)
	{
		usage();
		return 1;
	}
	
	// Attempt to open the input file for scanning.
	ifstream stm(argv[1], std::ios::ate);
	
	if (!stm.is_open() || !stm.good())
	{
		cout << "Error: could not open file '" << argv[1] << "'" << endl;
		return 1;
	}
	
	// Read the entire file.
	streamsize end = stm.tellg();
	stm.seekg(0);
	char * raw_code = 0;
	raw_code = new char[end + 1];
	stm.read(raw_code, end);
	stm.close();
	
	if (raw_code == 0)
	{
		cout << "Error: could not allocate/read the code from file!" << endl;
		return 10;
	}
	
	// Create the code string, and free the memory used by our char array.
	string code(raw_code);
	delete [] raw_code;
	
	if( verbose ){
		cout << "=== CODE LISTING ===" << endl;
		cout << code << endl;
		cout << "====================" << endl << endl;
	}
	
	// Create and initialize a scanner, then scan the code.
	scanner s;
	s.set_code(code);
	s.scan();
	
	// print out the tokenized code
	if( verbose ){
		const vector<token_base *> * tokens = s.tokens();
		cout << "=== TOKENIZATION ===" << endl;
		cout << "Token count: " << tokens->size() << endl;
		cout << "Tokens: " << endl;
		
		for (size_t i = 0; i < tokens->size(); ++i)
		{
			const token_base * tok = tokens->at(i);
			cout << endl << "TokenType: ";
			switch (tok->type())
			{
			case -1:
				{
					cout << "Error" << endl;
					cout << "\tMessage: " << 
						 reinterpret_cast<const token_error *>(tok)->message()
						 << endl;
					break;
				}
			case 0:
				{
					cout << "Type" << endl;
					cout << "\tFoamy type: " << 
						 reinterpret_cast<const token_type *>(tok)->ftype()
						 << endl;
					break;
				}
			case 1:
				{
					cout << "Reserved" << endl;
					cout << "\tWord: " <<
						 reinterpret_cast<const token_reserved *>(tok)->word()
						 << endl;
					break;
				}
			case 2:
				{
					cout << "Operator" << endl;
					cout << "\tOperator Type: " <<
						 reinterpret_cast<const token_operator *>(tok)->operator_type()
						 << endl;
					break;
				}
			case 3:
				{
					cout << "Symbol" << endl;
					cout << "\tSymbol Type: " <<
						 reinterpret_cast<const token_symbol *>(tok)->symbol()
						 << endl;
					break;
				}
			case 4:
				{
					cout << "Number" << endl;
					cout << "\tValue: " <<
						 reinterpret_cast<const token_number *>(tok)->number()
						 << endl;
					break;
				}
			case 5:
				{
					cout << "Name" << endl;
					cout << "\tValue: " <<
						 reinterpret_cast<const token_name *>(tok)->name()
						 << endl;
					break;
				}
			default:
				{
					cout << "Unidentified token type!" << endl;
					cout << "\tValue: " << tok->type() << endl;
					break;
				}
			}
		}
	}
	
	cout << endl << "[--File Scanned Successfuly--]" << endl << endl;
	
	
	// parse the tokens
	parser p ( s.tokens() );
	node_program * prog = p.begin_parse();
	node_function * func = dynamic_cast<node_function *>(prog->main());
	
	cout << endl << "[--File Parsed Successfuly--]" << endl << endl;
	
	
	// print out the abstract syntax tree
	if( verbose ){
		cout << "Abstract tree:" << endl;
		prog->printRec(cout,0);
		cout << endl << "Main Function:" << endl;
		func->printRec(cout,0);
	}
	
	cout << endl;
	
	
	// attempt to generate code from the tree
	codegen CG(std::string("DERP"));
	CG.set_tree(prog);
	cout << "Generated code:" << endl;
	CG.generate();
	
	return 0;
}
