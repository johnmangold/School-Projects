#include "mailbox.h"

using namespace std;

/************************************************************************
   Function: bool create_memory(vector<int> &ids, int mb_num, int mb_size
   Author: John Mangold, Colter Assman, Jason Anderson
   Description: Creates shared memory segments
   Parameters: vector<int> &ids - in/out - stores all the shmids
   		int mb_num - in - desired number of mailboxes
   		int mb_size - in - desired mailbox size in kilobytes
   		returns true - create memory segments
   		returns false - segments already exist
 ************************************************************************/
bool create_memory(vector<int> &ids, int mb_num, int mb_size)
{
	char *address;
	int shmid;
	int *start;

	//create shared memory blocks
	for(int i = 0;i < mb_num+1;i++)
	{
		shmid = shmget(SHMKEY+i, mb_size, IPC_CREAT | IPC_EXCL | 0666 );
		
		if( shmid < 0 )
		{
			return false;
		}
		ids.push_back(shmid);
	}
	
	//attach shared memory to process
	address = (char *) shmat(ids[0], 0, 0);
	
	//set up pointer to array of integers
	start = (int *) address;
	
	//assign size then shmids in sequential order in first block
	*start = mb_size;
	
	for( unsigned int i = 1; i <= ids.size(); i++)
	{
		*(start+i) = ids[i-1];
	}
	
	ids.clear();
	shmdt(address);
	
	return true;
}

/************************************************************************
   Function: bool delete_mailbox(
   Author: John Mangold, Colter Assman, Jason Anderson
   Description: Deletes shared memory segments with no processes attached
   Parameters: 	returns true - segments will be deleted
 ************************************************************************/
bool delete_mailbox()
{
	int shmid;
	int *start;
	
	//get shmid of first block and attach
	shmid = shmget(SHMKEY, 0, 0);
	start = (int *) shmat(shmid, 0, 0);

	for( unsigned int i = 1; *(start+i) != NULL; i++ )
	{
		shmctl(*(start+i), IPC_RMID, 0);
	}
	
	shmdt((char *) start);
	
	return true;
}

/************************************************************************
   Function: bool write_mailbox(int mb_num)
   Author: John Mangold, Colter Assman, Jason Anderson
   Description: Writes chars to desired mailbox
   Parameters: 	int mb_num - in - mailbox number to write to
   		returns true - Information was written to shared memory
 ************************************************************************/
bool write_mailbox(int mb_num)
{
	char *data;
	int shmid;
	int shmid1;
	int *start;
	unsigned int size;
	string s;
	struct sembuf wait, signal;
	int semid;
	unsigned short semval = 1;
	
	wait.sem_num = 0;
	wait.sem_op = -1;
	wait.sem_flg = SEM_UNDO;
	
	signal.sem_num = 0;
	signal.sem_op = 1;
	signal.sem_flg = SEM_UNDO;
	
	//create semaphore
	semid = semget(SEMKEY, 1, IPC_CREAT);
	
	//set semaphore value
	semctl(semid, 0, SETVAL, semval);
	
	//get shmid and size for appropriate mailbox
	//start+(mb_num+2)
	shmid = shmget(SHMKEY, 0, 0);
	start = (int *) shmat(shmid, 0, 0);
	size = *start;
	for(int i = 0; i < mb_num+2;i++)
	{
		shmid1 = *(start+i);
	}
	
	shmdt((char *) start);
	
	//attach to desired mailbox
	data = (char *) shmat(shmid1, 0, 0);
	if( data == (char *) -1)
	{
		cout << endl << "that didn't work" << endl;
	}
	
	//while input and not bigger than mailbox size
	//ctrl-d breaks this thing.  don't know why.  because programming.
	cout << "Enter data below.  Press \"Enter\" to commit.\n";
	getline(cin, s);
	
	if( s.size() >= size )
	{
		s = s.substr(0,size);
	}

	//set lock
	semop(semid, &wait, 1);

	for(unsigned int i = 0; i < s.size(); i++)
	{
		*(data+i) = s[i];
	}
	
	//unlock
	semop(semid, &signal, 1);
	
	//clean up semaphore and detach from shared memory
	semctl(semid, 0, IPC_RMID);
	shmdt(data);
	
	return true;
}

/************************************************************************
   Function: bool copy_mailbox(int mb_num1, int mb_num2)
   Author: John Mangold, Colter Assman, Jason Anderson
   Description: Copys contents from mb_num1 to mb_num2
   Parameters: 	int mb_num1 - in - mailbox number to copy from
   		int mb_num2 - in - mailbox number to copy to
   		returns true - Information was copied
 ************************************************************************/
bool copy_mailbox(int mb_num1, int mb_num2)
{
	int *start;
	char *start1;
	char *start2;
	int shmid;
	int shmid1;
	int shmid2;
	int size;
	struct sembuf wait, signal;
	int semid;
	unsigned short semval = 1;
	
	wait.sem_num = 0;
	wait.sem_op = -1;
	wait.sem_flg = SEM_UNDO;
	
	signal.sem_num = 0;
	signal.sem_op = 1;
	signal.sem_flg = SEM_UNDO;
	
	//create semaphore
	semid = semget(SEMKEY, 1, IPC_CREAT);
	
	//set semaphore value
	semctl(semid, 0, SETVAL, semval);
	
	//get shmid and size for both mailboxes
	shmid = shmget(SHMKEY, 0, 0);
	start = (int *) shmat(shmid, 0, 0);
	size = *start;
	
	for(int i = 0; i < mb_num1+2;i++)
	{
		shmid1 = *(start+i);
	}
	
	for(int i = 0; i < mb_num2+2;i++)
	{
		shmid2 = *(start+i);
	}
	
	shmdt((char *) start);
	
	//attach to both mailboxes
	start1 = (char *) shmat(shmid1, 0, 0);
	start2 = (char *) shmat(shmid2, 0, 0);
	
	//set lock
	semop(semid, &wait, 1);
	
	//copy contents from mailbox1 to mailbox2
	for( int i = 0; i < size; i++ )
	{
		*(start2+i) = *(start1+i);
	}
	
	//unlock
	semop(semid, &signal, 1);
	
	//remove semaphore and detach
	semctl(semid, 0, IPC_RMID);
	shmdt(start1);
	shmdt(start2);

	return true;
}

/************************************************************************
   Function: bool read_mailbox(int mb_num)
   Author: John Mangold, Colter Assman, Jason Anderson
   Description: Reads contents of mailbox and outputs to console
   Parameters: 	int mb_num - in - mailbox to read
   		returns true - mailbox contents were read
 ************************************************************************/
bool read_mailbox(int mb_num)
{
	int shmid;
	int shmid1;
	int *start;
	char *read;
	int size;
	int count = 0;
	
	//access first block and get size and mailbox shmid
	shmid = shmget(SHMKEY, 0, 0);
	start = (int *) shmat(shmid, 0, 0);
	size = *start;
	for(int i = 0; i < mb_num+2;i++)
	{
		shmid1 = *(start+i);
	}
	
	shmdt((char *) start);
	
	//attach to mailbox
	read = (char *) shmat(shmid1, 0, 0);
	
	//read through memory and output to screen
	while ( (*(read+count) != NULL) && (count < size))
	{
		cout << *(read+count);
		count++;
	}
	
	cout << endl;
	
	shmdt(read);
	
	return true;
}
































