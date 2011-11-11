// util.hpp
// @author Chris Cornelius
// Created 11/11/2011
// Utility functions, mostly for printing things and the like

#ifndef _UTIL_HPP_
#define _UTIL_HPP_

#include <ostream>
using std::ostream;
using std::endl;
#include "ftype_t.hpp"

// print an ftype_t as a string
inline ostream& operator<<(ostream& os, const ftype_t type)
{
  switch(type)
    {
    case ErrorType: os << "ErrorType"; break;
    case Void: os << "Void"; break;
    case Int: os <<"Int"; break;
    default: os <<"Unknown Type"; break;
    }

  return os;
}

// print an fident_t as a string
inline ostream& operator<<(ostream& os, const fident_t ident)
{
  os << ident.c_str();
  return os;
}


#endif // _UTIL_HPP_
