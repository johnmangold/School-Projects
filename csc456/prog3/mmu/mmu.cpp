#include "mmu.h"

using namespace std;

struct virtual_info
{
	int pid;
	int data;
};

struct physical_info
{
	int frame;
	int data;
};

struct location_info
{
	int pid;
	int frame;
};

int main(int argc, char** argv)
{
	string num_swaps;
	vector<virtual_info> virtual_memory(256); //2^16/2^8 = 2^8 virutal pages
	vector<location_info> tlb;  //must check that it doesn't contain more than 2^5
	vector<location_info> page_table(256); //page table matches virtual so 2^6
	vector<physical_info> physical_memory(128); //(2^15)/2^8=128 frames

	cout << "Enter the number of desired page swaps: ";
	getline(cin, num_swaps);
	
	if( num_swaps.find_first_not_of("0123456789") != string::npos )
	{
		cout << "Please only enter digits.  No letters or spaces.\n";
		return -1;
	}
	
	//seed random generator
	srand(time(NULL));

	//fill virutal_memory with addresses
	for(int i = 0; i< 256;i++)
	{
		virtual_memory[i].pid=i;
		virtual_memory[i].data=rand();
	}
	
	//fill physical_memory with random processes and addresses
	//fix this by making it random for numbers below 
	for(int i = 0;i< 128;i++)
	{
		physical_memory[i].frame=i;
		physical_memory[i].data = virtual_memory[(rand()%256)].data;
		
		//use pushback so things are queued
		if(size(tlb) < 32)
		{
			tlb.pid=virtual_memory[i].pid;
			tlb.frame=physical_memory[i].frame;
		}
	}
	
	//now begin swapping
	//check tlb first, if not found, tlb_miss++, if found tlb_hit++
	//check page table, find and place in physical memory
	//if not found page_fault++, move on
	//also time how long it takes to runt through all swaps
	//get percentages of hits, misses, and page faults.

	return 0;
}
























