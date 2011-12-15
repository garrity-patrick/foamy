// vartable.hpp
// @author Chris Cornelius, Patrick Garrity, Jonathan Sandness
// Created 12/14/2011
// Foamy (toy language project) - ProLang course, Fall 2011
// Holds the declaration for a variable table type
//

#ifndef _VARTABLE_HPP_
#define _VARTABLE_HPP_

#include <map>
#include <string>
#include <llvm/AllocaInst>
#include "ftype_t.hpp"

// represents a variable in the variable table (everything about it but name)
class var {
private:
	AllocaInst* _inst;
	ftype_t _type;

public:
	var() { _inst = NULL; _type = ErrorType; }
	var(const AllocaInst* inst, const ftype_t type) { _inst = inst; _type = type; }
	var(const var& src) {
		_inst = src._inst;
		_type = src._type;
	}
	
	AllocaInst* inst() { return _inst; }
	void set_inst(const AllocaInst* inst) { _inst = inst; }
	AllocaInst* alloca() { return _inst; }
	void set_alloca(const AllocaInst* inst) { _inst = inst; }
		
	ftype_t type() { return _type; }
	void set_type(const ftype_t type) { _type = type; }
	
};

class vartable {
protected:
	map<std::string, var*> _table;
	
public:
	vartable();
	vartable(const vartable& src) {  // deep copies!
		// add all
		map<std::string, var*>::iterator it = src._table.begin();
		while(it != src._table.end())
		{
			_table[(*it).first] = new var ((*it).second);
			it++;
		}
	}
	
	~vartable() {
		map<std::string, var*>::iterator it = _table.begin();
		while(it != _table.end())
		{
			delete (*it).second;
			it++;
		}
	}
	
	int modify(const string & var_name, var * v)
	{
		map<std::string, var*>::iterator it = _table.find(var_name);
		if (it == _table.end())
		{
			_table[var_name] = v;
		}
		else
		{
			delete _table[var_name];
			_table[var_name] = v;
		}
		
		return 0;
	}
	
	int insert(string var_name, var* v) {// adds the given var to the var table, returns 0 if successful
		map<std::string, var*>::iterator it = _table.find(var_name);
		if (it != _table.end()) // found variable -- duplicate addition!
		{ return -1; }
		
		// assert: okay to add var to the table
		_table[var_name] = v;
		
		return 0;
	}
	
	
	var* get(string var_name) {// returns 0 or the variable if found
		map<std::string, var*>::iterator it = _table.find(var_name);
		if (it == _table.end()) // couldn't find
		{ return 0; }
		
		return (*it).second;
	}
	
};




#endif // _VARTABLE_HPP_
