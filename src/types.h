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
	string cubes[26];
	
	
} func;


#ifndef NULL
#define NULL    ((void*)0)
#endif

#endif

