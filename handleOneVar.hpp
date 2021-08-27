#pragma once
#include "handleVars.hpp"
#include <iostream>
class OneVar : public HandleVars
{
private:
	string enterVariable(string var);
public:
	//Constructors
	OneVar() : OneVar("") {}
	OneVar(string inputEq) : HandleVars(inputEq) {}

	//Accessors
	virtual double getPoint(string somePoint) { return this->solveEquation(this->enterVariable(somePoint)); }
};