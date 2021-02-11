#include <stdio.h>
#include <stdlib.h>
//L:��߳�ʼλ�� R:�ұ߳�ʼλ�� RightEnd:�ұ��յ�λ�� 
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
	
	while( L<=LeftEnd ) //���ʣ�µ� 
		tempA[temp++] = A[L++];
	while( R<=RightEnd ) //�ұ�ʣ�µ� 
		tempA[temp++] = A[R++];
	
	for ( i=0; i<NumElements; i++, RightEnd--)
		A[RightEnd] = tempA[RightEnd]; //�������tempA���ƻ�A[]
}

void MSort( int A[], int tempA[], int L, int RightEnd )
{
	int Center;
	
	if ( L<RightEnd ){
		Center = (L+RightEnd)/2;
		MSort( A, tempA, L, Center );//�ݹ���� 
		MSort( A, tempA, Center+1, RightEnd );//�ݹ��ұ� 
		Merge( A, tempA, L, Center+1, RightEnd );//���� 
	}
}
 
void MergeSort( int A[], int N )
{
	int *tempA;
	tempA = (int*)malloc( N*sizeof(int) ); //��������������飬�Ͳ���Ҫ�ڵݹ�������ظ�malloc 
	if (tempA!=NULL) {
		MSort(A, tempA, 0, N-1);
		free(tempA);
	} 
	else printf("�ռ䲻��"); 
}

//Merge1:Merge�����в����ƻ�A������ 
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
	
	while( L<=LeftEnd ) //���ʣ�µ� 
		tempA[temp++] = A[L++];
	while( R<=RightEnd ) //�ұ�ʣ�µ� 
		tempA[temp++] = A[R++];
}

//�ϲ�����һ�������� 
void MergePass( int A[], int tempA[], int N, int length )
{
	int i, j;
	for ( i=0; i<=N-2*length; i+=2*length ) //�ȳɶԴ���
		Merge1( A, tempA, i, i+length, i+2*length-1 );
	if ( i+length<N ) //ʣ��������Ϊlength������ 
		Merge1( A, tempA, i, i+length, N-1 );
	else //ʣһ������Ϊlength����
		for ( j=i; j<N; j++ ) tempA[j] = A[j]; 
}

//�ǵݹ� 
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
	else printf("�ռ䲻��");
}
