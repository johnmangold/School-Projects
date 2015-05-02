#include "mailbox.h"

int main(int argc, char** argv)
{
	string input;
	string command, mbs_num, mbs_size;  //for mboxinit
	string boxnumber, boxnumber2;  //for mboxwrite, mboxread, mboxcopy
	vector<int> ids;
	
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
			//make size in kilobytes
			mbs_size = to_string(stoi(mbs_size)*1024);
			
			//create shared memory
			if(create_memory(ids, stoi(mbs_num), stoi(mbs_size)) == true)
			{
				cout << "Mailboxes created successfully." << endl;
			}
			else
			{
				cout << "Mailboxes already exists." << endl;
			}
		}
		else if( input.substr(0,7) == "mboxdel" )
		{
			if (delete_mailbox() == true)
			{
				cout << "All mailboxes will be deleted upon exit." << endl;
			}
		}
		else if( input.substr(0,9) == "mboxwrite" )
		{
			command = input.substr(0,9);
			input = input.substr(input.find_first_of(" ") + 1);
			
			boxnumber = input.substr(0);
			
			write_mailbox(stoi(boxnumber));
			
		}
		else if( input.substr(0,8) == "mboxread" )
		{
			command = input.substr(0,8);
			input = input.substr(input.find_first_of(" ") + 1);
			
			boxnumber = input.substr(0);
			
			read_mailbox(stoi(boxnumber));
		}
		else if( input.substr(0,8) == "mboxcopy" )
		{
			command = input.substr(0,8);
			input = input.substr(input.find_first_of(" ") + 1);
			
			boxnumber = input.substr(0,input.find_first_of(" "));
			input = input.substr(input.find_first_of(" ") + 1);
			
			boxnumber2 = input.substr(0);
			
			copy_mailbox(stoi(boxnumber), stoi(boxnumber2));
			
		}
		else if(input == "exit" || input == "Exit" )
		{
			break;
		}
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	return 0;
	
	
}
