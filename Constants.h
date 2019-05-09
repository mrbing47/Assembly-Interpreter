#pragma once
using namespace std;

class Constants
{
public:

	const string REG_A = "A";
	const string LABEL_SPLIT_ARGS = ":";
	const string INST_SPLIT_ARGS = " ,";
	const string MAP_OPCODE = "opcode";
	const string MAP_SRC = "src";
	const string MAP_DEST = "dest";
	const vector<string> MAP_PARAMS{ MAP_OPCODE,MAP_DEST,MAP_SRC };
	
};

