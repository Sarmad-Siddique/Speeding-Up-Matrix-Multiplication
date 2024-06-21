#include "stdio.h"
#include "stdlib.h"
#include "time.h"

void Run_32BitInt(char* input_file, char* output_file);
void Run_64BitInt(char* input_file, char* output_file);
void Run_32BitFloat(char* input_file, char* output_file);
void Run_64BitDouble(char* input_file, char* output_file);

int main(int argc, char** argv)
{
	if(argc != 3)
    	{
        	printf("2 command line arguments are expected to run the code. Exiting the code.\n");
        	return -1;
    	}
    	
    	char* input_file = argv[1];
    	char* output_file = argv[2];
    	
    	FILE* fptr = fopen(input_file, "r");
    	
    	if (fptr == NULL)
    	{
    		printf("File could not be opened\n");
    		exit(0);
    	}
    	
    	int programtype = 0;
    	int datatype = 0;
    	
    	fscanf(fptr, "%i", &programtype);
    	fscanf(fptr, "%i", &datatype);
    	
    	printf("ProgramType: %i\n", programtype);
    	printf("Data Type: %i\n", datatype);
    	
    	if(datatype == 1)
    	{
    		Run_32BitInt(input_file, output_file);
    	}
    	else if (datatype == 2)
    	{
    		Run_32BitFloat(input_file, output_file);
	}
	else if (datatype == 3)
    	{
    		Run_64BitInt(input_file, output_file);
	}
	else if (datatype == 4)
    	{
    		Run_64BitDouble(input_file, output_file);
	}
	else
	{
		printf("Invalid data type OpCode, Halting execution\n");
		exit(0);
	}
    	
    	
    	
    	
    	
    	    	
    	return 0;
    	
}

void Run_32BitInt(char* input_file, char* output_file)
{
    	FILE* fptr = fopen(input_file, "r");
    	
    	if (fptr == NULL)
    	{
    		printf("File could not be opened\n");
    		exit(0);
    	}
    	
    	int programtype = 0;
    	int datatype = 0;
    	int dimension1 = 0, dimension2 = 0;
    	char garbage;
    	
    	fscanf(fptr, "%d", &programtype);
    	fscanf(fptr, "%d", &datatype);
    	fscanf(fptr, "%d%c%d", &dimension1, &garbage, &dimension2);
    	
    	if(dimension1 != 4096 || dimension2 != 4096)
    	{
    		printf("Invalid Dimensions given for matrix 1\n");
    		printf("DImension 1: %d", dimension1);
    		printf("DImension 2: %d", dimension2);
    		exit(0);
    	}
    	
    	int i = 0, j = 0;
    	
    	static int matrix1[4096][4096];
    	static int matrix2[4096][4096];
    	static int matrix3[4096][4096];
    	
    	for (i = 0; i < 4096; i++)
    	{
    		for (j = 0; j < 4096; j++)
    		{
    			fscanf(fptr, "%d", &matrix1[i][j]);
    		}
    	}
    	
    	fscanf(fptr, "%d%c%d", &dimension1, &garbage, &dimension2);
    	
    	if(dimension1 != 4096 || dimension2 != 4096)
    	{
    		printf("Invalid Dimensions given for matrix 1\n");
    		printf("DImension 1: %d\n", dimension1);
    		printf("DImension 2: %d\n", dimension2);
    		exit(0);
    	}
    	
    	for (i = 0; i < 4096; i++)
    	{
    		for (j = 0; j < 4096; j++)
    		{
    			fscanf(fptr, "%d", &matrix2[i][j]);
    		}
    	}
    	
    	fclose(fptr);
    	
    	time_t seconds_start;
    	time_t seconds_finish;
    	
    	int k = 0;
    	
    	seconds_start = time(NULL);
    	
    	for (i = 0; i < 4096; i++)
    	{
    		for (k = 0; k < 4096; k++)
    		{
    			for (j = 0; j < 4096; j++)
    			{
    				matrix3[i][j] += matrix1[i][k] * matrix2[k][j]; 
    			}
    		}
    	}
    	
    	
    	seconds_finish = time(NULL);
    	
    	printf("Time taken for calculations = %ld\n", (seconds_finish - seconds_start) );
    	
    	fptr = fopen(output_file, "w");
    	
    	fprintf(fptr, "1\n4096X4096\n");
    	
    	for (i = 0; i < 4096; i++)
    	{
    		for (j = 0; j < 4096; j++)
    		{
    			fprintf(fptr, "%d ", matrix3[i][j]);
    		}
    		fprintf(fptr, " \n");
    	}
    	
    	fclose(fptr);
    	
}
void Run_64BitInt(char* input_file, char* output_file)
{
	FILE* fptr = fopen(input_file, "r");
    	
    	if (fptr == NULL)
    	{
    		printf("File could not be opened\n");
    		exit(0);
    	}
    	
    	int programtype = 0;
    	int datatype = 0;
    	int dimension1 = 0, dimension2 = 0;
    	char garbage;
    	
    	fscanf(fptr, "%d", &programtype);
    	fscanf(fptr, "%d", &datatype);
    	fscanf(fptr, "%d%c%d", &dimension1, &garbage, &dimension2);
    	
    	if(dimension1 != 4096 || dimension2 != 4096 )
    	{
    		printf("Invalid Dimensions given for matrix 1\n");
    		printf("DImension 1: %d", dimension1);
    		printf("DImension 2: %d", dimension2);
    		exit(0);
    	}
    	
    	int i = 0, j = 0;
    	
    	static long long int matrix1[4096][4096];
    	static long long int matrix2[4096][4096];
    	static long long int matrix3[4096][4096];
    	
    	for (i = 0; i < 4096; i++)
    	{
    		for (j = 0; j < 4096; j++)
    		{
    			fscanf(fptr, "%lli", &matrix1[i][j]);
    		}
    	}
    	
    	fscanf(fptr, "%d%c%d", &dimension1, &garbage, &dimension2);
    	
    	if(dimension1 != 4096 || dimension2 != 4096)
    	{
    		printf("Invalid Dimensions given for matrix 1\n");
    		printf("DImension 1: %d\n", dimension1);
    		printf("DImension 2: %d\n", dimension2);
    		exit(0);
    	}
    	
    	for (i = 0; i < 4096; i++)
    	{
    		for (j = 0; j < 4096; j++)
    		{
    			fscanf(fptr, "%lli", &matrix2[i][j]);
    		}
    	}
    	
    	fclose(fptr);
    	
    	time_t seconds_start;
    	time_t seconds_finish;
    	
    	int k = 0;
    	
    	printf("Running C matrix mul for 64 bit integers\n");
    	
    	seconds_start = time(NULL);
    	
    	for (i = 0; i < 4096; i++)
    	{
    		for (j = 0; j < 4096; j++)
    		{
    			for (k = 0; k < 4096; k++)
    			{
    				matrix3[i][j] += matrix1[i][k] * matrix2[k][j]; 
    			}
    		}
    	}
    	
    	
    	seconds_finish = time(NULL);
    	
    	printf("Time taken for calculations = %ld\n", (seconds_finish - seconds_start) );
    	
    	fptr = fopen(output_file, "w");
    	
    	fprintf(fptr, "3\n4096X4096\n");
    	
    	for (i = 0; i < 4096; i++)
    	{
    		for (j = 0; j < 4096; j++)
    		{
    			fprintf(fptr, "%lli ", matrix3[i][j]);
    		}
    		fprintf(fptr, " \n");
    	}
    	
    	fclose(fptr);
}
void Run_32BitFloat(char* input_file, char* output_file)
{
	FILE* fptr = fopen(input_file, "r");
    	
    	if (fptr == NULL)
    	{
    		printf("File could not be opened\n");
    		exit(0);
    	}
    	
    	int programtype = 0;
    	int datatype = 0;
    	int dimension1 = 0, dimension2 = 0;
    	char garbage;
    	
    	fscanf(fptr, "%d", &programtype);
    	fscanf(fptr, "%d", &datatype);
    	fscanf(fptr, "%d%c%d", &dimension1, &garbage, &dimension2);
    	
    	if(dimension1 != 4096 || dimension2 != 4096)
    	{
    		printf("Invalid Dimensions given for matrix 1\n");
    		printf("DImension 1: %d", dimension1);
    		printf("DImension 2: %d", dimension2);
    		exit(0);
    	}
    	
    	int i = 0, j = 0;
    	
    	static float matrix1[4096][4096];
    	static float matrix2[4096][4096];
    	static float matrix3[4096][4096];
    	
    	for (i = 0; i < 4096; i++)
    	{
    		for (j = 0; j < 4096; j++)
    		{
    			fscanf(fptr, "%g", &matrix1[i][j]);
    		}
    	}
    	
    	fscanf(fptr, "%d%c%d", &dimension1, &garbage, &dimension2);
    	
    	if(dimension1 != 4096 || dimension2 != 4096)
    	{
    		printf("Invalid Dimensions given for matrix 1\n");
    		printf("DImension 1: %d\n", dimension1);
    		printf("DImension 2: %d\n", dimension2);
    		exit(0);
    	}
    	
    	for (i = 0; i < 4096; i++)
    	{
    		for (j = 0; j < 4096; j++)
    		{
    			fscanf(fptr, "%g", &matrix2[i][j]);
    		}
    	}
    	
    	fclose(fptr);
    	
    	time_t seconds_start;
    	time_t seconds_finish;
    	
    	int k = 0;
    	
    	seconds_start = time(NULL);
    	
    	for (i = 0; i < 4096; i++)
    	{
    		for (j = 0; j < 4096; j++)
    		{
    			for (k = 0; k < 4096; k++)
    			{
    				matrix3[i][j] += matrix1[i][k] * matrix2[k][j]; 
    			}
    		}
    	}
    	
    	printf("Running C matrix mul for 32 bit floats\n");
    	
    	seconds_finish = time(NULL);
    	
    	printf("Time taken for calculations = %ld\n", (seconds_finish - seconds_start) );
    	
    	fptr = fopen(output_file, "w");
    	
    	fprintf(fptr, "2\n4096X4096\n");
    	
    	for (i = 0; i < 4096; i++)
    	{
    		for (j = 0; j < 4096; j++)
    		{
    			fprintf(fptr, "%g ", matrix3[i][j]);
    		}
    		fprintf(fptr, " \n");
    	}
    	
    	fclose(fptr);
}
void Run_64BitDouble(char* input_file, char* output_file)
{
	FILE* fptr = fopen(input_file, "r");
    	
    	if (fptr == NULL)
    	{
    		printf("File could not be opened\n");
    		exit(0);
    	}
    	
    	int programtype = 0;
    	int datatype = 0;
    	int dimension1 = 0, dimension2 = 0;
    	char garbage;
    	
    	fscanf(fptr, "%d", &programtype);
    	fscanf(fptr, "%d", &datatype);
    	fscanf(fptr, "%d%c%d", &dimension1, &garbage, &dimension2);
    	
    	if(dimension1 != 4096 || dimension2 != 4096)
    	{
    		printf("Invalid Dimensions given for matrix 1\n");
    		printf("DImension 1: %d", dimension1);
    		printf("DImension 2: %d", dimension2);
    		exit(0);
    	}
    	
    	int i = 0, j = 0;
    	
    	static double matrix1[4096][4096];
    	static double matrix2[4096][4096];
    	static double matrix3[4096][4096];
    	
    	for (i = 0; i < 4096; i++)
    	{
    		for (j = 0; j < 4096; j++)
    		{
    			fscanf(fptr, "%lf", &matrix1[i][j]);
    		}
    	}
    	
    	fscanf(fptr, "%d%c%d", &dimension1, &garbage, &dimension2);
    	
    	if(dimension1 != 4096 || dimension2 != 4096)
    	{
    		printf("Invalid Dimensions given for matrix 1\n");
    		printf("DImension 1: %d\n", dimension1);
    		printf("DImension 2: %d\n", dimension2);
    		exit(0);
    	}
    	
    	for (i = 0; i < 4096; i++)
    	{
    		for (j = 0; j < 4096; j++)
    		{
    			fscanf(fptr, "%lf", &matrix2[i][j]);
    		}
    	}
    	
    	fclose(fptr);
    	
    	time_t seconds_start;
    	time_t seconds_finish;
    	
    	int k = 0;
    	
    	printf("Running C matrix mul for 64 bit doubles\n");
    	
    	seconds_start = time(NULL);
    	
    	for (i = 0; i < 4096; i++)
    	{
    		for (j = 0; j < 4096; j++)
    		{
    			for (k = 0; k < 4096; k++)
    			{
    				matrix3[i][j] += matrix1[i][k] * matrix2[k][j]; 
    			}
    		}
    	}
    	
    	
    	seconds_finish = time(NULL);
    	
    	
    	printf("Time taken for calculations = %ld\n", (seconds_finish - seconds_start) );
    	
    	fptr = fopen(output_file, "w");
    	
    	fprintf(fptr, "4\n4096X4096\n");
    	
    	for (i = 0; i < 4096; i++)
    	{
    		for (j = 0; j < 4096; j++)
    		{
    			fprintf(fptr, "%g ", matrix3[i][j]);
    		}
    		fprintf(fptr, " \n");
    	}
    	
    	fclose(fptr);
}
