#ifndef MMU_H
#define MMU_H

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <math.h>
#include <time.h>

struct virtual_info
{
	int pid;
	int data;
};

struct physical_info
{
	int frame;
	int data;
};

struct location_info
{
	int pid;
	int frame;
	bool in_main;
};

#endif
