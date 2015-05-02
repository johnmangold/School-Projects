/************************************************************************
Program: Prog 2
Author: John Mangold, Andrew Housh, Jiasong Yan
Class: CSC317
Instructor: Dr. Krister Karlsson
Date: 1 May 2015
Description:    This program is to simulate an assembly processor.  It will read in
a file and perform the necessary action.  It will recognize improper addressing modes
and halt the program.
Input: 
Output:
Compilation instructions: compiles per usual.
Usage: ./b17 file.obj
Known bugs/missing features: None
Modifications:
Date                Comment
----    ------------------------------------------------
04/09/2015    Assign each member the starting work with parsing input file, 
	conversion between hex and binary string, and reference table of 
	address modes.
04/19/2015    Combine each member's code and implement several instruction 
	functions.
04/23/2015    Figure out the specific function for each instruction.
05/01/2015    Test the whole code and finish all the documentation.
************************************************************************/

#include "b17.h"

/************************************************************************
Function: int main (int argc, char** argv)
Author: John Mangold
Description: Handles necessary function calls.
Parameters: int argc - in - count of arguments
			char** argv - in - array of arguments

			returns 0 - ran successfully
************************************************************************/
int main( int argc, char** argv )
{
	vector<string> memory(4096);
	ifstream object_fin;
	string start_address;
	string operand_address;
	string operand;
	string opcode;
	string op;
	string address_mode;
	string op_name, address, accumulator;
	stringstream mem_address;

	for (int i = 0; i < 4096;i++)
	{
		memory[i] = "0";
	}
	
	if(argc != 2 )
	{
		cout << "Incorrect usage.  Correct usage: b17 prog.obj\n";
		return -1;
	}
	
	object_fin.open(argv[1]);
	if( !object_fin)
	{
		cout << "Could not open input object file.\n";
		return -2;
	}
	
	start_address = parse_file(object_fin, memory);

	for (int i=stoi(start_address,nullptr,16);!memory[i].empty();i++)
	{
		if(!memory[i].empty())
		{
			//We need to process each instrtuction as it comes
			//call the split function
			split_instruction(memory[i], operand_address, opcode);
			get_op_and_am(opcode, op, address_mode);

			//perform action
			mem_address.str(string());
			mem_address << hex << i;
			action(memory, op, op_name, address_mode, accumulator, operand_address, address, mem_address.str());

			//check for appropriate addressing mode with op

			//call print function
			print_line(mem_address.str(), memory[i], op_name, address, accumulator);
			cout << endl;
		}
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	return 0;
}
