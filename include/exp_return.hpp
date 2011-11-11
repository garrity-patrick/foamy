// exp_return.hpp
// @author Chris Cornelius
// Created 11/07/2011
// An extension of exp_base to represent exp_return

#ifndef _EXP_RETURN_HPP_
#define _EXP_RETURN_HPP_

#include "exp_base.hpp"

class exp_return : public exp_base
{
protected:
  exp_base* _arg;
  
public:
  // constructors, destructors
  exp_return() : exp_base() {
    _exptype = Return;
    _arg = 0;
  }

  exp_return(exp_base* next, exp_base* arg) : exp_base(next) {
    _exptype = Return;
    _arg = arg;
  }

  exp_return(const exp_return& src) : exp_base(src) {
    _arg = src._arg;
  }
  
  ~exp_return() : ~exp_base() {
    if(_arg) delete _arg;
  }
  
  // accessors
  exp_base* arg() { return _arg; }
  void set_arg(const exp_base* a) {
    if(_arg) delete _arg;
    _arg = a;
  }
  
};

#endif // _EXP_RETURN_HPP_

