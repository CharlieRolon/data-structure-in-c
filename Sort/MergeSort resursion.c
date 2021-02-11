#include <stdio.h>
#include <stdlib.h>
//L:左边初始位置 R:右边初始位置 RightEnd:右边终点位置 
void Merge( int A[], int tempA[], int L, int R, int RightEnd )
{
	int LeftEnd, NumElements, temp;
	int i;
	
	LeftEnd = R - 1;
	temp = L;
	NumElements = RightEnd - L + 1;
	
	while ( L<=LeftEnd && R<=RightEnd ) {
		if ( A[L] <= A[R] ) tempA[temp++] = A[L++];
		else tempA[temp++] = A[R++];
	}
	
	while( L<=LeftEnd ) //左边剩下的 
		tempA[temp++] = A[L++];
	while( R<=RightEnd ) //右边剩下的 
		tempA[temp++] = A[R++];
	
	for ( i=0; i<NumElements; i++, RightEnd--)
		A[RightEnd] = tempA[RightEnd]; //将有序的tempA复制回A[]
}

void MSort( int A[], int tempA[], int L, int RightEnd )
{
	int Center;
	
	if ( L<RightEnd ){
		Center = (L+RightEnd)/2;
		MSort( A, tempA, L, Center );//递归左边 
		MSort( A, tempA, Center+1, RightEnd );//递归右边 
		Merge( A, tempA, L, Center+1, RightEnd );//排序 
	}
}
 
void MergeSort( int A[], int N )
{
	int *tempA;
	tempA = (int*)malloc( N*sizeof(int) ); //在外面申请大数组，就不需要在递归过程中重复malloc 
	if (tempA!=NULL) {
		MSort(A, tempA, 0, N-1);
		free(tempA);
	} 
	else printf("空间不足"); 
}

//Merge1:Merge函数中不复制回A的做法 
void Merge1( int A[], int tempA[], int L, int R, int RightEnd )
{
	int LeftEnd, temp;
	int i;
	
	LeftEnd = R - 1;
	temp = L;
	
	while ( L<=LeftEnd && R<=RightEnd ) {
		if ( A[L] <= A[R] ) tempA[temp++] = A[L++];
		else tempA[temp++] = A[R++];
	}
	
	while( L<=LeftEnd ) //左边剩下的 
		tempA[temp++] = A[L++];
	while( R<=RightEnd ) //右边剩下的 
		tempA[temp++] = A[R++];
}

//合并到另一个数组中 
void MergePass( int A[], int tempA[], int N, int length )
{
	int i, j;
	for ( i=0; i<=N-2*length; i+=2*length ) //先成对处理
		Merge1( A, tempA, i, i+length, i+2*length-1 );
	if ( i+length<N ) //剩两个长度为length的子列 
		Merge1( A, tempA, i, i+length, N-1 );
	else //剩一个长度为length子列
		for ( j=i; j<N; j++ ) tempA[j] = A[j]; 
}

//非递归 
void MergeSort1( int A[], int N )
{
	int *tempA, length=1;
	tempA = malloc(N*sizeof(int));
	if (tempA!=NULL){
		while( length<N ){
			MergePass( A, tempA, N, length );
			length *= 2;
			MergePass( tempA, A, N, length);
			length *= 2;
		} 
		free(tempA);
	}
	else printf("空间不足");
}
