#include "b17.h"

/************************************************************************
Function: void split_instruction(string instruction,string &hex, string &lastThree)
Author: Andrew Housh
Description: takes a string and splits it into two separate strings
Parameters: string instruction - in - string representation of a hex instruction
			string &hex - out - string representation first 3 hex digits
			string &lastThree - out - string representation of last 3 hex digits
************************************************************************/
void split_instruction( string instruction, string &hex, string &lastThree ) {

    hex = instruction.substr( 0, 3 );
    lastThree = instruction.substr( 3, 3 );

}

/************************************************************************
Function: void get_op_and_am(string lastThree, string &opcode, string &addressMode)
Author: Andrew Housh
Description: changes 3 digit hex opcode to binary then splits into the operator and
				the address mode.
Parameters: string lastThree - in - string representation of hex opcode
string &opcode - out - string representation of binary operator code
string &addressMode - out - string representation of binary address mode code
************************************************************************/
void get_op_and_am( string lastThree, string &opcode, string &addressMode ) {

    lastThree = hex_to_bin( lastThree );
    opcode = lastThree.substr( 0, 6 );
    addressMode = lastThree.substr( 6, 4 );

}
