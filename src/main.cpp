//  CAD for Digital Systems
//  Midterm Project

// 3/18/2011


#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdlib.h>
#include "types.h"
#include <cstdio>
#include <string.h>


#include <iostream>
#include <string>
#include <sstream>

using namespace std;

#define ARG_NUM 2 // minimum number of arguments to expect

int VAR_FLAG = 0; // Set to 1 when number of variable has been read
int FUNC_FLAG = 0; // Set to 1 when number of functions has been read
int BODY_FLAG = 0; // Set to 1 when body of input file is entered
int END_FLAG = 0; // Set to 1 when all functions have been read
int DONE_FLAG = 0; // Set to 1 when .e is reached correctly

int numberOfFunctions;
int numberOfVariables;
int numberOfCubes;


// declare array of functions
func func_array[20]; // max 20 functions

string kernelmatrix[100][100]; // to store kernel-cube matrix

string allCubes[100];

string kernelCubes[100]; // list of all kernel cubes


string intToString(int number)
{
	string str;
	stringstream stream;
	stream << number;
	str = stream.str();
	return str;
}

bool isPresent(string array[], string query)
{
	// returns true if query is found in array[]
	
	int i = 0;
	//cout << "Reached isPresent" << endl;
	
	while (!array[i].empty()) {
		if (array[i] == query) {
			// found
			//cout << "Found!" << endl;
			return true;
		}
		i++;
	}
	//	cout << "Not Found." << endl;
	return false;
}

int lengthOfArray(string array [])
{
	int i = 0;
	while (!array[i].empty()) {
		i++;
	}
	
	return i;
	
}

str_array str_sort(string array[])
{
	// sort initially alphabetically
	
	string temp = "";
	int flag = 1;
	int i = 0;
	int j = 0;
	
	int min_length = 26;
	int max_length = 0;
	
	int counter = 0; // to store the length of the array
	
	
	// WARNING: May segfault if array is full
	while (!array[counter].empty()) {
		counter++;
	}
	
	string sorted[counter];
	
	// if flag = 1 then a swap was made
	// keep looping until no swaps => array is sorted
	
	while (flag == 1) {
		flag = 0;
		i = 0;
		
		while (!array[i].empty()) 
		{
			// check and swap if necessary
			if (!array[i+1].empty()) // check if near bounds
			{
				// calculate the smallest and largest length
				if (array[i].length() > max_length) {
					max_length = array[i].length();
				}
				if (array[i].length() < min_length) {
					min_length = array[i].length();
				}
				
				if (array[i] > array[i+1]) {
					// they need to be swapped
					temp = array[i];
					array[i] = array[i+1];
					array[i+1] = temp;
					flag = 1; 
				}
			}
			i++; // increment counter - move to next element
		}
		
	}
	
	// at this point the array is sorted alphabetically
	
	// now we sort by length
	
	int k = min_length;
	int y = 0;
	
	while (k <= max_length) {
		// for every length, loop through array and copy into new array
		for (int x = 0; x < counter; x++) {
			if (array[x].length() == k) {
				sorted[y] = array[x];
				y++;
			}
		}
		
		
		k++;
	}
	
	
	str_array returnArray;
	for (int z = 0; z < counter; z++) {
		returnArray.data[z] = sorted[z];
	}
	
	return returnArray;
	
	
}

void divide(int index, int position)
{
	// TODO: Fix bug where variables overlap
	
	func f1 = func_array[index];
	
	//cout << "Function ID: " << f1.fid << endl;
	
	
	
	int fk = f1.numKernels;
	string cur_cube; 
	int pos;			//position of divisor in cube
	int track = 0;		//how many cubes the divisor is present in
						//will make use of variables
	string divisor = f1.variables[position];
																//cout << "numCubes = " << f1.numCubes << endl;
		string kernelstor[10];
		
		for (int j = 0; j < 10; j++) {
			kernelstor[j] = f1.cubes[j];
		}
		
		
///////////////////THIS PART RETURNS A STRING ARRAY TEMP OF CUBES DIVISIBLE BY f1.vars[position] /////////////////////////		
		int kt = 0;
		string temp[10];
		for (int c = 0; c < f1.numCubes; c++) 
		{
			cur_cube = kernelstor[c];
			pos = cur_cube.find(divisor);	//finds divisor in cube
			//cout << "Current Cube: " << cur_cube << endl;
			if (pos != -1) {				//if divisor is in string
				cur_cube.replace(pos, 1, "");
				temp[kt] = cur_cube;
				kt++;
				//cout << "After: " << cur_cube << endl;
			}
		}
	//cout << "Temp length: " << lengthOfArray(temp) << endl;
	//for(int p=0;p<lengthOfArray(temp);p++){
	//	cout << temp[p] << endl; 
	//}
		//return temp;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////		
//////////////// USING TEMP RESULTS: /////////////////////////////
		
		if (lengthOfArray(temp) < 2) {      //f1.vars[position] is present in less than one cube, set its temp cubes to NULL
			temp[0] = "";
		}
		else {                              //f1.vars[position] is present in more than one cube, now check if any other variable is present in ALL
			f1.numKernels++;
			f1.cokernels[fk] = f1.variables[position];      //add position as co-kernel of f1
			f1.kernels[fk] = temp[0];         //add first cube divided by f1.vars.position to the kernel of f1
			for (int w=1; w<lengthOfArray(temp); w++) { //add the rest of the cubes to that kernel spot
				f1.kernels[fk] = f1.kernels[fk] + " + " + temp[w];
			}
			
			int location;
			string current_cube;
			
			string ntemp[lengthOfArray(temp)+10];
			int u = 0;
			
			for (int e = position + 1; e<f1.numVars; e++) {  //concatenate through variables
				u = 0;
				for(int c = 0; c < lengthOfArray(temp); c++){ //concatenate through cubes for variable e and add each divisible cube to ntemp[]
					current_cube = temp[c];
					location = current_cube.find(f1.variables[e]);
					if (location != -1) {				//if divisor is in string
						current_cube.replace(location, 1, "");
						ntemp[u] = current_cube;
						u++;				
					}
				}
				//cout << "Length of ntemp: " << lengthOfArray(ntemp) << " variable: " << f1.variables[e] << endl;
				//for(int p=0;p<lengthOfArray(ntemp);p++){
				//	cout << ntemp[p] << endl;}
				
				if (lengthOfArray(ntemp)==lengthOfArray(temp)) {	//all of kernel divisible by variable, add it to cokernel, replace kernel
					f1.cokernels[fk] = f1.cokernels[fk] + f1.variables[e];
					f1.kernels[fk] = ntemp[0];
					for (int w=1; w<lengthOfArray(ntemp); w++) { //add the rest of the cubes to that kernel spot
						f1.kernels[fk] = f1.kernels[fk] + " + " + ntemp[w];
					}
					
					u = 0;
					//cout << "About to reset ntemp" << endl;
						for (int z = 0; z < lengthOfArray(temp) + 10; z++)
						{
					//		cout << "reset: " << ntemp[z] << endl;
							ntemp[z] = "";
						}		
				}
				else {
					u = 0;
					for (int z = 0; z < lengthOfArray(ntemp); z++)
					{
						ntemp[z] = "";
					}
				}
					
					
			
		}
		
		}
	
	func_array[index] = f1;
		
	
}

func readFunction(string in_line)
{
	// parse each function
    
	func cur_func;
	int fid; // function id
	int nCubes = 0; // number of cubes
	
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
			numberOfCubes++;
			nCubes++;
			cur_func.cubes[i] = str1;			
		}
			i++;
		
	}
	
	
	// get array of all variables
	
	string vars [26];
	string temp;
	int x = 0;
	
	for (int j = 0; j < numberOfCubes; j++) {
		for (int k = 0; k < cur_func.cubes[j].length(); k++) {
		
			temp = cur_func.cubes[j][k]; 
			
			if (!isPresent(vars, temp)) {
				// not found
				vars[x] = cur_func.cubes[j][k];
				x++;
			}
		}
	}
	
	int numVars = x;
	
	string temp2;
	int flag = 1; 
	 int m = 0;
	// n = 0;
	
	
	while (flag == 1) {
		flag = 0;
		m = 0;
		while (!vars[m].empty()) {

			if (!vars[m+1].empty()) {
				
				if (vars[m] > vars[m+1])
				{
					temp2 = vars[m];
					vars[m] = vars[m+1];
					vars[m+1] = temp2;
					flag = 1;
				}
				
			}
			
			m++;
		}
		
		
		
	}
	
	
	/*
	for (x = 0; x < numVars; x++) {
		cout << vars[x] << endl;
	}
	*/
	
	cur_func.numCubes = nCubes;
	cur_func.numVars = numVars;
	cur_func.numKernels = 0; // initialize to 0
	
	
	for (i = 0; i < numVars; i++) {
		cur_func.variables[i] = vars[i];
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

int printKernels(bool silent)
{
	// if silent is true then won't print to screen
	
	int k_count = 1;
	
	
	for (int i = 0; i < numberOfFunctions; i++) {
		for (int j = 0; j < func_array[i].numKernels; j++) {
			
			if (!silent) {
				cout << k_count << '\t' << func_array[i].fid << '\t' << func_array[i].kernels[j] << endl;
			}
			k_count++;
		}
	}
	if (!silent) {
		cout << "Total Number of Kernels: " << (k_count - 1) << endl;	
	}
	
	return (k_count - 1);
	
	
}

void findKernelCubes()
{
	
	
	string kcubes[100]; // better approx for size later?
	string line;
	
	int numOfKernels = printKernels(true);
	
	
	string krl[numOfKernels];// store all kernels locally
	int fids[numOfKernels]; // store corresponding fids
	
	int count = 0;
	
	for (int x = 0; x < numberOfFunctions; x++) {
		for (int y = 0; y < func_array[x].numKernels; y++) {
			krl[count] = func_array[x].kernels[y]; 
			fids[count] = func_array[x].fid;
			count++;
		}
	}

	
	// TOKENIZE
	char *str1;
	char *cstr;
	int k_count = 0;
	
	for (int i = 0; i < numOfKernels; i++) {
		// parse each kernel
		line = krl[i];
		
		cstr = new char[line.size() + 1];
		strcpy (cstr, line.c_str());
		str1 = strtok(cstr, " + ");
		kcubes[k_count] = str1; // add the first string
		k_count++;
		
		//cout << "first str = " << str1 << endl;
		while (str1 != NULL) {
			str1 = strtok(NULL, " + ");
			if (str1 != NULL) {
				kcubes[k_count] = str1;
				k_count++;
			
			}
			
		}
		
	}

	int m = 0;
	
	// sort kcubes
	
	str_array sortedCubes;
	
	sortedCubes = str_sort(kcubes);
	
	
	// store in kernelCubes
	
	// TODO: Remove Duplicates
	
	while (!kcubes[m].empty()) {
		kernelCubes[m] = sortedCubes.data[m];
		cout << kernelCubes[m] << endl;
		m++;
	}
	
	
}

void printAllCubes(bool silent)
{
	// prints all cubes
	
	
	int i;
	int j;
	int k = 0;
	int x;
	
	string printed[numberOfCubes + 1]; // array of printed cubes
	
	
	
	for (i = 0; i < numberOfFunctions; i++) {
		// for each function, add its cube to the printed array only if it isn't in it
		j = 0;
		while (!func_array[i].cubes[j].empty()) {
			//cout << "i=" << i << " j=" << j << " k=" << k << endl; // for diagnostic info
			if (!isPresent(printed, func_array[i].cubes[j])) {
				// not found - add it to array
				printed[k] = func_array[i].cubes[j];
				k++;
			}
			
			
			j++;
		}
		
		
	}
	
	// sort the array
	
	str_array sortedArray = str_sort(printed);
	int n = 0;
	while (!sortedArray.data[n].empty()) {
		printed[n] = sortedArray.data[n];
		n++;
	}

	
	for (x = 0; x < k ; x++) {
		allCubes[x] = printed[x];
		if (!silent) {
		cout << printed[x] << endl;	
		}
		
	}
	
	
	
}

void findAllKernels()
{
	// call divide() for each variable in each kernel
	
	for (int i = 0; i < numberOfFunctions; i++) {
		for (int j = 0; j < func_array[i].numVars ; j++) {
			divide(i, j);
		}
	}
	
}

void createMatrix()
{
	// number of columns = number of cubes
	// number or rows = number of kernels
	
	int numOfKernels = printKernels(true); // returns number of kernels
	int row = 0;
	int col = 0;
	
	// write the first column, 0 (R/C)
	
	for (int i = 1; i <= numOfKernels; i++) {
		kernelmatrix[i][0] = intToString(i); 
	}
	
	// write first row 0, number of cubes
	
	for (int j = 1; j <= numberOfCubes; j++) {
		kernelmatrix[0][j] = intToString(j);
	}
	
	for (row = 0; row < numOfKernels; row++) { 
		for (col = 0; col < numberOfCubes; col++) {
		//	kernelmatrix[row][0] = intToString(row);
			// TODO: Print rest of matrix
		}
	}

//cout << "Kernel Matrix: " << kernelmatrix[1][0] << endl;

	
	
}

void printKernelMatrix()
{
	// first line is unique cubes - 4 tabs
	// second line is header - 0 tabs
	// third line is seperator - 0 tabs (use divider n times where n = number of unique cubes + 2)
	
	string divider = "---------";
	
	//int numOfKernels = printKernels(true);
	
	// print cubes of all functions

	cout << "\t\t\t\t";
	for (int i = 0; i < numberOfCubes; i++) {
		cout << allCubes[i] << '\t';
	}
	cout << endl;
	cout << "Kernels" << "\t\t" << "ID" << '\t' << "R\\C" << '\t';
	for (int j = 1; j <= numberOfCubes; j++) {
		cout << j << '\t';
	}
	cout << endl;
	
	for (int div1 = 0; div1 < numberOfCubes + 2; div1++) {
		cout << divider;
	}
	cout << endl;
	
	int numOfKernels = printKernels(true);
	
	
	string krl[numOfKernels];// store all kernels locally
	int fids[numOfKernels]; // store corresponding fids
	
	int count = 0;
	
	for (int x = 0; x < numberOfFunctions; x++) {
		for (int y = 0; y < func_array[x].numKernels; y++) {
			krl[count] = func_array[x].kernels[y]; 
			fids[count] = func_array[x].fid;
			count++;
		}
	}
	
	int k_count = 0;
	
	while (k_count < numOfKernels) 
	{
		if (k_count == 0) {
		cout << krl[k_count] << "\t\t" << fids[k_count] << '\t';	
		}
		else {
			cout << krl[k_count] << '\t' << fids[k_count] << '\t';
		}

		// print out corresponding row in the kernel matrix
		
		for (int a = 0; a < numberOfCubes; a++) {
			cout << kernelmatrix[k_count + 1][a] << '\t';
		}
		
		
		k_count++;
		cout << endl;
		
	}
	
	
	for (int div2 = 0; div2 < numberOfCubes + 2; div2++) {
		cout << divider;
	}
	cout << endl;
	
	
	
	
	
	
	
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

    int count;
    count = 1;
	
	int j = 0;
	
    
    while (fgets(cline, 80, fp) != NULL && DONE_FLAG == 0)
    {
		
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
	
    
	

	//cout << "Function ID: " << func_array[m].fid << endl;
	//cout << "numCubes: " << func_array[m].numCubes << endl;
	}
	
	cout << "Number of cubes: " << numberOfCubes << endl;
	
	

	findAllKernels();
	printKernels(false);

	findKernelCubes();
	
	int n = 0;
	while (!kernelCubes[n].empty()) {
		
	//	cout << "Kernel Cube (" << n << "): " << kernelCubes[n] << endl;
		n++;
	}
	
//	cout << "Number of Kernel Cubes: " << n << endl;
	
	printAllCubes(true);
	
	//findKernelCubes();
	createMatrix();
	
	//printKernelMatrix();
	
	// done reading file
	
	
	
	return 0;
}

