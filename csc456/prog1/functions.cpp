#include "dash.h"

using namespace std;

/************************************************************************
   Function: formatCmd
   Author: John Mangold
   Description: Takes user input and splits it into two separate strings.  The first string is the command name and the second is the variable portion.
   Parameters: in - string input - entire user input
	       in - string &first - string for holding command portion
	       in - string &last - string for holding variable phrase
	       out - None. Void function.
 ************************************************************************/
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

/************************************************************************
   Function: cmdnm
   Author: John Mangold
   Description: Checks given process ID and returns the name of the parent process.
   Parameters: in - int pid - the provided process ID
   	       out - string name - the parent process name
 ************************************************************************/
string cmdnm(int pid)
{
	string name;
	string dir;
	ifstream fin;
	
	dir = "/proc/" + to_string(pid) + "/status";
	fin.open(dir);
	if(!fin)
	{
		cout << "Could not open file." << endl;
		return "fail fail fail";
	}//end check if file is good.

	for (int i = 0; i < 6; i++)
	{
		getline(fin,name);
	}//end for loop getting PPID
	
	name = name[name.length()-1];
	fin.close();
	if(name == "0")
	{
		return "no parent";
	}
	dir = "/proc/" + name + "/status";
	fin.open(dir);
	if(!fin)
	{
		cout << "Could not open parent file." << endl;
		return "fail fail fail";
	}//end check if file is good.
	
	getline(fin,name);
	fin.close();
	name = name.substr(6);
	
	return name;
}//end of cmdnm function

/************************************************************************
   Function: get_pid
   Author: John Mangold
   Description: Checks the names of all running processes to see if they contain a given string.  If the string is found it is added to a running list.
   Parameters: in - string last - the string to search for
   	       in - vector<int> &nums - vector to store process IDs
   	       out - None.  Void function.
 ************************************************************************/
void get_pid(string last, vector<int> &nums)
{
	string output;
	string dir;
	string id;
	size_t found;
	ifstream fin;
	
	for(int i = 0;i < 20000;i++)
	{
		dir = "/proc/" + to_string(i) + "/status";
		fin.open(dir);
		if(fin.is_open())
		{
			getline(fin,output);
			output = output.substr(6);
			found = output.find(last);
			if(found != string::npos)
			{
				for(int i = 0;i<4;i++)
				{
					getline(fin,id);
				}
				
				id = id.substr(5);
				nums.push_back(atoi(id.c_str()));
			}
		}
		fin.close();
	}
	
}//end of get_pid function

/************************************************************************
   Function: systat
   Author: John Mangold
   Description: Reads various system files to gather system information such as Linux version, uptime, memory information, and cpu information
   Parameters: in - None.
   	       out - None.
 ************************************************************************/
void systat()
{
	string dir;
	string output;
	ifstream fin;
	
	cout << endl;
	fin.open("/proc/version");
	if (!fin)
	{
		cout << "Could not open version file." << endl;
		return;
	}
	
	getline(fin,output);
	output = output.substr(0,36);
	cout << output << endl;
	fin.close();
	
	//get uptime now
	fin.open("/proc/uptime");
	if (!fin)
	{
		cout << "Could not open uptime file." << endl;
		return;
	}
	
	getline(fin,output);
	output = output.substr(0,output.find(" "));
	cout << "Uptime (s): " << output << endl;
	fin.close();
	
	//get memory info now
	fin.open("/proc/meminfo");
	if (!fin)
	{
		cout << "Could not open meminfo file." << endl;
		return;
	}
	
	for(int i=0;i<3;i++)
	{
		getline(fin,output);
		cout << output << endl;
	}
	fin.close();
	
	//cpuinfo
	fin.open("/proc/cpuinfo");
	if (!fin)
	{
		cout << "Could not open cpuinfo file." << endl;
		return;
	}
	
	getline(fin,output);
	for(int i=0;i<8;i++)
	{
		getline(fin,output);
		cout << output << endl;
	}
	fin.close();
	
	cout << endl;
	
}//end systat function
