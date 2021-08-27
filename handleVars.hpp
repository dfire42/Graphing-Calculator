#pragma once

#include <vector>
#include <string>
#include <cmath>
#include "removeParenthesis.hpp"
#include "equation.hpp"

using std::vector;
using std::string;

class HandleVars
{
protected:
	string eq;

	double solveEquation(string eq) { return std::stod(equation::simplify(removeParenthesis::parse(eq))); };

	HandleVars(string eq) { this->eq = eq; };

public:
	virtual double getPoint(string somePoint) = 0;
};
