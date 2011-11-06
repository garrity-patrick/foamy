// node_base.hpp
// @author Chris Cornelius
// Created 11/05/2011
// basic node class for a 

#ifndef _NODE_BASE_HPP_
#define _NODE_BASE_HPP_

// possible types for the node object
enum NodeType {
  Error = -1,
  Program = 0,
  Function = 1,
  Sequence = 10,
  Expression = 20
};


// extend this class to create possible nodes for the abstract syntax tree
class node_base
{
protected:
  NodeType _type;
  
public:
  // standard constructors, destructors
  node_base(void) : _type(Error) { }
  node_base(NodeType t) : _type(t) { }
  node_base(const node_base& src) { this->operator=(src); }
  virtual ~node_base(void) { } 
  
  // operators
  node_base& operator=(const node_base& src)
  {
    _type = src._type;
    return *this;
  }
  
  // to get and set the node's type
  NodeType type(void) const
  { return _type; }
  
  void set_type(NodeType t)
  { _type = t; }
  
  
};

#endif // _NODE_BASE_HPP_
