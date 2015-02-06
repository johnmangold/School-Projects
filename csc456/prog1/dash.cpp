#include "dash.h"

using namespace std;

void formatCmd(string format, string &first, string &last);
string cmdnm(int pid);
void get_pid(string last, vector<int> &nums);
void systat();

int main(int argc, char **argv)
{
	string input, first, last;
	bool finished = false;
	
	while(finished == false)
	{
		cout << "dash>";
		getline(cin, input);
		
		if(input == "exit" || input == "x" || input == "X")
		{
			finished = true;
		}
		
		formatCmd(input, first, last);
		
		if(first == "cmdnm")
		{
			string commandName = cmdnm(atoi(last.c_str()));
			
			if(commandName != "fail fail fail")
			{	
				cout << "Parent Name: " << commandName
					<< endl << endl;
			}
			else
			{
				cout << "That doesn't seem to be a process."
					<< endl;
			}
		}
		else if(first == "pid")
		{
			vector<int> pids;
			get_pid(last, pids);
			
			for(int i = 0;i < pids.size(); i++)
			{
				cout << "PID matching " << last << ": "
					<< pids[i] << endl; 
			}
		}
		else if(first == "systat")
		{
			systat();
		}
		
	}
	
	
	
	
	return 0;
}
