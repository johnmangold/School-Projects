#include "b17.h"

int main( int argc, char** argv )
{
	vector<string> memory(4096);
	ifstream object_fin;
	string start_address;
	
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
			cout << memory[i] << endl;
		}
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	return 0;
}
