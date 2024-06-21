#include "stdio.h"
#include "stdlib.h"
#include "immintrin.h"
#include "time.h"
#include "omp.h"

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
    	
		printf("Doing multiplication...\n");

    	seconds_start = time(NULL);
    	
    	#pragma omp parallel for private(j,k) num_threads(8)
    	for (i = 0; i < 4096; i++) 
    	{
  			for (j = 0; j < 4096; j += 8) 
  			{
    			__m256i sum = _mm256_setzero_si256();
    			
    			for (int k = 0; k < 4096; k++) 
    			{
      				__m256i bc_mat1 = _mm256_set1_epi32(matrix1[i][k]);
      				__m256i vec_mat2 = _mm256_loadu_si256((__m256i*)&matrix2[k][j]);
      				__m256i prod = _mm256_mullo_epi32(bc_mat1, vec_mat2);
      				sum = _mm256_add_epi32(sum, prod);
    			}
    			_mm256_storeu_si256((__m256i*)&matrix3[i][j], sum);
  			}
		}
    	
    	
    	seconds_finish = time(NULL);
    	
    	printf("Finished in %ld seconds...", (seconds_finish - seconds_start) );

		printf("Resultant matrix written to %s",  output_file);
    	
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
    	
		#pragma omp parallel for private(j,k) num_threads(8)
    	for (i = 0; i < 4096; i++)
    	{
        	for (j = 0; j < 4096; j += 4)
        	{
            		__m256i sum = _mm256_setzero_si256();
            		for (k = 0; k < 4096; k++)
            		{
                		__m256i bc_mat1 = _mm256_set1_epi64x(matrix1[i][k]);
                		__m256i vec_mat2 = _mm256_loadu_si256((__m256i *)&matrix2[k][j]);
                		__m256i prod = _mm256_mul_epi32(bc_mat1, vec_mat2);
                		sum = _mm256_add_epi64(sum, prod);
            		}

            		_mm256_storeu_si256((__m256i *)&matrix3[i][j], sum);
        	}
    	}
    	
    	
    	seconds_finish = time(NULL);
    	
    	printf("Finished in %ld seconds...", (seconds_finish - seconds_start) );

		printf("Resultant matrix written to %s",  output_file);
    	
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
    	
    	printf("Running C matrix mul for 32 bit floats\n");
    	
    	time_t seconds_start;
    	time_t seconds_finish;
    	
    	int k = 0;
    	
    	seconds_start = time(NULL);
    	
		#pragma omp parallel for private(j,k) num_threads(8)
    	for (i = 0; i < 4096; i++)
    	{
        	for (j = 0; j < 4096; j += 8)
        	{
            		__m256 sum = _mm256_setzero_ps();
            		for (k = 0; k < 4096; k++)
            		{
                		__m256 bc_mat1 = _mm256_set1_ps(matrix1[i][k]);
                		__m256 vec_mat2 = _mm256_loadu_ps(&matrix2[k][j]);
                		__m256 prod = _mm256_mul_ps(bc_mat1, vec_mat2);
                		sum = _mm256_add_ps(sum, prod);
            		}

            		_mm256_storeu_ps(&matrix3[i][j], sum);
        	}
    	}
    	
    	
    	
    	seconds_finish = time(NULL);
    	
    	printf("Finished in %ld seconds...", (seconds_finish - seconds_start) );

		printf("Resultant matrix written to %s",  output_file);
    	
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
    	
    	printf("Running C matrix mul with vector instructions for 64 bit doubles\n");
    	
    	seconds_start = time(NULL);
    	
		#pragma omp parallel for private(j,k) num_threads(8)
    	for (i = 0; i < 4096; i++)
    	{
        	for (j = 0; j < 4096; j += 4)
        	{
            		__m256d sum = _mm256_setzero_pd();
            		for (k = 0; k < 4096; k++)
            		{
                		__m256d bc_mat1 = _mm256_set1_pd(matrix1[i][k]);
                		__m256d vec_mat2 = _mm256_loadu_pd(&matrix2[k][j]);
                		__m256d prod = _mm256_mul_pd(bc_mat1, vec_mat2);
                		sum = _mm256_add_pd(sum, prod);
            		}

            		_mm256_storeu_pd(&matrix3[i][j], sum);
        	}
    	}
    	
    	
    	seconds_finish = time(NULL);
    	
    	
    	printf("Finished in %ld seconds...", (seconds_finish - seconds_start) );

		printf("Resultant matrix written to %s",  output_file);
    	
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
