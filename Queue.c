#include <stdio.h>
#include <stdlib.h>
#define ERROR -1
typedef int Position;
struct QNode {
	int *Data;
	Position Front, Rear;
	int MaxSize; 
};

typedef struct QNode *Queue;

Queue CreateQueue( int MaxSize )
{
	Queue Q = (Queue)malloc(sizeof(struct QNode));
	Q->Data = (int *)malloc(MaxSize*sizeof(int));
	Q->Front = Q->Rear = 0;
	Q->MaxSize = MaxSize;
	return Q;
} 
 
int IsFull( Queue Q )
{
	return ((Q->Rear+1)%Q->MaxSize==Q->Front);
}
 
int AddQ( Queue Q, int X )
{
	if ( IsFull(Q) ) {
 		printf("FULL");
 		return 0;
	}
	else {
		Q->Rear = (Q->Rear+1)%Q->MaxSize;
		Q->Data[Q->Rear] = X;
		return 1;
	}
}
 
int IsEmpty( Queue Q )
{
 	return (Q->Front == Q->Rear);
}
 
int DeleteQ( Queue Q )
{
 	if ( IsEmpty(Q)) {
 		printf("EMPTY");
 		return ERROR;
	}
	else {
	 	Q->Front = (Q->Front+1)%Q->MaxSize;
	 	return Q->Data[Q->Front];
	}
}