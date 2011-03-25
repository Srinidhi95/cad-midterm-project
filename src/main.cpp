//  CAD for Digital Systems
//  Midterm Project

// 3/18/2011


#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdlib.h>
#include "types.h"

#include <iostream>
#include <string>

using namespace std;

#define ARG_NUM 2 // number of arguments to expect

int VAR_FLAG = 0; // Set to 1 when number of variable has been read
int FUNC_FLAG = 0; // Set to 1 when number of functions has been read
int BODY_FLAG = 0; // Set to 1 when body of input file is entered
int END_FLAG = 0; // Set to 1 when all functions have been read
int DONE_FLAG = 0; // Set to 1 when .e is reached correctly


int numberOfFunctions;
int numberOfVariables;


// declare array of functions
func func_array[20]; // max 20 functions


// TODO: print list of cubes (check for duplicates!)
// TODO: print kernel-matrix table


func readFunction(string in_line)
{
	// parse each function
    
	func cur_func;
	int fid; // function id
	
	char * str1;
	
	string line = in_line;
	
	
	
	if (line[line.length() - 1] == '\n') {
		line[line.length() - 1] = '\0';
	}
	
	cout << "Incoming string: " << line << endl;
	
    int i = 0;
	
	if (line == ".e" or line == ".e\n") {
		cout << "Should be here" << endl;
		printf("Error: You must have a blank line between body and .e\n");
		exit(1);
	}
	
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
	
	cout << "Function ID: " << cur_func.fid << endl;
	
	char * cstr;
	cstr = new char[line.size() + 1];
	strcpy (cstr, line.c_str());
	
	// now tokenize cstr
	
	str1 = strtok(cstr, " = ");
	str1 = strtok(NULL, " + ");
	
	while (str1 != NULL){
		
		str1 = strtok(NULL, " + ");
		if (str1 != NULL) {
			cur_func.cubes[i] = str1;			
		}
			i++;
		
	}
	
	return cur_func;
    
}


void printCubes(func function)
{
	// prints cubes of given function
	
	int i = 0;
	
	while (!function.cubes[i].empty()) {
	//	printf("%d\t%s\n", function.fid, function.cubes[i]);
		
		cout << function.fid << '\t' << function.cubes[i] << endl;
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
    
    char cline[80]; // to store the line
	//string line;
    
    int count;
    count = 1;
	
	int j = 0;
	
    
    while (fgets(cline, 80, fp) != NULL && DONE_FLAG == 0)
    {
		// read in the file one line at a time
		// 1st line is number of local functions
		// 2nd line is number of variables
		
		string line(cline); // creates a c++ string from the cstring returned by fgets
		
		
		if (VAR_FLAG == 1 && FUNC_FLAG == 1 && BODY_FLAG == 1 && END_FLAG == 1) 
		{
			
			// check for .e
			
			if (line == ".e" or line == ".e\n") {
				cout << "Finished reading input file." << endl;
				DONE_FLAG = 1;
			}
			else {
				cout << "Error: End of file indicator (.e) is missing." << endl;
				exit(1);
			}

			
		}
		
		
			if (VAR_FLAG == 1 && FUNC_FLAG == 1 && BODY_FLAG == 1 && END_FLAG == 0) // start reading functions
		{
			// processing the functions
		
		
			
			if (line[0] == '\n' && j == (numberOfFunctions)) {
				END_FLAG = 1;				
			}
			
			if (line[0] == '\n' && j < (numberOfFunctions)) {
				printf("Error: You specified %d functions. Only %d were read.\n", numberOfFunctions, j);
			}
			
	
			if (line[0] != '\n' && line != ".e") {
				
				func_array[j] = readFunction(line); // read function into array
			
			
			//printCubes(func_array[j]);
			
			if (j == numberOfFunctions)
			{
				printf("Error: You specified %d functions, just read number %d.\n", numberOfFunctions, j+1);
			}
			
			j++;
			
			}
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

