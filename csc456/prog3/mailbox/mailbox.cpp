/************************************************************************
   Program: Program 3
   Author: John Mangold, Colter Assman, Jason Anderson
   Class: CSC456
   Instructor: Dr. Christer Karlsson
   Date: 28 Apr 2015
   Description: Creates mailboxes using shared memory that allow data
   to be written to, read from, and copied.
   Input:  User input
   Output: To console
   Compilation instructions: Compiles per usual.
   Usage: ./mailbox
 ************************************************************************/
#include "mailbox.h"

/************************************************************************
   Function: int main(int argc, char** argv)
   Author: John Mangold, Colter Assman, Jason Anderson
   Description: Handles user input and necessary function calls
   Parameters: int argc - in - number of command line arguments
   		char** argv - in - actual arguments entered
 ************************************************************************/
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
		
			if(input.size() < 12)
			{
				cout << "\nPlease enter appropriate numbers after command." << endl;
				cout << "Usage: mboxinit <number of mailboxes> <size of mailboxes>" << endl << endl;
				continue;
			}
			//parse input for needed information
			command = input.substr(0,input.find_first_of(" "));
			input = input.substr(input.find_first_of(" ")+1);
			
			mbs_num = input.substr(0,input.find_first_of(" "));
			input = input.substr(input.find_first_of(" "));
			
			mbs_size = input;
			//make size in kilobytes
			mbs_size = to_string(stoi(mbs_size)*1024);
			
			if( stoi(mbs_size) == 0 )
			{
				cout << "Size of mailboxes cannot be 0" << endl;
				continue;
			}
			else if( stoi(mbs_num) == 0)
			{
				cout << "Number of mailboxes cannot be 0" << endl;
				continue;
			}
			
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
			if(input.size() < 11)
			{
				cout << "\nPlease enter appropriate numbers after command." << endl;
				cout << "Usage: mboxwrite <mailbox number>" << endl << endl;
				continue;
			}
		
			command = input.substr(0,9);
			input = input.substr(input.find_first_of(" ") + 1);
			
			boxnumber = input.substr(0);
			
			if( stoi(boxnumber) == 0)
			{
				cout << "Mailbox number cannot be 0" << endl;
				continue;
			}
			
			write_mailbox(stoi(boxnumber));
			
		}
		else if( input.substr(0,8) == "mboxread" )
		{
			if(input.size() < 10)
			{
				cout << "\nPlease enter appropriate numbers after command." << endl;
				cout << "Usage: mboxread <mailbox number>" << endl << endl;
				continue;
			}
		
			command = input.substr(0,8);
			input = input.substr(input.find_first_of(" ") + 1);
			
			boxnumber = input.substr(0);
			
			if( stoi(boxnumber) == 0)
			{
				cout << "Mailbox number cannot be 0" << endl;
				continue;
			}
			
			read_mailbox(stoi(boxnumber));
		}
		else if( input.substr(0,8) == "mboxcopy" )
		{
			if(input.size() < 12)
			{
				cout << "\nPlease enter appropriate numbers after command." << endl;
				cout << "Usage: mboxcopy <mailbox number to copy from> <mailbox number to copy to>" << endl << endl;
				continue;
			}
		
			command = input.substr(0,8);
			input = input.substr(input.find_first_of(" ") + 1);
			
			boxnumber = input.substr(0,input.find_first_of(" "));
			input = input.substr(input.find_first_of(" ") + 1);
			
			boxnumber2 = input.substr(0);
			
			if( stoi(boxnumber) == 0)
			{
				cout << "First mailbox number cannot be 0" << endl;
				continue;
			}
			else if( stoi(boxnumber2) == 0)
			{
				cout << "Second mailbox number cannot be 0" << endl;
				continue;
			}
			
			copy_mailbox(stoi(boxnumber), stoi(boxnumber2));
			
		}
		else if(input == "exit" || input == "Exit" )
		{
			break;
		}
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	return 0;
	
	
}
