// ftype_t.hpp
// @author Chris Cornelius
// Created 11/07/2011
// An enum representing possible types in the foamy language

// An accepted way to refer to foamy language types is ftype

#ifndef _FTYPE_T_HPP_
#define _FTYPE_T_HPP_

#include <cstring>

enum ftype_t {
  ErrorType=-1,
  Void = 0,
  Int=1
};

const char* FTYPE[] = {
"void",
"int"
};

const unsigned int FTYPE_SIZE = 2;

/* TODO: reinstate if needed
static const char* ftype_name(const ftype_t f)
{
  return FTYPE[(int)f];
}

static ftype_t ftype(const char* str)
{
  for(unsigned i = 0; i < FTYPE_SIZE; i++)
    {
      if(strcmp(FTYPE[i], str) == 0) {
	 return (ftype_t) i;
      }
    }
  ftype_t ret = ErrorType;
  return ret;
}
*/

#endif // _FTYPE_T_HPP_

