#ifndef __REMOVEPARENTHESIS_CPP__
#define __REMOVEPARENTHESIS_CPP__

#include "../header/removeParenthesis.hpp"
#include "../header/equation.hpp"

string removeSpaces(string eq);
string findParenthesis(string eq);
vector<vector<int>> adjustLocation(vector<vector<int>> parenLocations, int change, int i);
string handleParenthesis(string eq, vector<vector<int>> parenLocations);
string handleExponent(string base, string exponent);
string handleNeg(string eq, vector<vector<int>>& parenLocations, int location);
string distributeNeg(string eq);
string distributeMult(string parenLeft, string parenRight);
string distributePowVar(string parenLeft, string parenRight);
string distributePow(string parenLeft, string parenRight);
vector<string> getVals(string eq);
string simplify(string eq);


string removeSpaces(string eq)
{
	for (int i = 0; i < eq.size(); i++)
	{
		if (eq[i] == ' ')
			eq.erase(i--, 1);
	}
	return eq;
}

	/*
	Finds the locations of outer parenthesis and passes them to handleParenthesis
	 - If none returns the given string
	*/
string findParenthesis(string eq)
{
	vector<vector<int>> parenLocations;
	int openParen = 0;		//Used to track how many open parenthesis have been found	|	parenFound(+1 if open, -1 if closed)
	vector<int> paren;			//Tracks location of both parenthesis 0='(' 1=')'
	for (int i = 0; i < eq.size(); i++)
	{
		if (eq[i] == '(')
			if (openParen++ == 0)
				paren.push_back(i);
		if (eq[i] == ')')
			if (--openParen == 0)
			{
				paren.push_back(i);
				parenLocations.push_back(paren);
				paren.clear();
			}
	}
	string result;
	if (parenLocations.empty())
		result = simplify(eq);
	else
		result = simplify(handleParenthesis(eq, parenLocations));		//There were parenthesis inside the parenthesis
	return result;
}

	//adjusts all parenLocations after parenLocations[i][0] by change
vector<vector<int>> adjustLocation(vector<vector<int>> parenLocations, int change, int i)
{
	parenLocations[i][1] += change;
	for (++i; i < parenLocations.size(); i++)
	{
		parenLocations[i][0] += change;
		parenLocations[i][1] += change;
	}
	return parenLocations;
}

string handleParenthesis(string eq, vector<vector<int>> parenLocations)
{
	bool noAction = true;
	while (!parenLocations.empty())
	{
		int powPos = -1;
		int baseLocation = -1, start = -1, end = -1;
		bool baseParen = false, exponentParen = false;
		string base = "", exponent = "";
		for (int i = 0; i < parenLocations.size(); i++)		//Handle possible paren with exponent		Might take ()^x+4-7^() as ()^()
		{
			if (eq.size() > i + 1)
			{
				if (eq[parenLocations[i][1] + 1] == '^' && !baseParen)		//eq has paren^
				{
					base = eq.substr(parenLocations[i][0] + 1, parenLocations[i][1] - (parenLocations[i][0] + 1));
					base = findParenthesis(base);
					baseLocation = i;
					start = parenLocations[i][0];
					if (end == -1)
						end = parenLocations[i][1];
					baseParen = true;
				}
			}
			if (parenLocations[i][0] - 2 >= 0)		//distributes any leading negative in exponent
				if ((eq[parenLocations[i][0] - 1] == '-' && eq[parenLocations[i][0] - 2] == '^'))
					eq = handleNeg(eq, parenLocations, i);
			if (parenLocations[i][0] - 1 >= 0)
			{
				if (!exponentParen && eq[parenLocations[i][0] - 1] == '^')	//eq has ^paren
				{
					exponent = eq.substr(parenLocations[i][0] + 1, parenLocations[i][1] - (parenLocations[i][0] + 1));
					exponent = findParenthesis(exponent);
					end = parenLocations[i][1];
					if (baseLocation == -1)
					{
						baseLocation = i;
						start = parenLocations[i][0];
					}
					exponentParen = true;
				}
			}
		}
		if (baseParen && !exponentParen)	//Find exponent, Assumes 2X == ^(2X), and 2*X == (^2)*X
		{
			int valStart = ++end;
			while (eq[++end] == '.' || eq[end] == '-' || isalpha(eq[end]) || isdigit(eq[end]))		//Get the entire exponent value
			{
				if (eq[end] == '-' && end != 1 + valStart)
				{
					end--;
					break;
				}
				if (eq.size() <= end)
				{
					end--;
					break;
				}
			}
			if (--end - valStart <= 0)
				end = valStart + 1;
			exponent = eq.substr(1 + valStart, end - valStart);
		}
		else if (exponentParen && !baseParen)	//Find base
		{
			if (!isalpha(eq[start - 2]) && !isdigit(eq[start - 2]))	//in form .^() or *^() or +^() etc.		removes char before ^
			{
				eq.erase(start - 2);
				parenLocations[baseLocation][0]--;
				parenLocations = adjustLocation(parenLocations, -1, baseLocation);
			}
			if (isalpha(eq[start - 2]))		//Only accepts single letter variables
			{
				start -= 2;
				base = eq[start, 1];
			}
			else	//is a digit
			{
				start -= 1;
				while (isdigit(eq[--start]) || eq[start] == '.')
				{
					if (start < 0)
						break;
				}
				start++;
				base = eq.substr(start, (parenLocations[baseLocation][0] - 1) - start);
			}
		}
		if (baseParen || exponentParen)
		{
			int originalSize = eq.size();
			string result = handleExponent(base, exponent);
			eq.replace(start, 1 + end - start, result);
			parenLocations = adjustLocation(parenLocations, eq.size() - originalSize, baseLocation);
			parenLocations.erase(parenLocations.begin() + baseLocation);
			if (baseParen && exponentParen)
				parenLocations.erase(parenLocations.begin() + baseLocation);
			noAction = false;
		}

		//if (parenLocations[0][0] - 1 >= 0 && (isdigit(eq[parenLocations[0][0] - 1]) || isalpha(eq[parenLocations[0][0] - 1])))
		//{
		//	string left = eq.substr(0, parenLocations[0][0]);
		//	left = getVals(left).back();
		//	string right = eq.substr(parenLocations[0][0] + 1, parenLocations[0][1] - parenLocations[0][0] - 1);
		//	right = findParenthesis(right);
		//	eq.replace(parenLocations[0][0] - left.size(), 1 + parenLocations[0][1] - (parenLocations[0][0] - left.size()), distributeMult(left, right));
		//	parenLocations.erase(parenLocations.begin());
		//}

		for (int i = 0; i < parenLocations.size(); i++)		//handle possible paren multiplication
		{
			if (parenLocations[i][0] - 1 >= 0 && (isdigit(eq[parenLocations[i][0] - 1]) || isalpha(eq[parenLocations[i][0] - 1])
				|| eq[parenLocations[i][0] - 1] == '*'|| eq[parenLocations[i][0] - 1] == '/'))
			{
				if (eq[parenLocations[i][0] - 1] == '/')
				{
					eq[parenLocations[i][0] - 1] = '*';
					int originalSize = eq.size();
					string temp = distributePow(findParenthesis(eq.substr(parenLocations[i][0] + 1, parenLocations[i][1] - parenLocations[i][0] - 1)), "-1");
					eq.replace(parenLocations[i][0], 1 + parenLocations[i][1] - parenLocations[i][0], temp);
					parenLocations = adjustLocation(parenLocations, eq.size() - originalSize, i);
					parenLocations.erase(parenLocations.begin() + i);
					noAction = false;
					break;
				}
				int originalSize = eq.size();
				int valStart = parenLocations[i][0] - 1;
				while (eq[valStart] == '.' || eq[valStart] == '*' || eq[valStart] == '-' || isalpha(eq[valStart]) || isdigit(eq[valStart]))		//Get the entire first value
				{
					if (--valStart < 0)
						break;
					if (eq[valStart + 1] == '-' && eq[valStart] != '*')
						break;
				}
				valStart++;
				string val1 = eq.substr(valStart, parenLocations[i][0] - valStart - 1);
				string paren1 = eq.substr(parenLocations[i][0] + 1, parenLocations[i][1] - (parenLocations[i][0] + 1));
				paren1 = findParenthesis(paren1);
				eq.replace(valStart, parenLocations[i][1] - (valStart - 1), distributeMult(val1, paren1));
				parenLocations = adjustLocation(parenLocations, eq.size() - originalSize, i);
				parenLocations.erase(parenLocations.begin() + i--);
				noAction = false;
				int remainingParens = parenLocations.size();
				if (remainingParens <= i)
					break;
			}
			else
			{
				if (parenLocations[i][1] + 1 < eq.size())
					if (isdigit(eq[parenLocations[i][1] + 1]) || isalpha(eq[parenLocations[i][1] + 1]))
					{
						eq.insert(parenLocations[i][1] + 1, "*");
						adjustLocation(parenLocations, 1, i);
					}
				//there is at least one operation between the parenthesis
				int originalSize = eq.size();
				bool run = false;
				if (i + 1 < parenLocations.size())
				{
					if (parenLocations[i][1] != parenLocations[i + 1][0] - 1 && parenLocations[i][1] >= parenLocations[i + 1][0] - 3)
					{
						if (eq[parenLocations[i][1] + 1] == '*')
						{
							if (eq[parenLocations[i][1] + 2] == '-' && parenLocations[i + 1][0] - 1 == parenLocations[i][1] + 2)	//handles ()*-()
							{
								string paren1 = eq.substr(parenLocations[i + 1][0] + 1, parenLocations[i + 1][1]);
								paren1 = "+" + distributeNeg(findParenthesis(paren1));
								eq.replace(parenLocations[i][1] + 2, 1 + parenLocations[i + 1][1], paren1);
								parenLocations = adjustLocation(parenLocations, eq.size() - originalSize, i);
								originalSize = parenLocations.size();
							}
						}
					}
					else if (parenLocations[i][1] == parenLocations[i + 1][0] - 1)
						run = true;
				}
				if (run)
				{
					string paren1 = eq.substr(parenLocations[i][0] + 1, parenLocations[i][1] - 1 - parenLocations[i][0]);
					paren1 = findParenthesis(paren1);
					string paren2 = eq.substr(parenLocations[i + 1][0] + 1, parenLocations[i + 1][1] - 1 - parenLocations[i + 1][0]);
					paren2 = findParenthesis(paren2);
					eq.replace(parenLocations[i][0], 1 + parenLocations[i + 1][1] - parenLocations[i][0], distributeMult(paren1, paren2));
					parenLocations = adjustLocation(parenLocations, eq.size() - originalSize, i);
					parenLocations.erase(parenLocations.begin());
					parenLocations.erase(parenLocations.begin());
					noAction = false;
				}
				int stop;
				if (i + 1 < parenLocations.size())
					stop = parenLocations[i + 1][0];
				else
					stop = eq.size();
				bool digitFound = false;
				if (!parenLocations.empty())
					for (int j = parenLocations[i][1] + 2; j < stop; j++)
					{
						if (isdigit(eq[j]) || isalpha(eq[j]))
							digitFound = true;
						if (digitFound && (eq[j] == '-' || eq[j] == '+' || eq[j] == '*' || eq[j] == '/') && eq[j - 1] != '^')
						{
							string left = eq.substr(parenLocations[i][0] + 1, parenLocations[i][1] - parenLocations[i][0] - 1);
							left = findParenthesis(left);
							string right = eq.substr(parenLocations[i][1] + 2, j - parenLocations[i][1] - 2);
							int originalSize = eq.size();
							eq.replace(parenLocations[i][0], j - parenLocations[i][0], distributeMult(left, right));
							parenLocations = adjustLocation(parenLocations, eq.size() - originalSize, i);
							parenLocations.erase(parenLocations.begin() + i);
							noAction = false;
							break;
						}
					}
			}
		}
		for (int i = 0; i < parenLocations.size(); i++)		//Handles distributing negatives
		{
			if (parenLocations[i][0] > 0 && (eq[parenLocations[i][0] - 1] == '-'))
			{
				eq = handleNeg(eq, parenLocations, i--);
				noAction = false;
			}
		}
		if (noAction)
		{
			int originalSize = eq.size();
			string temp = findParenthesis(eq.substr(parenLocations[0][0] + 1, parenLocations[0][1] - parenLocations[0][0] - 1));
			eq.replace(parenLocations[0][0], 1 + parenLocations[0][1] - parenLocations[0][0], temp);
			parenLocations = adjustLocation(parenLocations, eq.size() - originalSize, 0);
			parenLocations.erase(parenLocations.begin());
			noAction = true;
		}
	}
	return eq;
}

/*
* control function for distributing negatives
* - location == the position of the relevant parenthesis in parenLocations
*/
string handleNeg(string eq, vector<vector<int>>& parenLocations, int location)
{
	eq.erase(parenLocations[location][0] - 1, 1);

	//Adjusts for deletion of leading '-'
	parenLocations[location][0]--;
	parenLocations = adjustLocation(parenLocations, -1, location);

	int  originalSize = eq.size();
	string paren1 = eq.substr(1 + parenLocations[location][0], parenLocations[location][1] - (parenLocations[location][0] + 1));
	eq.replace(parenLocations[location][0], 1 + parenLocations[location][1] - parenLocations[location][0], distributeNeg(findParenthesis(paren1)));
	parenLocations = adjustLocation(parenLocations, eq.size() - originalSize, location);
	//if (parenLocations[0][0] == 1)
	//	eq.erase(eq.begin());
	parenLocations.erase(parenLocations.begin() + location);
	return eq;
}

string handleExponent(string base, string exponent)
{
	bool hasVariable = false;
	for (int i = 0; i < exponent.size(); i++)
	{
		if (isalpha(exponent[i]))
		{
			hasVariable = true;
			base = '(' + base + ')';
			break;
		}
	}
	string result;
	if (hasVariable)
		result = distributePowVar(base, exponent);
	else
		result = distributePow(base, exponent);
	return result;
}

string distributeNeg(string eq)
{
	bool firstDigit = true;
	for (int i = 0; i < eq.size(); i++)
	{
		if (isdigit(eq[i]))
		{
			if (i == 0)
			{
				eq.insert(0, 1, '+');	//Second if() assumes a sign is given
				i++;
			}
			if (firstDigit == true)
			{
				firstDigit = false;
				if (eq[i - 1] == '+')	//flips sign to negative
				{
					eq.erase(--i, 1);
					eq.insert(i, 1, '-');
				}
				else if (eq[i - 1] == '-')	//flips sign to positive
				{
					eq.erase(--i, 1);
					eq.insert(i, 1, '+');
				}
			}
		}
		else
			firstDigit = true;
	}
	return eq;
}

string distributeMult(string parenLeft, string parenRight)
{
	vector<string> parenValsLeft = getVals(parenLeft), parenValsRight = getVals(parenRight);
	string result = "";
	for (int i = 0; i < parenValsLeft.size(); i++)
	{
		for (int j = 0; j < parenValsRight.size(); j++)
		{
			result += parenValsLeft[i] + "*" + parenValsRight[j] + '+';
		}
	}
	if (result[result.size() - 1] == '+')
		result.pop_back();
	return result;
}

string distributePowVar(string parenLeft, string parenRight)
{
	vector<string> parenValsRight = getVals(parenRight);
	string result = "";

	for (int i = 0; i < parenValsRight.size(); i++)
	{
		result += parenLeft + '^' + parenValsRight[i] + '*';
	}

	if (result[result.size() - 1] == '*')
		result.pop_back();
	return result;
}

string distributePow(string parenLeft, string parenRight)
{
	parenLeft = equation::simplify(parenLeft);
	parenRight = equation::simplify(parenRight);
	return parenLeft + '^' + parenRight;
}

/*
* used by distributeMult and distributePow to seperate the operations of parenthesis
* returns a vector of the operations contained in the passed string
*/
vector<string> getVals(string eq)
{
	vector<string> parenVals;
	bool digitStarted = false;
	int firstPos = 0;
	for (int i = 0; i < eq.size(); i++)
	{
		char val = eq[i];
		if (isdigit(val) || val == '.' || isalpha(val))
		{
			if (digitStarted == false)
			{
				digitStarted = true;
				firstPos = i;
				if (i != 0 && eq[i - 1] == '-')
					firstPos--;
			}
		}
		if (i != 0)
			if (val == '+' || val == '-')
				if (isdigit(eq[i - 1]) || isalpha(eq[i - 1]) || eq[i - 1] == '(')
				{
					digitStarted = false;
					parenVals.push_back(eq.substr(firstPos, i - firstPos));
				}
	}
	parenVals.push_back(eq.substr(firstPos, eq.size() - firstPos));
	return parenVals;
}

string simplify(string eq)
{
	string result;
	if (!eq.empty())
	{
		bool hasParens = false;
		for (int i = 0; i < eq.size(); i++)
			if (eq[i] == '(')
			{
				hasParens = true;
				break;
			}
			else if (eq[i] == ')')		//No Opening parenthesis
			{
				eq.erase(eq.begin() + i--);
			}
		if (!hasParens)
		{
			vector<string> eqVals = getVals(eq);
			string temp;
			while (!eqVals.empty())
			{
				bool hasVariable = false;
				for (int i = 0; i < eqVals[0].size(); i++)
				{
					if (isalpha(eqVals[0][i]))
					{
						hasVariable = true;
						break;
					}
				}
				if (hasVariable)
				{
					if (!temp.empty() && eqVals[0][0] != '-')
						temp += '+';
					temp += eqVals[0];
				}
				else
				{
					if (!result.empty() && eqVals[0][0] != '-')
						result += '+';
					result += eqVals[0];
					result = equation::simplify(result);
				}
				eqVals.erase(eqVals.begin());
			}
			if (!temp.empty() && temp[0] != '-')
				result += '+';
			result += temp;
		}
		else
			result = eq;
	}
	return result;
}

// namespace removeParenthesis
// {
	string removeParenthesis::parse(string eq)
	{
		eq = removeSpaces(eq);
		return findParenthesis(eq);
	}
// }

#endif
