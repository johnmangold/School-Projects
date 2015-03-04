#include "Hamming.h"

using namespace std;

//create functions for matrix multiplication and matrix addition

void matrix_mult(vector<vector<int>> farr, vector<vector<int>> sarr)
{
	int frow;
	int fcol;
	int srow;
	int scol;
	vector<vector<int>> answer;

	frow = farr.size();
	fcol = farr[0].size();
	
	srow = sarr.size();
	scol = sarr[0].size();
	
	for (int i=0;i != frow;i++)
	{
		vector<int> row;
		answer.push_back(row);
		for (int j=0;j != scol;j++)
		{
			int sum=0;
			for (int k=0;k != srow;k++)
			{
				sum += farr[i][k] * sarr[k][j];
			}
			answer.at(i).push_back(sum);
		}
	}
	
	/*for(int i=0;i<answer.size();i++)
	{
		for(int j=0;j<answer[i].size();j++)
		{
			cout << answer[i].at(j) << endl;
		}
	}*/
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
			cout << p[i].at(j) << endl;
		}
	}
	
}

void parity74(string last)
{	       
	vector<vector<int>> H = {{1,0,1,0,1,0,1},
		       		 {0,1,1,0,0,1,1},
		       		 {0,0,0,1,1,1,1}};
		       
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
		p.push_back(row);
		for(int j=0;j<1;j++)
		{
			piece = last[i];
			r[i].push_back(stoi(piece));
			cout << r[i][j] << endl;
		}
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
		p.push_back(row);
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
