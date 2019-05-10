#pragma once

#include<functional>
#include<string>
#include<map>
#include"Register.h"
#include "functions.h"
#include "datatypes.h"

using namespace std;
using namespace std::placeholders;


typedef map<string, function<void(string, string)>> map_str_to_fun;

class Instructions : public Register
{
	

	void add(string dest, string src)
	{
		string str = dest + " " + src;
		cout << str;
		return;
	}

public:
	map_str_to_fun funMap;

	Instructions()
	{
		this->funMap["add"] = bind(&Instructions::add,this,_1,_2);
	}

	

	
};
