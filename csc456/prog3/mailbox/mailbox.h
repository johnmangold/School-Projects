#ifndef MAILBOX_H
#define MAILBOX_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>     
#include <sys/shm.h>
#include <errno.h>
#include <unistd.h>
#include <string>
#include <iostream>

using namespace std;

#define SHMKEY 1066

//prototypes
bool create_memory(int &shmid, int mb_num, int mb_size, char *address, int *start);
bool delete_mailbox(int shmid);
bool write_mailbox(int *start, int mb_num, int mb_size);






#endif
