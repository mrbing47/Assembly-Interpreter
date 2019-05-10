#pragma once

#include<functional>
#include<string>
#include"Register.h"
#include "functions.h"
#include "datatypes.h"

using namespace std;


class Instructions : public Register
{
	typedef void(*fun)(string, string);
	map<string, fun> ptrMap;
	map<string, function<void(string,string)>> funMap;

public:
	
	void add(string dest, string src)
	{
		
	}

	Instructions()
	{
		this->funMap["add"] = &Instructions::add;
		this->ptrMap["add"] = &Instructions::add;
	}
	

	
};
