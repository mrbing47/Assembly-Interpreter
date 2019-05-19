#pragma once

class Error
{
public:
	const string DUPLICATE_LABEL = "\nERROR: DUPLICATE_LABEL\n\n";
	const string INVALID_LABEL = "\nERROR: INVALID_LABEL\n\n";
	const string INVALID_REG = "\nERROR: INVALID_REGISTER\n\n";
	const string INVALID_REG_PAIR = "\nERROR: INVALID_REGISTER_PAIR\n\n";
	const string INVALID_PARAMS_MORE = "\nERROR: INVALID_PARAMETERS, too many arguments\n\n";
	const string INVALID_PARAMS_FEW = "\nERROR: INVALID_PARAMETERS, few number of arguments\n\n";
	const string INVALID_HEX = "\nINVALID_HEX\n\n";
	const string INVALID_HEX_8 = "\nINVALID_HEX_8_BIT_NUMBER\n\n";
	const string INVALID_HEX_16 = "\nINVALID_HEX_16_BIT_NUMBER\n\n";
	const string INVALID_INST = "\nERROR: INVALID_INSTRUCTION\n\n";
	const string INVALID_MEMORY = "\nERROR: INVALID_MEMORY\n\n";
	const string MEMORY_ACCESS_DENIED = "\nERROR: MEMORY_ACCESS_DENIED\n\n";
	const string INFINITE_LOOP = "\nERROR: INFINITE_LOOP, cannot jump to the same line.\n\n";
	const string INVALID_CALL = "\nERROR: INVALID_CALL, only use CALL for subroutine.\n\n";
};

