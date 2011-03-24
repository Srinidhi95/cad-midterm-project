#ifndef _TYPES_H
#define _TYPES_H


typedef struct
{
	
	int fid;
	int numCubes;
	int numVars;
	//char cubes[15][26]; // stores 15 cubes of 26 characters each
	char kernels[15][26];
	char cokernels[15][26];
    char * cubes[26];

} func;


#ifndef NULL
#define NULL    ((void*)0)
#endif

#endif

