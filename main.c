#include<stdio.h>
#include<complex.h>
#include<stdlib.h>
#include"Faddeeva.h"

double complex FNF( double complex Z );

int main(void)
{
	int N = 1000;
	double domain = 20.0;

	double delta = domain/N;
	double test = -10.0 + delta*213;
	double complex tester = -10.0 + delta*213 + 0*I;
	printf("abs(tester) = %lf\n", cabs(tester));
	tester = Faddeeva_w(test, 0.0);
	printf("MIT creal(test) = %e\n", creal(tester));
	tester = FNF(test);
	printf("FNF creal(test) = %e\n", creal(tester));
	
	FILE *freal = fopen("real.dat", "w");
	FILE *fimag =  fopen("imag.dat", "w");

	for( int i = 0; i < N/2; i++ )
	{
		double imag = domain * (double) i / N;
		for( int j = 0; j < N; j++ )
		{
			double real = -domain/2.0 + domain * (double) j / N;
			double complex z = real + imag * I;
			double complex W = FNF(z); 
			//double complex W = Faddeeva_w(z,0.0); 

			fprintf(freal, "%e\t", creal(W));
			fprintf(fimag, "%e\t", cimag(W));
		}
		fprintf(freal,"\n");
		fprintf(fimag,"\n");
	}
	fclose(freal);
	fclose(fimag);
	return 0;
}

