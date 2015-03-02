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
   Description: Checks given process ID and returns the command line argument used to initiate the process.
   Parameters: in - int pid - the provided process ID
   	       out - string name - the parent process name
 ************************************************************************/
string cmdnm(int pid)
{
	string name;
	string dir;
	ifstream fin;
	
	dir = "/proc/" + to_string(pid) + "/cmdline";
	fin.open(dir);
	if(!fin)
	{
		cout << "Could not open file." << endl;
		return "fail fail fail";
	}//end check if file is good.
	
	getline(fin,name);
	fin.close();
	return name;
}//end of cmdnm function

/************************************************************************
   Function: get_pid
   Author: John Mangold
   Description: Checks the command line argument of each running process searching for the given string.  If the string is found it is added to the vector of ints.
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
	ifstream pin;
	
	if(last.find_first_not_of("\t\n\v\f\r") != string::npos)
	{
		for(int i = 0;i < 20000;i++)
		{
			dir = "/proc/" + to_string(i) + "/cmdline";
			fin.open(dir);
			if(fin.is_open())
			{
				getline(fin,output);
				if(!output.empty())
				{
					found = output.find(last);
					if(found != string::npos)
					{
						//open status and get pid
						dir = "/proc/" + to_string(i) +
							"/status";
						pin.open(dir);
						for(int i = 0;i<5;i++)
						{
							getline(pin,id);
						}
						pin.close();
						id = id.substr(6);
						//add pid to vector
						nums.push_back(atoi(id.c_str()));
					}
				}
			}
			fin.close();
		}
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

/*********** Functions for prog2 ******************************/
void redir_in(char *args[])
{
	int fpt1, child_pid;
	int wait_pid, status;
	struct rusage usage;
	struct timeval user_time, sys_time;

	child_pid = fork();
	if(child_pid != 0)
	{
		cout << "Child PID: " << child_pid << endl;
	}

	if(child_pid == 0)
	{
		if ((fpt1 = open(args[2], O_RDONLY)) == -1)
		{
			printf("Unable to open %s for reading.\n", args[2]);
			exit(-1);
		}
		close(0);       // close child standard input
		dup(fpt1);      // redirect the child input
		close(fpt1);    // close unnecessary file descriptor

		execl(args[0], args[0], 0);
		perror("Exec failed: ");
		exit(6);
	}
	else
	{
		wait_pid = wait(&status);
		
		getrusage(RUSAGE_CHILDREN, &usage);
		user_time = usage.ru_utime;
		sys_time = usage.ru_stime;
		cout << "\nUser Time: " << user_time.tv_sec <<"."  					<<user_time.tv_usec 
		     << "\nSystem Time: " << sys_time.tv_sec <<"." 
		     << sys_time.tv_usec 
		     << "\nPage Faults: " << usage.ru_majflt 
		     << "\nSwaps: " << usage.ru_nswap << endl;
	}
}

void redir_out(char *args[])
{
	int fpt2, child_pid;
	int wait_pid, status;
	struct rusage usage;
	struct timeval user_time, sys_time;
	
	child_pid = fork();
	if(child_pid != 0)
	{
		cout << "Child PID: " << child_pid << endl;
	}

	if(child_pid == 0)
	{
		if ((fpt2 = creat(args[2], 0644)) == -1)
		{
		printf("Unable to open %s for writing.\n", args[2]);
		exit(-1);
		}
		close(1);       // close child standard output 
		dup(fpt2);      // redirect the child output 
		close(fpt2);    // close unnecessary file descriptor
	
		execl(args[0], args[0], 0);
		perror("Exec failed: ");
		exit(5);
	}
	else
	{
		wait_pid = wait(&status);
		
		getrusage(RUSAGE_CHILDREN, &usage);
		user_time = usage.ru_utime;
		sys_time = usage.ru_stime;
		cout << "\nUser Time: " << user_time.tv_sec <<"."  					<<user_time.tv_usec 
		     << "\nSystem Time: " << sys_time.tv_sec <<"." 
		     << sys_time.tv_usec 
		     << "\nPage Faults: " << usage.ru_majflt 
		     << "\nSwaps: " << usage.ru_nswap << endl;
	}
}

void change(char *args[])
{
	char temp[100];
	int child_pid, wait_pid, status;
	struct rusage usage;
	struct timeval user_time, sys_time;
	
	strcpy(temp,"cd ");
	strcat(temp,args[1]);

	child_pid = fork();
	if(child_pid != 0)
	{
		cout << "Child PID: " << child_pid << endl;
	}
	
	if(child_pid == 0)
	{
		execl("/bin/sh", "-c", temp, (const char *)0);
	}
	else
	{
		wait_pid = wait(&status);
	
		getrusage(RUSAGE_CHILDREN, &usage);
		user_time = usage.ru_utime;
		sys_time = usage.ru_stime;
		cout << "\nUser Time: " << user_time.tv_sec <<"."  					<<user_time.tv_usec 
		     << "\nSystem Time: " << sys_time.tv_sec <<"." 
		     << sys_time.tv_usec 
		     << "\nPage Faults: " << usage.ru_majflt 
		     << "\nSwaps: " << usage.ru_nswap << endl;
	}
}

void pipe(char *args[])
{
	char temp1[100];
	char temp2[100];
	int fd_pipe[2];
	int pid1;
	int pid2;
	int status;
	int wait_pid;
	struct rusage usage;
	struct timeval user_time, sys_time;
	
	strcpy(temp1,"/bin/");
	strcat(temp1,args[0]);
	
	strcpy(temp2,"/bin/");
	strcat(temp2,args[2]);

	pid1 = fork();
	if(pid1 != 0);
	{
		cout << "Child 1 PID: " << pid1 << endl;
	}
	
	if (pid1 == 0)
	{
		// child process executes here for input side of pipe

		pipe(fd_pipe);           // create pipe

		pid2 = fork();
		if(pid2 != 0);
		{
			cout << "Child 2 PID: " << pid2 << endl;
		}
		
		if (pid2 == 0)
		{
			// grandchild process executes here for output side of pipe
			close(1);              // close standard output
			dup(fd_pipe[1]);       // redirect the output
			close(fd_pipe[0]);     // close unnecessary file descriptor
			close(fd_pipe[1]);     // close unnecessary file descriptor
			execl(temp2, args[2], 0);
			printf("execl of /bin/cat failed\n");
			exit(1);
		}

		// back to process for input side of pipe

		close(0);              // close standard input
		dup(fd_pipe[0]);       // redirect the input
		close(fd_pipe[0]);     // close unnecessary file descriptor
		close(fd_pipe[1]);     // close unnecessary file descriptor
		execl(temp1, args[0], 0);
		printf("execl of /bin/sort failed\n");
		exit(1);
	}
	else
	{
		// parent process executes here
		wait_pid = wait(&status);
		
		getrusage(RUSAGE_CHILDREN, &usage);
		user_time = usage.ru_utime;
		sys_time = usage.ru_stime;
		cout << "\nUser Time: " << user_time.tv_sec <<"."  					<<user_time.tv_usec 
		     << "\nSystem Time: " << sys_time.tv_sec <<"." 
		     << sys_time.tv_usec 
		     << "\nPage Faults: " << usage.ru_majflt 
		     << "\nSwaps: " << usage.ru_nswap << endl;
	}
}

void sig(char *args[])
{
	int status;
	int wait_pid;
	int child_pid;
	struct rusage usage;
	struct timeval user_time, sys_time;
	
	child_pid = fork();
	if(child_pid != 0)
	{
		cout << "Child PID: " << child_pid << endl;
	}
	
	if(child_pid == 0)
	{
		execl("/bin/kill", "kill", args[2], args[1], 0);
		perror("Kill exec failed: ");
		exit(10);
	}
	else
	{
		// parent process executes here
		wait_pid = wait(&status);
		
		getrusage(RUSAGE_CHILDREN, &usage);
		user_time = usage.ru_utime;
		sys_time = usage.ru_stime;
		cout << "\nUser Time: " << user_time.tv_sec <<"."  					<<user_time.tv_usec 
		     << "\nSystem Time: " << sys_time.tv_sec <<"." 
		     << sys_time.tv_usec 
		     << "\nPage Faults: " << usage.ru_majflt 
		     << "\nSwaps: " << usage.ru_nswap << endl;
	}
}





































