#include "mailbox.h"

using namespace std;

bool create_memory(int &shmid, int mb_num, int mb_size, char *address, int *start)
{
	//create shared memory block using info
	shmid = shmget(SHMKEY, mb_num*mb_size, IPC_CREAT | IPC_EXCL | 0666);
	
	//check that shared memory created successfully
	if(shmid < 0)
	{
		cout << "\nMailbox already exists.\n"
			<< "Either delete old mailbox or proceed to use current mailbox.\n";
			
		return false;
	}
	
	//attach shared memory to process
	address = (char *) shmat(shmid, 0, 0);
	
	//set up pointer to array of integers
	start = (int *) address;
	
	return true;
}

bool delete_mailbox(int shmid)
{
	if( shmctl(shmid, IPC_RMID, 0) == -1)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool write_mailbox(int *start, int mb_num)
{
	*(start + 1) = 55;
	
	cout << endl << *(start + 1) << endl;
	
	return true;
}


































