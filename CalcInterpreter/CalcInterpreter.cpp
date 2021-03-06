#include "pch.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm> 
#include <math.h>
using namespace std;

struct FullString
{
	vector<char> strng;

	void convert(string input)
	{
		input.erase(remove_if(input.begin(), input.end(), isspace), input.end()); // removes white spaces
		copy(input.begin(), input.end(), std::back_inserter(strng)); // converts to vector
	}
};

double digit(vector<char> &strng)
{
	int val = strng[0] - '0';
	strng.erase(strng.begin());
	return val;
}

double sign(vector<char> &strng)
{
	if (strng[0] == '-')
	{
		strng.erase(strng.begin());
		return -1;
	}
	else // if (string[0] == '+')
	{
		strng.erase(strng.begin());
		return 1;
	}
}

double unsignedNum(vector<char> &strng)
{
	double val = 0;
	while (strng[0] != '=') // checks that calculation isnt done
	{
		if (strng[0] == '.') // checks for decimal 
		{
			int level = 0; // every iteration of level represents the next decimal place

			strng.erase(strng.begin()); // erases decimal

			while (isdigit(strng[0]))
			{
				level++;
				val += (digit(strng) / pow(10, level));
			}
		}
		if (isdigit(strng[0]))
			val = (val * 10) + digit(strng);

		else break;
	}

	return val;
}

double value(vector<char> &strng)
{
	double val;
	double signVal = 1;

	if (!isdigit(strng[0]))
		signVal = sign(strng);

	val = unsignedNum(strng) * signVal;

	return val;
}

double term(vector<char> &strng)
{
	double val = value(strng);

	if (strng[0] != '=')
	{
		if (strng[0] == '+')
		{
			strng.erase(strng.begin());
			val = val + term(strng);
		}

		else if (strng[0] == '*')
		{
			strng.erase(strng.begin());
			val = val * term(strng);
		}
	}

	return val;
}

double expression(vector<char> &strng)
{
	double val = term(strng);

	if (strng[0] != '=')
	{
		if (strng[0] == '-')
		{
			strng.erase(strng.begin());
			val = val - expression(strng);
		}
		else if (strng[0] == '/')
		{
			try
			{
				strng.erase(strng.begin());
				double divVal = expression(strng);

				if (divVal == 0)
				{
					val = 0;
					throw "error";
				}

				val = val / divVal;
			}
			catch (...)
			{
				cout << "ERROR! Attempted division by zero or blank value";
			}
		}
	}

	return val;
}

double calculation(vector<char> &strng)
{
	double val = expression(strng);
	return val;
}

int main()
{
	cout << "enter 'x' to exit..." << endl << endl << "input>> ";
	string input;
	getline(cin, input);

	while (input != "x" && !input.empty())
	{
		try
		{
			if (input.back() != '=') throw "error";

			FullString fullString;

			fullString.convert(input);

			cout << calculation(fullString.strng) << endl << endl << "input>> ";

			getline(cin, input);
		}
		catch (...)
		{
			cout << "ERROR! Didn't end expression with '=' sign" << endl << endl << "input>> ";
			getline(cin, input);
		}
	}

	cout << endl << "exiting program..." << endl << endl;
}
