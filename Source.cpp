#include<iostream>
#include<vector>
#include<string>
#include<conio.h>

#include "Compiler.h"
#include "functions.h"
#include "datatypes.h"
using namespace std;

int main() 
{
	_Bit16 b1;
	b1 = 2;
	if (b1 < 3)
		cout << "WOW";
	if (3 == b1)
		cout << "NICE";

	/*
	string input = "";
	

	bool isHLT = false;
	do {

		getline(cin,input);
		
		input = trim(input);

		if (!input.empty())
		{

			if (strequal(input, "HLT"))
				isHLT = true;
			else
			{
			
				vector<string> inst = strsplit(input, ":");
					
				Compiler::create()
					->save(inst.size() > 1 ? trim(inst[0]) : "",
						strsplit(inst[inst.size() - 1], " ,"))
					->execute();
			}
		}
		
	} while (!isHLT);
	*/

	cout << "\nPress ENTER to exit";
	while (_getch() != 13);
	return 0;

}