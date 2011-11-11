// exp_const.hpp
// @author Chris Cornelius
// Created 11/07/2011
// An extension of exp_base to represent exp_const

#ifndef _EXP_CONST_HPP_
#define _EXP_CONST_HPP_

#include "exp_base.hpp"
#include "ftype_t.hpp"

class exp_const : public exp_base
{
protected:
  ftype_t _ftype;
  int _val;
  
public:
  // constructors, destructors
  exp_const() : exp_base() {
    _exptype = Const;
    _ftype = Void;
    _val = 0;
  }

  exp_const(exp_base* next, ftype_t ft, int val) : exp_base(next) {
    _exptype = Const;
    _ftype = ft;
    _val = val;
  }
  
  exp_const(const exp_const& src) : exp_base(src) {
    _exptype = Const;
    _ftype = src._ftype;
    _val = src._val;
  }
  
  ~exp_const() : ~exp_base() { }
  
  // accessors
  ftype_t ftype() { return _ftype; }
  void set_ftype(const ftype_t& f) { _ftype = f; }
  int val() { return _val; }
  void set_val(const int v) { _val = v; }

};

#endif // _EXP_CONST_HPP_

