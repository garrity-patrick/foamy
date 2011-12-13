// node_program.hpp
// @author Chris Cornelius
// Created 11/05/2011

#ifndef _NODE_PROGRAM_HPP_
#define _NODE_PROGRAM_HPP_

#include "node_base.hpp"
#include <vector>
using std::vector;
using std::size_t;

// represents a program in the abstract syntax tree
class node_program : public node_base
{
protected:
  vector <node_base*> _globals;
  node_base* mainFunction;
  
  void init() {
    mainFunction = NULL;
    _type = Program;
  }
  
public:
  // constructors, destructors
  node_program(void) { init(); }
  node_program(const node_program& src) { this->operator=(src); }
  node_program& operator=(const node_program& src)
  {
    init();
    mainFunction = src.mainFunction;
    _globals = src._globals;
    return *this;
  }
  ~node_program(void)
  {
    for (size_t i = 0; i < _globals.size(); i++) { delete _globals[i]; }
    delete mainFunction;
  }
  
  // accessor methods
  vector<node_base*>& globalsVector(void) { return _globals; }
  node_base* main() { return mainFunction; }
  void set_main(node_base* m) { mainFunction = m; }

  // functions for printing
  virtual std::ostream& printShort(std::ostream& os) {
    os << "(node_program)";
    return os;
  }
  virtual std::ostream& printLong(std::ostream& os) {
    os << "(node_program)";
    return os;
  }
  virtual std::ostream& printRec(std::ostream& os, unsigned depth=0) {
    print_spaces(os, depth);
    os << "(node_program" << endl;
    print_spaces(os, depth+1);
    os << "main function: " << endl;
    print_spaces(os, depth+2);
    if(mainFunction) mainFunction->printShort(os);
    os << endl;
    for(size_t i = 0; i < _globals.size(); i++)
      {
	print_spaces(os, depth+1);
	os << "globals["<<i<<"] : "<<endl;;
	
	if(_globals[i]) _globals[i]->printRec(os, depth+2);
      }
    os << endl;
    print_spaces(os, depth);
    os << ")";
    return os;
  }

  
};

#endif // _NODE_PROGRAM_HPP_
