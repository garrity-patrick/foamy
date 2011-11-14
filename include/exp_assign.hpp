// exp_assign.hpp
// @author Chris Cornelius
// Created 11/07/2011
// An extension of exp_base to represent exp_assign

#ifndef _EXP_ASSIGN_HPP_
#define _EXP_ASSIGN_HPP_

#include "exp_base.hpp"
#include "exp_var.hpp"

class exp_assign : public exp_base
{
protected:
  exp_base* _src;
  exp_var* _dest;
  
public:
  // constructors, destructors
  exp_assign() : exp_base() {
    _exptype = Assign;
    _src = _dest = NULL;
  }

  exp_assign(exp_base* next, exp_base* src, exp_var* dest) : exp_base(next) {
    _exptype = Assign;
    _src = src; _dest = dest;
  }

  exp_assign(const exp_assign& src) : exp_base(src) {
    _src = src._src;
    _dest = src._dest;
  }
  
  ~exp_assign() {
    if(_src) delete _src;
    if(_dest) delete _dest;
  }
  
  // accessors
  exp_base* src() { return _src; }
  void set_src(exp_base* s) {
	if(_src) delete _src;
	_src = s;
	}
  exp_var* dest() { return _dest; }
  void set_dest(exp_var* d) {
	if(_dest) delete _dest;
	_dest = d;
	}



  // functions for printing
  virtual std::ostream& printExpHead(std::ostream& os) {
    os << "exp_assign";
    return os;
  }

  virtual std::ostream& printExpMembers(std::ostream& os, unsigned depth=0) {

    os << std::endl;

    if(_dest) _dest->printRec(os, depth+1);
    os << " = ";
    os << std::endl;
    if(_src) _src->printRec(os, depth+1);

    return os;    
  }
  
  
};

#endif // _EXP_ASSIGN_HPP_

