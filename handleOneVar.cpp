#ifndef __HANDLEONEVAR_CPP__
#define __HANDLEONEVAR_CPP__

#include "../header/handleOneVar.hpp"
#include <iostream>
using std::cout;

string OneVar::enterVariable(string var)
{
	string localEq = this->eq;
	for (int i = 0; i < localEq.length(); i++)
	{
		if (isalpha(localEq[i]))
		{
			string tempVar = var;
			if (i > 0)
			{
				if (isdigit(localEq[i - 1]) || isalpha(localEq[i - 1]))
					tempVar = '*' + tempVar;
			}
			if (i + 2 < localEq.length())
			{
				if (isdigit(localEq[i + 1]) || isalpha(localEq[i + 1]))
					tempVar = tempVar +'*';
			}
			localEq.replace(i, 1, tempVar);
		}
	}

	return localEq;
}

#endif