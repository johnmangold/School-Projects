#include "mailbox.h"

#define SHMKEY 1066
#define K 1024

int main(int argc, char** argv)
{
	int shmid;
	string input;
	string command, mbs_num, mbs_size;  //for mboxinit
	string boxnumber, boxnumber2;  //for mboxwrite, mboxread, mboxcopy
	
	/*schmid = shmget(SHMKEY, 10*K, IPC_CREAT | IPC_EXCL | 0666);
	if(schmid < 0)
	{
		cout << "shmget failed" << endl;
	}*/
	
	while(true)
	{
		cout << "mailbox> ";
		getline(cin, input);
		
		if( input.substr(0,8) == "mboxinit")
		{
			command = input.substr(0,input.find_first_of(" "));
			input = input.substr(input.find_first_of(" ")+1,size_t (input.end()));
			
			mbs_num = input.substr(0,input.find_first_of(" "));
			input = input.substr(input.find_first_of(" ")+1,size_t (input.end()));
			
			mbs_size = command.substr(0);
			
			printf("\n%s   %s   %s\n", command.c_str(), mbs_num.c_str(), mbs_size.c_str());
		}
		else if( input.substr(0,7) == "mboxdel" )
		{
			command = input.substr(0,7);
			
			cout << endl << command << endl;
		}
		else if( input.substr(0,9) == "mboxwrite" )
		{
			command = input.substr(0,9);
			input = input.substr(input.find_first_of(" ")+1, input.end());
			
			boxnumber = input.substr(0);
			
			printf("\n%s   %s\n", command.c_str(), boxnumber.c_str());
			
		}
		else if( input.substr(0,8) == "mboxread" )
		{
			command = input.substr(0,8);
			input = input.substr(input.find_first_of(" ")+1,input.end());
			
			boxnumber = input.substr(0);
			
			printf("\n%s   %s\n", command.c_str(), boxnumber.c_str());
		}
		else if( input.substr(0,8) == "mboxcopy" )
		{
			command = input.substr(0,8);
			input = input.substr(input.find_first_of(" ")+1,input.end());
			
			boxnumber = input.substr(0,input.find_first_of(" "));
			input = input.substr(input.find_first_of(" ")+1,input.end());
			
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
