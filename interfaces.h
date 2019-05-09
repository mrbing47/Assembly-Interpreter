#pragma once

#include"datatypes.h"

class executeClass
{
public:
	virtual void execute() = 0;
};

class saveClass 
{
public:
	virtual executeClass* save(_Label, vector<string>) = 0;
};

