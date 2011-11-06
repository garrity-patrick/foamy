// node_seqnode.hpp
// @author Chris Cornelius
// Created 11/06/2011

#ifndef _NODE_SEQNODE_HPP_
#define _NODE_SEQNODE_HPP_

#include "node_base.hpp"
#include <list>
using std::list;
using std::size_t;

// represents a sequence node in the abstract syntax tree
class node_seqnode : public node_base
{
protected:
  node_seqnode* _next;   // the next item in the sequence
  
  void init() {
    _next = NULL;
    _type = Sequence;
  }
  
public:
  // constructors, destructors
  node_seqnode(void) { init(); }\
  node_seqnode(const node_seqnode& src) { this->operator=(src); }
  node_seqnode& operator=(const node_seqnode& src)
  {
    init();
    next = src._next;
  }
  ~node_seqnode(void)
  {
    delete next;
  }
  
  // accessor methods
  node_seqnode* next() { return _next; }
  void set_next(const node_seqnode* n) { _next = n;}
  
};

#endif // _NODE_SEQNODE_HPP_
