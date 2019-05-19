#pragma once
using namespace std;

class Constants
{
public:

	const string LABEL_SPLIT_ARGS = ":";
	const string INST_SPLIT_ARGS = " ,";
	const string MAP_OPCODE = "opcode";
	const string MAP_SRC = "src";
	const string MAP_DEST = "dest";
	const string ADDITION = "addition";
	const string SUBTRACTION = "subtraction";
	const string LOOP_STARTED = "\nProgram is in loop, please wait while it finishes...\n\n";
	const string LOOP_ENDED = "\nLoop has ended.\n\n";
	const string INSIDE_SUB = "\nProgram is inside ";
	const string RETURN_SUB = "\nProgram is returning from ";
	const vector<string> MAP_PARAMS{ MAP_OPCODE,MAP_DEST,MAP_SRC };
	
	const int SIGN_BIT = 7;
	const int ZERO_BIT = 6;
	const int AUX_CARRY_BIT = 4;
	const int PARITY_BIT = 2;
	const int CARRY_BIT = 0;
};

