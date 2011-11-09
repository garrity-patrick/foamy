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
  ftype_t _ftype;
  fident_t _fident;

public:
  // constructors, destructors
  exp_var() : exp_base() {
    _exptype = Var;
  }
  
  exp_XXX(exp_base* next, ftype_t ft, fident_t fi) : exp_base(next) {
    _exptype = Var;
    _ftype = ft;  _fident = fi;
  }

  exp_var(const exp_var& src) : exp_base(src) {
    _ftype = src._ftype;
    _fident = src._fident;
  }
  
  ~exp_var() : ~exp_base() { }
  
  // accessors
  ftype_t ftype() { return _ftype; }
  fident_t fident() { return _fident; }
  
  void set_ftype(const ftype_t ft) { _ftype = ft; }
  void set_fident(const fident_t fi) { _fident = fi; }
  
};

#endif // _EXP_VAR_HPP_

