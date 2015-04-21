#include<iostream>
#include<string>

using namespace std;

int opcode[22] = {0,1,16,17,18,24,25,26,32,33,34,35,36,37,38,40,41,42,48,49,50,51};
int modes[22] = {1,1,2,3,3,4,5,5,2,2,1,1,2,2,2,4,4,1,3,3,3};
//enum address_mode {Direct, Immediate, Indexed, none, Indirect, none, Indexed_Indirect};
string instruction[22] = {"HALT","NOP","LD","ST","EM","LDX,","STX","EMX","ADD","SUB","CLR",
	"COM","AND","OR","XOR","ADDX","SUBX","CLRX","J","JZ","JN","JP"};
int mode_code[5] = {0,1,2,4,6};
string address[5] = {"Direct", "Immediate", "Indexed","Indirect","Indexed Indirect"};

void print_instruction(int t_opcode);
void print_address_mode(int t_mode_code);
void check_address_modes(int t_opcode, int t_mode_code);

int main()
{
	int t_opcode_1 = 16;
	int t_opcode_2 = 32;
	int t_opcode_3 = 33;
	int t_opcode_4 = 16;
	int t_mode_code_1 = 0;
	int t_mode_code_2 = 1;
	int t_mode_code_3 = 2;
	int t_mode_code_4 = 4;
	int t_mode_code_5 = 6;

	/*int t_mode_1 = Immediate;
	int t_mode_2 = Direct;
	int t_mode_3 = Indexed;
	int t_mode_4 = Indirect;
	int t_mode_5 = Indexed_Indirect;*/

	print_instruction(t_opcode_1);
	print_instruction(t_opcode_2);
	print_instruction(t_opcode_3);
	print_instruction(t_opcode_4);
	cout<<endl;

	check_address_modes(t_opcode_2, t_mode_code_2); 
	cout<<endl;
	check_address_modes(17, 1); 
	cout<<endl;
	check_address_modes(3, t_mode_code_2);
	cout<<endl;
	check_address_modes(16, 3);

	return 1;
}

void print_instruction(int t_opcode)
{
	for (int i = 0; i<22; i++)
	{
		if (t_opcode == opcode[i])
			cout<<instruction[i]<<endl;
	}
}

void print_address_mode(int t_mode_code)
{
	for (int i = 0; i<5; i++)
	{
		if (t_mode_code == mode_code[i])
			cout<<address[i]<<endl;
	}
} 

void check_address_modes(int t_opcode, int t_mode_code)
{
	int modes_type = -1;
	int _mode_code = -1;
	for (int i = 0; i<22; i++)
	{
		if (t_opcode == opcode[i])
		{
			cout<<instruction[i]<<" ";
			//cout<<modes[i]<<endl;
			modes_type = modes[i];
		}		
	}

	if (modes_type == -1)
	{
		cout<<"undefined opcode"<<endl;
			return;
	}

	for (int i = 0; i<5; i++)
	{
		if (t_mode_code == mode_code[i])
		{
			cout<<address[i]<<endl;
			_mode_code = mode_code[i];
		}
	}

	if (_mode_code == -1)
	{
		cout<<"illegal addressing mode"<<endl;
		return;
	}

	if (modes_type == 1)	//ignored
	{
		cout<<"Ignored"<<endl;

	}
	else if (modes_type == 2 && (_mode_code == 0 || _mode_code == 1 || _mode_code == 2 || _mode_code == 4 || _mode_code == 6 ))	//all
	{
		cout<<"All"<<endl;

	}
	else if (modes_type == 3 && (_mode_code == 0 || _mode_code == 2 || _mode_code == 4 || _mode_code == 6 ))	//all except immediate
	{
		cout<<"All except Immediate"<<endl;

	}
	else if (modes_type == 4 && (_mode_code == 0 || _mode_code == 1 ))	//direct, immediate
	{
		cout<<"Direct, Immediate"<<endl;
	}
	else if (modes_type == 5 && _mode_code == 0)	//direct
	{
		cout<<"Direct"<<endl;

	}
	else	//unimplemented
	{
		cout<<"unimplemented addressing mode"<<endl;
	}
	return;
}