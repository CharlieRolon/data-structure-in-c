#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

typedef struct AVLNode *Position;
typedef Position AVLTree;
struct AVLNode {
	int Data;
	AVLTree Left;
	AVLTree Right;
	int Height;
};

int Max ( int a, int b )
{
	return a > b ? a : b; 
}

int GetHeight( AVLTree A )
{
	int HL, HR;
	if ( A ) {
		HL = GetHeight( A->Left );
		HR = GetHeight( A->Right );
		return Max( HL, HR ) + 1;
	}
	return 0;
}

AVLTree SingleLeftRotation( AVLTree A )
{ 
	AVLTree B = A->Left;
	A->Left = B->Right;
	B->Right = A;
	A->Height = Max( GetHeight(A->Left), GetHeight(A->Right))+1;
	B->Height = Max( GetHeight(B->Left), A->Height )+1;
	
	return B; 
}

AVLTree SingleRightRotation( AVLTree A )
{
	AVLTree B = A->Right;
	A->Right = B->Left;
	B->Left = A;
	A->Height = Max( GetHeight(A->Left), GetHeight(A->Right))+1;
	B->Height = Max(  A->Height, GetHeight(B->Left) )+1;
	
	return B; 
}

AVLTree DoubleLeftRightRotation( AVLTree A )
{ 
	A->Left = SingleRightRotation(A->Left);
	return SingleLeftRotation(A);
}

AVLTree DoubleRightLeftRotation( AVLTree A )
{
	A->Right = SingleLeftRotation(A->Left);
	return SingleRightRotation(A);
}

AVLTree Insert ( AVLTree T, int X )
{
 	if ( !T ) {
 		T = (AVLTree)malloc(sizeof(struct AVLNode));
		T->Data = X;
		T->Height = 0;
		T->Left = T->Right = NULL; 
	}
	
	else if ( X < T->Data ){
	T->Left = Insert( T->Left, X );
	if ( GetHeight(T->Left)-GetHeight(T->Right) == 2 )
		if ( X < T->Left->Data )
			T = SingleLeftRotation(T);
		else
			T = DoubleLeftRightRotation(T); 
	}
	 
	else if ( X > T->Data ){
	T->Right = Insert( T->Right, X );
	if ( GetHeight(T->Right)-GetHeight(T->Left) == 2 )
		if ( X > T->Left->Data )
			T = SingleRightRotation(T);
		else
			T = DoubleRightLeftRotation(T); 
	} 
	
	T->Height = Max (GetHeight(T->Left),GetHeight(T->Right)) + 1;
	return T;
} 


