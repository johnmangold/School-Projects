#include "Hamming.h"

using namespace std;

//create functions for matrix addition
//finish parity.  figure out next step after getting syndrome
//finish decode

void matrix_mult(vector<vector<int>> farr, vector<vector<int>> sarr,
		 vector<vector<int>> &oarr)
{
	int frow;
	int fcol;
	int srow;
	int scol;

	frow = farr.size();
	fcol = farr[0].size();
	
	srow = sarr.size();
	scol = sarr[0].size();
	
	if(fcol != srow)
	{
		cout << "Number of columns in first matrix must be equal to\n"
			<< "the number of rows in the second column.\n";
		oarr[0].push_back(-1);
		return;
	}
	
	for (int i=0;i != frow;i++)
	{
		vector<int> row;
		oarr.push_back(row);
		for (int j=0;j != scol;j++)
		{
			int sum=0;
			for (int k=0;k != srow;k++)
			{
				sum += farr[i][k] * sarr[k][j];
			}
			oarr.at(i).push_back(sum%2);
		}
	}
}

bool get_parts(string option, string &first, string &last)
{
	size_t index;
	
	index = option.find_first_not_of(" \t");
	option = option.substr(index);
	index = option.find_first_of(" ");
	first = option.substr(0, index);
	last = option.substr(index+1);
	
	//check that last is all ones and zeroes
	index = last.find_first_not_of("01");
	if( index != string::npos)
	{
		cout << "Bit string must be only ones and zeroes ex. 1001\n";
		return false;
	}
	else
	{
		return true;
	}
}

void encode74(string last)
{
	vector<vector<int>> G = {{1,1,0,1},
				 {1,0,1,1},
				 {1,0,0,0},
				 {0,1,1,1},
				 {0,1,0,0},
				 {0,0,1,0},
				 {0,0,0,1}};
		       
	vector<vector<int>> p;
	vector<vector<int>> message;
	string piece;

	if(last.length() != 4)
	{
		cout << "Bit string must be 4 bits.\n";
		return;
	}
	
	for(int i=0;i<4;i++)
	{
		vector<int> row;
		p.push_back(row);
		for(int j=0;j<1;j++)
		{
			piece = last[i];
			p[i].push_back(stoi(piece));
		}
	}
	
	matrix_mult(G,p,message);
	if(message[0].at(0) == -1)
	{
		cout 
		<< "Matrices were not appropriate sizes for multiplication.\n";
		return;
	}
	else
	{
		cout << "( ";
		for(unsigned int i=0;i<message.size();i++)
		{
			for(unsigned int j=0;j<message[0].size();j++)
			{
				cout << message[i].at(j) << " ";
			}
		}
		cout << ")T\n";
	}
	
}

void parity74(string last)
{	       
	vector<vector<int>> H = {{1,0,1,0,1,0,1},
		       		 {0,1,1,0,0,1,1},
		       		 {0,0,0,1,1,1,1}};
		       
	vector<vector<int>> r;
	vector<vector<int>> syndrome;
	vector<vector<int>> fix;
	string piece;

	if(last.length() != 7)
	{
		cout << "Bit string must be 7 bits.\n";
		return;
	}
	
	for(int i=0;i<7;i++)
	{
		vector<int> row;
		r.push_back(row);
		for(int j=0;j<1;j++)
		{
			piece = last[i];
			r[i].push_back(stoi(piece));
			cout << r[i][j] << endl;
		}
	}
	
	matrix_mult(H,r,syndrome);
	if(syndrome[0].at(0) == -1)
	{
		cout 
		<< "Matrices were not appropriate sizes for multiplication.\n";
		return;
	}
	else
	{
		cout << "Syndrome Vector: ( ";
		for(unsigned int i=0;i<syndrome.size();i++)
		{
			for(unsigned int j=0;j<syndrome[0].size();j++)
			{
				cout << syndrome[i].at(j) << " ";
			}
		}
		cout << ")T\n";
	}
	
	if(syndrome[0].at(0) != 0 || syndrome[1].at(0) != 0 || 
		syndrome[2].at(0) != 0)
	{
		int index;
		
		if(syndrome[0].at(0) != 0)
		{
			index = 1;
		}
		else if(syndrome[1].at(0) != 0)
		{
			index = 2;
		}
		else if(syndrome[2].at(0) != 0)
		{
			index = 3;
		}
		
		if(r[0].at(
	}

}

void decode74(string last)
{
	vector<vector<int>> R = {{0,0,1,0,0,0,0},
		       		 {0,0,0,0,1,0,0},
		       		 {0,0,0,0,0,1,0},
		       		 {0,0,0,0,0,0,1}};
		       
	vector<vector<int>> r;
	string piece;

	if(last.length() != 7)
	{
		cout << "Bit string must be 7 bits.\n";
		return;
	}
	
	for(int i=0;i<7;i++)
	{
		vector<int> row;
		r.push_back(row);
		for(int j=0;j<1;j++)
		{
			piece = last[i];
			r[i].push_back(stoi(piece));
			cout << r[i][j] << endl;
		}
	}

}

void encode1511(string last)
{
	if(last.length() != 11)
	{
		cout << "Bit string must be 11 bits.\n";
		return;
	}

	cout << last << endl;
}

void parity1511(string last)
{
	if(last.length() != 15)
	{
		cout << "Bit string must be 15 bits.\n";
		return;
	}

	cout << last << endl;
}

void decode1511(string last)
{
	if(last.length() != 15)
	{
		cout << "Bit string must be 15 bits.\n";
		return;
	}

	cout << last << endl;
}

void h74()
{
	bool good;
	string option;
	string first;
	string last;

	cout << "encode, parity, or decode: ";
	getline(cin, option);
	
	good = get_parts(option, first, last);
	if(good == false)
	{
		return;
	}
	
	if(first == "encode")
	{
		encode74(last);
	}
	else if(first == "parity")
	{
		parity74(last);
	}
	else if(first == "decode")
	{
		decode74(last);
	}
}

void h1511()
{
	bool good;
	string option;
	string first;
	string last;

	cout << "encode, parity, or decode: ";
	getline(cin, option);
	
	good = get_parts(option, first, last);
	if(good == false)
	{
		return;
	}
	
	if(first == "encode")
	{
		encode1511(last);
	}
	else if(first == "parity")
	{
		parity1511(last);
	}
	else if(first == "decode")
	{
		decode1511(last);
	}
}
