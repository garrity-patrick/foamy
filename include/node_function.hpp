// node_function.hpp
// @author Chris Cornelius
// Created 11/05/2011

#ifndef _NODE_FUNCTION_HPP_
#define _NODE_FUNCTION_HPP_

#include "node_base.hpp"
#include "node_seqnode.hpp"
#include <list>
using std::list;
using std::size_t;

// represents a function in the abstract syntax tree
class node_function : public node_base
{
protected:
  node_base* _id;          // identifier for this function
  node_base* _ret;         // return type
  list <node_base*> _args; // arguments to the function
  node_seqnode* _body;     // pointer to first element in body of function
  
  void init() {
    _type = Function;
    _ret = NULL;
    _id = NULL;
  }
  
public:
  // constructors, destructors
  node_function(void) { init(); }
  node_function(node_base* id, node_base* ret, list<node_base*> args, node_base* body){
    init();  _id = id;  _ret = ret;  _args = args;  _body = body;
  }
  node_function(const node_function& src) { this->operator=(src); }
  node_function& operator=(const node_function& src)
  {
    init();
    _args = src._args;
    _ret = src.ret;
  }

  ~node_function(void)
  {
    for (size_t i = 0; i < _args.size(); i++) { delete _args[i]; }
    delete _id;  delete _ret;  delete _body;
  }
  
  // accessor methods
  node_base* ret() { return _ret; }
  void set_ret(const node_base* r) { _ret = r; }
  node_base* id() { return _id; }
  void set_id(const node_base* i) { _id = i; }
  node_seqnode* body() { return _body; }
  void set_body(const node_seqnode* b) { _body = b; }
  
  list<node_base*>& argsList(void) { return _args; }


  
};

#endif // _NODE_FUNCTION_HPP_
