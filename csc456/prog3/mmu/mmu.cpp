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
	bool in_main;
};

int main(int argc, char** argv)
{
	string num_swaps;
	vector<virtual_info> virtual_memory(256); //2^16/2^8 = 2^8 virutal pages
	vector<location_info> tlb(32);  //must check that it doesn't contain more than 2^5
	vector<location_info> page_table(256); //page table matches virtual so 2^6
	vector<physical_info> physical_memory(128); //(2^15)/2^8=128 frames
	virtual_info virtual_entry;
	physical_info physical_entry;
	

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
		virtual_info temp_virtual;
		temp_virtual.pid=i;
		temp_virtual.data=rand();
		virtual_memory[i] = temp_virtual;
	}
	
	//fill physical_memory with random processes and addresses
	//fix this by making it random for numbers below 
	for(int i = 0;i< 128;i++)
	{
		physical_info temp_physical;
		location_info temp_location;
		virtual_info temp_virtual;
		location_info temp;
		
		//get frame for page table and physical memory
		temp_physical.frame=i;
		temp_location.frame = i;
		
		//get data for physical memory
		temp_virtual = virtual_memory[(rand()%256)];
		temp_physical.data = temp_virtual.data;
		//set entry in physical memory array
		physical_memory[i] = temp_physical;
		
		//get pid for page table and set to in_main to true
		temp_location.pid = temp_virtual.pid;
		temp_location.in_main = true;
		page_table[i] = temp_location;
		
		//use pushback so things are queued
		if(size(tlb) < 32)
		{
			temp.pid = temp_virtual.pid;
			temp.frame = i;
			temp.in_main = true;
			tlb[31-i] = temp;
		}
		else
		{
			temp.pid = temp_virtual.pid;
			temp.frame = i;
			temp.in_main = true;
		
			//remove last element and place new one in front
			tlb.pop_back();
			tlb.insert(0, temp);
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
























