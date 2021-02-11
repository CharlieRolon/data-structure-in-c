#include <stdio.h>
#include <stdlib.h>

void InsertionSort( int A[], int N )
{
	int P, i;
	int temp;
	for ( P=1; P<N; P++ ) {
		temp = A[P];
		for ( i=P; i>0 && A[i-1]>temp; i-- )
			A[i] = A[i-1];
		A[i] = temp;
	}
}

void BubbleSort( int A[], int N )
{
	int P, i, temp, flag = 0;
	for ( P=N-1; P>0; P-- )
		for ( i=0; i<P; i++ ) {
			if (A[i] < A[i+1]){
				temp = A[i];
				A[i] = A[i+1];
				A[i+1] = temp;
				flag = 1;
			}
		if ( flag ){
			flag = 0;
			break;
		}
	}
}
