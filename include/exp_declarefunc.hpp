// exp_declarefunc.hpp
// @author Chris Cornelius
// Created 11/07/2011
// An extension of exp_base to represent exp_declarefunc

#ifndef _EXP_DECLAREFUNC_HPP_
#define _EXP_DECLAREFUNC_HPP_

#include "exp_base.hpp"
#include "node_function.hpp"

class exp_declarefunc : public exp_base
{
protected:
  node_function* _func;
  
public:
  // constructors, destructors
  exp_declarefunc() : exp_base() {
    _exptype = DeclareFunc;
    _func = NULL;
  }

  exp_declarefunc(exp_base* next, node_function* f) : exp_base(next) {
    _exptype = DeclareFunc;
    _func = f;
  }

  exp_declarefunc(const exp_declarefunc& src) : exp_base(src) {
    _func = src._func;
  }
  
  ~exp_declarefunc() {
    if(_func) delete _func;
  }
  
  // accessors
  node_function* func() { return _func; }
  void set_func(node_function* f) { _func = f; }
  
    // functions for printing
  virtual std::ostream& printExpHead(std::ostream& os) {
    os << "exp_declarefunc " ;
    return os;
  }

    // recursively prints the members of an expression
  virtual std::ostream& printExpMembers(std::ostream& os, unsigned depth=0) {
    
    os<< endl;
    if(_func) _func->printRec(os, depth+1);
    
    return os;
  }
};

#endif // _EXP_DECLAREFUNC_HPP_

