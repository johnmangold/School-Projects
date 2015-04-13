#include "mmu.h"

using namespace std;

int main(int argc, char** argv)
{
	string num_swaps;
	map<long long int, long long int> virtual_memory; //given 2^32 processes
	map<int, int> tlb;  //must check that it doesn't contain more than 2^10
	map<int, int> page_table; //page size 512kb so 2^13 for page table
	map<int, int> physical_memory; //4GB(2^12)

	cout << "Enter the number of desired page swaps: ";
	getline(cin, num_swaps);
	
	if( num_swaps.find_first_not_of("0123456789") != string::npos )
	{
		cout << "Please only enter digits.  No letters or spaces.\n";
		return -1;
	}

	//fill virutal_memory with addresses
	for(long long int i = 0; i< pow(2,32);i++)
	{
		virtual_memory[i]=i;
	}
	
	//fill physical_memory with random processes and addresses
	//fix this by making it random for numbers below 2^32
	for(int i = 0;i< pow(2,12);i++)
	{
		physical_memory[i] = i;
	}
	
	//now begin swapping
	//check tlb first, if not found, tlb_miss++, if found tlb_hit++
	//check page table, find and place in physical memory
	//if not found page_fault++, move on
	//also time how long it takes to runt through all swaps
	//get percentages of hits, misses, and page faults.

	return 0;
}
