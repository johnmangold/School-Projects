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
		cout << input << endl << first << endl << last << endl;
		
		if(first == "cmdnm")
		{
			string commandName = cmdnm(atoi(last.c_str()));
		}
		else if(first == "pid")
		{
			vector<int> pids;
			get_pid(last, pids);
		}
		else if(first == "systat")
		{
			systat();
		}
		
	}
	
	
	
	
	return 0;
}
