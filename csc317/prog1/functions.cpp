#include "Hamming.h"

using namespace std;

//everything works for input.
//check proper length of bit string when entering encode, parity, decode

bool get_parts(string option, string &first, string &last)
{
	size_t index;
	
	index = option.find_first_not_of(" \t");
	option = option.substr(index);
	index = option.find_first_of(" ");
	first = option.substr(0, index);
	last = option.substr(index+1);
	
	//check that last is all ones and zeroes
	index = last.find_first_not_of("01");
	if( index != string::npos)
	{
		cout << "Bit string must be only ones and zeroes ex. 1001\n";
		return false;
	}
	else
	{
		return true;
	}
}

void encode74(string last)
{
	int G[7][4] = {{1,1,0,1},
		       {1,0,1,1},
		       {1,0,0,0},
		       {0,1,1,1},
		       {0,1,0,0},
		       {0,0,1,0},
		       {0,0,0,1}};
		       
	int H[3][7] = {{1,0,1,0,1,0,1},
		       {0,1,1,0,0,1,1},
		       
		       {0,0,0,1,1,1,1}};


	if(last.length() != 4)
	{
		cout << "Bit string must be 4 bits.\n";
		return;
	}
	
	cout << last << endl;
}

void parity74(string last)
{
	int G[7][4] = {{1,1,0,1},
		       {1,0,1,1},
		       {1,0,0,0},
		       {0,1,1,1},
		       {0,1,0,0},
		       {0,0,1,0},
		       {0,0,0,1}};
		       
	int H[3][7] = {{1,0,1,0,1,0,1},
		       {0,1,1,0,0,1,1},
		       {0,0,0,1,1,1,1}};

	if(last.length() != 7)
	{
		cout << "Bit string must be 7 bits.\n";
		return;
	}

	cout << last << endl;
}

void decode74(string last)
{
	int G[7][4] = {{1,1,0,1},
		       {1,0,1,1},
		       {1,0,0,0},
		       {0,1,1,1},
		       {0,1,0,0},
		       {0,0,1,0},
		       {0,0,0,1}};
		       
	int H[3][7] = {{1,0,1,0,1,0,1},
		       {0,1,1,0,0,1,1},
		       {0,0,0,1,1,1,1}};

	if(last.length() != 7)
	{
		cout << "Bit string must be 7 bits.\n";
		return;
	}

	cout << last << endl;
}

void encode1511(string last)
{
	if(last.length() != 11)
	{
		cout << "Bit string must be 11 bits.\n";
		return;
	}

	cout << last << endl;
}

void parity1511(string last)
{
	if(last.length() != 15)
	{
		cout << "Bit string must be 15 bits.\n";
		return;
	}

	cout << last << endl;
}

void decode1511(string last)
{
	if(last.length() != 15)
	{
		cout << "Bit string must be 15 bits.\n";
		return;
	}

	cout << last << endl;
}

void h74()
{
	bool good;
	string option;
	string first;
	string last;

	cout << "encode, parity, or decode: ";
	getline(cin, option);
	
	good = get_parts(option, first, last);
	if(good == false)
	{
		return;
	}
	
	if(first == "encode")
	{
		encode74(last);
	}
	else if(first == "parity")
	{
		parity74(last);
	}
	else if(first == "decode")
	{
		decode74(last);
	}
}

void h1511()
{
	bool good;
	string option;
	string first;
	string last;

	cout << "encode, parity, or decode: ";
	getline(cin, option);
	
	good = get_parts(option, first, last);
	if(good == false)
	{
		return;
	}
	
	if(first == "encode")
	{
		encode1511(last);
	}
	else if(first == "parity")
	{
		parity1511(last);
	}
	else if(first == "decode")
	{
		decode1511(last);
	}
}
