#ifndef B17_H
#define B17_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdio.h>

using namespace std;

struct cell
{
	std::string operand_address;
	std::string opcode;
};

string parse_file(ifstream &fin, vector<string> &mem);
string hex_to_bin(string hex);
void split_instruction(string instruction, string &hex, string &lastThree);
void get_op_and_am(string lastThree, string &opcode, string &addressMode);
void print_line(string address, string instruction, string opcode, string address_mode, string accumulator_hex, 
	string x0_hex, string x1_hex, string x2_hex, string x3_hex);

#endif
