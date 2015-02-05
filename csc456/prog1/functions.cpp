#include "dash.h"

using namespace std;

//takes user input and splits it into one or two strings
//parameters in: string input, string &first, string &last
//parameters out: none, void function
void formatCmd(string input, string &first, string &last)
{
	size_t found = input.find(" ");
	//contains no space must be systat
	if(found ==  string::npos)
	{
		first = input;
		return;
	}//end of no space in input
	//has space can either be cmdnm or pid
	else
	{
		first = input.substr(0,found);  //creates string from 0 until just before first space
		last = input.substr(found+1);  //creates string from space+1 until end
	}//end splitting input string

}//end of formatCmd function

//uses given pid to find parent process name
//parameters in: int pid
//parameters out: string name
string cmdnm(int pid)
{
	string name;
	
	name = "arnold palmer";
	
	return name;
}//end of cmdnm function

//finds all process IDs that contain string last
//parameters in: string last, vector<in> &nums
//parameters out: none, void function
void get_pid(string last, vector<int> &nums)
{
	
	
}//end of get_pid function

//prints system information to stdout
//parameters in: none
//parameters out: none, void function
void systat()
{
	
	
}//end systat function
