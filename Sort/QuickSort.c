#include <stdio.h>
#include <stdlib.h>
//quick sort, baby!!

//重点: 如何选出主元，如何分成两个独立子集
//best T(N)=O(NlogN) 正好中分 
//特点: 需要递归实现
//解决: 大规模用递归，小规模直接调用简单排序，可定义一个cutoff阈值 

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

void Swap( int *a, int *b )
{
	int t = *a; *a = *b; *b = t;
}

int Median3 ( int A[], int Left, int Right )
{
	int Center = (Left+Right)/2;
	if ( A[Left]>A[Center] )
		Swap( &A[Left], &A[Center] );
	if ( A[Left]>A[Right] )
		Swap( &A[Left], &A[Right] );
	if ( A[Center]>A[Right] )
		Swap( &A[Center], &A[Right] );
	//A[Left]<=A[Center]<=A[Right]
	Swap( &A[Center], &A[Right-1] );//将pivot藏到右边
	//只需考虑A[Left+1]~A[Right-2]
	return A[Right-1]; 
}

void Qsort( int A[], int Left, int Right )
{
	int Pivot, Cutoff, Low, High;
	Cutoff = 4;
	if ( Cutoff <= Right - Left ){
		Pivot = Median3( A, Left, Right );
		Low = Left; High = Right - 1;
		while (1) { /*将序列中比基准小的移到基准左边，大的移到右边*/
			while ( A[++Low] < Pivot );
			while ( A[--High] > Pivot );
			if ( Low<High )
				Swap( &A[Low], &A[High] );
			else break;
		}
		Swap( &A[Low], &A[Right-1] ); /* 将基准换到正确的位置 */
		Qsort( A, Left, Low-1 );
		Qsort( A, Low+1, Right );
	}
	else
		InsertionSort( A+Left, Right-Left+1);
} 

void QuickSort ( int A[], int N )
{
	Qsort( A, 0, N-1 ); 
}
