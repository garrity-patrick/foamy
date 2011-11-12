// exp_base.hpp
// @author Chris Cornelius
// Created 11/07/2011
// Represents an expression for the foamy language
// Note that this class extends node_base

#ifndef _EXP_BASE_HPP_
#define _EXP_BASE_HPP_

#include "node_base.hpp"

// possible expression types
enum ExpType {
  ExpError = -1,
  Var = 0,
  Const = 1,
  Operator = 10,
  Declare = 11,
  DeclareFunc = 12,
  Assign = 13,
  Call = 14,
  Return = 15  
};



// extend this class to make various types of expressions
// remember that all expressions are nodes on the abstract syntax tree
class exp_base : public node_base
{
protected:
  ExpType _exptype;
  exp_base* _next;
  
public:
  // constructors, operators
  exp_base() {
    _exptype = ExpError;
    _next = NULL;
  }
  
  // construct from a pointer to next object
  exp_base(exp_base* next)
  {
    _exptype = ExpError;
    _next = next;
  }
  
  exp_base(const exp_base& src) {
    _exptype = src._exptype;
    _next = src._next;
  }
  virtual ~exp_base() {
    if(_next)
      delete _next;
  }
  
  // accessors
  ExpType exptype() { return _exptype; }
  void set_exptype(const ExpType w) { _exptype = w; }



  
  // prints just the name of this expression, any vital info
  virtual std::ostream& printExpHead(std::ostream& os) {
    os <<"exp_base UNIMPLEMENTED PRINT FUNCTION exptype=";
    switch(_exptype){
    case ExpError: os << "expression error"; break;
    case Var: os << "var"; break;
    case Const: os << "const"; break;
    case Operator: os << "operator"; break;
    case Declare: os << "declare"; break;
    case DeclareFunc: os << "declarefunc"; break;
    case Assign: os << "assign"; break;
    case Call: os << "call"; break;
    case Return: os << "return"; break;  
    default: os << "unfound type"; break;
    }
    return os;    
  }

  // recursively prints the members of an expression
  virtual std::ostream& printExpMembers(std::ostream& os, unsigned depth=0) {
    
    // os<< endl; // if the expression has members, start with a newline to separate them from the ExpHead
    // if this expression had any members, we'd print them here
    return os;
  }
  
  
  
  // node-based functions for printing
  std::ostream& printShort(std::ostream& os) {
    os<<"(";
    printExpHead(os);
    if(_next != NULL) os << " ..."; // indicate whether or not this expression is chained
    os << ")";
    return os;
  }
  std::ostream& printLong(std::ostream& os) {
    os<<"(";
    printExpHead(os);
    if(_next != NULL) os << " ..."; // indicate whether or not this expression is chained
    os << ")";

    return os;
  }
  std::ostream& printRec(std::ostream& os, unsigned depth=0) {
    print_spaces(os, depth);
    os<<"(";
    printExpHead(os);
    // indicate whether or not this expression is chained
    //    if(_next != NULL) os << " ...";

    printExpMembers(os, depth);

    if(_next != NULL)
      {
	os<<endl;
	_next->printRec(os, depth);
      }
    else {
      os << ")";
    }
    return os;
  }  
};


#endif // _EXP_BASE_HPP_

