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
#include <vector>

using namespace std;

#define SHMKEY 1066

//prototypes
bool create_memory(vector<int> &ids, int mb_num, int mb_size);
bool delete_mailbox();
bool write_mailbox(int mb_num);
bool copy_mailbox(int mb_num1, int mb_num2);
bool read_mailbox(int mb_num);




#endif
