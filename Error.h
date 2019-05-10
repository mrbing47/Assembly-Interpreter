#pragma once

class Error
{
public:
	const string DUPLICATE_LABEL = "\nERROR: DUPLICATE_LABEL\n\n";
	const string INVALID_REG = "\nERROR: INVALID_REGISTER\n\n";
	const string INVALID_PARAMS_MORE = "\nERROR: INVALID_PARAMETERS, too many arguments\n\n";
	const string INVALID_PARAMS_FEW = "\nERROR: INVALID PARAMETER, few number of arguments\n\n";
	const string INVALID_HEX = "\nINVALID_HEX\n\n";
	const string INVALID_HEX_8 = "\nINVALID_HEX_8_BIT_NUMBER\n\n";
	const string INVALID_HEX_16 = "\nINVALID_HEX_16_BIT_NUMBER\n\n";
	const string INVALID_INST = "\nERROR: INVALID_INSTRUCTION\n\n";
};

