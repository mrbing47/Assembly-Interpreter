#pragma once

#include<functional>
#include<string>
#include<map>
#include"Register.h"
#include "functions.h"
#include "Error.h"
#include "Compiler.h"
#include "datatypes.h"

using namespace std;
using namespace std::placeholders;


class Instructions : public Register, public Error
{

	int mValue(_Bit8 reg_H, _Bit8 reg_L)
	{
		return (reg_H.toInt() << 8) + reg_L.toInt();
	}
	
	bool checkParams(string dest, string src, int n)
	{
		if (n == 0)
		{
			if (src != "")
			{
				cout << INVALID_PARAMS_MORE;
				return false;
			}
		}
		if (n == 1)
		{
			if (dest != "")
			{
				cout << INVALID_PARAMS_MORE;
				return false;
			}
			if (src == "")
			{
				cout << INVALID_PARAMS_FEW;
				return false;
			}

		}
		if (n == 2)
		{
			if (dest == "")
			{
				cout << INVALID_PARAMS_FEW;
				return false;
			}
		}
		return true;
	}

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
			if (bit == 8)
				cout << INVALID_HEX_8;
			if (bit == 16)
				cout << INVALID_HEX_16;
			return false;
		}
		return true;
	}
	
	bool htd(string dest, string src)
	{
		if(!checkParams(dest,src,1))
			return false;
		
		int dec = hexToDec(src);

		if (checkHex(dec, 16))
			cout << dec << endl;

		return false;
	}

	bool shw8(string dest, string src)
	{
		if (!checkParams(dest, src, 1))
			return false;

		if(reg.find(src) != reg.end())
		{
			int value = reg[src].toInt();
			
			if (src == "m")
				value = mValue(reg["h"], reg["l"]);

			cout << toUpperCase(src) << '=' << value << endl;
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
		if (!checkParams(dest, src, 2))
			return false;
	
		if (reg.find(dest) != reg.end())
		{
			int dec = hexToDec(src);
			if (checkHex(dec, 8))
			{
				reg[dest] = dec;
			}
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
		if (!checkParams(dest, src, 1))
			return false;

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

	bool inr(string dest, string src)
	{
		if (!checkParams(dest, src, 1))
			return false;
		if (reg.find(src) != reg.end())
			reg[src] += 1;
		else
			return false;

		return true;
	}

	bool adi(string dest, string src)
	{
		if (!checkParams(dest, src, 1))
			return false;

		int dec = hexToDec(src);

		if (checkHex(dec, 8))
			reg["a"] += dec;
		else
			return false;

		return true;
	}

	bool shl(string dest, string src)
	{
		if (!checkParams(dest, src, 0))
			return false;

		for (auto i = labelMap.begin(); i != labelMap.end(); i++)
			cout << i->first << '\t' << i->second << endl;
		

		return true;
	}

	bool mov(string dest, string src)
	{
		if (!checkParams(dest, src, 2))
			return false;
		
		return true;
	}

public:

	map<string,function<bool(string,string)>> funMap;

	Instructions()
	{
		this->funMap["shw8"] = bind(&Instructions::shw8, this, _1, _2);
		this->funMap["shl"] = bind(&Instructions::shl, this, _1, _2);
		this->funMap["htd"] = bind(&Instructions::htd, this, _1, _2);

		this->funMap["add"] = bind(&Instructions::add, this, _1, _2);
		this->funMap["adi"] = bind(&Instructions::adi, this, _1, _2);
		this->funMap["mvi"] = bind(&Instructions::mvi, this, _1, _2);
		this->funMap["inr"] = bind(&Instructions::inr, this, _1, _2);
	}

};
