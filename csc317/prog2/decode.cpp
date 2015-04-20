#include "b17.h"

void split_instruction( string instruction, string &hex, string &lastThree ) {

    hex = instruction.substr( 0, 3 );
    lastThree = instruction.substr( 3, 3 );

}

void get_op_and_am( string lastThree, string &opcode, string &addressMode ) {

    lastThree = hex_to_bin( lastThree );
    opcode = lastThree.substr( 0, 6 );
    addressMode = lastThree.substr( 6, 4 );

}
