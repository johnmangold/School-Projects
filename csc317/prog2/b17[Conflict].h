#ifndef B17_H
#define B17_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdio.h>
<<<<<<< HEAD
=======
#include <sstream>
>>>>>>> 424eddc06c138babc8fd03622288f4ee924984c4

using namespace std;

struct cell
{
	std::string operand_address;
	std::string opcode;
};

string parse_file(ifstream &fin, vector<string> &mem);
string hex_to_bin(string hex);
<<<<<<< HEAD
void print_line(string address, string instruction, string opcode, string address_mode, string accumulator_hex,
	string x0_hex, string x1_hex, string x2_hex, string x3_hex);
=======
void split_instruction(string instruction, string &hex, string &lastThree);
void get_op_and_am(string lastThree, string &opcode, string &addressMode);
void print_line(string address, string instruction, string op_name, string address_mode, string accumulator_hex, 
	string x0_hex, string x1_hex, string x2_hex, string x3_hex);
void action(string op, string &op_name, string address_mode, string &accumulator,
	string &x0, string &x1, string &x2, string &x3, string operand_address, string &address);
>>>>>>> 424eddc06c138babc8fd03622288f4ee924984c4

#endif
