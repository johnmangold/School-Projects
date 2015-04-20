/*

  INSTEAD OF CREATING A FUNCTION TO CONVERT HEX TO DEC, I FOUND A WAY TO AVOID ALL THAT.
  THE FOLLOWING WILL CONVERT A HEX STRING TO AN INT. FOR EXAMPLE, IF STRING HEX IS 1FF,
  THEN X WILL BE 511. MAKE SURE YOU ADD THE #INCLUDE

#include <sstream>

    string hex;
    int x;

    std::stringstream hextodec;
    hextodec << std::hex << hex;
    hextodec >> x;

*/
#include "b17.h"

string hex_to_bin( string hex ) {
    string bin;

    for( auto i : hex ) {
        i == '0' ? bin.append( "0000" ) : "0";
        i == '1' ? bin.append( "0001" ) : "0";
        i == '2' ? bin.append( "0010" ) : "0";
        i == '3' ? bin.append( "0011" ) : "0";
        i == '4' ? bin.append( "0100" ) : "0";
        i == '5' ? bin.append( "0101" ) : "0";
        i == '6' ? bin.append( "0110" ) : "0";
        i == '7' ? bin.append( "0111" ) : "0";
        i == '8' ? bin.append( "1000" ) : "0";
        i == '9' ? bin.append( "1001" ) : "0";
        i == 'a' ? bin.append( "1010" ) : "0";
        i == 'b' ? bin.append( "1011" ) : "0";
        i == 'c' ? bin.append( "1100" ) : "0";
        i == 'd' ? bin.append( "1101" ) : "0";
        i == 'e' ? bin.append( "1110" ) : "0";
        i == 'f' ? bin.append( "1111" ) : "0";
    }  //end of for loop

    return bin;
}


string bin_to_hex( string bin ) {
    string temp;
    string hex;

    for( unsigned int i = 0; i < bin.size( ); i+=4 ) {
        temp = bin.substr( i, 4 );

        temp == "0000" ? hex.append( "0" ) : "0";
        temp == "0001" ? hex.append( "1" ) : "0";
        temp == "0010" ? hex.append( "2" ) : "0";
        temp == "0011" ? hex.append( "3" ) : "0";
        temp == "0100" ? hex.append( "4" ) : "0";
        temp == "0101" ? hex.append( "5" ) : "0";
        temp == "0110" ? hex.append( "6" ) : "0";
        temp == "0111" ? hex.append( "7" ) : "0";
        temp == "1000" ? hex.append( "8" ) : "0";
        temp == "1001" ? hex.append( "9" ) : "0";
        temp == "1010" ? hex.append( "a" ) : "0";
        temp == "1011" ? hex.append( "b" ) : "0";
        temp == "1100" ? hex.append( "c" ) : "0";
        temp == "1101" ? hex.append( "d" ) : "0";
        temp == "1110" ? hex.append( "e" ) : "0";
        temp == "1111" ? hex.append( "f" ) : "0";
    }  //end of for loop

    return hex;
}
