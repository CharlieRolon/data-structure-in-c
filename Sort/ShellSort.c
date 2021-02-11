#include <stdio.h>

//希尔排序：
//Dk间隔有序的序列，Dk-1间隔中Dk间隔也必有序，(Dk>Dk-1)
//Dk为增量序列，最好是互质的，可避免产生最坏情况
//如Hibbard增量序列：Dk = 2^k-1; Sedgewick增量序列 
void ShellSort( int A[], int N )
{ //sedgewick增量序列
	int D, Si, P, i;
	int temp;
	int Sedgewick[] = {929, 505, 209, 109, 41, 19, 5, 1, 0};
	
	for ( Si=0; Sedgewick[Si]>=N; Si++ );
	for ( D=Sedgewick[Si]; D>0; D=Sedgewick[++Si] )
		//插入排序部分 
		for ( P=D; P<N; P++ )
			temp = A[P];
			for ( i=P; i>=D && A[i-D]>temp; i-=D )
				A[i] = A[i-D];
			A[i] = temp;
 } 
