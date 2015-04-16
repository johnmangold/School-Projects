#include "mmu.h"

using namespace std;

/*
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
*/

int main(int argc, char** argv)
{
	string num_swaps;
	vector<virtual_info> virtual_memory(256); //2^16/2^8 = 2^8 virutal pages
	vector<location_info> tlb(32);  //must check that it doesn't contain more than 2^5
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
		virtual_info temp_virtual;
		location_info temp_location;
		temp_virtual.pid=i;
		temp_location.pid=i;
		temp_location.in_main = false;
		temp_virtual.data=rand();
		virtual_memory[i] = temp_virtual;
		page_table[i] = temp_location;
	}
	
	//fill physical_memory with random processes and addresses
	//fix this by making it random for numbers below 
	for(int i = 0;i< 128;i++)
	{
		physical_info temp_physical;
		virtual_info temp_virtual;
		location_info temp;
		int index;
		
		//get frame for page table and physical memory
		temp_physical.frame=i;
		
		//get data for physical memory
		index = rand()%256;
		temp_virtual = virtual_memory[index];
		temp_physical.data = temp_virtual.data;
		//set entry in physical memory array
		physical_memory[i] = temp_physical;
		
		//get pid for page table and set to in_main to true
		if(page_table[index].pid == temp_virtual.pid)
		{
			page_table[index].frame = temp_physical.frame;
			page_table[index].in_main = true;
		}
		
		//use pushback so things are queued
		if(tlb.size() < 32)
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
			tlb.insert(tlb.begin(), temp);
		}
	}
	
	//now begin swapping
	//check tlb first, if not found, tlb_miss++, if found tlb_hit++
	//check page table, find and place in physical memory
	//if not found page_fault++, move on
	//also time how long it takes to runt through all swaps
	//get percentages of hits, misses, and page faults.
	
	int tlb_miss = 0;
	int tlb_hit = 0;
	int page_fault = 0;
	int page_hit = 0;
	
	for(int i = 0;i < stoi(num_swaps); i++)
	{
		virtual_info virtual_page;
		bool hit = false;
		int index;
		
		//get random virtual page
		virtual_page = virtual_memory[rand()%256];
		
		//check tlb set hit to true if found
		for(unsigned int j = 0;j < tlb.size(); j++)
		{
			if(virtual_page.pid == tlb[j].pid)
			{
				hit = true;
				tlb_hit++;
				break;
			}
		}
		
		//tlb miss check page table
		if(hit == false)
		{
			tlb_miss++;
		
			for(unsigned int j = 0;j < page_table.size(); j++)
			{
				if(virtual_page.pid == page_table[j].pid && page_table[j].in_main == true)
				{
					hit = true;
					page_hit++;
					tlb.pop_back();
					tlb.insert(tlb.begin(),page_table[j]);
					break;
				}
				else if(virtual_page.pid == page_table[j].pid && page_table[j].in_main == false)
				{
					page_fault++;
					index = rand()%128;
					//update page table
					for(unsigned int k = 0;k < page_table.size();k++)
					{
						if(page_table[k].frame == physical_memory[index].frame)
						{
							page_table[k].in_main = false;
							break;
						}
					}
					
					//place new data in physical memory
					page_table[j].frame = physical_memory[index].frame;
					physical_memory[index].data = virtual_page.data;
					page_table[j].in_main = true;
					
					//update tlb
					for(unsigned int k = 0;k < tlb.size();k++)
					{
						if(tlb[k].frame == physical_memory[index].frame)
						{
							tlb.erase(tlb.begin()+k);
							break;
						}
					}
					
					tlb.insert(tlb.begin(),page_table[j]);
				}
			}
		}
	}

	//surprisingly this all works.
	//print statistics and look at adding in options to run larger settings maybe

	return 0;
}
























