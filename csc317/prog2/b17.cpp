#include "b17.h"

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
			operand = memory[stoi(operand_address,nullptr,16)];
			get_op_and_am(opcode, op, address_mode);

			//check the opcode and address mode
			//must check in this order
			//halt instruction, undefined opcode, unimplemented opcode,
			//illegal address mode, unimplemented address mode
			//simply create halt function and type in appropriate message
			//within if to catch each of the four bad halts
			//perform action
			action(memory, op, op_name, address_mode, accumulator, operand_address, address);

			//call print function
			print_line(operand_address, memory[i], op_name, address, accumulator);
			cout << endl;
		}
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	return 0;
}
