#include "mailbox.h"

struct mailbox_info
{
	int number_of_boxes;
	int size_of_boxes;
	string message;
};

int main(int argc, char** argv)
{
	char *address;
	int *block_start;
	int shmid;
	mailbox_info *info;
	string input;
	string command, mbs_num, mbs_size;  //for mboxinit
	string boxnumber, boxnumber2;  //for mboxwrite, mboxread, mboxcopy
	
	while(true)
	{
		cout << "mailbox> ";
		getline(cin, input);
		
		if( input.substr(0,8) == "mboxinit")
		{
			//parse input for needed information
			command = input.substr(0,input.find_first_of(" "));
			input = input.substr(input.find_first_of(" ")+1);
			
			mbs_num = input.substr(0,input.find_first_of(" "));
			input = input.substr(input.find_first_of(" "));
			
			mbs_size = input;
			
			//set mailbox info struct
			//info->number_of_boxes = stoi(mbs_num);
			//info->size_of_boxes = stoi(mbs_size);
			
			//create shared memory
			create_memory(shmid, stoi(mbs_num), stoi(mbs_size), address, block_start);

		}
		else if( input.substr(0,7) == "mboxdel" )
		{
			if (delete_mailbox(shmid) == true)
			{
				cout << "Will be deleted once last process detaches from " << shmid << endl;
			}
		}
		else if( input.substr(0,9) == "mboxwrite" )
		{
			command = input.substr(0,9);
			input = input.substr(input.find_first_of(" ") + 1);
			
			boxnumber = input.substr(0);
			
			cout << endl << write_mailbox(block_start, stoi(boxnumber), stoi(mbs_size));
			
		}
		else if( input.substr(0,8) == "mboxread" )
		{
			command = input.substr(0,8);
			input = input.substr(input.find_first_of(" ") + 1);
			
			boxnumber = input.substr(0);
			
			printf("\n%s   %s\n", command.c_str(), boxnumber.c_str());
		}
		else if( input.substr(0,8) == "mboxcopy" )
		{
			command = input.substr(0,8);
			input = input.substr(input.find_first_of(" ") + 1);
			
			boxnumber = input.substr(0,input.find_first_of(" "));
			input = input.substr(input.find_first_of(" ") + 1);
			
			boxnumber2 = input.substr(0);
			
			printf("\n%s   %s   %s\n", command.c_str(), boxnumber.c_str(), boxnumber2.c_str());
		}
		else if(input == "exit" || input == "Exit" )
		{
			break;
		}
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	return 0;
	
	
}
