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
	long n = 100000000;
	unsigned seed = time(NULL) + 1337;
	complex double ctr = 0;

	double start = omp_get_wtime();
	long hit = 0;
	for( long i = 0; i < n; i++ )
	{
		double real = 1.0* (double) rand_r(&seed) / RAND_MAX;
		double imag = 1.0 *(double) rand_r(&seed) / RAND_MAX;
		double complex A = real + imag*I;
		if( cabs(A) <= 6.0 )
			hit++;
		complex double result = FNF(A);
		//complex double result = Faddeeva_w(A,0.0);
		ctr += result;
	}
	double end = omp_get_wtime();
	printf("TIME = %lf seconds\n", end-start);
	printf("%lf us per evaluation\n", (end-start) / n *1e6);
	printf("result: %.2lf + %.2lfi\n", creal(ctr), cimag(ctr));
	printf("Percent Full Faddeeva Rate: %.4lf%%\n", (double) hit / n * 100.0);

	return 0;
}

