#include "../header/equation.hpp"

vector<int> solveOp(string& inputEq, int start)
{
	bool leftDone = false, rightDone = false;
	double left, right;
	int lPos, rPos;
	for (int i = 0; i < inputEq.size(); i++)		//Will go out of bounds if not checked
	{
		if (!leftDone)
		{
			if ((start - 1) - i >= 0)
			{
				bool run = false;
				char temp = inputEq.at(start - 1 - i);
				if (!isdigit(temp) && temp != '-' && temp != '.')		//Likely cause of any issues with double operators eg.(*-), (--), or(+-)
				{
					run = true;
					lPos = start - i;
				}
				else if (i != 0 && inputEq.at(start - i) == '-')
				{
					run = true;
					lPos = start - i;
				}
				else //handles negative numbers
				{
					if ((start - 2) - i >= 0)
					{
						if (isdigit((start - 2) - i))
						{
							run = true;
							lPos = start - i;
						}
					}
				}
				if (run)
				{
					leftDone = true;
					left = stod(inputEq.substr(lPos, i + 1));
				}
			}
			else
			{
				leftDone = true;
				left = stod(inputEq.substr(0, start));
				lPos = 0;
			}

		}
		if (!rightDone)
		{
			bool run = false;
			if (start + 1 + i < inputEq.size())
			{
				if (!isdigit(inputEq.at(start + 1 + i)) && inputEq.at(start + 1 + i) != '-' && inputEq.at(start + 1 + i) != '.')
				{
					run = true;
				}
				else if (inputEq.at(start + 1 + i) == '-' && i > 0)
				{
					run = true;
				}
				if (run)
				{
					rightDone = true;
					right = stod(inputEq.substr(start + 1, i));
					rPos = start + i;
				}
			}
			else
			{
				rightDone = true;
				right = stod(inputEq.substr(start + 1, i));
				rPos = inputEq.size() - 1;
			}
		}

		if (leftDone && rightDone)
		{
			double result = 0;
			switch (inputEq.at(start))
			{
			case '+':
				result = left + right;
				break;
			case '-':
				result = left - right;
				break;
			case '*':
				result = left * right;
				break;
			case '/':
				result = left / right;
				break;
			case '^':
				bool negative = false;
				if (right < 0)
				{
					negative = true;
					right *= -1;
				}
				result = pow(left, right);
				if (negative)
					result = 1 / result;
			}
			int originalSize = inputEq.size();

			//remove any trailing zeros and the decimal point if whole number
			string resString = std::to_string(result);
			resString.erase(resString.find_last_not_of('0') + 1, string::npos);
			if (resString.at(resString.size() - 1) == '.')
				resString.erase(resString.size() - 1, 1);

			/* bug where a-b*-b forgets a-b and replaces it with ab */
			if (lPos != 0 && inputEq[lPos] == '-' && resString[0] != '-')
				resString = "+" + resString;

			inputEq.replace(lPos, 1 + rPos - lPos, resString);

			vector<int> toReturn;
			toReturn.push_back(inputEq.size() - originalSize);
			toReturn.push_back(rPos);
			return toReturn;
		}
	}
}

void adjust(vector<int>& ops, int change, int start)
{
	for (int i = 0; i < ops.size(); i++)
	{
		if (start <= ops[i])
		{
			ops[i] += change;
		}
	}
}

string equation::simplify(string eq)
{
	vector<int> add, sub, mult, div, pow, paren;
	for (int i = 0; i < eq.size(); i++)		//Gets the amount of each equation type
	{
		switch (eq[i])
		{
		case '+':
			add.push_back(i);
			break;
		case '-':
			if (i > 0)
				if (isdigit(eq.at(i - 1)) || isalpha(eq.at(i - 1)))		//handles +- *- /- ^- --
					sub.push_back(i);
			break;
		case '*':
			mult.push_back(i);
			break;
		case '/':
			div.push_back(i);
			break;
		case '^':
			pow.push_back(i);
			break;
		}
	}
	int runtime = add.size() + sub.size() + mult.size() + div.size() + pow.size();
	vector<int> searchOp;
	if (runtime > 0)		//for loop runs when runtime == 0 otherwise
	{
		for (int i = 0; i < runtime; i++)
		{
			if (!pow.empty())
			{
				searchOp = pow;
				pow.erase(pow.begin());
			}
			else if (!mult.empty())		//Mult before division in an attempt to reduce decimals
			{
				searchOp = mult;
				mult.erase(mult.begin());
			}
			else if (!div.empty())
			{
				searchOp = div;
				div.erase(div.begin());
			}
			else if (!sub.empty())
			{
				searchOp = sub;
				sub.erase(sub.begin());
			}
			else if (!add.empty())
			{
				searchOp = add;
				add.erase(add.begin());
			}
			vector<int> result = solveOp(eq, searchOp.front());
			if (runtime != 0)
			{
				adjust(add, result[0], result[1]);
				adjust(sub, result[0], result[1]);
				adjust(mult, result[0], result[1]);
				adjust(div, result[0], result[1]);
				adjust(pow, result[0], result[1]);
			}
		}
	}
	return eq;
}
