#include <omp.h> 
#include <stdio.h> 
#include <stdlib.h>
#define NUMTHREADS 6
int main(argc,argv) 
{ 
	int nthreads, tid;
	int n;
	int r, seed;
	int sum = 0;

	// Generates 4 random numbers and sums them together.
	// Each thread has his own random seed, based on his
	// thread id.

    #pragma omp parallel private(tid,seed) num_threads(NUMTHREADS)
	{ 
		tid = omp_get_thread_num();
    	seed = time(NULL)%1000 * (tid+1);
	    srand(seed);
		if (tid == 0)
        {
        	nthreads = omp_get_num_threads();
        	printf("Number of threads in parallel region = %d\n", nthreads);
        }

        #pragma omp  for  private(n,r) reduction(+ : sum)
		for (n=0; n<NUMTHREADS*2;n++) {
            r = rand() % 100;
            printf("Thread No %d  working on %d got rand %d\n",tid, n, r);
            sum += r;
        }
    }
    printf("Sum of rands  was: %d\n",sum);
    return 0;
}

