#pragma once

/*
	Check out https://www.daenotes.com/electronics/digital-electronics/instruction-set-intel-8085
	for the reference for these instructions
*/

#include<functional>
#include<string>
#include<map>
#include"Register.h"
#include "functions.h"
#include "Constants.h"
#include "Error.h"
#include "Compiler.h"
#include "datatypes.h"

using namespace std;
using namespace std::placeholders;


class Instructions : public Register, public Error, public Constants
{

	/*
		These are the Helping functions for the instructions.
		They help to minimise the code as much as possible
	*/

	int mValueOut()
	{
		return (reg["h"].toInt() << 8) + reg["l"].toInt();
	}

	void mValueIn(string value)
	{

	}

	bool checkReg(string dest, string src)
	{
		if (dest == "")
		{
			if (reg.count(src))
				return true;
			else
			{
				cout << INVALID_REG;
				return false;
			}
		}
		else
		{
			if (reg.count(dest) && reg.count(src))
				return true;
			else
			{
				cout << INVALID_REG;
				return false;
			}
		}
	}

	bool checkmAddr(function<bool()> const &lamda, string reg)
	{
		if (memory.count(mValueOut()) || reg == "d")
		{
			if (mValueOut() >= 4095)
			{
				return lamda();
			}
			else
			{
				cout << MEMORY_ACCESS_DENIED;
				return false;
			}
		}
		else
		{
			cout << INVALID_MEMORY_ACCESS;
			return false;
		}

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

	/*
		These are the Custom Intsructions to help the programmer
		look into the value of memory, register, and Label map
	*/

	bool help(string dest, string src)
	{
		if (!checkParams(dest, src, 0))
			return false;

		cout << endl;

		for (auto i = funMap.begin(); i != funMap.end(); i++)
			cout << i->first << endl;

		cout << endl;
		return false;
	}

	bool htd(string dest, string src)
	{
		if (!checkParams(dest, src, 1))
			return false;

		int dec = hexToDec(src);

		if (checkHex(dec, 16))
			cout << dec << endl;

		return false;
	}

	bool shw(string dest, string src)
	{
		if (!checkParams(dest, src, 1))
			return false;

		if (reg.count(src))
		{
			int value = reg[src].toInt();

			if (src == "m")
				value = mValueOut();

			cout << toUpperCase(src) << '=' << value << endl;
		}
		else
		{
			if (reg16.count(src))
				cout << toUpperCase(src) << "=" << reg[src] << endl;
			else
				return false;
		}
		return true;

	}
	bool shl(string dest, string src)
	{
		if (!checkParams(dest, src, 0))
			return false;

		for (auto i = labelMap.begin(); i != labelMap.end(); i++)
		{
			_Label label = i->first;
			cout << toUpperCase(label.toString()) << '\t' << i->second << endl;
		}

		return true;
	}

	bool shm(string dest, string src)
	{
		if (!checkParams(dest, src, 0))
			return false;

		for (auto i = memory.begin(); i != memory.end(); i++)
			cout << i->first << '\t' << i->second << endl;

		return true;
	}

	/*
		These are the Data Transfer Group of Instructions
		which are used to transfer data from register to register
		or from memory to memory and vice versa
	*/

	bool mov(string dest, string src)
	{
		if (!checkParams(dest, src, 2))
			return false;

		if (checkReg(dest, src))
		{
			if (src == "m")
			{
				return checkmAddr([this, dest]() -> bool
				{
					reg[dest] = memory[mValueOut()];
					return true;
				}, "s");
			}
			if (dest == "m")
			{
				return checkmAddr([this, src]() -> bool
				{
					memory[mValueOut()] = reg[src];
					return true;
				}, "d");
			}
			reg[dest] = reg[src];
		}
		else
			return false;


		return true;
	}

	bool mvi(string dest, string src)
	{
		if (!checkParams(dest, src, 2))
			return false;

		if (checkReg(dest, ""))
		{
			int dec = hexToDec(src);
			if (checkHex(dec, 8))
			{
				if (dest == "m")
				{
					return checkmAddr([this, dec]() -> bool
					{
						memory[mValueOut()] = dec;
						return true;
					}
					, "d");
				}
				reg[dest] = dec;
			}
			else
				return false;
		}
		else
			return false;

		return true;

	}

	/*
		These are the  Arithmetic Group of Instructions
		which manipulate the data in the registers 
		and the memory
	*/

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


	
	bool hlt(string dest, string src)
	{
		if (!checkParams(dest, src, 0))
			return false;

		cout << "\nPress ENTER to exit";

		return true;
	}

public:

	map<string, function<bool(string, string)>> funMap;

	Instructions()
	{
		//Custom Instructions
		this->funMap["shw"] = bind(&Instructions::shw, this, _1, _2);
		this->funMap["shm"] = bind(&Instructions::shm, this, _1, _2);
		this->funMap["shl"] = bind(&Instructions::shl, this, _1, _2);
		this->funMap["htd"] = bind(&Instructions::htd, this, _1, _2);
		this->funMap["help"] = bind(&Instructions::help, this, _1, _2);
		
		//Data Transfer Instructions
		this->funMap["mvi"] = bind(&Instructions::mvi, this, _1, _2);
		this->funMap["mov"] = bind(&Instructions::mov, this, _1, _2);

		//Arithmetic Instructions
		this->funMap["add"] = bind(&Instructions::add, this, _1, _2);
		this->funMap["adi"] = bind(&Instructions::adi, this, _1, _2);
		this->funMap["inr"] = bind(&Instructions::inr, this, _1, _2);

		//Logical Instructions

		//Branch Control Instructions

		//I/O and Machine Control Instructions
		this->funMap["hlt"] = bind(&Instructions::hlt, this, _1, _2);

	}


};
