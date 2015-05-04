#include "Prog3.h"

/********************************************************************************//*****
* @Author Colter Assman
*
* @Date 5/3/2015
*
* @Description  This returns the page in the frame if it is in it. Otherwise it returns
				-1. Used to check if page is already in frame. 
***************************************************************************************/
int found(int x,vector<int> vec)
{
	for(int i = 0; i < vec.size(); i++)
	{
		if(vec[i] == x)
			return(i);
	}

	return(-1);
}

/********************************************************************************//*****
* @Author Colter Assman
*
* @Date 5/3/2015
*
* @Description  This converts the page list the user gives and puts the pages into the 
				frame. 
***************************************************************************************/
vector<int> convertToArray(string pagelist)
{
	//int prev = 0;
	int comma;
	int pos = 0;
	int count = 0;
	vector<int> tempArray;

	//find the comma and get everything between the commas
	while((comma = pagelist.find(",", pos)) != string::npos)
	{
		tempArray.push_back(atoi((pagelist.substr(pos, comma-pos)).c_str()));
		count++;
		pos = comma + 1;
	}
	tempArray.push_back(atoi((pagelist.substr(pos, pagelist.length() - pos)).c_str()));

	return tempArray;
}

/********************************************************************************//*****
* @Author Colter Assman
*
* @Date 5/3/2015
*
* @Description  This is the first in first out page replacement algorithm. It replace
				the oldest page in the frame and replaces it with the new page.
***************************************************************************************/
void fifo()
{
	int max, res, page;
	int faults = 0;
	int nofaults = 0;
	string pagelist;
	int c=0;
	vector<int> pagearray;
	vector<int> frames;

	cout<<"\nEnter the maximum number of frames in the main memory:  ";
	cin >> max;

	for(int i = 0; i < max; i++)
		frames.push_back(-1);

	cout << "\nEnter the sequence of page requests(#,#,#,...):  ";

	cin >> pagelist;
	pagearray = convertToArray(pagelist);
	for (int i = 0; i < pagearray.size(); i++)
	{

		page = pagearray[i];

		if((res = found(page,frames)) != -1) 
		{
			cout << "page " << page << " already exists in frame " << res << "\n\n";
			nofaults++;
		}
		else
		{
			cout << "page fault has occured" << endl;
			//cout << "page "<< page << " has been allocated frame " << c % max 
			//	<< " by replacing page " << frames[c % max] << "\n\n";
			frames[c % max] = page;
			c++;
			faults++;
		}
	}

	cout << "Total faults: " << faults << endl;
	cout << "Total accesses: " << nofaults << endl;

}

/********************************************************************************//*****
* @Author Colter Assman
*
* @Date 5/3/2015
*
* @Description  This is the Least Recently Used algorithm. It replaces the page that
				has been least recently referenced.
***************************************************************************************/
void lru()
{
	int max, res, page;
	int faults = 0;
	int nofaults = 0;
	string pagelist;
	vector<int> pagearray;
	vector<int> frames;

	cout<<"\nEnter the maximum number of frames in the main memory:  ";
	cin >> max;

	for(int i = 0; i < max; i++)
		frames.push_back(-1);

	cout << "\nEnter the sequence of page requests(#,#,#,...):  ";

	cin >> pagelist;
	pagearray = convertToArray(pagelist);
	for (int i = 0; i < pagearray.size(); i++)
	{

		page = pagearray[i];

		if((res = found(page,frames)) != -1) 
		{
			//put the page in front of the the queue
			cout << "page " << page << " already exists in frame " << res << "\n\n";
			frames.erase(frames.begin()+res);
			frames.insert(frames.begin(),page);

			nofaults++;
		}
		else
		{
			cout << "page fault has occured" << endl;
			//cout << "page "<< page << " has been allocated frame " << c % max 
			//	<< " by replacing page " << frames[c % max] << "\n\n";
			frames.insert(frames.begin(),page);
			frames.pop_back();
			faults++;
		}
	}

	cout << "Total faults: " << faults << endl;
	cout << "Total accesses: " << nofaults << endl;

}

/********************************************************************************//*****
* @Author Colter Assman
*
* @Date 5/3/2015
*
* @Description  This is the Optimal algorithm. This looks at what is coming in the future
				for pages and decides what would be the best page to replace. For this, 
				I decided to look 3 pages ahead and decide based off of that. If the page
				is referenced in the next 3 pages, it is not replaced. 
***************************************************************************************/
void opt()
{
	int max, res, page;
	int faults = 0;
	int nofaults = 0;
	string pagelist;
	bool frameflag = false;
	vector<int> pagearray;
	vector<int> frames;
	vector<bool> check;

	cout<<"\nEnter the maximum number of frames in the main memory:  ";
	cin >> max;

	for(int i = 0; i < max; i++)
	{
		frames.push_back(-1);
		check.push_back(false);
	}

	cout << "\nEnter the sequence of page requests(#,#,#,...):  ";

	cin >> pagelist;
	pagearray = convertToArray(pagelist);
	for (int i = 0; i < pagearray.size(); i++)
	{

		page = pagearray[i];

		if((res = found(page,frames)) != -1) 
		{
			cout << "page " << page << " already exists in frame " << res << "\n\n";
			nofaults++;
		}
		else
		{
			cout << "page fault has occured" << endl;
			//cout << "page "<< page << " has been allocated frame " << c % max 
			//	<< " by replacing page " << frames[c % max] << "\n\n";
			for (int j = 0; j < frames.size(); j++)
			{
				if (frames[j] == pagearray[i+1] or frames[j] == pagearray[i+2] or frames[j] == pagearray[i+3])
				{
					check[j] = true;
				}
				else
					check[j] = false;
			}

			for (int j = 0; j < check.size(); j++)
			{
				if (!check[j])
				{
					frames[j] = page;
					frameflag = true;
					break;
				}
			}

			if (frameflag == false)
				frames[frames.size()-1] = page;

			frameflag = false;
			faults++;
		}
	}

	cout << "Total faults: " << faults << endl;
	cout << "Total accesses: " << nofaults << endl;

}

/********************************************************************************//*****
* @Author Colter Assman
*
* @Date 5/3/2015
*
* @Description  This is the Clock algorithm. Once a page gets referenced, I set a bit
				in the bits vector. This is used when a page is going to be replaced. If
				this bit is set, it skips that page and sets that bit to 0. If a page
				has 0 bit set, it is replaced. 
***************************************************************************************/
void myclock()
{
	int max, res, page;
	int faults = 0;
	int nofaults = 0;
	string pagelist;
	int c=0;
	vector<int> pagearray;
	vector<int> frames;
	vector<int> bits;

	cout<<"\nEnter the maximum number of frames in the main memory:  ";
	cin >> max;

	for(int i = 0; i < max; i++)
	{
		frames.push_back(-1);
		bits.push_back(-1);
	}

	cout << "\nEnter the sequence of page requests(#,#,#,...):  ";

	cin >> pagelist;
	pagearray = convertToArray(pagelist);
	for (int i = 0; i < pagearray.size(); i++)
	{

		page = pagearray[i];

		if((res = found(page,frames)) != -1) 
		{
			cout << "page " << page << " already exists in frame " << res << "\n\n";
			bits[res] = 1;
			nofaults++;
		}
		else
		{
			cout << "page fault has occured" << endl;
			//cout << "page "<< page << " has been allocated frame " << c % max 
			//	<< " by replacing page " << frames[c % max] << "\n\n";
			while(1)
			{
				if (bits[c % max] == 1)
				{
					bits[c % max] = 0;
					c++;
				}
				else if (bits[c % max] == 0)
				{
					frames[c % max] = page;
					break;
				}
				else
				{
					frames[c % max] = page;
					bits[c % max] = 0;
					break;
				}
			}
			c++;
			faults++;
		}
	}
	
	cout << "Total faults: " << faults << endl;
	cout << "Total accesses: " << nofaults << endl;
}


/********************************************************************************//*****
* @Author Colter Assman
*
* @Date 5/3/2015
*
* @Description  This is the least frequently used algorithm. It keeps a count of the 
				number of times a page has been used. It replaced the page with the 
				smallest count.
***************************************************************************************/
void lfu()
{
	int max, res, page;
	int faults = 0;
	int nofaults = 0;
	string pagelist;
	int c = 0;
	int smallest;
	int small_place;
	vector<int> pagearray;
	vector<int> frames;
	int count[1000];

	cout<<"\nEnter the maximum number of frames in the main memory:  ";
	cin >> max;

	for(int i = 0; i < max; i++)
		frames.push_back(-1);

	for(int i = 0; i < 1000; i++)
		count[i] = 0;

	cout << "\nEnter the sequence of page requests(#,#,#,...):  ";

	cin >> pagelist;
	pagearray = convertToArray(pagelist);
	for (int i = 0; i < pagearray.size(); i++)
	{

		page = pagearray[i];

		if((res = found(page,frames)) != -1) 
		{
			cout << "page " << page << " already exists in frame " << res << "\n\n";
			count[page] += 1;
			nofaults++;
		}
		else
		{
			cout << "page fault has occured" << endl;
			//cout << "page "<< page << " has been allocated frame " << c % max 
			//	<< " by replacing page " << frames[c % max] << "\n\n";

			count[page] += 1;

			if (c < max)
			{
				frames[c] = page;
				c++;
				faults++;
				continue;
			}
				

			smallest = count[frames[0]];
			small_place = 0;
			for (int i = 0; i < frames.size(); i++)
			{
				if (count[frames[i]] < smallest)
				{
					smallest = count[frames[i]];
					small_place = i;
				}
			}

			frames[small_place] = page;
			faults++;
		}
	}

	cout << "Total faults: " << faults << endl;
	cout << "Total accesses: " << nofaults << endl;

}

/********************************************************************************//*****
* @Author Colter Assman
*
* @Date 5/3/2015
*
* @Description  This is the Second chance algorithm. It is just like the clock algorithm
				except there is another bit that is set when a page is replaced. When a
				page comes up for replacement and one of the bits are set, it is set to 0.
				If both are set to 1, only the respective one is set to 0. If both are 0,
				then the page is replaced. 
***************************************************************************************/
void sec_ch()
{
	int max, res, page;
	int faults = 0;
	int nofaults = 0;
	string pagelist;
	int c=0;
	vector<int> pagearray;
	vector<int> frames;
	vector<int> used;
	vector<int> dirty;

	cout<<"\nEnter the maximum number of frames in the main memory:  ";
	cin >> max;

	for(int i = 0; i < max; i++)
	{
		frames.push_back(-1);
		used.push_back(-1);
		dirty.push_back(-1);
	}

	cout << "\nEnter the sequence of page requests(#,#,#,...):  ";

	cin >> pagelist;
	pagearray = convertToArray(pagelist);
	for (int i = 0; i < pagearray.size(); i++)
	{

		page = pagearray[i];

		if((res = found(page,frames)) != -1) 
		{
			cout << "page " << page << " already exists in frame " << res << "\n\n";
			used[res] = 1;
			nofaults++;
		}
		else
		{
			cout << "page fault has occured" << endl;
			//cout << "page "<< page << " has been allocated frame " << c % max 
			//	<< " by replacing page " << frames[c % max] << "\n\n";
			while(1)
			{
				if (used[c % max] == 1)
				{
					used[c % max] = 0;
					c++;
				}
				else if (dirty[c % max] == 1)
				{
					dirty[c % max] = 0;
					c++;
				}
				else
				{
					frames[c % max] = page;
					dirty[c % max] = 1;
					break;
				}
			}
			c++;
			faults++;
		}
	}


	cout << "Total faults: " << faults << endl;
	cout << "Total accesses: " << nofaults << endl;
}

/********************************************************************************//*****
* @Author Colter Assman
*
* @Date 5/3/2015
*
* @Description  This is used to choose which algorithm you want to run.
***************************************************************************************/
void pra()
{
  int choice = 0;

	while (choice != -1)
	{
		cout << "\nPlease select a page replacement algorithm" << endl;
		cout << "------------------------------------------" << endl;
		cout << "1: FIFO (first-in first-out)" << endl;
		cout << "2: Optimal" << endl;
		cout << "3: LRU (least recently used)" << endl;
		cout << "4: LFU (least frequently used)" << endl;
		cout << "5: Clock" << endl;
		cout << "6: Second Chance" << endl;
		cout << "-1: Back to main menu" << endl;
    cout << "-2: Exit program" << endl << endl;
		cout << "Your choice: ";

		cin >> choice;

		cout << endl;

		switch (choice)
		{
			case 1:
				fifo();
				break;
			case 2:
				opt();
				break;
			case 3:
				lru();
				break;
			case 4:
				lfu();
				break;
			case 5:
				myclock();
				break;
			case 6:
				sec_ch();
				break;
			case -1:
				break;
      case -2:
        exit(0);
			default:
				cout << "Please enter a valid choice" << endl;
		}
	}
}
