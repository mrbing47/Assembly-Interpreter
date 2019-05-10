#pragma once

#include<functional>
#include<string>
#include<map>
#include"Register.h"
#include "functions.h"
#include "Error.h"
#include "datatypes.h"

using namespace std;
using namespace std::placeholders;


typedef map<string, function<bool(string, string)>> map_str_to_fun;

class Instructions : public Register, public Error
{
	bool checkHex(int dec, int bit)
	{
		if (dec == -1)
		{
			cout << INVALID_HEX;
			return false;
		}
		int max = 1 << bit;
		if (dec > max - 1)
		{
			cout << INVALID_HEX_8;
			return false;
		}
		return true;
	}
	
	bool shw8(string dest, string src)
	{
		if (dest != "")
		{
			cout << INVALID_PARAMS_MORE;
			return false;
		}
		if(reg.find(src) != reg.end())
		{
			cout << toUpperCase(src) << '=' << reg[src] << endl;
			return true;
		}
		else
		{
			cout << INVALID_REG;
			return false;
		}
	}

	bool mvi(string dest, string src)
	{
		if (dest == "")
		{
			cout << INVALID_PARAMS_FEW;
			return false;
		}
	
		if (reg.find(dest) != reg.end())
		{
			int dec = hexToDec(src);
			if (checkHex(dec, 8))
				reg[dest] = dec;
			else
				return false;
		}
		else
		{
			cout << INVALID_REG;
			return false;
		}
		return true;

	}

	bool add(string dest, string src)
	{
		if (dest != "")
		{
			cout << INVALID_PARAMS_MORE;
			return true;
		}
		try {
			reg["a"] += reg.at(src);
			return true;
		}
		catch (exception e)
		{
			cout << INVALID_REG;
			return false;
		}
	}

	bool inx(string dest, string src)
	{
		if (dest != "" || src != "")
		{
			cout << INVALID_PARAMS_MORE;
			return false;
		}
		
		reg["a"] += 1;

		return true;
	}

	bool adi(string dest, string src)
	{
		if (dest != "")
		{
			cout << INVALID_PARAMS_MORE;
			return false;
		}

		int dec = hexToDec(src);

		if (checkHex(dec, 8))
			reg["a"] += dec;
		else
			return false;

		return true;

	}

public:
	map_str_to_fun funMap;

	Instructions()
	{
		this->funMap["add"] = bind(&Instructions::add, this, _1, _2);
		this->funMap["adi"] = bind(&Instructions::adi, this, _1, _2);
		this->funMap["shw8"] = bind(&Instructions::shw8, this, _1, _2);
		this->funMap["mvi"] = bind(&Instructions::mvi, this, _1, _2);
		this->funMap["inx"] = bind(&Instructions::inx, this, _1, _2);
	}

	

	
};
