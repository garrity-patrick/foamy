#include "scanner.hpp"
#include "token_error.hpp"
#include "token_type.hpp"
#include "token_reserved.hpp"
#include "token_operator.hpp"
#include "token_symbol.hpp"
#include "token_number.hpp"
#include "token_name.hpp"

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
}
