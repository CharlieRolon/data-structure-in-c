#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

double f( int n, double a[], double x );
double g( int n, double a[], double x );
int main(int argc, char *argv[]) {
	clock_t start, stop;
	double duration;
	double a[] = {1,2,3,4,5,6,7,8,9};
	start = clock();
	for ( int i=0; i<1e7; i++ ){
		f(9, a, 1.1);
	}
	stop = clock();
	duration = ((double)(stop-start))/CLK_TCK;
	printf("%6.2e\n",duration);
	return 0;
}
//°ËÌ«ÐÐ 
double f( int n, double a[], double x )
{
	int i;
	double p = a[0];
	for ( i=1; i<=n; i++) {
		p += (a[0] * pow(x,i)); 
	}
	return p;
}
//ÐÐ
double g( int n, double a[], double x )
{
	int i;
	double p = a[n];
	for ( i=n; i>0; i-- )
		p = a[i-1] + x*p;
	return p; 
}
