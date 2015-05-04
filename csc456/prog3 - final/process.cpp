#include "Prog3.h"

/********************************************************************************//*****
* @Author Jason Anderson
*
* @Date 4-20-2015
*
* @Description  Gets the user input and sends the program to the process input function
***************************************************************************************/
void ProcessSchedule()
{
  string input;
  
  //loop user interface
  while(true)
  {
    //prompt user for input
    cout << "Choose a process scheduler to simulate: " << endl;
    cout << "RR for Round Robin, Priority, SJF for Shortest Job First, or all." << endl;
    cout << "Type exit to quit the program.  Type back to go back to main menu." << endl;
    cout << ">> ";

    //get user input
    getline(cin, input);
   
    int specs[MAX_PROCESSES][3];
    int process;
    int test = 0;
    
    test = process_input(input, specs, process);
    if(test == 1)
      return;
  }
}

/********************************************************************************//*****
* @Author Jason Anderson
*
* @Date 4-20-2015
*
* @Description  Gets the user input and sends the program to the correct section of the
* 		code.
***************************************************************************************/
int process_input(string input, int specs[][3], int process)
{
    //handle exit
    if(input == "exit")
      exit(0);

    else if(input == "back")
      return 1;

    //call the Round Robin function
    else if(input == "RR")
    {
      process = setup(specs);
      RoundRobin(specs, process);
    }
 
    //call the priority function
    else if(input == "Priority")
    {
      process = setup(specs);
      PrioritySchedule(specs, process);
    }
 
    //call the shortest job first function
    else if(input == "SJF")
    {
      process = setup(specs);
      ShortestJobFirst(specs, process);
    }
 
    //call all the jobs to compare
    else if(input == "all")
    {
      process = setup(specs);
      RoundRobin(specs, process);
      PrioritySchedule(specs, process);
      ShortestJobFirst(specs, process);
    }
 
    //handle extraneous input
    else
    {
      cout << "Invalid input.  Please try again." << endl;
      return -1;
    }
    cin.ignore();
}

/********************************************************************************//*****
* @Author Jason Anderson
*
* @Date 4-20-2015
*
* @Description  Sends the code to the correct function.
***************************************************************************************/
int setup(int specs[][3])
{
  string MethodInput;
  int process;
  srand(time(NULL));

  while(true)
  {
    int test = 0;
    cout << "Do you want to input process manually or have the processes chosen randomly?\n";
    cout << "(manual or random): ";
    getline(cin, MethodInput);
    test = method_input(MethodInput, specs, process);
    if(test == 1)
      return process;
  }
  return process;
}

/********************************************************************************//*****
* @Author Jason Anderson
*
* @Date 4-20-2015
*
* @Description  Gets the user input and sends the program to the correct section of the
* 		code.
***************************************************************************************/
int method_input(string MethodInput, int specs[][3], int &process)
{
  if(MethodInput == "manual")
  {
    process = ManualSetup(specs);
    return 1;
  }
  
  else if(MethodInput == "random")
  {
    process = RandomSetup(specs);
    return 1;
  }

  else
  {
    cout << "Invalid input. Please try again." << endl;
    return 2;
  }
}

/********************************************************************************//*****
* @Author Jason Anderson
*
* @Date 4-20-2015
*
* @Description  Lets the user input how many processes and the start and burst times
*		for each of the processes.
***************************************************************************************/
int ManualSetup(int specs[][3])
{
  int processes;

  //get how many processes to simulate from user
  cout << "How many processes do you want to simulate? (MAX = " << MAX_PROCESSES << ")\n";
  cout << ">>> ";
  cin >> processes;

  cout << "If you want to simulate a priority scheduler then please enter the processes\n";
  cout << "order of priority with the first process entered having the highest priority\n";
  cout << "and the last process entered the lowest priority.  Ignore this message if \n";
  cout << "you do not want to simulate a priority scheduler. \n" << endl;

  //get arrival time and burst time from user
  for(int i = 0; i < processes; i++)
  {
    specs[i][0] = i;
    cout << "Arrival Time for Process " << i << ": ";
    cin >> specs[i][1];
    cout << "Burst Time for Process " << i << ": ";
    cin >> specs[i][2];
  }
  
  int p = processes;
  //insertion sort to sort the processes by arrival time
  for(int i = 1; i < p; i++)
  {
    int temp[2];
    for(int j = 0; j < 3; j++)
      temp[j] = specs[i][j];
    int k = i;
    while(k > 0 && specs[k-1][1] > temp[1])
    {
      for(int l = 0; l < 3; l++)
        specs[k][l] = specs[k-1][l];
      k--;
      for(int l = 0; l < 3; l++)
        specs[k][l] = temp[l];
    }
  }

  p = processes;

  //if the earliest arrival time is not at time 0 change all of the arrival times
  // so that the first time is at time 0
  if(specs[0][1] != 0)
  {
    int offset = specs[0][1];
    for(int i = 0; i < p; i++)
      specs[i][1] -= offset;
  }  

  p = processes;
 
  cout << endl;

  for(int i = 0; i < p; i++)
  {
    for(int j = 0; j < 3; j++)
      cout << specs[i][j] << " ";
    cout << endl;
  }

  cout << endl;

  //return the number of processes
  return p;
}

/********************************************************************************//*****
* @Author Jason Anderson
*
* @Date 4-20-2015
*
* @Description  Lets the code randomly choose how many processes and their arrival and
*		burst times.
***************************************************************************************/
int RandomSetup(int specs[][3])
{
  int processes;

  processes = rand() % MAX_PROCESSES;

  //get arrival time and burst time from user
  for(int i = 0; i < processes; i++)
  {
    specs[i][0] = i;
    specs[i][1] = rand() % 25;
    specs[i][2] = rand() % 25;
  }
  
  int p = processes;
  //insertion sort to sort the processes by arrival time
  for(int i = 1; i < p; i++)
  {
    int temp[2];
    for(int j = 0; j < 3; j++)
      temp[j] = specs[i][j];
    int k = i;
    while(k > 0 && specs[k-1][1] > temp[1])
    {
      for(int l = 0; l < 3; l++)
        specs[k][l] = specs[k-1][l];
      k--;
      for(int l = 0; l < 3; l++)
        specs[k][l] = temp[l];
    }
  }

  p = processes;

  //if the earliest arrival time is not at time 0 change all of the arrival times
  // so that the first time is at time 0
  if(specs[0][1] != 0)
  {
    int offset = specs[0][1];
    for(int i = 0; i < p; i++)
      specs[i][1] -= offset;
  }  

  p = processes;
 
  cout << endl;

  cout << "There are " << processes << " processes.\n" << endl;;
  for(int i = 0; i < p; i++)
  {
    for(int j = 0; j < 3; j++)
      cout << specs[i][j] << " ";
    cout << endl;
  }

  cout << endl;

  //return the number of processes
  return p;
}

/********************************************************************************//*****
* @Author Jason Anderson
*
* @Date 4-20-2015
*
* @Description  The simulation of the round robin scheduler.  Runs a process until
*		completion or until the end of the quantum time.  Whichever happens
*		first.
***************************************************************************************/
void RoundRobin(int specs[][3], int process)
{
  //prompt user for the quantum time
  int quantumTime;
  cout << "Please specify a time increment for the Round Robin scheduler in ms: ";
  cin >> quantumTime;

//Initalize variables
  int time = 0;
  int prevTime = 0;
  int elapsedTime = 0;
  int curr_process = 0;
  bool flag = true;
  bool RRflag = false;
  int counter = 0;
  int nextProcess;
  double avgWaitTime = 0;

  cout << "process: " << process << endl;

  int processDetails[MAX_PROCESSES][3];
  for(int process_num = 0; process_num < process; process_num++)
    for(int detail = 0; detail < 3; detail++)
      processDetails[process_num][detail] = specs[process_num][detail];

  cout << "Start of Round Robin scheduler." << endl << endl;

  while(flag)
  {
    if(quantumTime < processDetails[curr_process][2])
    {
      prevTime = time;
      time += quantumTime;
      if(processDetails[curr_process][2] != 0)
      {
        elapsedTime = time - prevTime;
        processDetails[curr_process][2] -= elapsedTime;
      }
    }
    else 
    {
      //Update time to the burst of the current process
      time += processDetails[curr_process][2];
      processDetails[curr_process][2] = 0;
    }

    //Set nextProcess to curr_process+1 so that the loop knows what process to start with
    nextProcess = curr_process + 1;
    if(curr_process + 1 == process)
      nextProcess = 0;

    //Set flag to false so if there are no more processes to schedule then the while loop
    //will be broken.
    flag = false;
    RRflag = false;
    counter = 0;
    
    //add the wait time of a finished process to average wait time.
    //wait time is the (finish time - start time) - length of process.
    if(processDetails[curr_process][2] == 0)
      avgWaitTime += (time - specs[curr_process][1] - specs[curr_process][2]);

    cout << "Time: " << time << " Process: " << processDetails[curr_process][0] << endl;

    //Find the next process with burst time left
    while(counter != process)
    {
      //Make sure the burst isn't 0.
      if(processDetails[nextProcess][2] > 0)
      {
        //Find the next process that still have time left on its burst.
        if((processDetails[nextProcess][1] <= time) && RRflag == false)
        {
          curr_process = nextProcess;
          flag = true;
          RRflag = true;
        }
      }
      nextProcess++;
      counter++;
      if(nextProcess == process)
        nextProcess = 0;
    }
  }
  avgWaitTime /= (double)process;
  cout << endl;
  cout << "Average wait time for Round Robin: " << avgWaitTime << endl << endl;
}

/********************************************************************************//*****
* @Author Jason Anderson
*
* @Date 4-20-2015
*
* @Description  The simulation of the priority scheduler.  Runs a process until
*		completion or until a new process enters with a higher priority.
*		whichever happens first.
***************************************************************************************/
void PrioritySchedule(int specs[][3], int process)
{
  //Initalize variables
  int time = 0;
  int prevTime = 0;
  int elapsedTime = 0;
  int curr_process = 0;
  int next_process = 1;
  int timeToNextProcess = 0;
  bool flag = true;
  int min[2];
  int next[2];
  double avgWaitTime = 0;

  int processDetails[MAX_PROCESSES][3];
  for(int process_num = 0; process_num < process; process_num++)
    for(int detail = 0; detail < 3; detail++)
      processDetails[process_num][detail] = specs[process_num][detail];

  cout << "Start of Priority scheduler." << endl << endl;

  while(flag)
  {
    timeToNextProcess = processDetails[next_process][1] - time;
    if((processDetails[next_process][1] < 0) || 
       (processDetails[curr_process][2] < timeToNextProcess))
    {
      //Update time to the burst of the current process
      time += processDetails[curr_process][2];
      processDetails[curr_process][2] = 0;
    }
    else
    {
      //Update elapsed time
      prevTime = time;
      time = processDetails[next_process][1];
      if(processDetails[curr_process][2] != 0)
      {
        elapsedTime = time - prevTime;
        processDetails[curr_process][2] -= elapsedTime;
      }
    }

    //Set min and next to 1 higher than the max number of processes
    min[0] = MAX_PROCESSES + 1;
    next[0] = MAX_PROCESSES + 1;

    //Set flag to false so if there are no more processes to schedule then the while loop
    //will be broken.
    flag = false;
    
    //Find the process with the highest priority of the processes that have been started.
    for(int i = 0; i < process; i++)
    {
      //Make sure the burst isn't 0.
      if(processDetails[i][2] > 0)
      {
        //Find the process with highest priority
        if((processDetails[i][1] <= time) && (processDetails[i][0] < min[0]))
        {
          min[0] = processDetails[i][0];
          min[1] = i;
          flag = true;
        }
      }
      //Find the next process to start.  Isn't always going to be curr_process+1
      //If we have already done it the start will be -1.
      if(processDetails[i][1] >= 0)
      {
        if((processDetails[i][1] > time) && (processDetails[i][1] < next[0]))
        {
          next[0] = processDetails[i][1];
          next[1] = i;
        }
      }
    }
    cout << "Time: " << time << " Process: " << processDetails[curr_process][0] << endl;
    //add the wait time of a finished process to average wait time.
    //wait time is the (finish time - start time) - length of process.
    if(processDetails[curr_process][2] == 0)
      avgWaitTime += (time - specs[curr_process][1] - specs[curr_process][2]);
    curr_process = min[1];
    if(next_process != -1)
      processDetails[next_process][1] = -1;
    next_process = next[1];
  }
  avgWaitTime /= (double)process;
  cout << endl;
  cout << "Average wait time for Priority: " << avgWaitTime << endl << endl;
}

/********************************************************************************//*****
* @Author Jason Anderson
*
* @Date 4-20-2015
*
* @Description  The simulation of the shortest job first scheduler.  Runs the process 
*		with the least amount of time to completion or until a new process
*		arrives.  Whichever happens first.  It then updates the burst times and
*		checks to see if it needs to change which process is to be run.
***************************************************************************************/
void ShortestJobFirst(int specs[][3], int process)
{
  //Initalize variables
  int time = 0;
  int prevTime = 0;
  int elapsedTime = 0;
  int curr_process = 0;
  int next_process = 1;
  int timeToNextProcess = 0;
  int min[2];
  int next[2];
  double avgWaitTime = 0;

  int processDetails[MAX_PROCESSES][3];
  for(int process_num = 0; process_num < process; process_num++)
    for(int detail = 0; detail < 3; detail++)
      processDetails[process_num][detail] = specs[process_num][detail];

  //Set min to 0 so it enters the while loop
  min[0] = 0;

  cout << "Start of SJF scheduler." << endl;

  while(min[0] != 10000)
  {
    timeToNextProcess = processDetails[next_process][1] - time;
    if((processDetails[next_process][1] == -1) || 
       (processDetails[curr_process][2] < timeToNextProcess))
    {
      time += processDetails[curr_process][2];
      processDetails[curr_process][2] = 0;
    }
    else
    {
      prevTime = time;
      time = processDetails[next_process][1];
      if(processDetails[curr_process][2] != 0)
      {
        elapsedTime = time - prevTime;
        processDetails[curr_process][2] -= elapsedTime;
      }
    }
    //Set min[0] to a big number so that the for loop finds the true min value of the 
    //Process times.
    min[0] = 10000;
    next[0] = 10000;
    //Find the process with the smallest burst of the processes that have been started.
    for(int i = 0; i < process; i++)
    {
      //Make sure the burst isn't 0.
      if(processDetails[i][2] > 0)
      {
        //Find the process with lowest remaining burst
        if((processDetails[i][1] <= time) && (processDetails[i][2] < min[0]))
        {
          min[0] = processDetails[i][2];
          min[1] = i;
        }
      }
      //Find the next process to start.  Isn't always going to be curr_process+1
      //If we have already done it the start will be -1.
      if(processDetails[i][1] >= 0)
      {
        if((processDetails[i][1] > time) && (processDetails[i][1] < next[0]))
        {
          next[0] = processDetails[i][1];
          next[1] = i;
        }
      }
    }
    cout << "Time: " << time << " Process: " << processDetails[curr_process][0] << endl;
    //add the wait time of a finished process to average wait time.
    //wait time is the (finish time - start time) - length of process.
    if(processDetails[curr_process][2] == 0)
      avgWaitTime += (time - specs[curr_process][1] - specs[curr_process][2]);
    curr_process = min[1];
    if(next_process != -1)
      processDetails[next_process][1] = -1;
    next_process = next[1];

  }
  avgWaitTime /= (double)process;
  cout << endl;
  cout << "Average wait time for SJF: " << avgWaitTime << endl << endl;
}
