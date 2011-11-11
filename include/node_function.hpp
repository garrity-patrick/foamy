// node_function.hpp
// @author Chris Cornelius
// Created 11/05/2011

#ifndef _NODE_FUNCTION_HPP_
#define _NODE_FUNCTION_HPP_

#include "node_base.hpp"
#include "exp_base.hpp"
#include "ftype_t.hpp"
#include "fident_t.hpp"
#include "util.hpp"

#include <vector>
using std::vector;
using std::size_t;


// struct to hold arguments to a function
struct func_arg {
  ftype_t type;
  fident_t name;
  
  func_arg() : name() { type = Void; }
  func_arg(ftype_t t, fident_t n) : name(n) { type = t; }
};



// represents a function in the abstract syntax tree
class node_function : public node_base
{
protected:
  fident_t _name;          // identifier for this function
  ftype_t _rettype;         // return type
  vector <func_arg> _args; // arguments to the function
  exp_base* _body;     // pointer to first element in body of function
  
  void init() {
    _type = Function;
    _rettype = Void;
    _body = NULL;
  }
  
public:
  // constructors, destructors
  node_function(void) { init(); }
  node_function(fident_t name, ftype_t ret, vector<func_arg> args, exp_base* body){
    init();  _name = name;  _rettype = ret;  _args = args;  _body = body;
  }
  node_function(const node_function& src) { this->operator=(src); }
  node_function& operator=(const node_function& src)
  {
    init();
    _name = src._name;
    _args = src._args;
    _rettype = src._rettype;
    _body = src._body;
  }

  ~node_function(void)
  {
    //for (size_t i = 0; i < _args.size(); i++) { delete _args[i]; }
    delete _body;
  }
  
  // accessor methods
  ftype_t rettype() { return _rettype; }
  void set_rettype(const ftype_t t) { _rettype = t; }
  fident_t name() { return _name; }
  void set_name(const fident_t i) { _name = i; }
  exp_base* body() { return _body; }
  void set_body(exp_base* b) { _body = b; }
  
  vector<func_arg> args(void) { return _args; }
  void set_args(const vector<func_arg> a) { _args = a; }
  
  // functions for printing
  virtual std::ostream& printShort(std::ostream& os) {
    os << "(function: " << _name << " ";
    os << "type: " << _rettype << " ";
    os << ")";
    return os;
  }
  virtual std::ostream& printLong(std::ostream& os) {
    os << "(function: " << _name << " ";
    os << "type: " << _rettype << " ";
    os << "args: ";
    for(unsigned i = 0; i<_args.size(); ++i) os<<_args[i].name << " "; 
    os << ")";
    return os;
  }
  virtual std::ostream& printRec(std::ostream& os, unsigned depth=0) {
    print_spaces(os, depth);
    os << "(function: " << _name << " ";
    os << "type: " << _rettype << " ";
    os << "args: ";
    for(unsigned i = 0; i<_args.size(); ++i) os<<_args[i].name << " ";
    os << endl;

    // recur on _body
    if(_body) _body->printRec(os, depth+1);

    os << endl;
    print_spaces(os, depth);    os << ")";
    return os;
  }
  
  
  
};

#endif // _NODE_FUNCTION_HPP_
