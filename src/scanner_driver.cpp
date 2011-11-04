#include "scanner.hpp"
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
	cout << "scanner [file]" << endl;
	cout << "Test the foamy scanner by generating and displaying a list of "
		 << "tokens." << endl;
}

int main(int argc, char ** argv)
{
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
	}
	
	// Create the code string, and free the memory used by our char array.
	string code(raw_code);
	delete [] raw_code;
	
	cout << "=== CODE LISTING ===" << endl;
	cout << code << endl;
	cout << "====================" << endl << endl;
	
	// Create and initialize a scanner, then scan the code.
	scanner s;
	s.set_code(code);
	s.scan();
	
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
				cout << "\tDatatype: " << 
					 reinterpret_cast<const token_type *>(tok)->datatype()
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
	
	return 0;
}
