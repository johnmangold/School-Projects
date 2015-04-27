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
