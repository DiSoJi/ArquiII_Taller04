#include "stdio.h"
#include <omp.h>
#include <stdlib.h> 

void saxpy(int n, float a, float * restrict x, float * restrict y)
{
    double start_time, run_time;
    /*start timer */
	start_time = omp_get_wtime();
    for (int i = 0; i < n; ++i){

        y[i] = a*x[i] + y[i];

    }
    run_time = omp_get_wtime() - start_time;
    printf("Unparalled Version Duration:  %f \n", run_time);
    printf("With a vector size of:  %d \n", n);
}
void *random_Gen(float *x, float *y, int n){
	srand(time(0));
	for (int i = 0; i < n; i++){
        x[i] = (rand() % 1000);
        y[i] = (rand() % 1000);
        
    }
};

int main(){
    int n = 100000;
    float x[n];
    float y[n];
    random_Gen(x,y,n);
    saxpy(n, 2.0, x, y);
    
}
