#pragma once

#include<string>

using namespace std;

int charindex(const string inst, const char ch)
{
	int strlen = inst.length();
	for (int i = 0; i < strlen; i++)
		if (inst[i] == ch)
			return i;
	return -1;
}

string trim(const string inst)
{
	string str = "";
	string whitespaces = "";
	int strlen = inst.length();
	bool isFirstCharFound = false;

	for (int i = 0; i < strlen; i++)
	{
		if (inst[i] != ' ')
		{
			if (!isFirstCharFound)
			{
				whitespaces = "";
				isFirstCharFound = true;
			}
			str = str + whitespaces + inst[i];
			whitespaces = "";

		}
		else
		{
			whitespaces += " ";
		}
	}
	return str;
}

int hexToDec(const string value)
{
	int hexNum = 0;
	string dupNum = value;
	int exp = 0;

	while (!dupNum.empty())
	{
		int n = (int)dupNum.back();
		
		if (n >= 65)
			n -= 55;
		else
			n -= 48;

		hexNum += n * (1 << exp);

		exp += 4;

		dupNum.pop_back();
	}
	return hexNum;
}

