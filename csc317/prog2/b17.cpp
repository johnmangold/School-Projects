#include "b17.h"

using namespace std;

string parse_file(ifstream &fin);

struct cell
{
	string operand_address;
	string opcode;
};

int main( int argc, char** argv )
{
	vector<cell> memory(4096);
	ifstream object_fin;
	string start_address;
	
	if(argc < 2 || argc > 2 )
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
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	return 0;
}