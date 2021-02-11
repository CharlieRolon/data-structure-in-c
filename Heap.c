#include <stdio.h>
#include <stdlib.h>
#define ERROR -1

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

typedef struct HNode *Heap;
struct HNode {
	int *Data;
	int Size;
	int Capacity;
};
typedef Heap MaxHeap;
typedef Heap MinHeap;

#define MAXDATA 1000

MaxHeap CreateHeap( int MaxSize )
{
	MaxHeap H = (MaxHeap)malloc(sizeof(struct HNode));
	H->Data = (int*)malloc((MaxSize+1)*sizeof(int));
	H->Size = 0;
	H->Capacity = MaxSize;
	H->Data[0] = MAXDATA; 
	
	return H;
}

int IsFull( MaxHeap H )
{
	return (H->Size == H->Capacity);
}

int Insert( MaxHeap H, int X )
{
	int i;
	
	if (IsFull(H)) {
		return 0;
	}
	i = ++H->Size;
	for ( ; H->Data[i/2]<X; i/=2 )
		H->Data[i] = H->Data[i/2];
	H->Data[i] = X;
	return 1;
}

int Delete( MaxHeap H )
{
	if (!H->Size){
		return ERROR;
	}
	int MaxItem = H->Data[1];
	int temp = H->Data[H->Size--];
	int Child, Parent;
	for ( Parent=1 ; Child<H->Size; Parent=Child){
		Child = 2*Parent;
		if ((Child!=H->Size) && 
			(H->Data[Child]<H->Data[Child+1]))
			Child++;
		if (temp>=H->Data[Child])
			break;
		else
			H->Data[Parent] = H->Data[Child];
	}
	H->Data[Parent] = temp;
	return MaxItem;
} 


void PercDown( MaxHeap H, int p )
{
	int Parent, Child;
	int X;
	
	X = H->Data[p];
	for( Parent=p; Parent*2<=H->Size; Parent=Child ){
		Child = Parent*2;
		if (Child!=H->Size && H->Data[Child]<H->Data[Child+1])
			Child++;
		if ( X >= H->Data[Child] ) break;
		else H->Data[Parent] = H->Data[Child];
	} 
	H->Data[Parent] = X;
 }
 
void BuildHeap( MaxHeap H )
{
	int i;
	for ( i = H->Size/2; i>0; i-- )
		PercDown( H, i );
 } 

