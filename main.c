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
	double min_real = -9.999980e+03;
	double max_real = 9.984410e+01;
	double real_domain = max_real - min_real;
	double min_img = 3.461271e-01;
	double max_img = 6.752828e-01;
	double img_domain = max_img - min_img;

	complex double ctr = 0;
	double start = omp_get_wtime();
	long hit = 0;
	#pragma omp parallel default(none) \
	shared(n,min_real, real_domain, min_img, img_domain) \
	reduction(+:hit,ctr)
	{
		unsigned seed = time(NULL)*(omp_get_thread_num() + 1) + 1337;

		#pragma omp for schedule(dynamic,100)
		for( long i = 0; i < n; i++ )
		{
			double real = min_real + real_domain * rand_r(&seed) / RAND_MAX;
			double imag = min_img +  img_domain  * rand_r(&seed) / RAND_MAX;
			double complex A = real + imag*I;
			if( cabs(A) <= 6.0 )
				hit++;
			complex double result = FNF(A);
			ctr += result;
		}
	}
	double end = omp_get_wtime();
	double FNF_tpf = (end-start) / n * 1.0e9;
	printf("Fast Nuclear Faddeva===================================\n");
	printf("TIME = %lf seconds\n", end-start);
	printf("Time per Faddeeva: %.3lf (ns)\n", FNF_tpf);
	printf("result: %.2lf + %.2lfi\n", creal(ctr), cimag(ctr));
	printf("Percent Full Faddeeva Rate: %.4lf%%\n", (double) hit / n * 100.0);

	ctr = 0;
	hit = 0;
	start = omp_get_wtime();
	#pragma omp parallel default(none) \
	shared(n,min_real, real_domain, min_img, img_domain) \
	reduction(+:hit,ctr)
	{
		unsigned seed = time(NULL)*(omp_get_thread_num() + 1) + 1337;

		#pragma omp for schedule(dynamic,100)
		for( long i = 0; i < n; i++ )
		{
			double real = min_real + real_domain * rand_r(&seed) / RAND_MAX;
			double imag = min_img +  img_domain  * rand_r(&seed) / RAND_MAX;
			double complex A = real + imag*I;
			if( cabs(A) <= 6.0 )
				hit++;
			complex double result = Faddeeva_w(A,0.0);
			ctr += result;
		}
	}
	end = omp_get_wtime();
	double MIT_tpf = (end-start) / n * 1.0e9;
	printf("MIT Faddeva============================================\n");
	printf("TIME = %lf seconds\n", end-start);
	printf("Time per Faddeeva: %.3lf (ns)\n", MIT_tpf);
	printf("result: %.2lf + %.2lfi\n", creal(ctr), cimag(ctr));
	printf("Percent Full Faddeeva Rate: %.4lf%%\n", (double) hit / (2*n) * 100.0);
	printf("SUMMARY================================================\n");
	printf("FNF: %.3lf (ns)\n", FNF_tpf);
	printf("MIT: %.3lf (ns)\n", MIT_tpf);
	printf("FNF Speedup: %.2lf%%\n", (MIT_tpf - FNF_tpf)/(MIT_tpf) * 100.0);

	return 0;
}

