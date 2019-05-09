#include<iostream>
#include<vector>
#include<string>
#include<conio.h>

#include "Compiler.h"
#include "Register.h"
#include "typedefs.h"
#include "functions.h"
#include "Constants.h"
#include "datatypes.h"

using namespace std;

int main() 
{

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

	cout << "Press ENTER to exit";
	while (_getch() != 13);
	return 0;

}