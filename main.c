#include<stdio.h>
#include<complex.h>
#include<stdlib.h>
#include"Faddeeva.h"
#include<time.h>
#include<math.h>
#include<omp.h>

double complex FNF( double complex Z );

int main(void)
{
	printf("Threads = %d\n", omp_get_max_threads());
	long n = 1000000000;

	complex double ctr = 0;
	double start = omp_get_wtime();
	long hit = 0;
	#pragma omp parallel default(none) shared(n) reduction(+:hit,ctr)
	{
		unsigned seed = time(NULL)*(omp_get_thread_num() + 1) + 1337;

		#pragma omp for schedule(dynamic,100)
		for( long i = 0; i < n; i++ )
		{
			double real = -20000.0 + 26000.0* rand_r(&seed) / RAND_MAX;
			double imag = 0.2*rand_r(&seed) / RAND_MAX;
			double complex A = real + imag*I;
			if( cabs(A) <= 6.0 )
				hit++;
			complex double result = FNF(A);
			ctr += result;
		}
	}
	double end = omp_get_wtime();
	printf("Fast Nuclear Faddeva===================================\n");
	printf("TIME = %lf seconds\n", end-start);
	printf("Time per Faddeeva: %.3lf (ns)\n", (end-start) / (n) * 1.0e9);
	printf("result: %.2lf + %.2lfi\n", creal(ctr), cimag(ctr));
	printf("Percent Full Faddeeva Rate: %.4lf%%\n", (double) hit / n * 100.0);

	ctr = 0;
	start = omp_get_wtime();
	hit = 0;
	#pragma omp parallel default(none) shared(n) reduction(+:hit,ctr)
	{
		unsigned seed = time(NULL)*(omp_get_thread_num() + 1) + 1337;

		#pragma omp for schedule(dynamic,100)
		for( long i = 0; i < n; i++ )
		{
			double real = -20000.0 + 26000.0* rand_r(&seed) / RAND_MAX;
			double imag = 0.2*rand_r(&seed) / RAND_MAX;
			double complex A = real + imag*I;
			if( cabs(A) <= 6.0 )
				hit++;
			complex double result = Faddeeva_w(A,0.0);
			ctr += result;
		}
	}
	end = omp_get_wtime();
	printf("MIT Faddeva============================================\n");
	printf("TIME = %lf seconds\n", end-start);
	printf("Time per Faddeeva: %.3lf (ns)\n", (end-start) / (n) * 1.0e9);
	printf("result: %.2lf + %.2lfi\n", creal(ctr), cimag(ctr));
	printf("Percent Full Faddeeva Rate: %.4lf%%\n", (double) hit / n * 100.0);

	return 0;
}

