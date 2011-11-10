// exp_base.hpp
// @author Chris Cornelius
// Created 11/07/2011
// Represents an expression for the foamy language
// Note that this class extends node_base

#ifndef _EXP_BASE_HPP_
#define _EXP_BASE_HPP_

#include "node_base.hpp"

// possible expression types
enum ExpType {
  Error = -1,
  Var = 0,
  Const = 1,
  Operator = 10,
  Declare = 11,
  Assign = 12,
  Call = 13
};



// extend this class to make various types of expressions
// remember that all expressions are nodes on the abstract syntax tree
class exp_base : public node_base
{
protected:
  ExpType _exptype;
  exp_base* _next;
  
public:
  // constructors, operators
  exp_base() {
    _exptype = Error;
    _next = NULL;
  }
  
  // construct from a pointer to next object
  exp_base(exp_base* next)
  {
    _exptype = Error;
    _next = next;
  }
  
  exp_base(const exp_base& src) {
    _exptype = src._exptype;
    _next = src._next;
  }
  virtual ~exp_base() {
    if(_next)
      delete _next;
  }
  
  // accessors
  ExpType exptype() { return _exptype; }
  void set_exptype(const ExpType w) { _exptype = w; }
  
  
}


#endif // _EXP_BASE_HPP_

