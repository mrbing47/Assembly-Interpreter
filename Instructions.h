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

	void alter_flags(_Bit8 num1, _Bit8 num2,int res_value, string type_op)
	{
		if (type_op == ADDITION)
		{
			int temp = (num1.toInt() & 15) + (num2.toInt() & 15);

			flags[AUX_CARRY_BIT] = ((int)log2(temp) + 1) > 4 ? true : false;

			flags[CARRY_BIT] = res_value > 255 ? true : false;
		}
		if(type_op == SUBTRACTION)
		{
			flags[CARRY_BIT] = num1 < num2 ? true : false;
		}

		flags[ZERO_BIT] = res_value % 256 == 0 ? true : false;
	}

	int rpValueOut(string rp)
	{
		if (rp == "b")
			return (reg["b"].toInt() << 8) + reg["c"].toInt();
		if (rp == "d")
			return (reg["d"].toInt() << 8) + reg["e"].toInt();
		if (rp == "m")
			return (reg["h"].toInt() << 8) + reg["l"].toInt();

		return 0;
	}

	bool rpValueIn(string rp, _Bit16 value)
	{
		if (rp == "b")
		{
			reg["c"] = value.toInt() % 256;
			reg["b"] = value.toInt() / 256;
			return true;
		}
		if (rp == "d")
		{
			reg["e"] = value.toInt() % 256;
			reg["d"] = value.toInt() / 256;
			return true;
		}
		if (rp == "h")
		{
			reg["l"] = value.toInt() % 256;
			reg["h"] = value.toInt() / 256;
			return true;
		}

		cout << INVALID_REG_PAIR;
		return false;
	}

	bool checkRP(string rp)
	{
		if (rp == "b" || rp == "d" || rp == "h")
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
			if ((bit == 8 and reg.count(src)) or (bit == 16 and reg16.count(src)))
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

	bool checkAddr(vector<_Bit16> vec_bit16, string type_addr)
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
			if (vec_bit16[0] > 4095) { return true; }

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

	bool shf(string dest, string src)
	{
		for (int i = 7; i >= 0; i--)
		{
			if(i == 7)
				cout<<"SIGN_BIT=";
			if (i == 6)
				cout << "ZERO_BIT=";
			if (i == 4)
				cout << "AUX_CARRY_BIT=";
			if (i == 2)
				cout << "PARITY_BIT=";
			if (i == 0)
				cout << "CARRY_BIT=";
			if (i == 1 or i == 3 or i == 5)
				continue;
			cout << (int)flags[i] << '\n';
		}

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
				if (checkAddr({ rpValueOut("m") }, "s"))
				{
					reg[dest] = memory[rpValueOut("m")];
					return true;
				}
				else { return false; }
			}
			if (dest == "m")
			{
				if (checkAddr({ rpValueOut("m") }, "d"))
				{
					memory[rpValueOut("m")] = reg[src];
					return true;
				}
				else { return false; }
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
					if (checkAddr({ rpValueOut("m") }, "d"))
					{
						memory[rpValueOut("m")] = dec;
						return true;
					}
					else { return false; }
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
		if (!checkParams(dest, src, 1))
			return false;

		int dec = hexToDec(src);

		if (!checkHex(dec, 16))
			return false;

		if (checkAddr({ dec }, "s"))
		{
			reg["a"] = memory[dec];
			return true;
		}
		else { return false; }
	}

	bool sta(string dest, string src)
	{
		if (!checkParams(dest, src, 1))
			return false;

		int dec = hexToDec(src);

		if (!checkHex(dec, 16))
			return false;

		if (checkAddr({ dec }, "d"))
		{
			memory[dec] = reg["a"];
			return true;
		}
		else { return false; }
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

		if (checkAddr({ dec, dec + 1 }, "s"))
		{
			reg["l"] = memory[dec];
			reg["h"] = memory[dec + 1];
			return true;
		}
		else { return false; }
	}

	bool shld(string dest, string src)
	{
		if (!checkParams(dest, src, 1))
			return false;

		int dec = hexToDec(src);

		if (!checkHex(dec, 16))
			return false;

		if (checkAddr({ dec }, "d"))
		{
			memory[dec] = reg["l"];
			memory[dec + 1] = reg["h"];
			return true;
		}
		else { return false; }
	}

	bool ldax(string dest, string src)
	{
		if (!checkParams(dest, src, 1))
			return false;

		if (checkRP(src))
		{
			if (checkAddr({ rpValueOut(src) }, "d"))
			{
				reg["a"] = memory[rpValueOut(src)];
				return true;
			}
			else { return false; }
		}
		else { return false; }
	}

	bool stax(string dest, string src)
	{
		if (!checkParams(dest, src, 1))
			return false;

		if (checkRP(src))
		{
			if (checkAddr({ rpValueOut(src) }, "d"))
			{
				memory[rpValueOut(src)] = reg["a"];
				return true;
			}
			else { return false; }
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
			int reg_value;
			if (src == "m")
			{
				if (checkAddr({ rpValueOut("m") }, "s"))
				{
					reg_value = memory[rpValueOut("m")].toInt();
				}
				else { return false; }
			}
			else
				reg_value = reg[src].toInt();

			alter_flags(reg["a"], reg_value,reg_value + reg["a"].toInt(),ADDITION);

			reg["a"] += reg_value;
			return true;
		}
		else
		{
			cout << INVALID_REG;
			return false;
		}
	}

	bool adc(string dest, string src)
	{
		if (!checkParams(dest, src, 1))
			return false;

		if (checkReg(dest, src, 8))
		{
			int res_value;
			int reg_value;

			if (src == "m")
			{
				if (checkAddr({ rpValueOut("m") }, "s"))
					reg_value = memory[rpValueOut("m")].toInt();
				else
					return false;
			}
			else
				reg_value = reg[src].toInt();

			res_value = reg["a"].toInt() + reg_value;

			alter_flags(reg["a"], reg_value, res_value,ADDITION);

			reg["a"] = res_value + (int)flags[CARRY_BIT];

			if (reg["a"] == 0)
				flags[ZERO_BIT] = true;
			else
				flags[ZERO_BIT] = false;

			return true;
		}
		else { return false; }
	}

	bool aci(string dest, string src)
	{
		if (!checkParams(dest, src, 1))
			return false;

		if (checkReg(dest, src, 8))
		{
			int res_value;
			int dec = hexToDec(src);

			if (checkHex(dec, 8))
			{
				res_value = reg["a"].toInt() + dec;

				alter_flags(reg["a"], dec, res_value, ADDITION);

				reg["a"] = res_value + (int)flags[CARRY_BIT];

				alter_flags(reg["a"], dec, reg["a"].toInt() + dec, ADDITION);

				return true;
			}
			else
				return false;
		}
		else { return false; }
	}

	bool adi(string dest, string src)
	{
		if (!checkParams(dest, src, 1))
			return false;

		int dec = hexToDec(src);

		if (checkHex(dec, 8))
		{
			alter_flags(reg["a"], dec, reg["a"].toInt() + dec,ADDITION);
			reg["a"] += dec;
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
			{
				if (checkAddr({ rpValueOut("m") }, "s"))
				{
					reg["a"] -= memory[rpValueOut("m")];
					flags[ZERO_BIT] = reg["a"] == 0 ? true : false;

					return true;
				}
				else { return false; }
			}

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
			alter_flags(reg["a"], dec, reg["a"].toInt() - dec, SUBTRACTION);
			reg["a"] -= dec;
		}
		else
			return false;

		return true;
	}

	bool sbb(string dest, string src)
	{
		if (!checkParams(dest, src, 1))
			return false;

		if (reg.count(src))
		{
			if (src == "m")
			{
				if (checkAddr({ rpValueOut("m") }, "s"))
				{
					reg["a"] -= memory[rpValueOut("m")];
					flags[ZERO_BIT] = reg["a"] == 0 ? true : false;

					return true;
				}
				else { return false; }
			}

			reg["a"] -= reg.at(src);
			return true;
		}
		else
		{
			cout << INVALID_REG;
			return false;
		}
	}

	bool inr(string dest, string src)
	{
		if (!checkParams(dest, src, 1))
			return false;
		if (checkReg(dest, src, 8))
		{
			alter_flags(reg[src], 1, reg[src].toInt() + 1,ADDITION);
			reg[src] += 1;
		}
		else
			return false;

		return true;
	}
	bool dcr(string dest, string src)
	{
		if (!checkParams(dest, src, 1))
			return false;
		if (checkReg(dest, src, 8))
		{
			alter_flags(reg[src], 1, reg[src].toInt() - 1, SUBTRACTION);
			reg[src] -= 1;
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
			{
				if (checkAddr({ rpValueOut("m") }, "s"))
				{
					reg["a"] &= memory[rpValueOut("m")];
					return true;
				}
				else { return false; }
			}

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
			{
				if (checkAddr({ rpValueOut("m") }, "s"))
				{
					reg["a"] |= memory[rpValueOut("m")];
					return true;
				}
				else { return false; }
			}

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
			{
				if (checkAddr({ rpValueOut("m") }, "s"))
				{
					reg["a"] ^= memory[rpValueOut("m")];
					return true;
				}
				else { return false; }
			}

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

	bool cma(string dest, string src)
	{
		if (!checkParams(dest, src, 0))
			return false;

		reg["a"] = ~reg["a"].toInt() & 0xff;
		return true;
	}

	bool cmc(string dest, string src)
	{
		if (!checkParams(dest, src, 0))
			return false;

		flags[CARRY_BIT] = !flags[CARRY_BIT];
		return true;
	}

	bool stc(string dest, string src)
	{
		if(!checkParams(dest,src,0))
			return false;

		flags[CARRY_BIT] = true;
		return true;
	}

	bool rlc(string dest, string src)
	{
		if(!checkParams(dest,src,0))
			return false;

		flags[CARRY_BIT] = (bool)((reg["a"].toInt() >> 7) & 1);
		reg["a"] = reg["a"].toInt() << 1;
		reg["a"] |= flags[CARRY_BIT];
		return true;
	}

	bool rrc(string dest, string src)
	{
		if (!checkParams(dest, src, 0))
			return false;

		flags[CARRY_BIT] = (bool)(reg["a"].toInt() & 1);
		reg["a"] = reg["a"].toInt() >> 1;
		reg["a"] |= flags[CARRY_BIT] << 7;
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
		this->funMap["shf"] = bind(&Instructions::shf, this, _1, _2);
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
		this->funMap["stax"] = bind(&Instructions::stax, this, _1, _2);
		this->funMap["xchg"] = bind(&Instructions::xchg, this, _1, _2);

		//Arithmetic Instructions
		/*this->funMap["add"] = bind(&Instructions::add, this, _1, _2);
		this->funMap["adi"] = bind(&Instructions::adi, this, _1, _2);
		this->funMap["sub"] = bind(&Instructions::sub, this, _1, _2);
		this->funMap["sui"] = bind(&Instructions::sui, this, _1, _2);
		this->funMap["inr"] = bind(&Instructions::inr, this, _1, _2);
		*/
		//Logical Instructions
		this->funMap["ana"] = bind(&Instructions::ana, this, _1, _2);
		this->funMap["ani"] = bind(&Instructions::ani, this, _1, _2);
		this->funMap["ora"] = bind(&Instructions::ora, this, _1, _2);
		this->funMap["ori"] = bind(&Instructions::ori, this, _1, _2);
		this->funMap["xra"] = bind(&Instructions::xra, this, _1, _2);
		this->funMap["xri"] = bind(&Instructions::xri, this, _1, _2);
		this->funMap["cma"] = bind(&Instructions::cma, this, _1, _2);
		this->funMap["stc"] = bind(&Instructions::stc, this, _1, _2);
		this->funMap["cmc"] = bind(&Instructions::cmc, this, _1, _2);
		this->funMap["rlc"] = bind(&Instructions::rlc, this, _1, _2);
		this->funMap["rrc"] = bind(&Instructions::rrc, this, _1, _2);

		//Branch Control Instructions

		//I/O and Machine Control Instructions
		this->funMap["hlt"] = bind(&Instructions::hlt, this, _1, _2);
	}
};
