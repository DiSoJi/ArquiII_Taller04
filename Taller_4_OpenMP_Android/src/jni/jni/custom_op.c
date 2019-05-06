#include <stdio.h> 
#include <stdlib.h> 
#include <omp.h>
//# define ARRAY_SIZE 10
#include <assert.h>
#include <arm_neon.h>

#define SIZE 10000


void main (){

    int m, n, p, q;
    //double sum = 0;
    m = SIZE;
    n = p = SIZE;
    q = SIZE;

    float **first = malloc(m * sizeof(float *));
    for(int i = 0; i < m; i++) {
        first[i] = malloc(n * sizeof(float));
    }
    float **second = malloc(p * sizeof(float *));
    for(int i = 0; i < p; i++) {
        second[i] = malloc(q * sizeof(float));
    }
    float **result = malloc(m * sizeof(double *));
    for(int i = 0; i < m; i++) {
        result[i] = malloc(q * sizeof(double));
    }

    srand(time(0));
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            first[i][j] = (rand() % 255);
        }
    }

    for (int i = 0; i < p; i++){
        for (int j = 0; j < q; j++){
            second[i][j] = (rand() % 255);
        }
    }
    //Matrix Addition
    double start_time, run_time;
    //float32x4_t result;
    start_time = omp_get_wtime();
    //#pragma omp parallel for
    for (int i = 0; i < SIZE; i+=4 ){
        for (int j = 0; j < SIZE; j+=4){
            result[i][j] = first[i][j] + second [i][j];
        }
    }
    run_time = omp_get_wtime() - start_time;
    printf("Unparalled Version Duration:  %f \n", run_time);
    printf("With a squared Matrix size of:  %d \n", SIZE);

}