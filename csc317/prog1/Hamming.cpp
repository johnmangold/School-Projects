#include "Hamming.h"

using namespace std;

void h74();
void h1511();
void matrix_mult(vector<vector<int>> farr, vector<vector<int>> sarr,
		 vector<vector<int>> &oarr);

int main(int argc, char** argv)
{
	string input;

	while(true)
	{
		cout << "H74, H1511, or exit: ";
		getline(cin, input);
	
		if( input == "exit" )
		{
			break;
		}
		else if( input == "H74" || input == "h74")
		{
			h74();
		}
		else if( input == "H1511" || input == "h1511")
		{
			h1511();
		}
	
	}
	
	return 0;
}
