#ifndef __INTERPRETER_CPP__
#define __INTERPRETER_CPP__

#include "../header/Interpreter.hpp"

int Interpreter::howManyVars(string eq)
{
	vector<char> usedLetters;
	for (int i = 0; i < eq.length(); i++)
	{
		if (isalpha(eq[i]))
		{
			if (usedLetters.size() > 0)
			{
				bool alreadyKnown = false;
				for (int j = 0; j < usedLetters.size(); j++)
				{
					if (eq[i] == usedLetters[j])
					{
						alreadyKnown = true;
						break;
					}
				}
				if (!alreadyKnown)
				{
					usedLetters.size();
				}
			}
			else
				usedLetters.push_back(eq[i]);
		}
	}
	return usedLetters.size();
}

HandleVars* Interpreter::getParsedEquation(string eq)
{
	eq = removeParenthesis::parse(eq);
	HandleVars* test;
	switch (howManyVars(eq))
	{
	case 0:
		test = new NoVar(eq);
		break;
	case 1:
		test = new OneVar(eq);
		break;
	default:
		test = nullptr;
	}
	return test;
}

#endif