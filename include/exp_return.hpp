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
    _exptype = ExpReturn;
    _arg = 0;
  }

  exp_return(exp_base* next, exp_base* arg) : exp_base(next) {
    _exptype = ExpReturn;
    _arg = arg;
  }

  exp_return(const exp_return& src) : exp_base(src) {
    _arg = src._arg;
  }
  
  ~exp_return() {
    if(_arg) delete _arg;
  }
  
  // accessors
  exp_base* arg() { return _arg; }
  void set_arg(exp_base* a) {
    if(_arg) delete _arg;
    _arg = a;
  }
  

  // overriding function for printing
  virtual std::ostream& printExpHead(std::ostream& os) {
    os << "exp_return";
    return os;
  }

  // overriding function for printing
  virtual std::ostream& printExpMembers(std::ostream& os, unsigned depth) {
    os << endl;
    if(_arg) _arg->printRec(os, depth+1);
    return os;
  }


};

#endif // _EXP_RETURN_HPP_

