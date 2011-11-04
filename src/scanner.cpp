#include "scanner.hpp"
#include "token_error.hpp"
#include "token_type.hpp"
#include "token_reserved.hpp"
#include "token_operator.hpp"
#include "token_symbol.hpp"
#include "token_number.hpp"
#include "token_name.hpp"
#include <sstream>

void scanner::clear(void)
{
	for (size_t i = 0; i < _tokens.size(); ++i)
	{
		token_base * t = _tokens[i];
		delete t;
	}
	
	_tokens.clear();
}

void scanner::scan(void)
{
	using std::string;
	using std::vector;
	using std::stringstream;
	
	// Clear the list of tokens, and make sure we have code to tokenize.
	_tokens.clear();
	if (_code.size() == 0) return;
	
	// The character that we are currently looking at:
	char look = '\0';
	
	// The current position in the code.
	size_t pos = 0;
	
	// The end of the code.
	size_t end = _code.size();
	
	// The scanning loop -- continue until all code has been tokenized.
	while (pos < end)
	{
		// Skip any whitespace. We don't care about it.
		pos = skip_whitespace(pos);
		if (pos >= end) break;
		
		// Get the current character:
		look = _code[pos];
		
		// Determine what type of token it is:
		if (is_alphabetic(look))
		{
			// Anything that begins with a letter is a name of some sort. This
			// could be a type, a reserved word, or a locally defined variable.
			string s;
			s.push_back(look);
			pos++;
			
			while (pos < end)
			{
				look = _code[pos];
				if (is_name(look))
				{
					s.push_back(look);
					pos++;
				}
				else
				{
					break;
				}
			}
			
			// Now the string s has been created, and we need to check what it
			// is exactly. We handle determining whether it is a type, reserved,
			// or user-defined variable here.
			
			// Step 1: Check s against reserved words.
			int word = -1;
			for (size_t i = 0; i < RESERVED_SIZE; ++i)
			{
				if (s.compare(RESERVED[i]) == 0)
				{
					word = (int)i;
					break;
				}
			}
			
			if (word >= 0)
			{
				token_reserved * tok = new token_reserved();
				tok->set_word((ReservedWord)word);
				_tokens.push_back(tok);
				continue;
			}
			
			// Step 2: Check s against datatypes (special class of reserved word).
			int datatype = -1;
			for (size_t i = 0; i < DATATYPE_SIZE; ++i)
			{
				if (s.compare(DATATYPE[i]) == 0)
				{
					datatype = (int)i;
					break;
				}
			}
			
			if (datatype >= 0)
			{
				token_type * tok = new token_type();
				tok->set_datatype((Datatype)datatype);
				_tokens.push_back(tok);
				continue;
			}
			
			// The token is not a reserved word or datatype, so it must be a
			// standard name.
			token_name * tok = new token_name();
			tok->set_name(s);
			_tokens.push_back(tok);
			continue;
		}
		else if (is_numeric(look))
		{
			// Anything that begins with a number is... a number!
			string s;
			while (pos < end)
			{
				look = _code[pos];
				if (is_numeric(look)) { s.push_back(look); ++pos; } else break;
			}
			
			// Convert our string into a number. This is guaranteed to work,
			// since we are verifying that only numeric characters are used.
			int num_val = 0;
			stringstream ss(s);
			ss >> num_val;
			
			// Add the token to the list.
			token_number * tok = new token_number(num_val);
			_tokens.push_back(tok);
		}
		else
		{
			switch (look)
			{
			case '(':
				{
					// Left parenthesis
					token_symbol * tok = new token_symbol();
					tok->set_symbol(LParen);
					_tokens.push_back(tok);
					break;
				}
			case ')':
				{
					// Right parenthesis
					token_symbol * tok = new token_symbol();
					tok->set_symbol(RParen);
					_tokens.push_back(tok);
					break;
				}
			case '{':
				{
					// Left brace
					token_symbol * tok = new token_symbol();
					tok->set_symbol(LBrace);
					_tokens.push_back(tok);
					break;
				}
			case '}':
				{
					// Right brace
					token_symbol * tok = new token_symbol();
					tok->set_symbol(RBrace);
					_tokens.push_back(tok);
					break;
				}
			case ';':
				{
					// Semi-colon operator
					token_symbol * tok = new token_symbol();
					tok->set_symbol(Semicolon);
					_tokens.push_back(tok);
					break;
				}
			case ':':
				{
					// Colon operator
					token_symbol * tok = new token_symbol();
					tok->set_symbol(Colon);
					_tokens.push_back(tok);
					break;
				}
			case '=':
				{
					// Assignment operator
					token_operator * tok = new token_operator();
					tok->set_operator_type(Equals);
					_tokens.push_back(tok);
					break;
				}
			case '+':
				{
					// Plus operator
					token_operator * tok = new token_operator();
					tok->set_operator_type(Plus);
					_tokens.push_back(tok);
					break;
				}
			case '#':
				{
					// Comment: discard the rest of the line.
					while (pos < end && look != '\n') look = _code[pos++];
					break;
				}
			default:
				{
					// Unidentified symbol / token.
					token_error * tok = new token_error();
					tok->set_message(string("Unidentified symbol"));
					_tokens.push_back(tok);
					break;
				}
			}
			
			// Increment our position:
			++pos;
		}
	}
}

bool scanner::is_alphabetic(char c) const
{
	if ((c >= 'A' && c <= 'Z') ||
		(c >= 'a' && c <= 'z'))
	return true;
	return false;
}

bool scanner::is_numeric(char c) const
{
	if (c >= '0' && c <= '9') return true; return false;
}

bool scanner::is_alphanumeric(char c) const
{
	return (is_alphabetic(c) || is_numeric(c));
}

bool scanner::is_name(char c) const
{
	return (is_alphanumeric(c) || c == '_');
}

bool scanner::is_whitespace(char c) const
{
	if (c == ' ' ||
		c == '\n' ||
		c == '\t')
	return true;
	return false;
}

size_t scanner::skip_whitespace(size_t position)
{
	while (position < _code.size() && is_whitespace(_code[position])) position++;
	return position;
}
