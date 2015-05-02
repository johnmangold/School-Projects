#include "mailbox.h"

using namespace std;

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

bool write_mailbox(int mb_num)
{
	char c;
	char *data;
	int shmid;
	int shmid1;
	int *start;
	unsigned int size;
	int count = 0;
	string s;
	
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
	cout << "Enter data below.  Ctrl-d to stop.\n";
	getline(cin, s);
	
	if( s.size() >= size )
	{
		s = s.substr(0,size);
	}

	for(unsigned int i = 0; i < s.size(); i++)
	{
		*(data+i) = s[i];
	}
	
	shmdt(data);
	
	return true;
}

bool copy_mailbox(int mb_num1, int mb_num2)
{
	int *start;
	char *start1;
	char *start2;
	int shmid;
	int shmid1;
	int shmid2;
	int size;
	
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
	
	//copy contents from mailbox1 to mailbox2
	for( int i = 0; i < size; i++ )
	{
		*(start2+i) = *(start1+i);
	}
	
	shmdt(start1);
	shmdt(start2);

	return true;
}

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
































