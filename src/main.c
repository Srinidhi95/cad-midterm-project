//  CAD for Digital Systems
//  Midterm Project

// 3/18/2011


#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdlib.h>
#include <ctype.h>

#define ARG_NUM 2 // number of arguments to expect


int main (int argc, char* argv[])
{
    
    // Check for number of arguments
    if (argc < ARG_NUM)
    {
        printf("At least %d arguments are required.\n", ARG_NUM);
        exit(1);
    }
    
    FILE * fp; // to open input file
    size_t * size_of_file;
    
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

    int count;
    count = 1;
    
    while (fgets(line, 80, fp) != NULL)
    {
        printf("Just read line number: %d\n", count);
        count++;
    }
       
    
 return 0;
}