#include<iostream>
#include<vector>
#include<string>
#include<conio.h>

#include "Compiler.h"
#include "Register.h"
#include "typedefs.h"
#include "functions.h"

using namespace std;

int main() 
{

	string input = "";
	string label = "";
	Compiler compiler;

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
				if (inst.size() > 1)
					label = trim(inst[0]);
				else
					label = "";

				compiler.execute(label, strsplit(inst[inst.size() - 1], " ,"));

			}
		}
		
	} while (!isHLT);

	/*cout << "\n\n\n";
	map<Label, Bit16> label = compiler.getLabel();
	map<Bit16, string> inputs = compiler.getInst();
	for (auto i = inputs.begin(); i != inputs.end(); i++)
	{
		cout << i->first << "\t" << i->second << endl;
	}
	cout << "\n\n\n";
	for (auto i = label.begin(); i != label.end(); i++)
	{
		cout << i->first << "\t" << i->second << endl;
	}
	*/
	/*vector<string> inst = strsplit("MOV A,B", ":");
	vector<string> str = strsplit(inst[inst.size() - 1], " ,");
	for (auto i = str.begin(); i != str.end(); i++)
	{
		cout << *i << '.' << endl;
	}*/
	while (_getch() != 13);
	return 0;

}

