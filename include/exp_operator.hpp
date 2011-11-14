// exp_operator.hpp
// @author Chris Cornelius
// Created 11/07/2011
// An extension of exp_base to represent exp_operator - the set of binary operators

#ifndef _EXP_OPERATOR_HPP_
#define _EXP_OPERATOR_HPP_

#include "exp_base.hpp"
//Temporary fix to get around multiple enum declaration for OperatorType
#include "token_operator.hpp"


class exp_operator : public exp_base
{
protected:
  OperatorType _optype;
  exp_base* _lexp;
  exp_base* _rexp;

public:
  // constructors, destructors
  exp_operator() : exp_base() {
    _exptype = ExpOperator;
    _optype = ErrorOperator;
    _lexp = _rexp = NULL;
  }

  exp_operator(exp_base* next, OperatorType op, exp_base* lexp, exp_base* rexp) : exp_base(next) {
    _exptype = ExpOperator;
    _optype = op;  _lexp = lexp;  _rexp = rexp;
  }
  
  exp_operator(const exp_operator& src) : exp_base(src) {
    _optype = src._optype;
    _lexp = src._lexp;
    _rexp = src._rexp;
  }
  
  ~exp_operator() {
    if(_lexp) delete _lexp;
    if(_rexp) delete _rexp;
  }
  
  // accessors
  OperatorType optype() { return _optype; }
  void set_optype(const OperatorType o) { _optype = o; }

  exp_base* lexp() { return _lexp; }
  exp_base* rexp() { return _rexp; }

  void set_lexp(exp_base* l) {
    if(_lexp) delete _lexp;
    _lexp = l;
  }
  
  void set_rexp(exp_base* r) {
    if(_rexp) delete _rexp;
    _rexp = r;
  }


  // functions for printing
  virtual std::ostream& printExpHead(std::ostream& os) {
    os << "exp_operator ";
    switch(_optype){
    case ErrorOperator: os << "Operator Type Error"; break;
    case OpEquals: os << "=="; break;
    case Plus: os << "+"; break;
    case Minus: os << "-"; break;
    case Greater: os << ">"; break;
    case Less: os << "<"; break;
    default: os << "Unknown optype"; break;
    }
    return os;
  }

  virtual std::ostream& printExpMembers(std::ostream& os, unsigned depth=0) {

    os << endl;

    if(_lexp) _lexp->printRec(os,depth+1);
    if(_rexp) os << endl;
    if(_rexp) _rexp->printRec(os, depth+1);
    
    return os;    
  }
  
};

#endif // _EXP_OPERATOR_HPP_

