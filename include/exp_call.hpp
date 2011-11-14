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

  exp_call(exp_base* next, fident_t f, exp_base* args) : exp_base(next) {
    _exptype = Call;
    _args = args;  _fident = f;
  }

  exp_call(const exp_call& src) : exp_base(src) {
    _fident = src._fident;
    _args = src._args;  // TODO: should this be a shallow or deep copy?
  }
  
  ~exp_call() {
    if(_args) delete _args;
  }
  
  // accessors
  fident_t fident() { return _fident; }
  void set_fident(fident_t f) { _fident = f; }
  exp_base* args() { return _args; }
  void set_args(exp_base* a) {
	if(_args) delete _args;
	_args = a;
	}

  // prints just the name of this expression, any vital info
  virtual std::ostream& printExpHead(std::ostream& os) {
    os <<"exp_call " << fident();
    return os;    
  }

  // recursively prints the members of an expression
  virtual std::ostream& printExpMembers(std::ostream& os, unsigned depth=0) {
    
    os<< std::endl;
    print_spaces(os, depth+1); os << "Call: " << fident() << " ";
    if(_args) os << std::endl;
    if(_args) _args->printRec(os, depth+1);
    
    return os;
  }


};

#endif // _EXP_CALL_HPP_

