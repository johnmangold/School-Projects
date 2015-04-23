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
					mem[address_decimal + i] = instruction.substr(0, instruction.find_first_of(" "));
					instruction = instruction.substr(instruction.find_first_of(" ") + 1);
			}
		}
		else
		{
			start = line;
		}
		
	}
	
	return start;
}

void print_line(string address, string instruction, string op_name, string address_mode, string accumulator_hex)
{
	printf("%03s:  %s  %3s  %s  AC[%06s]  X0[%03d]  X1[%03d]  X2[%03d]  X3[%03d]", address.c_str(), instruction.c_str(), op_name.c_str(), address_mode.c_str(), accumulator_hex.c_str(), 0, 0, 0, 0);
}

void action(vector<string> memory, string op, string &op_name, string address_mode, string &accumulator, string operand_address, string &address) //more parameters needed to pass back values
{
	//andrew: nop, or, xor, clr, and, com
	//yan: j, jp, jn, jz
	//john: st, em, sub, 

	//check and set address portion
	if (address_mode == "0001")
	{
		address = "IMM";
	}

	//check op and perform necessary action
	if (op == "000000")
	{
		//perform halt
		op_name = "HALT";
		address = "   ";
	}
	else if (op == "010000")
	{
		//perform load
		accumulator = operand_address;
		op_name = "LD";
	}
	else if (op == "100000")
	{
		int temp;
		stringstream decimal;
		//perform add
		address = operand_address;
		op_name = "ADD";
		temp = stoi(accumulator, nullptr, 16) + stoi(memory[stoi(operand_address,nullptr,16)], nullptr, 16);
		decimal << hex << temp;
		accumulator = decimal.str();

	}
	else if (op == "110000")
	{
		//perform jump
	}
	else if (op == "000001")
	{
		//perform nop
	}
	else if (op == "010001")
	{
		//perform store
	}
	else if (op == "100001")
	{
		//perform sub
		int temp;
		stringstream decimal;
		//perform add
		address = operand_address;
		op_name = "ADD";
		temp = stoi(accumulator, nullptr, 16) - stoi(memory[stoi(operand_address,nullptr,16)], nullptr, 16);
		decimal << hex << temp;
		accumulator = decimal.str();
	}
	else if (op == "110001")
	{
		//perform jz
	}
	else if (op == "010010")
	{
		//perform em
	}
	else if (op == "100010")
	{
		//perform clr
	}
	else if (op == "110010")
	{
		//perform jn
	}
	else if (op == "100011")
	{
		//perform com
	}
	else if (op == "110011")
	{
		//perform jp
	}
	else if (op == "100100")
	{
		//perform and
	}
	else if (op == "100101")
	{
		//perform or
	}
	else if (op == "100110")
	{
		//perform xor
	}
	else if (op == "101000")
	{
		//perform addx
	}
	else if (op == "101001")
	{
		//perform subx
	}
	else if (op == "101010")
	{
		//perform clrx
	}
	else if (op == "011000")
	{
		//perform ldx
	}
	else if (op == "011001")
	{
		//perform stx
	}
	else if (op == "011010")
	{
		//perform emx
	}
	else if (stoi(op, nullptr, 2) < stoi("000000",nullptr,2) ||
		stoi(op, nullptr, 2) > stoi("111111",nullptr,2))
	{
		//call halt("Machine Halted - undefined opcode")
		//this will print to screen and stop simulation
		//perform halt due to undefined opcode.  print undefined opcode
		cout << "Machine Halted - undefined opcode" << endl;
		exit(EXIT_SUCCESS);
	}
	else
	{
		//call halt("Machine Halted - unimplemented opcode")
		//this will print to screen and stop simulation
		//perform halt due to unimplemented opcode.  print unimplemented opcode.
		cout << "Machine Halted - unimplemented opcode" << endl;
		exit(EXIT_SUCCESS);
	}
}
