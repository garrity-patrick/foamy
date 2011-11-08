// ftype_t.hpp
// @author Chris Cornelius
// Created 11/07/2011
// An enum representing possible types in the foamy language

// An accepted way to refer to foamy language types is ftype

#ifndef _FTYPE_T_HPP_
#define _FTYPE_T_HPP_

enum ftype_t {
  ErrorType=-1,
  Void = 0,
  Int = 1
};

static const size_t FTYPE_SIZE = 2;
static const char* FTYPE[] = 
  {
    "void",
    "int"
  };



#endif // _FTYPE_T_HPP_

