#pragma once

#include<functional>

#include"Register.h"
#include "functions.h"
#include "datatypes.h"

using namespace std;

class Instructions : public Register
{
	map<string, function<int(string, string)>> inst;

public:
	
	

};
