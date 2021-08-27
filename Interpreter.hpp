#pragma once
#include <string>
#include <vector>
#include "handleNoVars.hpp"
#include "handleOneVar.hpp"
#include "removeParenthesis.hpp"

using std::string;
using std::vector;

class Interpreter
{
private:
	int howManyVars(string eq);
protected:
	//data
	string eq;

public:
	//constructors
	Interpreter(string eq) { this->eq = eq; this->getParsedEquation(); };
	Interpreter() : Interpreter("") {};

	//accessors
	HandleVars* getParsedEquation() { return this->getParsedEquation(this->eq); };
	HandleVars* getParsedEquation(string eq);

	//mutators
	void setEquation(string equation) { this->eq = equation; };
};