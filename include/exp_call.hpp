// exp_call.hpp
// @author Chris Cornelius
// Created 11/07/2011
// An extension of exp_base to represent exp_call

#ifndef _EXP_CALL_HPP_
#define _EXP_CALL_HPP_

#include "exp_base.hpp"
#include "fident_t.hpp"

class exp_call : public exp_base
{
protected:
  fident_t _fident;
  exp_base* _args;
  
public:
  // constructors, destructors
  exp_call() : exp_base() {
    _exptype = Call;
    _args = NULL;
  }

  // TODO: parameter-based constructor
  // exp_XXX(exp_base* next, PARAMS) : exp_base(next) {
  
  exp_call(const exp_call& src) : exp_base(src) {
    _fident = src._fident;
    _args = src._args;  // TODO: should this be a shallow or deep copy?
  }
  
  ~exp_call() : ~exp_base() {
    if(_args) delete _args;
  }
  
  // accessors
  fident_t fident() { return _fident; }
  void set_fident(const fident_t f) { _fident = f; }
  exp_base* args() { return _args; }
  void set_args(const exp_base* a) {
	if(_args) delete _args;
	_args = a;
	}

};

#endif // _EXP_CALL_HPP_

