#pragma once

/*
	For reference check out https://www.daenotes.com/electronics/digital-electronics/instruction-set-intel-8085
*/

#include<functional>
#include<string>
#include<map>
#include"Register.h"
#include "functions.h"
#include "Constants.h"
#include "Error.h"
#include "datatypes.h"
#include <iso646.h>

using namespace std;
using namespace std::placeholders;


class Instructions : public Register, public Error, public Constants
{

	/*
		These are the Helping functions for the instructions.
		They help to minimise the code as much as possible
	*/

	int rpValueOut(string rp)
	{
		if (rp == "b")
			return (reg["b"].toInt() << 8) + reg["c"].toInt();
		if (rp == "d")
			return (reg["d"].toInt() << 8) + reg["e"].toInt();
		if (rp == "m")
			return (reg["h"].toInt() << 8) + reg["l"].toInt();
	}

	bool rpValueIn(string rp, int value)
	{
		if (rp == "b")
		{
			reg["c"] = value % 256;
			reg["b"] = value / 256;
			return true;
		}
		if (rp == "d")
		{
			reg["e"] = value % 256;
			reg["d"] = value / 256;
			return true;
		}
		if (rp == "h")
		{
			reg["l"] = value % 256;
			reg["h"] = value / 256;
			return true;
		}

		cout << INVALID_REG_PAIR;
		return false;
	}

	bool checkRP(string rp)
	{
		if(rp == "b" || rp == "d" || rp == "h")
			return true;
		else
		{
			cout << INVALID_REG_PAIR;
			return false;
		}
	}

	bool checkReg(string dest, string src, int bit)
	{
		if (dest.empty())
		{
			if ((bit == 8 and reg.count(src)) or (reg16.count(src) and bit == 16))
				return true;
			else
			{
				cout << INVALID_REG << "here";
				return false;
			}
		}
		else
		{
			if ((bit == 8 and reg.count(dest) and reg.count(src)) or (
				    bit == 16 and reg16.count(dest) and reg16.count(src)))
				return true;
			else
			{
				cout << INVALID_REG;
				return false;
			}
		}
	}

	bool checkAddr(function<bool()> const& lamda, vector<_Bit16> vec_bit16, string type_addr)
	{
		bool isFound = true;

		for (auto i = vec_bit16.begin(); i != vec_bit16.end(); i++)
			if (!memory.count(*i))
			{
				isFound = false;
				break;
			}
			
		
		
		if ((isFound || type_addr == "d") and memory.size() <= 2)
		{
			if (vec_bit16[0] > 4095) { return lamda(); }

			cout << MEMORY_ACCESS_DENIED;
			return false;
		}

		cout << INVALID_MEMORY;
		return false;
	}

	bool checkParams(string dest, string src, int n) const
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

	bool checkHex(int dec, int bit) const
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
		These are the Custom Instructions to help the programmer
		look into the value of memory, register, and Label map
	*/

	bool hlp(string dest, string src)
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
				value = rpValueOut("m");

			cout << toUpperCase(src) << '=' << value << endl;
		}
		else
		{
			if (reg16.count(src))
				cout << toUpperCase(src) << "=" << reg[src] << endl;
			else
			{
				cout << INVALID_REG;
				return false;
			}
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

		if (checkReg(dest, src, 8))
		{
			if (src == "m")
			{
				return checkAddr([this, dest]() -> bool
				{
					reg[dest] = memory[rpValueOut("m")];
					return true;
				}, { rpValueOut("m") }, "s");
			}
			if (dest == "m")
			{
				return checkAddr([this, src]() -> bool
				{
					memory[rpValueOut("m")] = reg[src];
					return true;
				}, { rpValueOut("m") }, "d");
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

		if (checkReg("", dest, 8))
		{
			int dec = hexToDec(src);
			if (checkHex(dec, 8))
			{
				if (dest == "m")
				{
					return checkAddr([this, dec]() -> bool
					{
						memory[rpValueOut("m")] = dec;
						return true;
					}, { rpValueOut("m") }, "d");
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

	bool lda(string dest, string src)
	{
		if(!checkParams(dest,src,1))
			return false;

		int dec = hexToDec(src);

		if (!checkHex(dec, 16))
			return false;

		return checkAddr([this, dec]()->bool
		{
			reg["a"] = memory[dec];
			return true;

		}, { dec }, "s");

		
	}

	bool sta(string dest, string src)
	{
		if (!checkParams(dest, src, 1))
			return false;

		int dec = hexToDec(src);

		if (!checkHex(dec, 16))
			return false;

		return checkAddr([this, dec]()->bool
		{
			memory[dec] = reg["a"];
			return true;

		}, { dec }, "d");


	}

	bool lxi(string dest, string src)
	{
		if (!checkParams(dest, src, 2))
			return false;

		if (reg.count(dest))
		{
			int dec = hexToDec(src);
			if (!checkHex(dec, 16))
				return false;

			rpValueIn(dest, dec);
			return true;
		}
		return false;
	}

	bool lhld(string dest, string src)
	{
		if (!checkParams(dest, src, 1))
			return false;

		int dec = hexToDec(src);

		if (!checkHex(dec, 16))
			return false;

		return checkAddr([this, dec]()->bool
		{
			reg["l"] = memory[dec];
			reg["h"] = memory[dec + 1];
			return true;

		}, {dec, dec + 1}, "s");

	}

	bool shld(string dest, string src)
	{
		if (!checkParams(dest, src, 1))
			return false;

		int dec = hexToDec(src);

		if (!checkHex(dec, 16))
			return false;

		return checkAddr([this, dec]()->bool
		{
			memory[dec] = reg["l"];
			memory[dec + 1] = reg["h"] ;
			return true;

		}, {dec}, "d");

	}

	bool ldax(string dest, string src)
	{
		if (!checkParams(dest, src, 1))
			return false;

		if (checkRP(src))
		{
			return checkAddr([this, src]()->bool
			{
				reg["a"] = memory[rpValueOut(src)];
				return true;
			}, { rpValueOut(src) }, "d");
		}
		else { return false; }

	}

	bool stax(string dest, string src)
	{
		if (!checkParams(dest, src, 1))
			return false;

		if(checkRP(src))
		{
			return checkAddr([this,src]()->bool
			{
				memory[rpValueOut(src)] = reg["a"];
				return true;
			}, {rpValueOut(src)}, "d");
		}
		else { return false; }
		
	}

	bool xchg(string dest, string src)
	{
		if (!checkParams(dest, src, 0))
			return false;

		_Bit8 tempH = reg["h"];
		_Bit8 tempL = reg["l"];

		reg["h"] = reg["d"];
		reg["l"] = reg["e"];

		reg["d"] = tempH;
		reg["e"] = tempL;

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

		if (reg.count(src))
		{
			if (src == "m")
				return checkAddr([this,src]()-> bool
				{
					reg["a"] += memory[rpValueOut("m")];
					flags[ZERO_BIT] = reg["a"] == 0 ? true : false;

					return true;
			}, { rpValueOut("m") }, "s");

			reg["a"] += reg.at(src);
			return true;
		}
		else
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
		{
			reg["a"] += dec;
			flags[ZERO_BIT] = reg["a"] == 0 ? true : false;
		}
		else
			return false;

		return true;
	}

	bool sub(string dest, string src)
	{
		if (!checkParams(dest, src, 1))
			return false;

		if (reg.count(src))
		{
			if (src == "m")
				return checkAddr([this, src]()-> bool
				{
					reg["a"] -= memory[rpValueOut("m")];
					flags[ZERO_BIT] = reg["a"] == 0 ? true : false;

					return true;
			}, { rpValueOut("m") }, "s");

			reg["a"] -= reg.at(src);
			return true;
		}
		else
		{
			cout << INVALID_REG;
			return false;
		}
	}

	bool sui(string dest, string src)
	{
		if (!checkParams(dest, src, 1))
			return false;

		int dec = hexToDec(src);

		if (checkHex(dec, 8))
		{
			reg["a"] -= dec;
			flags[ZERO_BIT] = reg["a"] == 0 ? true : false;
		}
		else
			return false;

		return true;
	}

	bool inr(string dest, string src)
	{
		if (!checkParams(dest, src, 1))
			return false;
		if (checkReg(dest, src, 8))
		{
			reg[src] += 1;
			flags[ZERO_BIT] = reg["a"] == 0 ? true : false;
		}
		else
			return false;

		return true;
	}

	/*
	 *	These are the Logical Group of Instructions
	 *	which manipulate the data using Bitwise operators
	 */

	bool ana(string dest, string src)
	{
		if (!checkParams(dest, src, 1))
			return false;

		if (reg.count(src))
		{
			if (src == "m")
				return checkAddr([this, src]() -> bool
				{
					reg["a"] &= memory[rpValueOut("m")];
					return true;
			}, { rpValueOut("m") }, "s");

			reg["a"] &= reg[src];
		}
		else
		{
			cout << INVALID_REG;
			return false;
		}

		return true;
	}

	bool ani(string dest, string src)
	{
		if (!checkParams(dest, src, 1))
			return false;

		int dec = hexToDec(src);

		if (checkHex(dec, 8))
			reg["a"] &= dec;
		else
			return false;

		return true;
	}

	bool ora(string dest, string src)
	{
		if (!checkParams(dest, src, 1))
			return false;

		if (reg.count(src))
		{
			if (src == "m")
				return checkAddr([this, src]() -> bool
				{
					reg["a"] |= memory[rpValueOut("m")];
					return true;
			}, { rpValueOut("m") }, "s");

			reg["a"] |= reg[src];
		}
		else
		{
			cout << INVALID_REG;
			return false;
		}

		return true;
	}

	bool ori(string dest, string src)
	{
		if (!checkParams(dest, src, 1))
			return false;

		int dec = hexToDec(src);

		if (checkHex(dec, 8))
			reg["a"] |= dec;
		else
			return false;

		return true;
	}

	bool xra(string dest, string src)
	{
		if (!checkParams(dest, src, 1))
			return false;

		if (reg.count(src))
		{
			if (src == "m")
				return checkAddr([this, src]() -> bool
				{
					reg["a"] ^= memory[rpValueOut("m")];
					return true;
			}, { rpValueOut("m") }, "s");

			reg["a"] ^= reg[src].toInt();
		}
		else
		{
			cout << INVALID_REG;
			return false;
		}

		return true;
	}

	bool xri(string dest, string src)
	{
		if (!checkParams(dest, src, 1))
			return false;

		int dec = hexToDec(src);

		if (checkHex(dec, 8))
			reg["a"] ^= dec;
		else
			return false;

		return true;
	}

	/*
	 *	These are the I/O and Machine Control Group of Instructions
	 *	which are used for input/output ports, stack and machine control.
	 */

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
		this->funMap["hlp"] = bind(&Instructions::hlp, this, _1, _2);
		
		//Data Transfer Instructions
		this->funMap["mvi"] = bind(&Instructions::mvi, this, _1, _2);
		this->funMap["mov"] = bind(&Instructions::mov, this, _1, _2);
		this->funMap["lda"] = bind(&Instructions::lda, this, _1, _2);
		this->funMap["sta"] = bind(&Instructions::sta, this, _1, _2);
		this->funMap["lxi"] = bind(&Instructions::lxi, this, _1, _2);
		this->funMap["lhld"] = bind(&Instructions::lhld, this, _1, _2);
		this->funMap["shld"] = bind(&Instructions::shld, this, _1, _2);
		this->funMap["ldax"] = bind(&Instructions::ldax, this, _1, _2);
		this->funMap["stad"] = bind(&Instructions::stax, this, _1, _2);
		this->funMap["xchg"] = bind(&Instructions::xchg, this, _1, _2);

		//Arithmetic Instructions
		this->funMap["add"] = bind(&Instructions::add, this, _1, _2);
		this->funMap["adi"] = bind(&Instructions::adi, this, _1, _2);
		this->funMap["sub"] = bind(&Instructions::sub, this, _1, _2);
		this->funMap["sui"] = bind(&Instructions::sui, this, _1, _2);
		this->funMap["inr"] = bind(&Instructions::inr, this, _1, _2);

		//Logical Instructions
		this->funMap["ana"] = bind(&Instructions::ana, this, _1, _2);
		this->funMap["ani"] = bind(&Instructions::ani, this, _1, _2);
		this->funMap["ora"] = bind(&Instructions::ora, this, _1, _2);
		this->funMap["ori"] = bind(&Instructions::ori, this, _1, _2);
		this->funMap["xra"] = bind(&Instructions::xra, this, _1, _2);
		this->funMap["xri"] = bind(&Instructions::xri, this, _1, _2);

		//Branch Control Instructions

		//I/O and Machine Control Instructions
		this->funMap["hlt"] = bind(&Instructions::hlt, this, _1, _2);
	}
};
