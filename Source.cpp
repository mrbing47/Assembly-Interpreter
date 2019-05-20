#include<iostream>
#include<functional>
#include <vector>
#include<string>
#include <conio.h>

#include "Compiler.h"

using namespace std;

int main()
{
	string input = "";
	
	CompilerProcess* compiler = Compiler::create();

	bool isHLT = false;
	do
	{
		getline(cin, input);

		compiler
		        ->process(input)
		        ->save()
		        ->execute();
	}
	while (true);
	return 0;
}
