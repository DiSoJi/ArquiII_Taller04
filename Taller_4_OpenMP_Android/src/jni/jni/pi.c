/*

This program will numerically compute the integral of

                  4/(1+x*x) 
				 
History: Written by Tim Mattson, 11/99.

#-----------------------------------------------------

Modified by JGG 

#--------------------------------------------------------

*/

#include <stdio.h>
#include <omp.h>

static long num_steps = 100000000;
double step;
int main ()
{
	int i, nprocs;
	double x, pi, sum = 0.0;
	double start_time, run_time;

	step = 1.0/(double) num_steps;

	/*start timer */
	start_time = omp_get_wtime();


	for (i=1;i<= num_steps; i++){
	x = (i-0.5)*step;
	sum = sum + 4.0/(1.0+x*x);
	}
	
	pi = step * sum;
	run_time = omp_get_wtime() - start_time;
	printf("\n pi is %f in %f seconds \n",pi,run_time);
	
}	  


