#pragma once

class CompilerExecute
{
public:
	virtual bool execute() = 0;
};

class CompilerSave
{
public:
	virtual CompilerExecute* save() = 0;
};

class CompilerProcess
{
public:
	virtual CompilerSave* process(string) = 0;
};