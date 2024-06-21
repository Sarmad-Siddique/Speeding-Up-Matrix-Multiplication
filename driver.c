#include "stdio.h"
#include "stdlib.h"

int main(int argc, char** argv)
{
	if(argc != 3)
    	{
        	printf("2 command line arguments are expected to run the code. Exiting the code.\n");
        	return -1;
    	}
    	
    	char* input_file = argv[1];
    	char* output_file = argv[2];
    	
    	int programtype = 0;
    	
    	FILE* fptr = fopen(input_file, "r");
    	
    	if (fptr == NULL)
    	{
    		printf("File could not be opened\n");
    		exit(0);
    	}
    	
    	fscanf(fptr, "%i", &programtype);
    	
    	fclose(fptr);
    	
    	if(programtype == 1)
    	{
		printf("Calling Matrix Multiplication in Python\n");
		
		char buffer[100];
		
		char* command = "python3 matrixmul.py";
		
		int j = snprintf(buffer, 99, "%s %s %s", command, input_file, output_file);
		
		system(buffer);
	}
	else if (programtype == 2)
	{
		printf("Calling Matrix Multiplication in Java\n");
		char buffer[100];
		
		char* command = "java matrixmul_java";
		
		int j = snprintf(buffer, 99, "%s %s %s", command, input_file, output_file);
		
		system(buffer);
	}
	else if (programtype == 3)
	{
		printf("Calling Matrix Multiplication in C\n");
		char buffer[100];
		
		char* command = "./mc";
		
		int j = snprintf(buffer, 99, "%s %s %s", command, input_file, output_file);
		
		system(buffer);
		
	}
	else if (programtype == 4)
	{
		printf("Calling Matrix Multiplication in C with vector Instructions\n");
		
		char buffer[100];
		
		char* command = "./av";
		
		int j = snprintf(buffer, 99, "%s %s %s", command, input_file, output_file);
		
		system(buffer);
		
		
	}
	else if (programtype == 5)
	{
		printf("Calling Matrix Multiplication in C with pthreads\n");
		
		char buffer[100];
		
		char* command = "./pt";
		
		int j = snprintf(buffer, 99, "%s %s %s", command, input_file, output_file);
		
		system(buffer);
	}
	else if (programtype == 6)
	{
		printf("Calling Matrix Multiplication in C with pthreads AND Vector instructions\n");
		
		char buffer[100];
		
		char* command = "./avpt";
		
		int j = snprintf(buffer, 99, "%s %s %s", command, input_file, output_file);
		
		system(buffer);
	}
	else
	{
		printf("Program Type OpCode is invalid, in the given Input File, Halting execution of code\n");
		exit(0);
	}
	
	
	return 0;
}
