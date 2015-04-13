#include "mmu.h"

using namespace std;

int main(int argc, char** argv)
{
	string num_swaps;
	map<int, int> virtual_memory;
	map<int, int> tlb;
	map<int, int> page_table; 
	map<int, int> physical_memory;

	cout << "Enter the number of desired page swaps: ";
	getline(cin, num_swaps);
	
	if( num_swaps.find_first_not_of("0123456789") != string::npos )
	{
		cout << "Please only enter digits.  No letters or spaces.\n";
		return -1;
	}


	return 0;
}
