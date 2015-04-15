#include "main.h"

using namespace std;

void parse_file(ifstream &fin, vector<cell> &mem)
{
	string line;
	string base_address;
	int address_decimal;
	string instruction_count;
	string instruction;
	cell temp_cell;
	
	//use while getline to read file
	while(getline(fin,line))
	{
		//break file into address
		base_address = line.substr(0, line.find_first_of(" "));
		//need hex to decimal function
		//address_decimal = hex2dec(base_address);
		//get instruction_count string
		instruction_count = line.substr(line.find_first_of(" ")+1);
		instruction_count = instruction_count.substr(0,instruction_count.find_first_of(" "));
		
		//for loop using instruction count to get instructions
		//must break instruction into address and opcode+address mode
		instruction = line.substr(line.find_first_of(" ")+1);
		instruction = instruction.substr(line.find_first_of(" ")+1);
		
		for( int i = 0; i < (int) instruction_count; i++)
		{
			temp_cell.operand_address = instruction.substr(0,3);
			temp_cell.opcode = instruction.substr(3,instruction.find_first_of(" "));
			mem[address_decimal + i] = temp_cell;
			instruction = instruction.substr(instruction.find_first_of(" ")+1);
		}
		
	}
}