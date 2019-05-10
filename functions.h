#pragma once

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

int hexToDec(const string hexNum)
{
	int decNum = 0;
	string dupNum = hexNum;
	int exp = 0;

	while (!dupNum.empty())
	{
		int n = (int)dupNum.back();
		
		if ((n >= 65 and n <= 70) or
			(n >= 97 and n <= 102) or
			(n >= 48 and n <= 57))
		{

			if (n >= 65)
				n -= 55;
			else
			{
				if (n >= 97)
					n -= 87;
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

bool strequal(string first, string second, bool caseSensitive = false)
{
	if (first.length() == second.length())
	{
		int strlen = first.length();
		for (int i = 0; i < strlen; i++)
		{
			char fch = first[i];
			char sch = second[i];

			if (!caseSensitive)
			{
				if ((int)sch > 64 and (int)sch < 91)
					sch += 32;

				if ((int)fch > 64 and (int)fch < 91)
					fch += 32;
			}

			if (fch != sch)
				return false;
		}

		return true;
	}
	else
		return false;
}

vector<string> strsplit(string str, string splitpt)
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
