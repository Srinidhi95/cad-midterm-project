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
#include <fstream>

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

int numKernelCubes; // number of unique cubes present in the list of kernels


// declare array of functions
func func_array[20]; // max 20 functions

string kernelmatrix[100][100]; // to store kernel-cube matrix

string allCubes[100];
int fids_array[26];

string kernelCubes[100]; // list of all kernel cubes

string primeRecs[100];
string candidateRecs[100];
int numPrimeRecs;
string candidateRecstop = "";
string topcandidatefid = "";

ofstream outStream; // output filestream


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
	if (!query.empty()){
	
	
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

bool kernelfind(string cubes[],  int position, int index) 
{
	int functindex = index;
	//func func_array[index] = func_array[index];
	//int foundkernels = false;
	//string switchkernels;	//save the last kernel data
	//string switchcokernels;	//save the last cokernel
	//int switchposition;						//save the last position
	//string switchtemp[lengthOfArray(cubes)];				//save the cubes array

	//cout << "Recurred" << endl;
	//cout << "Length of cubes: " << lengthOfArray(cubes) << endl;
	/*for(int l=0; l<lengthOfArray(cubes); l++)
			{
				cout << cubes[l] << endl;
			}
	*/
	//cout << "BBBBBBB ->>>>>> Cubes at: " << func_array[index].numKernels << "  " << func_array[index].kernels[0] << endl;
	
////CASE 1	
	if(lengthOfArray(cubes) < 2) //base case 1 -  if we didn't find any kernels for this variable, move up in variable and run function again
	{
	//	cout << ">>>>>>>Divided by: " << func_array[index].cokernels[func_array[index].numKernels] << "  " << func_array[index].kernels[0] << endl;
		//cout << "Fewer than 2 cubes, but more variables after " << func_array[index].variables[position] << endl;
		if(position<func_array[index].numVars){
			position++;
			kernelfind(cubes, position, functindex);
			return true;
		}
		else{
		//cout << "Fewer than 2 cubes, last variable: " << func_array[index].variables[position] << endl;
		//cout << "Cubes at: " << func_array[index].numKernels << "  " << func_array[index].kernels[0] << endl;
			/*string fkernel;
			fkernel = func_array[index].cubes[0];
			for(int y = 1; y < lengthOfArray(func_array[index].cubes); y++){
				fkernel = fkernel + " + " + func_array[index].cubes[y];
			}
			if(func_array[index].kernels[func_array[index].numKernels]!="")
			{
				func_array[index].numKernels++;
			}
			
			func_array[index].kernels[func_array[index].numKernels] = fkernel;
			*/
			
			return false;
		}
	}
		//ELSE = DONE ?????????????????????????????????? BREAK?

////CASE 2	
	if(1<lengthOfArray(cubes))	//if there are more than one cube in the array given
	{
		//cout << "More than one cube" << endl;
		string cur_cube; 
		int pos;			//position of divisor in cube
		int track = 0;		//how many cubes the divisor is present in
		string divisor = func_array[index].variables[position];
		//cout << "numCubes = " << func_array[index].numCubes << endl;
		string kernelstor[lengthOfArray(cubes) + 1];
		
		for (int j = 0; j < lengthOfArray(cubes); j++) {
			kernelstor[j] = cubes[j];
		}
		///////////////////THIS PART RETURNS A STRING ARRAY TEMP OF CUBES DIVISIBLE BY func_array[index].vars[position] /////////////////////////		
		int kt = 0;
		string temp[lengthOfArray(cubes) + 1];
		for (int c = 0; c < lengthOfArray(kernelstor); c++) 
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
		///temp returned
		
		//VARIABLES(POSITION) PRESENT IN EVERY CUBE
		if(lengthOfArray(cubes)==lengthOfArray(temp))    //func_array[index].vars[position] is present in every cube, add to kernel spot
		{	
			//cout << func_array[index].variables[position] << " is present in every cube" << endl;
			func_array[index].cokernels[func_array[index].numKernels] = func_array[index].cokernels[func_array[index].numKernels] + func_array[index].variables[position];      //add position to this co-kernel of func_array[index]
			func_array[index].kernels[func_array[index].numKernels] = temp[0];         //add first cube divided by func_array[index].vars.position to the kernel of func_array[index]
			
						
			
			for (int w=1; w<lengthOfArray(temp); w++) { //add the rest of the cubes to that kernel spot
				func_array[index].kernels[func_array[index].numKernels] = func_array[index].kernels[func_array[index].numKernels] + " + " + temp[w];
			}
			//cout << "Divided by: " << func_array[index].variables[position] << "  " << func_array[index].kernels[func_array[index].numKernels] << endl;
			//WARNING: kernel spot is the same for now!!!!!! 
			//Check for other variables that could be present for this kernel:
			position++;
			//func_array[index].numKernels++;
			kernelfind(temp, position, functindex);
			func_array[index].numKernels++; //checked, move up the kernel spot, DONE
			
			//cout << "Storing cube " << func_array[index].kernels[func_array[index].numKernels] << " at function index:" << index << endl;
			//cout << "numKernels: " << func_array[index].numKernels << endl;
			//cout << "value of temp: " << temp[0] << endl;

			return true;
		}
		
		//VARIABLE(POSITION) PRESENT IN MORE THAN 2 CUBES, BUT NOT ALL
		if(lengthOfArray(temp)<lengthOfArray(cubes) && 1<lengthOfArray(temp))    //func_array[index].vars[position] is present in some cubes, but not all
		{	
			//cout << func_array[index].variables[position] << " is present in more than one cube, but not ALL" << endl;

			func_array[index].storedkernels[func_array[index].storedindex] = func_array[index].kernels[func_array[index].numKernels];	//save the last kernel data
			func_array[index].storedcokernels[func_array[index].storedindex] = func_array[index].cokernels[func_array[index].numKernels];	//save the last cokernel
			func_array[index].storedposition = position;						//save the last position
			for (int j = 0; j < 10; j++) 
			{
				func_array[index].storedtemp[func_array[index].storedindex][j] = cubes[j];
				//cout << "The stored array at index " << func_array[index].storedindex << ": " << func_array[index].storedtemp[func_array[index].storedindex][j] << endl;
			}
			func_array[index].storedindex++;
			//cout << "BREAKPOINT VARIABLE: " << func_array[index].variables[func_array[index].storedposition] << " index: " << func_array[index].storedposition << " out of " << func_array[index].numVars << endl;
			
			func_array[index].cokernels[func_array[index].numKernels] = func_array[index].cokernels[func_array[index].numKernels] + func_array[index].variables[position];      //add position to this co-kernel of func_array[index]
			func_array[index].kernels[func_array[index].numKernels] = temp[0];         //add first cube divided by func_array[index].vars.position to the kernel of func_array[index]
			for (int w=1; w<lengthOfArray(temp); w++) 
			{ //add the rest of the cubes to that kernel spot
				func_array[index].kernels[func_array[index].numKernels] = func_array[index].kernels[func_array[index].numKernels] + " + " + temp[w];
			}
				////WARNING: ERROR-PRONE ZONE!!!///////
			//cout << "About to recur on kernels of " << func_array[index].variables[position] << endl;
			position++;
			kernelfind(temp, position, functindex);
			//cout << "Kernels at " << func_array[index].numKernels << ":   " << func_array[index].kernels[func_array[index].numKernels] << endl;
			func_array[index].numKernels++; //DONE, now re-input the break-off (<ALL) point cout << "Kernels at " << func_array[index].numKernels << endl;
			
			int totalvars = func_array[index].numVars - 1;
			
			if(func_array[index].storedposition==totalvars){
				for (int i = 0; i < lengthOfArray(temp); i++)
				{
					temp[i] = ""; // reset the temp array
				}
				kernelfind(temp, func_array[index].storedposition, functindex);
				return false;
			}
			
			else
			{
				func_array[index].storedindex--;
				func_array[index].cokernels[func_array[index].numKernels] = func_array[index].storedcokernels[func_array[index].storedindex];
				func_array[index].kernels[func_array[index].numKernels] = func_array[index].storedkernels[func_array[index].storedindex];	///PROBLEM???
				//WARNING: kernel spot is the same for now!!!!!! 
				//Check for other variables that could be present for this kernel:
				//cout << "!!!!!! About to recur on " << func_array[index].variables[func_array[index].storedposition+1] << endl;
				//cout << "!!!!!!Kernels at " << func_array[index].numKernels - 1 << ":   " << func_array[index].kernels[func_array[index].numKernels - 1] << endl;
				
				string switchtemp[10];
				for(int l=0; l<10; l++)
				{
					switchtemp[l] =	func_array[index].storedtemp[func_array[index].storedindex][l];		
				}
				
				func_array[index].storedposition++;
				kernelfind(switchtemp, func_array[index].storedposition, functindex);
				//cout << "!-!Kernels at " << func_array[index].numKernels - 1 << ":   " << func_array[index].kernels[func_array[index].numKernels - 1] << endl;
				func_array[index].numKernels++; //checked, move up the kernel spot
				return true;
			}
			//else {
			//	return true;
			//}

		}

		//VARIABLES(POSITION) PRESENT IN LESS THAN 2 CUBES
		else 
		{      //func_array[index].vars[position] is present in less than one cube, set its temp cubes to NULL
			//cout << func_array[index].variables[position] << " is present in less than 2 cubes" << endl;
			//cout << "!!!>>>>>>>>>>>>>Cubes at: " << 0 << "  " << func_array[index].kernels[0] << endl;

			position++;
			
			if(position<func_array[index].numVars)
			{
				kernelfind(cubes, position, functindex);
			}
			
			else
			{
				for (int i = 0; i < lengthOfArray(temp); i++)
				{
					temp[i] = ""; // reset the temp array
				}
				kernelfind(temp, position, functindex);
			}
			return false;
		}
	
}
	
	else
	{
	return false;
	}
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
	
	//cout << "Incoming string: " << line << endl;
	
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
	
	//cout << "Function ID: " << cur_func.fid << endl;
	
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
	int set;
	for (set = 0; set < 26; set++)
	{
		vars[set] = "";
		}

	string temp = "";
	int x = 0;
	int j = 0;
	int k = 0;
	
	for (j = 0; j < numberOfCubes; j++) {
		for (k = 0; k < cur_func.cubes[j].length(); k++) {
		
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
	
	/*for (int i = 0; i < numberOfFunctions; i++){
		string skernels[] = func_array[i].kernels;
		string scokernels[] = func_array[i].cokernels;
		
		for (int m; <#condition#>; <#increment#>) {
			<#statements#>
		}
		
	}*/
	
	int k_count = 1;
	
	for (int i = 0; i < numberOfFunctions; i++) {
		for (int j = 0; j < func_array[i].numKernels; j++) {
		if (!silent) {
							cout << func_array[i].kernels[j] << endl;

				//cout << k_count << '\t' << func_array[i].fid << '\t' << func_array[i].kernels[j] << endl;
				outStream << k_count << '\t' << func_array[i].fid << '\t' << func_array[i].kernels[j] << endl;
			}
			k_count++;
		}
	}
	
	if (!silent) {
		//cout << "Total Number of Kernels: " << (k_count - 1) << endl;	
		outStream << "Total Number of Kernels: " << (k_count - 1) << endl;	
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
		
		if (str1 != NULL) {
			
		
		if (!isPresent(kcubes, str1)) {
			// not found - add it to array
			kcubes[k_count] = str1;
			k_count++;
		}
		}
		
		//cout << "first str = " << str1 << endl;
		while (str1 != NULL) {
			str1 = strtok(NULL, " + ");
			if (str1 != NULL) {
				if (!isPresent(kcubes, str1)) {
					// not found - add it to array
					kcubes[k_count] = str1;
					k_count++;
				}
				
			
			}
			
		}
		
	}

	int m = 0;
	
	// sort kcubes
	
	str_array sortedCubes;
	
	sortedCubes = str_sort(kcubes);
	
	
	// store in kernelCubes
	
	while (!kcubes[m].empty()) {
		kernelCubes[m] = sortedCubes.data[m];
		outStream << (m + 1) << '\t' << kernelCubes[m] << endl;
		m++;
	}
	
	outStream << endl << "Total Number of Cubes: " << m << endl;
	
	numKernelCubes = m; // set the number of unique kernel cubes;
	
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
		//cout << x << '\t' << printed[x] << endl;	
		outStream << x << '\t' << printed[x] << endl;	
		}
		
	}
	
	
	
}

void findAllKernels()
{
	// call divide() for each variable in each kernel
	
//	for (int i = 0; i < numberOfFunctions; i++) {
//		for (int j = 0; j < func_array[i].numVars ; j++) {
//			divide(i, j);

//kernelfind(func_array[0].cubes, 2, 0);
	for (int i = 0; i < numberOfFunctions; i++) 
	{
		func_array[i].storedindex = 0;
		kernelfind(func_array[i].cubes,  0, i);
		
		string fkernel = func_array[i].cubes[0];
		for(int y = 1; y < lengthOfArray(func_array[i].cubes); y++){
			fkernel = fkernel + " + " + func_array[i].cubes[y];
		}
		
		if(func_array[i].numKernels!=0)
		{
		//	cout << "HIT" << endl;
			func_array[i].numKernels--;
		}
			
		func_array[i].kernels[func_array[i].numKernels] = fkernel;
		func_array[i].cokernels[func_array[i].numKernels] = "1";
		func_array[i].numKernels++;
	}
	
	for (int i = 0; i < numberOfFunctions; i++) 
	{
		for(int b = 0; b<10; b++)
			{
				//cout << "Kernel in spot " << b << " is:   " << func_array[i].kernels[b] << "   co-kernel:   " << func_array[i].cokernels[b] << endl;
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
	
	int found = 0; 
	
	string krl[numOfKernels + 1];// store all kernels locally
	
	
	char *str1;
	char *cstr;
	string line;
	
	int count = 0;
	
	for (int x = 0; x < numberOfFunctions; x++) {
		for (int y = 0; y < func_array[x].numKernels; y++) {
			krl[count] = func_array[x].kernels[y]; 
			count++;
		}
	}
	
	// write the first column, 0 (R/C)
	
	for (int i = 1; i <= numOfKernels; i++) {
		kernelmatrix[i][0] = intToString(i); 
	}
	
	// write first row 0, number of cubes
	
	for (int j = 1; j <= numKernelCubes; j++) {
		kernelmatrix[0][j] = intToString(j);
	}
	
	for (row = 1; row <= numOfKernels; row++) { 
		for (col = 1; col <= numKernelCubes; col++) {
			
			// check if kernel cube at col is present in kernel at row
		
			line = krl[row - 1];
			found = 0;
				
			cstr = new char[line.size() + 1];
			strcpy (cstr, line.c_str());
			str1 = strtok(cstr, " + ");
			if (str1 != NULL) {
				if (str1 == kernelCubes[col - 1]) {
					// found a match
					found = 1;
					
				}
				
			}
			
			if (found == 0) {
				while (str1 != NULL) {
					str1 = strtok(NULL, " + ");
					if (str1 != NULL) {
						if (str1 == kernelCubes[col - 1]) {
							// found a match
							found = 1;
						}
						
						
					}
					
				}
			}
			
			
			if (found == 1) {
				// found a match
				kernelmatrix[row][col] = '1';
			}
			else {
				kernelmatrix[row][col] = '0';
			}
			
		}
	}


	
	
}

void printKernelMatrix()
{
	// first line is unique cubes - 4 tabs
	// second line is header - 0 tabs
	// third line is seperator - 0 tabs (use divider n times where n = number of unique cubes + 2)
	
	string divider = "----------";
	

	
	// print cubes of all functions

	outStream << "\t\t\t\t\t\t\t";
	for (int i = 0; i < numKernelCubes; i++) {
		outStream << kernelCubes[i] << '\t';
	}
	outStream << endl;
	outStream << "Kernels" << "\t\t\t\t\t" << "ID" << '\t' << "R\\C" << '\t';
	for (int j = 1; j <= numKernelCubes; j++) {
		outStream << j << '\t';
	}
	outStream << endl;
	
	for (int div1 = 0; div1 < numKernelCubes + 2; div1++) {
		outStream << divider;
	}
	outStream << endl;
	
	int numOfKernels = printKernels(true);
	
	
	string krl[numOfKernels]; // store all kernels locally
	int fids[numOfKernels];   // store corresponding fids
	
	int count = 0;
	
	for (int x = 0; x < numberOfFunctions; x++) {
		for (int y = 0; y < func_array[x].numKernels; y++) {
			krl[count] = func_array[x].kernels[y]; 
			fids[count] = func_array[x].fid;
			fids_array[count] = fids[count]; // used later with prime rectangles
			count++;
		}
	}
	
	int k_count = 0;
	
	while (k_count < numOfKernels) 
	{
		if (krl[k_count].length() < 8) {
			outStream << krl[k_count] << "\t\t\t\t\t" << fids[k_count] << '\t';
		}
		
		if (krl[k_count].length() >= 8 && krl[k_count].length() < 15) {
		outStream << krl[k_count] << "\t\t\t\t" << fids[k_count] << '\t';	
		}
		else if (krl[k_count].length() >= 15) {
			outStream << krl[k_count] << "\t\t\t" << fids[k_count] << '\t';
		}

		// print out corresponding row in the kernel matrix
		
		for (int a = 0; a <= numKernelCubes; a++) {
			outStream << kernelmatrix[k_count + 1][a] << '\t';
		}
		
		
		k_count++;
		outStream << endl;
		
	}
	
	
	for (int div2 = 0; div2 < numKernelCubes + 2; div2++) {
		outStream << divider;
	}
	outStream << endl;

	
}

void computePrimeRec()
{
	// loop through the kernelMatrix and find the column with the most ones
	
	int numKernels = printKernels(true); // returns the number of kernels = # of rows
	
	int numofOnes[numKernelCubes + 10]; // an array to hold the number of ones
	
	string rowlocations[numKernelCubes + 10];
	string cubes[numKernelCubes + 10];
	
	int counter;
	int maxlength = 0;
	
	// and numKernelCubes = number of columns
	
	for (int i = 1; i <= numKernelCubes; i++) {
		// for each column
		counter = 0;
		for (int j = 1; j <= numKernels; j++) {
			if (kernelmatrix[j][i] == "1") {
				counter++; // found a one
				if (counter == 1) {
					rowlocations[i] = rowlocations[i] + intToString(j);
				}
				else {
				rowlocations[i] = rowlocations[i] + "," + intToString(j);		   // store location info	
				}

				
			}
			// store counter in an array
			numofOnes[i] = counter;
		}
		
		if (counter > maxlength) {
			maxlength = counter;
		}
	}
	int n = 0;
	while (maxlength > 1) {
		
		for (int k = 1; k <= numKernelCubes; k++) {
			if (numofOnes[k] == maxlength && numofOnes[k] != 1) {
				primeRecs[n] += "({" + rowlocations[k] + "},{" + intToString(k) + ",";
				
				cubes[n] = kernelCubes[k - 1]; 
				for (int m = k + 1; m <= numKernelCubes; m++) {
					if ((1<numofOnes[m]) && ((rowlocations[m].find(rowlocations[k])==0)||(rowlocations[k].find(rowlocations[m])))) 
					{
						//cout << "Row locations of " << m << " - Row locations of " << k << endl;
						cubes[n] = cubes[n] + " + " + kernelCubes[m - 1];
						primeRecs[n] += intToString(m) + ",";
					}
					else if (m == numKernelCubes)
					{
						primeRecs[n] += "})";
						maxlength--;
					}
				}
				n++;
			}
		}	
		
	}
	
	int pos = 0;
	for (int y = 0; y < n; y++) {
		pos = primeRecs[y].find_last_of(",");
		
		if (pos > 0) {
		
			primeRecs[y].replace(pos, 1, "");
		}
	}
	
	outStream << "Prime Rectangles: " << endl;
	for (int x = 0; x < n; x++) {
		outStream << primeRecs[x] << "\t\t" << cubes[x] << endl;
	}
	
	outStream << endl << "Total Number of Prime Rectangles: " << n << endl << endl;
	numPrimeRecs = n;
	
}

void computeCandidateRec()
{
	
//	primeRecs
//	string candidateRecs[numPrimeRecs + 1]; // to store candidate rectangles
	
	string str;
	
	char *str1;
	
	string s_str;
	int pos;
	int pos_end;
	int count = 0;
	int index;
	int cur_fid;
	int flag = 0;
	
	string cube;
	
	char * cstr;
	
	for (int i = 0; i < numPrimeRecs; i++) {
		
		str = primeRecs[i];
		
		pos = str.find("},{");
		
		if(pos >= 0){
			//found
			s_str = str.substr(pos + 3, 50);
			//cout << "substring: " << s_str << endl;	
			
		}
		
		
		if (s_str.find(",") >= 0) {
			
			pos_end = s_str.find("}");
			s_str = s_str.substr(0,pos_end);
			
			cstr = new char[s_str.size() + 1];
			strcpy (cstr, s_str.c_str());
			
			// now tokenize cstr
			str1 = strtok(cstr, ",");		
			//str1 = strtok(NULL, " + ");
			index = atoi(str1);
			
			cube = kernelCubes[index - 1];
			//cout << "cube: " << cube << endl;
		
			//cout << "index: " << index<< endl;
			
			cur_fid = fids_array[index - 1];
			if (i==0) {
				topcandidatefid = topcandidatefid + " " + intToString(cur_fid);
			}
			
			while (str1 != NULL){
				
				str1 = strtok(NULL, ",");
				if (str1 != NULL) {
					
					index = atoi(str1);
					cube = cube + " + " + kernelCubes[index - 1];
				
				//	cout << "index2 = " << index << endl;
					if (cur_fid == fids_array[index]) {
						flag = 0;
					}
					else {
						flag = 1;
					}

				}
		
				
			}
		
			if (flag == 1) {
				// is a candidate
				if(count==0){
					candidateRecstop = cube;
				}
				}
				candidateRecs[count] = primeRecs[i];
				outStream << candidateRecs[count] << "\t\t" << cube << endl;
				
			
				count++;

			}
			
			
						
		}
		
	outStream << endl << "Number of Candidate Rectangles: " << count << endl;
	
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
    
	cout << "Reading file... " << endl;
	
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
	
	int m;

	
	cout << "Processing input file... ";

	findAllKernels();
	
	outStream.open ("Cubes.txt");
	findKernelCubes();
	outStream.close();
	
	createMatrix();
	
	
	cout << "Done!" << endl;
	
	cout << "Outputting Results... " << endl;
	
	
	outStream.open ("Kernels.txt");
	printKernels(false); //-- to print the kernels
	outStream.close();
		

	
	outStream.open ("KernelCubeMatrix.txt");
	printKernelMatrix();
	outStream.close();
	
	outStream.open ("PrimeRecs.txt");
	computePrimeRec();
	computeCandidateRec();
	
	outStream.close();
	cout << "Done!" << endl;


	return 0;
}

