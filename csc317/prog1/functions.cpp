#include "Hamming.h"

using namespace std;

/************************************************************************
   Function: void matrix_mult(vector<vector<int>> farr,
   			      vector<vector<int>> sarr,
   			      vector<vector<int>> &oarr)
   Author: John Mangold
   Description: Multiplies matrix farr and matrix sarr and stores the
   		resulting matrix in oarr which is pass by reference.
   Parameters: in - vector<vector<int>> farr - first matrix
   	       in - vector<vector<int>> sarr - second matrix
   	       in/out - vector<vector<int>> &oarr - results matrix
 ************************************************************************/
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

/************************************************************************
   Function: bool get_parts(string option, string &first, string &last)
   Author: John Mangold
   Description: Separates input and stores each part in a string.
   		Checks input to insure it is only 1s and 0s.
   Parameters: in - string option - string containing the choice and bit string
   	       in/out - string &first - string for storing the first part
   	       in/out - string &second - string for storing the second part
   	       out - bool true - string is only 1s and 0s
   	       out - bool false - string is not only 1s and 0s
 ************************************************************************/
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

/************************************************************************
   Function: void encode74(string last)
   Author: John Mangold
   Description: Encodes a 4 bit data string with 3 parity bits.
   		Calls necessary function matrix_mult.
   Parameters: in - string last - string containing 4 bit data string
 ************************************************************************/
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

/************************************************************************
   Function: void parity74(string last)
   Author: John Mangold
   Description: Checks given 7 bit string for proper parity.  If it is
   		good then the 3 bit zero vector is printed.  If it is not
   		good then the 3 bit syndrome vector is printed followed by
   		the corrected message.
   Parameters: in - string last - string containing 7 bit string
 ************************************************************************/
void parity74(string last)
{	       
	vector<vector<int>> H = {{1,0,1,0,1,0,1},
		       		 {0,1,1,0,0,1,1},
		       		 {0,0,0,1,1,1,1}};
		       
	vector<vector<int>> r;
	vector<vector<int>> syndrome;
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
		string bin;
		int off_bit;
		
		bin.append(to_string(syndrome[2].at(0)));
		bin.append(to_string(syndrome[1].at(0)));
		bin.append(to_string(syndrome[0].at(0)));
		
		off_bit = bitset<3>(bin).to_ulong();
		
		if(r[off_bit-1].at(0) == 1)
		{
			r[off_bit-1].at(0) = 0;
		}
		else
		{
			r[off_bit-1].at(0) = 1;
		}
		
		cout << "Corrected Message: ( ";
		for(unsigned int i=0;i<r.size();i++)
		{
			for(unsigned int j=0;j<r[0].size();j++)
			{
				cout << r[i].at(j) << " ";
			}
		}
		cout << ")T\n";
	}
	

}

/************************************************************************
   Function: void decode74(string last)
   Author: John Mangold
   Description: Encodes a 4 bit data string with 3 parity bits.
   Parameters: in - string last - string containing 7 bit message
 ************************************************************************/
void decode74(string last)
{
	vector<vector<int>> R = {{0,0,1,0,0,0,0},
		       		 {0,0,0,0,1,0,0},
		       		 {0,0,0,0,0,1,0},
		       		 {0,0,0,0,0,0,1}};
		       
	vector<vector<int>> r;
	vector<vector<int>> message;
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
		}
	}
	
	matrix_mult(R,r,message);
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

/************************************************************************
   Function: void encode1511(string last)
   Author: John Mangold
   Description: Encodes an 11 bit data string with 4 parity bits.
   Parameters: in - string last - string containing 11 bit data string
 ************************************************************************/
void encode1511(string last)
{
	vector<vector<int>> G = {{1,1,0,1,1,0,1,0,1,0,1},
				 {1,0,1,1,0,1,1,0,0,1,1},
				 {1,0,0,0,0,0,0,0,0,0,0},
				 {0,1,1,1,0,0,0,1,1,1,1},
				 {0,1,0,0,0,0,0,0,0,0,0},
				 {0,0,1,0,0,0,0,0,0,0,0},
				 {0,0,0,1,0,0,0,0,0,0,0},
				 {0,0,0,0,1,1,1,1,1,1,1},
				 {0,0,0,0,1,0,0,0,0,0,0},
				 {0,0,0,0,0,1,0,0,0,0,0},
				 {0,0,0,0,0,0,1,0,0,0,0},
				 {0,0,0,0,0,0,0,1,0,0,0},
				 {0,0,0,0,0,0,0,0,1,0,0},
				 {0,0,0,0,0,0,0,0,0,1,0},
				 {0,0,0,0,0,0,0,0,0,0,1}};
	
	vector<vector<int>> p;
	vector<vector<int>> message;
	string piece;

	if(last.length() != 11)
	{
		cout << "Bit string must be 11 bits.\n";
		return;
	}

	for(int i=0;i<11;i++)
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

/************************************************************************
   Function: void parity1511(string last)
   Author: John Mangold
   Description: Checks a 15 bit message for the proper parity.  If it is
   	        good, it prints the 4 bit zero vector. If it is not good,
   	        then it prints the 4 bit syndrome vector followed by the
   	        corrected message.
   Parameters: in - string last - string containing the 15 bit message
 ************************************************************************/
void parity1511(string last)
{
	vector<vector<int>> H = {{1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
				 {0,1,1,0,0,1,1,0,0,1,1,0,0,1,1},
				 {0,0,0,1,1,1,1,0,0,0,0,1,1,1,1},
				 {0,0,0,0,0,0,0,1,1,1,1,1,1,1,1}};
	
	vector<vector<int>> r;
	vector<vector<int>> syndrome;
	string piece;

	if(last.length() != 15)
	{
		cout << "Bit string must be 15 bits.\n";
		return;
	}

	for(int i=0;i<15;i++)
	{
		vector<int> row;
		r.push_back(row);
		for(int j=0;j<1;j++)
		{
			piece = last[i];
			r[i].push_back(stoi(piece));
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
		syndrome[2].at(0) != 0 || syndrome[3].at(0) != 0)
	{
		string bin;
		int off_bit;
		
		bin.append(to_string(syndrome[3].at(0)));
		bin.append(to_string(syndrome[2].at(0)));
		bin.append(to_string(syndrome[1].at(0)));
		bin.append(to_string(syndrome[0].at(0)));
		
		off_bit = bitset<4>(bin).to_ulong();
		
		if(r[off_bit-1].at(0) == 1)
		{
			r[off_bit-1].at(0) = 0;
		}
		else
		{
			r[off_bit-1].at(0) = 1;
		}
		
		cout << "Corrected Message: ( ";
		for(unsigned int i=0;i<r.size();i++)
		{
			for(unsigned int j=0;j<r[0].size();j++)
			{
				cout << r[i].at(j) << " ";
			}
		}
		cout << ")T\n";
	}
}

/************************************************************************
   Function: void decode1511(string last)
   Author: John Mangold
   Description: Decodes given 15 bit message and prints the 11 data bits
   Parameters: in - string last - string containing the 15 bit message
 ************************************************************************/
void decode1511(string last)
{
	vector<vector<int>> R = {{0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
				 {0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
				 {0,0,0,0,0,1,0,0,0,0,0,0,0,0,0},
				 {0,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
				 {0,0,0,0,0,0,0,0,1,0,0,0,0,0,0},
				 {0,0,0,0,0,0,0,0,0,1,0,0,0,0,0},
				 {0,0,0,0,0,0,0,0,0,0,1,0,0,0,0},
				 {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0},
				 {0,0,0,0,0,0,0,0,0,0,0,0,1,0,0},
				 {0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
				 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}};
	
	vector<vector<int>> r;
	vector<vector<int>> message;
	string piece;

	if(last.length() != 15)
	{
		cout << "Bit string must be 15 bits.\n";
		return;
	}

	for(int i=0;i<15;i++)
	{
		vector<int> row;
		r.push_back(row);
		for(int j=0;j<1;j++)
		{
			piece = last[i];
			r[i].push_back(stoi(piece));
		}
	}
	
	matrix_mult(R,r,message);
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

/************************************************************************
   Function: void h74()
   Author: John Mangold
   Description: Handles necessary function calls for a [7,4] Hamming code
   Parameters: none
 ************************************************************************/
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

/************************************************************************
   Function: void h1511()
   Author: John Mangold
   Description: Handles necessary function calls for a [15,11] Hamming code
   Parameters: none
 ************************************************************************/
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
