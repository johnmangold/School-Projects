#ifndef B17_H
#define B17_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

struct cell
{
	std::string operand_address;
	std::string opcode;
};

string parse_file(ifstream &fin, vector<string> &mem);
string hex_to_bin(string hex);

#endif
