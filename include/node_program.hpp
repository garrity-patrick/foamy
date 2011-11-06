// node_program.hpp
// @author Chris Cornelius
// Created 11/05/2011

#ifndef _NODE_PROGRAM_HPP_
#define _NODE_PROGRAM_HPP_

#include "node_base.hpp"
#include <list>
using std::list;
using std::size_t;

// represents a program in the abstract syntax tree
class node_program : public node_base
{
protected:
  list <node_base*> _globals;
  node_base* mainFunction;
  
  void init() {
    mainFunction = NULL;
    _type = Program;
  }
  
public:
  // constructors, destructors
  node_program(void) { init(); }
  node_program(void) { init(); }
  node_program(const node_program& src) { this->operator=(src); }
  node_program& operator=(const node_program& src)
  {
    init();
    mainFunction = src.mainFunction;
    globalFunctions = src.globalFunctions;
  }
  ~node_program(void)
  {
    for (size_t i = 0; i < _globals.size(); i++) { delete _globals[i]; }
    delete mainFunction;
  }
  
  // accessor methods
  list<node_base*>& globalsList(void) { return _globals; }
  node_base* main() { return mainFunction; }
  void set_main(const node_base* m) { mainFunction = m;}
  
};

#endif // _NODE_PROGRAM_HPP_
