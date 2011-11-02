#ifndef _SCANNER_HPP_
#define _SCANNER_HPP_

#include "token_base.hpp"
#include <vector>
#include <string>

class scanner
{
private:
	std::string _code;
	std::vector<token_base *> _tokens;

public:
	scanner(void) { }
	~scanner(void) { clear(); }
	
	const std::string & code(void) const { return _code; }
	void set_code(const std::string & code) { _code = code; }
	
	const std::vector<token_base *> * tokens(void) const { return &_tokens; }
	
	void clear(void);
	void scan(void);

private:
	bool is_alphabetic(char c) const;
	bool is_numeric(char c) const;
	bool is_alphanumeric(char c) const;
	bool is_name(char c) const;
	bool is_whitespace(char c) const;
	size_t skip_whitespace(size_t position);
};

#endif
