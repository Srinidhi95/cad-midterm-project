//  CAD for Digital Systems
//  Midterm Project

// 3/18/2011


#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdlib.h>
#include <ctype.h>
#include <xlocale.h>
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



func readFunction(char *in_line)
{
	// parse each function
    
	func cur_func;
	int fid; // function id
	
	char *str1;
	
	printf("Incoming string is: %s\n", in_line);

    int i = 0;
	
	if (in_line[0] != 'f') {
		printf("Error: Function must be in format fxx where xx is the function number.\n");
		exit(1);
	}
	
	if (in_line[2] == ' ') {
		fid = (in_line[1] - 48);
		//printf("fid = %d\n", fid);
	}
	else {
		fid = ((10 * (in_line[1] - 48)) + (in_line[2] - 48));
		//printf("fid = %d\n", fid);
		
	}

	cur_func.fid = fid;
	
	str1 = strtok(in_line, " = ");
	str1 = strtok(NULL, " + "); 
	
	while (str1 != NULL) {
		
		str1 = strtok(NULL, " + ");
		cur_func.cubes[i] = str1; // CAUSES SEGFAULT
		i++;
		
	}

	return cur_func;
    
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
    
    struct stat file_stat;
     
    if (stat(argv[1], &file_stat) < 0)
    {
        perror(argv[0]);
        exit(1);
    }
    
    size_of_file = file_stat.st_size;
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
			
			func myFunction;
			
			myFunction = readFunction(line);
			
			int x = 0;
			
			while (myFunction.cubes[x] != '\0') {
				printf("Cube[%d] = %s\n", x, myFunction.cubes[x]);
				x++;
			}
			
			
			//printf("Cube[0] of function is: %s\n", myFunction.cubes[0]);
			//printf("Cube[1] of function is: %s\n", myFunction.cubes[1]);

			printf("Function ID = %d\n", myFunction.fid);
			
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
       
    
 return 0;
}