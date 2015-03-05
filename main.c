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
	long n = 10000000;
	unsigned seed = time(NULL) + 1337;
	complex double ctr = 0;
	double scale = 10.0;
	
	double start = omp_get_wtime();
	long hit = 0;
	// FNF
	for( long i = 0; i < n; i++ )
	{
		double real = scale* (double) rand_r(&seed) / RAND_MAX;
		double imag = scale *(double) rand_r(&seed) / RAND_MAX;
		double complex A = real + imag*I;
		if( cabs(A) <= 6.0 )
			hit++;
		complex double result = FNF(A);
		ctr += result;
	}
	double end = omp_get_wtime();
	double FNF_time = end-start;
	start = end;
	// MIT
	for( long i = 0; i < n; i++ )
	{
		double real = scale* (double) rand_r(&seed) / RAND_MAX;
		double imag = scale *(double) rand_r(&seed) / RAND_MAX;
		double complex A = real + imag*I;
		if( cabs(A) <= 6.0 )
			hit++;
		complex double result = Faddeeva_w(A,0.0);
		ctr += result;
	}
	end = omp_get_wtime();
	double MIT_time = end-start;

	printf("FNF avg. W evaluation time: %6.3lf (us)\n", FNF_time / n *1e6);
	printf("MIT avg. W evaluation time: %6.3lf (us)\n", MIT_time / n *1e6);
	printf("result: %.2lf + %.2lfi\n", creal(ctr), cimag(ctr));
	printf("Percent Full Faddeeva Rate: %.4lf%%\n", (double) hit / (2*n) * 100.0);

	return 0;
}

