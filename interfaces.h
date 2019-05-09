#pragma once
class executeClass
{
public:
	virtual void execute() = 0;
};

class saveClass 
{
public:
	virtual executeClass* save(Label, vector<string>) = 0;
};

