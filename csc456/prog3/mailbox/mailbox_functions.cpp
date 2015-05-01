#include "mailbox.h"

using namespace std;

bool create_memory(int &shmid, int mb_num, int mb_size, char *address, int *start)
{
	//create shared memory block using info
	shmid = shmget(SHMKEY, (mb_num+1)*mb_size, IPC_CREAT | IPC_EXCL | 0666 );
	if( shmid < 0 )
	{
		shmid = shmget(SHMKEY, 0, 0 );
		if( shmid < 0 )
		{
			cout << "Couldn't get shmid.\n";
			exit(EXIT_SUCCESS);
		}
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

bool write_mailbox(int *start, int mb_num, int mb_size)
{
	cout << endl << "test 1" << endl;

	*start = 55;
	
	cout << endl << "test 2" << endl;
	
	cout << endl << *start << endl;
	
	cout << endl << "test 3" << endl;
	
	return true;
}


































