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
	if (accumulator_hex.size() > 6)
	{
		accumulator_hex.resize(6);
	}

	printf("%03x:  %06x  %-4s  %s  AC[%06x]  X0[%03d]  X1[%03d]  X2[%03d]  X3[%03d]", stoi(address,nullptr,16), stoi(instruction,nullptr,16), op_name.c_str(), address_mode.c_str(), stoi(accumulator_hex,nullptr,16), 0, 0, 0, 0);
}

void action(vector<string> &memory, string op, string &op_name, string address_mode, string &accumulator, string operand_address, string &address, string mem_address)
{
	int temp;
	stringstream decimal;
	string opcode;
	long long big;
	long long base = 4294967295;


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
		print_line(mem_address, memory[stoi(mem_address,nullptr,16)], op_name, address, accumulator);
		cout << endl << "Machine Halted - HALT instruction executed" << endl;
		exit(EXIT_SUCCESS);
	}
	else if (op == "010000")
	{
		//perform load
		if (address_mode != "0001")
		{
			address = operand_address;
			accumulator = memory[stoi(operand_address, nullptr, 16)];
		}
		else
		{
			accumulator = operand_address;
		}
		op_name = "LD";
	}
	else if (op == "100000")
	{
		big = stoll(accumulator, nullptr, 16);
		if (big > INT_MAX)
		{
			big -= base;
			big -= 1;
		}

		//perform add
		if (address_mode != "0001")
		{
			address = operand_address;
			temp = big + stoi(memory[stoi(operand_address, nullptr, 16)], nullptr, 16);
		}
		else
		{
			temp = big + stoi(operand_address, nullptr, 16);
		}
		op_name = "ADD";
		decimal.str(string());
		decimal << hex << temp;
		accumulator = decimal.str();

	}
	else if (op == "110000")
	{

		if (address_mode == "0001")
		{
			address = "???";
			op_name = "J";
			print_line(mem_address, memory[stoi(mem_address, nullptr, 16)], op_name, address, accumulator);
			cout << endl << "Machine Halted - illegal addressing mode" << endl;
			exit(EXIT_SUCCESS);
		}
		//perform jump
		address = operand_address;
		op_name = "J";
		print_line(mem_address, memory[stoi(mem_address,nullptr,16)], op_name, address, accumulator);
		cout << endl;

		for (int i = stoi(operand_address, nullptr, 16); !memory[i].empty(); i++)
		{
			if (!memory[i].empty())
			{
				//We need to process each instrtuction as it comes
				//call the split function
				split_instruction(memory[i], operand_address, opcode);
				get_op_and_am(opcode, op, address_mode);

				//perform action
				decimal.str(string());
				decimal << hex << i;
				action(memory, op, op_name, address_mode, accumulator, operand_address, address, decimal.str());

				//check for appropriate addressing mode with op

				//call print function
				print_line(decimal.str(), memory[i], op_name, address, accumulator);
				cout << endl;
			}
		}
	}
	else if (op == "000001")
	{
		//perform nop
		if (address_mode != "0001")
		{
			address = operand_address;
		}
		
		op_name = "NOP";
	}
	else if (op == "010001")
	{
		if (address_mode == "0001")
		{
			address = "???";
			op_name = "ST";
			print_line(mem_address, memory[stoi(mem_address, nullptr, 16)], op_name, address, accumulator);
			cout << endl << "Machine Halted - illegal addressing mode" << endl;
			exit(EXIT_SUCCESS);
		}

		//perform store
		address = operand_address;
		op_name = "ST";
		memory[stoi(operand_address, nullptr, 16)] = accumulator;
	}
	else if (op == "100001")
	{
		big = stoll(accumulator, nullptr, 16);
		if (big > INT_MAX)
		{
			big -= base;
			big -= 1;
		}

		//perform sub
		if (address_mode != "0001")
		{
			address = operand_address;
			temp = big - stoi(memory[stoi(operand_address, nullptr, 16)], nullptr, 16);
		}
		else
		{
			temp = big - stoi(operand_address, nullptr, 16);
		}

		op_name = "SUB";
		decimal.str(string());
		decimal << hex << temp;
		accumulator = decimal.str();
	}
	else if (op == "110001")
	{
		if (address_mode == "0001")
		{
			address = "???";
			op_name = "JZ";
			print_line(mem_address, memory[stoi(mem_address, nullptr, 16)], op_name, address, accumulator);
			cout << endl << "Machine Halted - illegal addressing mode" << endl;
			exit(EXIT_SUCCESS);
		}

		//perform jz
		address = operand_address;
		op_name = "JZ";

		if ( stoi(accumulator, nullptr, 16) == stoi("000000", nullptr, 16) )
		{
			print_line(mem_address, memory[stoi(mem_address, nullptr, 16)], op_name, address, accumulator);
			cout << endl;

			for (int i = stoi(operand_address, nullptr, 16); !memory[i].empty(); i++)
			{
				if (!memory[i].empty())
				{
					//We need to process each instrtuction as it comes
					//call the split function
					split_instruction(memory[i], operand_address, opcode);
					get_op_and_am(opcode, op, address_mode);

					//perform action
					decimal.str(string());
					decimal << hex << i;
					action(memory, op, op_name, address_mode, accumulator, operand_address, address, decimal.str());

					//check for appropriate addressing mode with op

					//call print function
					print_line(decimal.str(), memory[i], op_name, address, accumulator);
					cout << endl;
				}
			}
		}
	}
	else if (op == "010010")
	{
		if (address_mode == "0001")
		{
			address = "???";
			op_name = "EM";
			print_line(mem_address, memory[stoi(mem_address, nullptr, 16)], op_name, address, accumulator);
			cout << endl << "Machine Halted - illegal addressing mode" << endl;
			exit(EXIT_SUCCESS);
		}

		//perform em
		string temp;
		address = operand_address;
		op_name = "EM";
		temp = memory[stoi(operand_address, nullptr, 16)];
		memory[stoi(operand_address, nullptr, 16)] = accumulator;
		accumulator = temp;
	}
	else if (op == "100010")
	{
		//perform clr
		if (address_mode != "0001")
		{
			address = operand_address;
		}

		op_name = "CLR";
		accumulator = "0";

	}
	else if (op == "110010")
	{
		if (address_mode == "0001")
		{
			address = "???";
			op_name = "JN";
			print_line(mem_address, memory[stoi(mem_address, nullptr, 16)], op_name, address, accumulator);
			cout << endl << "Machine Halted - illegal addressing mode" << endl;
			exit(EXIT_SUCCESS);
		}

		//perform jn
		address = operand_address;
		op_name = "JN";

		big = stoll(accumulator,nullptr,16);
		if (big > INT_MAX)
		{
			big -= base;
			big -= 1;
		}

		if ( big < 0 )
		{
			print_line(mem_address, memory[stoi(mem_address, nullptr, 16)], op_name, address, accumulator);
			cout << endl;

			for (int i = stoi(operand_address, nullptr, 16); !memory[i].empty(); i++)
			{
				if (!memory[i].empty())
				{
					//We need to process each instrtuction as it comes
					//call the split function
					split_instruction(memory[i], operand_address, opcode);
					get_op_and_am(opcode, op, address_mode);

					//perform action
					decimal.str(string());
					decimal << hex << i;
					action(memory, op, op_name, address_mode, accumulator, operand_address, address, decimal.str());

					//check for appropriate addressing mode with op

					//call print function
					print_line(decimal.str(), memory[i], op_name, address, accumulator);
					cout << endl;
				}
			}
		}
	}
	else if (op == "100011")
	{
		//perform com
		accumulator = hex_to_bin( accumulator );

		for( auto i : accumulator )
			i = 0 ? i = 1 : i = 0;

		temp = stoi( accumulator, nullptr, 2 );
		temp += 1;
		decimal.str( string( ) );
		decimal << hex << temp;
		accumulator = decimal.str( );
	}
	else if (op == "110011")
	{
		if (address_mode == "0001")
		{
			address = "???";
			op_name = "JP";
			print_line(mem_address, memory[stoi(mem_address, nullptr, 16)], op_name, address, accumulator);
			cout << endl << "Machine Halted - illegal addressing mode" << endl;
			exit(EXIT_SUCCESS);
		}

		//perform jp
		address = operand_address;
		op_name = "JP";

		big = stoll(accumulator, nullptr, 16);
		if (big > INT_MAX)
		{
			big -= base;
			big -= 1;
		}

		if (big > 0)
		{
			print_line(mem_address, memory[stoi(mem_address, nullptr, 16)], op_name, address, accumulator);
			cout << endl;

			for (int i = stoi(operand_address, nullptr, 16); !memory[i].empty(); i++)
			{
				if (!memory[i].empty())
				{
					//We need to process each instrtuction as it comes
					//call the split function
					split_instruction(memory[i], operand_address, opcode);
					get_op_and_am(opcode, op, address_mode);

					//perform action
					decimal.str(string());
					decimal << hex << i;
					action(memory, op, op_name, address_mode, accumulator, operand_address, address, decimal.str());

					//check for appropriate addressing mode with op

					//call print function
					print_line(decimal.str(), memory[i], op_name, address, accumulator);
					cout << endl;
				}
			}
		}
	}
	else if (op == "100100")
	{
		//perform and
		if( op != "0001" )
			address = operand_address;

		temp = stoi( memory[stoi( operand_address, nullptr, 16 ) ], nullptr, 16 );
		temp = stoi( accumulator, nullptr, 16 ) & temp;

		decimal.str( string( ) );
		decimal << hex << temp;
		accumulator = decimal.str( );
	}
	else if (op == "100101")
	{
		//perform or
		if( op != "0001" )
			address = operand_address;

		temp = stoi( memory[stoi( operand_address, nullptr, 16 ) ], nullptr, 16 );
		temp = stoi( accumulator, nullptr, 16 ) | temp;

		decimal.str( string( ) );
		decimal << hex << temp;
		accumulator = decimal.str( );

	}
	else if (op == "100110")
	{
		//perform xor
		if( op != "0001" )
			address = operand_address;

		temp = stoi( memory[stoi( operand_address, nullptr, 16 ) ], nullptr, 16 );
		temp = stoi( accumulator, nullptr, 16 ) ^ temp;

		decimal.str( string( ) );
		decimal << hex << temp;
		accumulator = decimal.str( );

	}
	else if (op == "101000")
	{
		//perform addx
		op_name = "ADDX";
		if (address_mode != "0001")
		{
			address = operand_address;
		}

		print_line(mem_address, memory[stoi(mem_address, nullptr, 16)], op_name, address, accumulator);
		cout << endl << "Machine Halted - unimplemented opcode" << endl;
		exit(EXIT_SUCCESS);
	}
	else if (op == "101001")
	{
		//perform subx
		op_name = "SUBX";
		if (address_mode != "0001")
		{
			address = operand_address;
		}
		print_line(mem_address, memory[stoi(mem_address, nullptr, 16)], op_name, address, accumulator);
		cout << endl << "Machine Halted - unimplemented opcode" << endl;
		exit(EXIT_SUCCESS);
	}
	else if (op == "101010")
	{
		//perform clrx
		op_name = "CLRX";
		address = operand_address;
		print_line(mem_address, memory[stoi(mem_address, nullptr, 16)], op_name, address, accumulator);
		cout << endl << "Machine Halted - unimplemented opcode" << endl;
		exit(EXIT_SUCCESS);
	}
	else if (op == "011000")
	{
		//perform ldx
		op_name = "LDX";
		if (address_mode != "0001")
		{
			address = operand_address;
		}
		print_line(mem_address, memory[stoi(mem_address, nullptr, 16)], op_name, address, accumulator);
		cout << endl << "Machine Halted - unimplemented opcode" << endl;
		exit(EXIT_SUCCESS);
	}
	else if (op == "011001")
	{
		//perform stx
		op_name = "STX";
		address = operand_address;
		print_line(mem_address, memory[stoi(mem_address, nullptr, 16)], op_name, address, accumulator);
		cout << endl << "Machine Halted - unimplemented opcode" << endl;
		exit(EXIT_SUCCESS);
	}
	else if (op == "011010")
	{
		//perform emx
		op_name = "EMX";
		address = operand_address;
		print_line(mem_address, memory[stoi(mem_address, nullptr, 16)], op_name, address, accumulator);
		cout << endl << "Machine Halted - unimplemented opcode" << endl;
		exit(EXIT_SUCCESS);
	}
	else
	{
		//call halt("Machine Halted - undefined opcode")
		//this will print to screen and stop simulation
		//perform halt due to undefined opcode.  print undefined opcode
		op_name = "????";
		address = operand_address;
		print_line(mem_address, memory[stoi(mem_address, nullptr, 16)], op_name, address, accumulator);
		cout << endl << "Machine Halted - undefined opcode" << endl;
		exit(EXIT_SUCCESS);
	}

	if (address_mode != "0010" && address_mode != "0100" && address_mode != "0110" && address_mode != "0001" && address_mode != "0000")
	{
		address = "???";
		print_line(mem_address, memory[stoi(mem_address, nullptr, 16)], op_name, address, accumulator);
		cout << endl << "Machine Halted - illegal addressing mode" << endl;
		exit(EXIT_SUCCESS);
	}

	if (address_mode == "0010" || address_mode == "0100" || address_mode == "0110")
	{
		address = "???";
		print_line(mem_address, memory[stoi(mem_address, nullptr, 16)], op_name, address, accumulator);
		cout << endl << "Machine Halted - unimplemented addressing mode" << endl;
		exit(EXIT_SUCCESS);
	}
}
