// node_program.hpp
// @author Chris Cornelius
// Created 11/05/2011

#ifndef _NODE_PROGRAM_HPP_
#define _NODE_PROGRAM_HPP_

#include "node_base.hpp"
#include <list>
using std::list;

// represents a program in the abstract syntax tree
class node_program : public node_base
{
protected:
  list <node_base*> globalFunctions;
  node_base* mainFunction;
  
  void init() {
    mainFunction = NULL;
    _type = Program;
  }
  
public:
  // constructors, destructors
  node_program(void) { init(); }
  node_program(void) { init(); }
  node_program(const node_program& src)
  {
    init();
    mainFunction = src.mainFunction;
    globalFunctions = src.globalFunctions;
  }
  ~node_program(void) { }
  
  // accessor methods
  
  
};

#endif // _NODE_PROGRAM_HPP_
