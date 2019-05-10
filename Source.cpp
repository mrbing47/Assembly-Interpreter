#include<iostream>
#include<functional>
#include<vector>
#include<string>
#include<conio.h>

#include "Compiler.h"
#include "functions.h"
#include "datatypes.h"
#include "Instructions.h"
#include "Error.h"
#include "Instructions.h"

using namespace std;

int add(int a, int b)
{
	return a + b;
};

int main() 
{
	
	string input = "";
	
	saveClass *compiler = Compiler::create();

	bool isHLT = false;
	do {

		getline(cin,input);
		
		input = toLowerCase(trim(input));

		if (!input.empty())
		{

			if (strequal(input, "HLT"))
				isHLT = true;
			else
			{
				vector<string> inst = strsplit(input, ":");	

				compiler
					->save(inst.size() > 1 ? trim(inst[0]) : "",
						strsplit(inst[inst.size() - 1], " ,"))
					->execute();
			}
		}
		
	} while (!isHLT);
	
	cout << "\nPress ENTER to exit";
	while (_getch() != 13);
	return 0;

}
