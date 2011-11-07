// exp_operator.hpp
// @author Chris Cornelius
// Created 11/07/2011
// An extension of exp_base to represent exp_operator - the set of binary operators

#ifndef _EXP_OPERATOR_HPP_
#define _EXP_OPERATOR_HPP_

#include "exp_base.hpp"

enum OperatorType {
  Error = -1,
  EqualsEquals = 0,
  Plus = 1,
  Minus = 2,
  Greater = 3,
  Less = 4
}

class exp_operator : public exp_base
{
protected:
  OperatorType _optype;
  exp_base* _lexp;
  exp_base* _rexp;

public:
  // constructors, destructors
  exp_operator() : exp_base() {
    _exptype = Operator;
    _optype = Error;
    _lexp = _rexp = NULL;
  }

  // TODO: parameter-based constructor
  // exp_XXX(exp_base* next, PARAMS) : exp_base(next) {
  
  exp_operator(const exp_operator& src) : exp_base(src) {
    _optype = src._optype;
    _lexp = src._lexp;
    _rexp = src._rexp;
  }
  
  ~exp_operator() : ~exp_base() {
    if(_lexp) delete _lexp;
    if(_rexp) delete _rexp;
  }
  
  // accessors
  OperatorType optype() { return _optype; }
  void set_optype(const OperatorType o) { _optype = o; }

  exp_base* lexp() { return _lexp; }
  exp_base* rexp() { return _rexp; }

  void set_lexp(const exp_base* l) {
    if(_lexp) delete _lexp;
    _lexp = l;
  }
  
  void set_rexp(const exp_base* r) {
    if(_rexp) delete _rexp;
    _rexp = r;
  }
  
};

#endif // _EXP_OPERATOR_HPP_

