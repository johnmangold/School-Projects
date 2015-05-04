#include "Prog3.h"

int main(int argc, char** argv)
{
  string input;
  while(true)
  {
    cout << "Choose a simulation to run or type 'mailbox' to look at the shared memory \n";
    cout << "example.  Type 'scheduler' for process scheduler simulation, 'mmu' for the\n";
    cout << " memory management unit, or 'pra' for page replacement algorithms." << endl;
    cout << "Type 'exit' to close out of the program." << endl;
    cout << "> ";

    //get user input
    getline(cin, input);
    user_input(input);
  }
  return 0;
}

void user_input(string input)
{
    if(input == "exit")
      exit(1);
    else if(input == "mailbox")
      mailbox();
    else if(input == "scheduler")
      ProcessSchedule();
    else if(input == "mmu")
      mmu();
    else if(input == "pra")
    {
      pra();
      cin.ignore();
    }
    else
    {
      cout << "\nInvalid input. Please try again." << endl;
      return;
    }
}

///////////////////////start of colters functions/////////////////////////////////////////
