// exp_var.hpp
// @author Chris Cornelius
// Created 11/07/2011
// An extension of exp_base to represent exp_var

#ifndef _EXP_VAR_HPP_
#define _EXP_VAR_HPP_

#include "exp_base.hpp"
#include "ftype_t.hpp"

class exp_var : public exp_base
{
protected:
  fident_t _name;

public:
  // constructors, destructors
  exp_var() : exp_base() {
    _exptype = Var;
  }
  
  exp_var(exp_base* next, fident_t n) : exp_base(next) {
    _exptype = Var;
    _name = n;
  }

  exp_var(const exp_var& src) : exp_base(src) {
    _name = src._name;
  }
  
  ~exp_var() { }
  
  // accessors
  fident_t name() { return _name; }
  void set_name(const fident_t n) { _name = n; }
  
  
  
  

  // functions for printing
  virtual std::ostream& printExpHead(std::ostream& os) {
    os << "exp_var " << _name;
    return os;
  }


};

#endif // _EXP_VAR_HPP_

