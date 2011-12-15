// printer_driver.cpp
// @author Chris Cornelius
// Created 11/11/2011
// to test basic printing functions


#include <iostream>
#include <vector>
#include <string>
using namespace std;

#include "node_base.hpp"
#include "node_function.hpp"
#include "node_program.hpp"
#include "exp_base.hpp"
#include "exp_return.hpp"
#include "exp_var.hpp"
#include "exp_assign.hpp"
#include "exp_call.hpp"
#include "exp_const.hpp"
#include "exp_declare.hpp"
#include "exp_declarefunc.hpp"
#include "exp_operator.hpp"
//#include "codegen.hpp"

int main()
{
  vector<func_arg> args;
  func_arg a(Int, "x");
  args.push_back(a);
  a.name = "y";
  args.push_back(a);
  a.name = "z";
  args.push_back(a);
  
  exp_return* f3 = new exp_return(NULL, new exp_var(NULL, "H"));
  exp_operator* f2 = new exp_operator((exp_base*)f3, Plus, new exp_const(NULL, Int, 0), new exp_var(NULL,"H"));
  exp_declare* f1 = new exp_declare((exp_base*)f2, Int, "H");
  node_function* func1 = new node_function("func1",Void,args,(exp_base*)f1);
  exp_declarefunc* e8 = new exp_declarefunc(NULL, func1);
  exp_var* e7 = new exp_var((exp_base*) e8, "var7");
  exp_var* e6 = new exp_var((exp_base*) e7, "var6");
  exp_call* e3 = new exp_call(NULL, "function2", (exp_base*) e6);
  exp_var* e4 = new exp_var(NULL, "W");
  exp_var* e1ret = new exp_var(NULL, "x");
  exp_return* e1 = new exp_return(NULL, (exp_base*) e1ret);
  exp_assign* e = new exp_assign ((exp_base*) e1, (exp_base*) e3, (exp_var*) e4);

 

  node_function* f = new node_function("f", Void, args, (exp_base*)e);
  
  node_program* p = new node_program;
  p->globalsVector().push_back((node_base*) f);
  //p->globalsVector().push_back((node_base*) f);
  p->set_main(f);
  

  cout << endl;
  p->printRec(cout,0);
  cout << endl;cout << endl;cout << endl;
  
  //codegen CG(std::string("DERP"));
  //CG.set_tree(p);
  //CG.generate();
  
  
}

