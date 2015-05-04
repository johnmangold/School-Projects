#ifndef PROG3_H
#define PROG3_H
#ifndef MAILBOX_H
#define MAILBOX_H

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>     
#include <sys/shm.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
using namespace std;

#define SHMKEY 1066

//function prototypes
void user_input(string input);
void ProcessSchedule();
int process_input(string input, int specs[][3], int process);
int setup(int specs[][3]);
int method_input(string MethodInput, int specs[][3], int &process);
int ManualSetup(int specs[][3]);
int RandomSetup(int specs[][3]);
void RoundRobin(int specs[][3], int process);
void PrioritySchedule(int specs[][3], int process);
void ShortestJobFirst(int specs[][3], int process);
void mmu();
void pra();
int mailbox();
bool create_memory(int &shmid, int mb_num, int mb_size, char *&address, int *&start);
bool delete_mailbox(int shmid);
bool write_mailbox(int *start, int mb_num, int mb_size);
bool copy_mailbox(int *start, int mb_num1, int mb_num2, int mb_size);

const int MAX_PROCESSES = 100;

struct virtual_info
{
	int pid;
	int data;
};

struct physical_info
{
	int frame;
	int data;
};

struct location_info
{
	int pid;
	int frame;
	bool in_main;
};

struct mailbox_info
{
	int number_of_boxes;
	int size_of_boxes;
	int group_shmid;
	int *begin;
	string message;
};

#endif
#endif
