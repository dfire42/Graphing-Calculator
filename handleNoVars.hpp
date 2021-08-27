#pragma once
#include "handleVars.hpp"
#include <iostream>
class NoVar :  public HandleVars
{
public:
	//Constructors
	NoVar() : NoVar("") {}
	NoVar(string inputEq) : HandleVars(inputEq) {}

	//Accessors
	virtual double getPoint(string somePoint) { return this->solveEquation(this->eq); }		//Will always be something like the lines x=1 or y=1, so this is fine
};