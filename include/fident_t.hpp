// fident_t.hpp
// @author Chris Cornelius
// Created 11/07/2011
// A class representing identifiers in the foamy language

#ifndef _FIDENT_T_HPP_
#define _FIDENT_T_HPP_

#include <ostream>
using std::ostream;
#include <string>
using std::string;

// 11/10/11 - General use ... only need bigger class if needs expand
typedef string fident_t;

/* Commented out 11/10/11 because full class functionality is not needed
class fident_t
{
protected:
  const static string DEFAULT_NAME = "UNNAMED_IDENT";

  string _name;
  
public:
  // constructors, destructors
  fident_t() : _name(DEFAULT_NAME) { }
  fident_t(const string n) { _name = n; }
  fident_t(const fident_t& src) { this->operator=(src); }
  
  // operators
  fident_t& operator=(const fident_t& src)
  {
    _name = src._name;
    
    return *this;
  }
  
  bool operator==(const fident_t& other) const
  {
    // return false if any relavent comparisons don't match
    if(_name.compare(other._name) != 0) return false;

    // assert: all comparisons match
    return true;
  }
  
  // accessors
  string name() { return _name; }
  void set_name(const string n) { _name = n; }
  
};

// define an operator<< to help with printing of these objects
ostream& operator<<(ostream& os, fident_t& f)
{
  os << _name;
  return os;
}*/


#endif // _FIDENT_T_HPP_

