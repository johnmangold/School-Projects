#include "b17.h"

string parse_file(ifstream &fin, vector<string> &mem)
{
	string line;
	string base_address;
	string start;
	int address_decimal;
	string instruction_count;
	string instruction;
	cell temp_cell;
	
	//use while getline to read file
	while(getline(fin,line))
	{
		if(line.size() > 3 )
		{
			//break file into address
			base_address = line.substr(0, line.find_first_of(" "));
			//need hex to decimal function
			address_decimal = stoi(base_address,nullptr,16);
			//get instruction_count string
			instruction_count = line.substr(line.find_first_of(" ")+1);
			instruction_count = instruction_count.substr(0,instruction_count.find_first_of(" "));
			
			//for loop using instruction count to get instructions
			//must break instruction into address and opcode+address mode
			instruction = line.substr(line.find_first_of(" ")+1);
			instruction = instruction.substr(instruction.find_first_of(" ")+1);
			
			for( int i = 0; i < stoi(instruction_count); i++)
			{
				mem[address_decimal + i] = instruction.substr(0,instruction.find_first_of(" "));
				instruction = instruction.substr(instruction.find_first_of(" ")+1);
			}
		}
		else
		{
			start = line;
		}
		
	}
	
	return start;
}
