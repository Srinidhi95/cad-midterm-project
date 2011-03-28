#ifndef _TYPES_H
#define _TYPES_H

#include <iostream>
#include <string>

using namespace std;


typedef struct
{
	
	int fid;
	int numCubes;
	int numVars;
	int numKernels;
	
	string kernels[26];
	string cokernels[26];
	string cubes[10];
	
	string variables[26];
	
	string storedkernels[10];
	string storedcokernels[10];
	int storedposition;
	string storedtemp[10][10];
	int storedindex;
	
} func;




typedef struct
{
	string data [100];
	
} str_array;


#ifndef NULL
#define NULL    ((void*)0)
#endif

#endif

