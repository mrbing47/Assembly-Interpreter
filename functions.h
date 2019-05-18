#pragma once

using namespace std;

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

int hexToDec(const string hexNum)
{
	int decNum = 0;
	string dupNum = hexNum;
	int exp = 0;

	while (!dupNum.empty())
	{
		int n = (int)dupNum.back();
		
		if ((n >= 65 && n <= 70) ||
			(n >= 97 && n <= 102) ||
			(n >= 48 && n <= 57))
		{

			if (n >= 97)
				n -= 87;
			else
			{
				if (n >= 65)
					n -= 55;
				else
					n -= 48;
			}

		}
		else
			return -1;

		decNum += n * (1 << exp);

		exp += 4;

		dupNum.pop_back();
	}
	return decNum;
}

vector<string> str_split(string str, string splitpt)
{
	vector<string> resStr;
	string temp = "";
	
	int strlen = str.length();
	int arrlen = splitpt.length();


	bool contains = false;

	for (int i = 0; i <= strlen; i++)
	{
		contains = false;
		for (int j = 0; j <= arrlen; j++)
		{
			if (str[i] == splitpt[j])
			{
				contains = true;
				break;
			}
		}

		if (contains)
		{
			if (temp != "")
				resStr.push_back(temp);
			
			temp = "";
		}
		else
			temp += str[i];
	}

	return resStr;
}

string toLowerCase(string str)
{
	string resStr = "";
	int strLen = str.length();
	for (int i = 0; i < strLen; i++)
	{
		if (str[i] >= 65 and str[i] <= 90)
			resStr += (str[i] + 32);
		else
			resStr += str[i];
	}
	return resStr;
}

string toUpperCase(string str)
{
	string resStr = "";
	int strLen = str.length();
	for (int i = 0; i < strLen; i++)
	{
		if (str[i] >= 97 and str[i] <= 122)
			resStr += (str[i] - 32);
		else
			resStr += str[i];
	}
	return resStr;
}

