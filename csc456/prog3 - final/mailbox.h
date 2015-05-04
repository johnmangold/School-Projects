#ifndef MAILBOX_H
#define MAILBOX_H

#include <sys/types.h> //used for semaphores and shared memory
#include <sys/ipc.h>  //used for semaphores and shared memory
#include <sys/shm.h>  //used for shared memory
#include <sys/sem.h>  //used for semaphores
#include <string>  //used for user input
#include <iostream> //used for console input/output
#include <vector>  //used for ids vector

using namespace std;

//globals
#define SHMKEY 1066
#define SEMKEY 12345

//prototypes
bool create_memory(vector<int> &ids, int mb_num, int mb_size);
bool delete_mailbox();
bool write_mailbox(int mb_num);
bool copy_mailbox(int mb_num1, int mb_num2);
bool read_mailbox(int mb_num);



#endif
