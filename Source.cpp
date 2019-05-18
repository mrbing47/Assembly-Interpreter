#include<iostream>
#include<functional>
#include <vector>
#include<string>
#include<conio.h>

#include "Compiler.h"
#include "functions.h"

using namespace std;

int main()
{
	string input = "";

	CompilerProcess* compiler = Compiler::create();

	bool isHLT = false;
	do
	{
		getline(cin, input);

		isHLT = compiler
		        ->process(input)
		        ->save()
		        ->execute();
	}
	while (!isHLT);

	while (_getch() != 13);
	return 0;
}
