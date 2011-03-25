#ifndef _TYPES_H
#define _TYPES_H

#include <iostream>
#include <string>

using namespace std;


/*
class func {
public:
	
	int fid;
	int numVars;
	int numCubes;
	
	string kernels[];
	string cokernels[];
	string cubes[];
	
	
};


*/



typedef struct
{
	
	int fid;
	int numCubes;
	int numVars;

	// for C++ implementation
	
	string kernels[26];
	string cokernels[26];
	string cubes[10];
	
	string variables[26];
	
	
} func;




typedef struct
{
	string data [100];
	
} str_array;


#ifndef NULL
#define NULL    ((void*)0)
#endif

#endif

