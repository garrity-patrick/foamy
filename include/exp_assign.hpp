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

  // TODO: parameter-based constructor
  // exp_XXX(exp_base* next, PARAMS) : exp_base(next) {

  exp_assign(const exp_assign& src) : exp_base(src) {
    _src = src._src;
    _dest = src._dest;
  }
  
  ~exp_assign() : ~exp_base() {
    if(src) delete src;
    if(dest) delete dest;
  }
  
  // accessors
  exp_base* src() { return _src; }
  void set_src(const exp_base* s) {
	if(_src) delete _src;
	_src = s;
	}
  exp_var* dest() { return _dest; }
  void set_dest(const exp_var* d) {
	if(_dest) delete _dest;
	_dest = d;
	}
  
};

#endif // _EXP_ASSIGN_HPP_

