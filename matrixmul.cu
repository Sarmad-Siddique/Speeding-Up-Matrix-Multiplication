#include <iostream>
#include <math.h>
#include <functional>
#include <stdlib.h>    
#include <time.h>       
#include <chrono>

#define ROW_TILE_WIDTH 32
#define COL_TILE_WIDTH 32

template<typename T>
__global__
void matrix_multiply(T *A, T *B, T* C, int width, int C_rows, int C_cols)
{
    int row = blockIdx.y * blockDim.y + threadIdx.y;   
    int col = blockIdx.x * blockDim.x + threadIdx.x;
        
    if( row < C_rows && col < C_cols ){
        T value = 0;
        for(int k = 0; k < width; k++){
            value += A[row * width + k] * B[k * C_cols + col];
        }
        C[row * C_cols + col] = value;
    }
}

template<typename T>
void initialize_matrix(T* M, int rows, int cols, std::function<float()> F) {
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
        M[i * cols + j] = F();
        }
    }
}


int main(void)
{
    int A_rows = 4096;
    int A_cols = 4096;
    int B_rows = 4096;
    int B_cols = 4096;
    int C_rows = 4096;
    int C_cols = 4096;
    int A_size = 4096 * 4096;
    int B_size = 4096 * 4096;
    int C_size = 4096 * 4096;
    float *A, *B, *C;

    
    cudaMallocManaged(&A, A_size*sizeof(float));
    cudaMallocManaged(&B, B_size*sizeof(float));
    cudaMallocManaged(&C, C_size*sizeof(float));

    srand (time(NULL));
    auto rand_numbers = []() -> float {
        auto f = static_cast<float>(rand())/(static_cast<float>(RAND_MAX/1000));
        int n = static_cast<int>(f);
        return static_cast<float>(n);
    };

    initialize_matrix<float>(A, A_rows, A_cols, rand_numbers);
    initialize_matrix<float>(B, B_rows, B_cols, rand_numbers);

    dim3 dim_grid(C_cols/COL_TILE_WIDTH, C_rows/ROW_TILE_WIDTH, 1);
    dim3 dim_block(COL_TILE_WIDTH, ROW_TILE_WIDTH, 1);

    std::cout << "Starting matrix multiplication (GPU): "  << A_rows << " x " << A_cols <<  std::endl;

    uint64_t start_time, end_time, elapsed;

    start_time = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::high_resolution_clock::now().time_since_epoch())
            .count();
        
    matrix_multiply<float><<<dim_grid, dim_block>>>(A, B, C, A_cols, C_rows, C_cols);

    end_time = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::high_resolution_clock::now().time_since_epoch())
            .count();

    elapsed = (end_time - start_time);

    std::cout << "ELapsed: " << elapsed << std::endl;

    cudaDeviceSynchronize();

    // FILE* fptr = fopen("output.txt", "w");
    	
    // fprintf(fptr, "1\n4096X4096\n");
    	
    // for (int i = 0; i < 4096; i++)
    // {
    // 	for (int j = 0; j < 4096; j++)
    // 	{
    // 		fprintf(fptr, "%f ", C[i * C_cols + j]);
    // 	}
    // 	fprintf(fptr, " \n");
    // }
    	
    // fclose(fptr);

    cudaFree(A);
    cudaFree(B);
    cudaFree(C);
    
    return 0; 
}