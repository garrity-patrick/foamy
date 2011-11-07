// exp_declare.hpp
// @author Chris Cornelius
// Created 11/07/2011
// An extension of exp_base to represent exp_declare

#ifndef _EXP_DECLARE_HPP_
#define _EXP_DECLARE_HPP_

#include "exp_base.hpp"
#include "exp_var.hpp"

class exp_declare : public exp_base
{
protected:
  exp_var* _var;
  
public:
  // constructors, destructors
  exp_declare() : exp_base() {
    _exptype = Declare;
    _var = NULL;
  }

  // TODO: parameter-based constructor
  // exp_XXX(exp_base* next, PARAMS) : exp_base(next) {
  
  exp_declare(exp_var* v) : exp_base() {
    _exptype = Declare;
    _var = v;
  }
  
  exp_declare(const exp_declare& src) : exp_base(src) {
    _var = src._var;
  }
  
  ~exp_declare() : ~exp_base() { }
  
  // accessors
  exp_var* var() { return _var; }
  void set_var(const exp_var* v) {
    if(_var) delete _var;
    _var = v;
  }
  
};

#endif // _EXP_DECLARE_HPP_

