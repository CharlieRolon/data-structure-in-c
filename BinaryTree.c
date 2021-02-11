#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

typedef struct TNode *Position;
typedef Position BinTree;
struct TNode {
	int Data;
	BinTree Left;
	BinTree Right;
};

void InorderTraversal ( BinTree BT )
{
	if ( BT ) {
		InorderTraversal (BT->Left);
		printf("%d", BT->Data);
		InorderTraversal (BT->Right);
	}
}

Position FindMin( BinTree BST )
{
	if (!BST) return NULL;
	if ( BST->Left )
		return FindMin( BST->Left );
	else return BST;
}

BinTree Insert( BinTree BST, int x )
{
	if (!BST) {
		BST = (BinTree)malloc(sizeof(struct TNode));
		BST->Data = x;
		BST->Left = BST->Right = NULL; 
	}
	else {
		if (x<BST->Data)
			BST->Left = Insert( BST->Left, x );
		else if(x>BST->Data)
			BST->Right = Insert( BST->Right, x);
	}
	return BST;
 } 
 
BinTree Delete( BinTree BST, int x )
{
 	Position tmp;
 	
 	if (!BST)
 		printf("EMPTY");
 	else {
 		if (x<BST->Data)
 			BST->Left = Delete( BST->Left, x );
 		else if ( x>BST->Data )
 			BST->Right = Delete( BST->Right, x );
 		else {
 			if ( BST->Left && BST->Right ){
 				tmp = FindMin( BST->Right );
 				BST->Data = tmp->Data;
 				BST->Right = Delete( BST->Right, BST->Data );
			}
			else {
			 	tmp = BST;
			 	if ( !BST->Left )
			 		BST = tmp->Right;
			 	else
			 		BST = tmp->Left;
			 	free( tmp );
			}		
		}
	}
	return BST;
}


int main(int argc, char *argv[]) {
	return 0;
}
