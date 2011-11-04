#ifndef _TOKEN_RESERVED_HPP_
#define _TOKEN_RESERVED_HPP_

#include "token_base.hpp"

enum ReservedWord
{
	ErrorReserved=-1,Return=0
};

static const unsigned int RESERVED_SIZE = 1;
static const char * RESERVED[] =
{
	"return"
};

class token_reserved : public token_base
{
private:
	ReservedWord _word;

public:
	token_reserved(void) : _word(ErrorReserved) { _type = Reserved; }
	
	token_reserved(ReservedWord r) : _word(r) { _type = Reserved; }
	
	token_reserved(const token_reserved & other) :
		_word(other._word)
	{
		_type = Reserved;
	}
	
	virtual ~token_reserved(void) { }
	
	token_reserved & operator=(const token_reserved & other)
	{
		_word = other._word;
		return *this;
	}
	
	ReservedWord word(void) const { return _word; }
	
	void set_word(ReservedWord r) { _word = r; }
};

#endif
