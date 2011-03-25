//  CAD for Digital Systems
//  Midterm Project

// 3/18/2011


#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdlib.h>
#include <ctype.h>
#include "types.h"
#include <string.h>


#define ARG_NUM 2 // number of arguments to expect

int VAR_FLAG = 0; // Set to 1 when number of variable has been read
int FUNC_FLAG = 0; // Set to 1 when number of functions has been read
int BODY_FLAG = 0; // Set to 1 when body of input file is entered


int numberOfFunctions;
int numberOfVariables;


// declare array of functions
func func_array[20]; // max 20 functions


// TODO: print list of cubes (check for duplicates!)
// TODO: print kernel-matrix table


func readFunction(char * in_line)
{
	// parse each function
    
	func cur_func;
	int fid; // function id
	
	char line[strlen(in_line)+1];
	memcpy(line, in_line, strlen(in_line) + 1);

	char *str1;
	
	// remove extra new line characters
	if (line[strlen(line) - 1] == '\n') {
		line[strlen(line) - 1] = '\0';
	}
	
	
	printf("Incoming string is: %s\n", line);

    int i = 0;
	
	if (line[0] != 'f') {
		printf("Error: Function must be in format fxx where xx is the function number.\n");
		exit(1);
	}
	
	if (line[2] == ' ') {
		fid = (line[1] - 48);
	
	}
	else {
		fid = ((10 * (line[1] - 48)) + (line[2] - 48));
	}

	cur_func.fid = fid;
	
	str1 = strtok(line, " = ");
	str1 = strtok(NULL, " + "); 
	
	while (str1 != NULL) {
		
		str1 = strtok(NULL, " + ");
		printf("str1 = %s\n", str1);
		
		// TODO: Assigning cubes[i] to temp pointer that changes
		// Need to allocate memory and store string
		
		if (str1 != NULL) {
			cur_func.cubes[i] = malloc(strlen(line) + 1);
			printf("Allocated size = %d\n", (strlen(line) + 1));
			strcpy(cur_func.cubes[i], str1);
		}

		//cur_func.cubes[i] = str1;
		i++;
		
	}

	return cur_func;
    
}


void printCubes(func function)
{
	// prints cubes of given function
	
	int i = 0;
	
	while (function.cubes[i] != '\0') {
		printf("%d\t%s\n", function.fid, function.cubes[i]);
		i++;
	}
	
}



int main (int argc, char* argv[])
{
    
    // Check for number of arguments
    if (argc < ARG_NUM)
    {
        printf("At least %d argument(s) required.\n", (ARG_NUM - 1));
        exit(1);
    }
    
    FILE * fp; // to open input file
    int size_of_file;
    
    struct stat file_stat; // to store file statistics
     
    if (stat(argv[1], &file_stat) < 0)
    {
        perror(argv[0]); // file not found
        exit(1);
    }
    
    size_of_file = file_stat.st_size; // get size of file
    printf("Size of file: %d\n", size_of_file);
    
    fp = fopen(argv[1], "r"); // open file for reading
    if (fp == NULL) 
    {
        perror(argv[0]);
        exit(1); 
    }
    
    char line[80]; // to store the line

    //char *line = malloc(80);
    
    int count;
    count = 1;
	
	int j = 0;

    
    while (fgets(line, 80, fp) != NULL)
    {
		// read in the file one line at a time
		// 1st line is number of local functions
		// 2nd line is number of variables
		
		
		if (VAR_FLAG == 1 && FUNC_FLAG == 1 && BODY_FLAG == 1)
		{
			// processing the functions
			
			// TODO: need check for .e (end of file)
						
			//printf("Storing at position j = %d\n", j);
		//	printf("Line: %s\n", line);
			
		//	printCubes(readFunction(line));
		//	printf("After first print cube\n");
		//	printf("Line: %s\n", line);

			//printf( "lineA=%s\n", line );
			func_array[j] = readFunction(line);
		//	printf( "lineB=%s\n", line );
			printCubes(func_array[j]);
			
			
		//	func_array[j] = myFunction; // store function in function array
		
		//	printCubes(myFunction);
			
		//	int x = 0;
			
		/*	while (myFunction.cubes[x] != '\0') {
				printf("Cube[%d] = %s\n", x, myFunction.cubes[x]);
				x++;
			}
		*/	
			
			//printf("Cube[0] of function is: %s\n", myFunction.cubes[0]);
			//printf("Cube[1] of function is: %s\n", myFunction.cubes[1]);

		//	printf("Function ID = %d\n", myFunction.fid);
			
		//	printf("Line Contents: %s\n", line);
			
			if (j == numberOfFunctions)
			{
				printf("Error: You specified %d functions, just read number %d.\n", numberOfFunctions, j+1);
			}
			
			//printf("j=%d\n", j);
			j++;
		
			
		}
		
				
		if (VAR_FLAG == 1 && FUNC_FLAG == 1 && BODY_FLAG == 0) {
			if (line[0] == '\n') {
				BODY_FLAG = 1;
			}
			else {
				printf("Error: You must have a blank line before the body.\n");
				exit(1);
			}

		}
		
		
		if (line[0] == '.' && FUNC_FLAG == 1 && VAR_FLAG == 0) {
			
			if (line[2] == '\n') {
				numberOfVariables = ((int)line[1] - 48);
			}
			else {
				numberOfVariables = (((int)line[1] - 48) * 10) + ((int)line[2] - 48);
			}
			
			VAR_FLAG = 1;
			
			printf("Number of Variables: %d\n", numberOfVariables);
			if (numberOfVariables > 26) {
				printf("Too many variables. Maximum is 26.\n");
				exit(1);
			}
		}
	
		if (line[0] == '.' && FUNC_FLAG == 0) {
				if (line[2] == '\n') {
					numberOfFunctions = ((int)line[1] - 48);
									}
			else {
				numberOfFunctions = (((int)line[1] - 48) * 10) + ((int)line[2] - 48);
			}
			FUNC_FLAG = 1; 

			printf("Number of Functions: %d\n", numberOfFunctions);
			if (numberOfFunctions > 20) {
				printf("Too many input functions. Maximum is 20.\n");
				exit(1);
			}
		
		}
		
        count++;
    }
       
	int m; //= 0;
	for (m = 0; m < numberOfFunctions; m++) {
		printCubes(func_array[m]);
	}
    
	// done reading file
	
	
 return 0;
}