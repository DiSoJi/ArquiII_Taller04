
#include <stdio.h> 
#include <stdlib.h> 
#include <omp.h>
//# define ARRAY_SIZE 10
#include <assert.h>
#include <arm_neon.h>

/*
void saxpy(int n, float a, float * restrict x, float * restrict y)
{
    double start_time, run_time;
    //start timer 
	start_time = omp_get_wtime();
    #pragma omp parallel for
    for (int i = 0; i < n; ++i){
        y[i] = a*x[i] + y[i];
    }

    run_time = omp_get_wtime() - start_time;
    printf("Paralled Version Duration:  %f \n", run_time);
    printf("With a vector size of:  %d \n", n);
}
*/
void saxpy_neon(int n, float a, float * restrict x, float * restrict y){

    //int n_neon = n/4;
    
    //float32x4_t result_neon = vaddl_s16(x,y);
    //float32x4_t 
    //int32x64_t vaddl_s(); 
    double start_time, run_time;
    float32x4_t temp_result;
    float32x4_t result;
    //start timer 
    float32x4_t scalar_vector = {a,a,a,a};
	start_time = omp_get_wtime();
    #pragma omp parallel for shared(x,y)
    for (int i = 0; i < n; i+=4){
        float32x4_t vector_a = {x[i],x[i+1],x[i+2],x[i+3]};
        float32x4_t vector_b = {y[i],y[i+1],y[i+2],y[i+3]};
        temp_result = vmulq_f32(vector_a, scalar_vector);
        result = vaddq_f32(temp_result, vector_b);
    }
    run_time = omp_get_wtime() - start_time;
    printf("Paralled Version Duration:  %f \n", run_time);
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
    int n = 10000;
    float x[n];
    float y[n];
    random_Gen(x,y,n);
    //saxpy(n, 2.0, x, y);
    saxpy_neon(n, 2.0, x, y);
}


