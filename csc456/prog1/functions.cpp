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

//finds all process IDs that contain string last
//parameters in: string last, vector<in> &nums
//parameters out: none, void function
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

//prints system information to stdout
//parameters in: none
//parameters out: none, void function
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
