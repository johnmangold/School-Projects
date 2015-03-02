#include "dash.h"

using namespace std;

void formatCmd(string format, string &first, string &last);
string cmdnm(int pid);
void get_pid(string last, vector<int> &nums);
void systat();
/******************** prog2 function prototypes *************************/
void redir_in(char *args[]);
void redir_out(char *args[]);
void change(char *args[]);
void pipe(char *args[]);
void sig(char *args[]);

/************************************************************************
   Function: main
   Author: John Mangold
   Description: Handles user input and necessary function calls.
   Parameters: in - int argc - number of command line arguments
   	       in - char **argv - char array of arguments
   	       out - int - return -1 if can't open a file
   			   return 0 if run sucessfully
 ************************************************************************/
int main(int argc, char **argv)
{
	char  line[100]; 
	char *args[100]; 
	int   num_args; 
	int   i;
	string name;
	
	while(true)
	{
		cout << "dash>";
		gets(line);
		if(strcmp(line, "exit" ) == 0)
		{
			break;
		}
		
		num_args = 0;
		args[num_args] = strtok(line, " ");
		while (args[num_args] != NULL)
		{
			num_args++;
			args[num_args] = strtok(NULL, " ");
		}

		if(num_args >= 1)
		{
			
			if(strcmp(args[0],"cd") == 0)
			{
				change(args);
			}
			else if(strcmp(args[0],"signal") == 0)
			{
				sig(args);
			}
			else if(strcmp(args[0],"cmdnm") == 0)
			{
				name = cmdnm(atoi(args[1]));
				cout << "Command Name: " << name << endl;
			}
			else if(strcmp(args[0],"systat") == 0)
			{
				systat();
			}
			
			if(num_args >= 2)
			{
				if(strcmp(args[1],">") == 0)
				{
					redir_in(args);
				}
				else if(strcmp(args[1],"<") == 0)
				{
					redir_out(args);
				}
				else if(strcmp(args[1],"|") == 0)
				{
					pipe(args);
				}
			}
		}
				
	}
	
	return 0;
}
