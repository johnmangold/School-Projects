#include "mmu.h"

using namespace std;

int main(int argc, char** argv)
{
	string num_proc;
	map<int, int> virtual_memory;
	map<int, int> tlb;
	map<int, int> page_table; 
	map<int, int> physical_memory;

	cout << "Enter the number of desired processes: ";
	getline(cin, num_proc);
	
	if( num_proc.find_first_not_of("0123456789") != string::npos )
	{
		cout << "Please only enter digits.  No letters or spaces.\n";
		return -1;
	}


	return 0;
}
