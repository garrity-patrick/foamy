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
  // TODO: implement _val field
  
public:
  // constructors, destructors
  exp_const() : exp_base() {
    _exptype = Const;
    _ftype = Void;
  }

  exp_const(exp_base* next, ftype_t ft) : exp_base(next) {
    _exptype = Const;
    _ftype = ft;
  }
  
  exp_const(const exp_const& src) : exp_base(src) {
    _exptype = Const;
    _ftype = src._ftype;
  }
  
  ~exp_const() : ~exp_base() { }
  
  // accessors
  ftype_t ftype() { return _ftype; }
  void set_ftype(const ftype_t& f) { _ftype = f; }
  
};

#endif // _EXP_CONST_HPP_

