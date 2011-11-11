// exp_declare.hpp
// @author Chris Cornelius
// Created 11/07/2011
// An extension of exp_base to represent exp_declare

#ifndef _EXP_DECLARE_HPP_
#define _EXP_DECLARE_HPP_

#include "exp_base.hpp"
#include "fident_t.hpp"
#include "ftype_t.hpp"

class exp_declare : public exp_base
{
protected:
  ftype_t _type;
  fident_t _name;
  
public:
  // constructors, destructors
  exp_declare() : exp_base() {
    _exptype = Declare;
  }

  exp_declare(exp_base* next, ftype_t type, fident_t name) : exp_base(next) {
    _exptype = Declare;
    _type = type;
    _name = name;
  }
  
  exp_declare(ftype_t type, fident_t name) : exp_base() {
    _exptype = Declare;
    _type = type;
    _name = name;
  }
  
  exp_declare(const exp_declare& src) : exp_base(src) {
    _type = src._type;
    _name = src._name;
  }
  
  ~exp_declare() { }
  
  // accessors
  ftype_t type() { return _type; }
  void set_type(const ftype_t type) { _type = type; }
  fident_t name() { return _name; }
  void set_name(const fident_t name) { _name = name; }
  
  
};

#endif // _EXP_DECLARE_HPP_

