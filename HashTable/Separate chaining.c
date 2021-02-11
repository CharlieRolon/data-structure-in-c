#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define KEYLENGTH 15
#define MAXTABLESIZE 1000000

typedef char ElementType[KEYLENGTH+1]; //字符串
typedef int Index;

typedef struct LNode *PtrToLNode;
struct LNode {
	ElementType Data;
	PtrToLNode Next;
};
typedef PtrToLNode Position;
typedef PtrToLNode List;

typedef struct TblNode* HashTable; 
struct TblNode{
	int TableSize;
	List Heads;
};

int NextPrime( int N )
{ // 返回大于N且不超过MAXTABLESIZE的最小素数
	int i, p = (N%2)?N+2:N+1; //p从大于N的下一个奇数开始
	
	while (p<=MAXTABLESIZE) {
		for ( i=(int)sqrt(p); i>2; i-- )
			if (!(p%i)) break;
		if ( i==2 ) break;
		else p+=2; //试探下一个奇数
	} 
	return p;
}

HashTable CreateTable( int TableSize )
{
	HashTable H;
	int i;
	
	H = (HashTable)malloc(sizeof(struct TblNode));
	H->TableSize = NextPrime(TableSize);
	
	//分配链表头节点数组
	H->Heads = (List)malloc(H->TableSize*sizeof(struct LNode));
	//初始化表头结点
	for ( i=0; i<H->TableSize; i++ ) {
		H->Heads[i].Data[0] = '\0';
		H->Heads[i].Next = NULL;
	}
	
	return H;
}

Position Find( HashTable H, ElementType Key )
{
	Position P;
	Index Pos;
	
	Pos = Hash( Key, H->TableSize );
	P = H->Heads[Pos].Next; //从该链表的第一个结点开始
	while ( P && strcmp(P->Data, Key)) {
		P = P->Next;
	}
	return P;
}

int Insert( HashTable H, ElementType Key )
{
	Position P, NewCell;
	Index Pos;
	
	P = Find( H, Key );
	if ( !P ) { //关键词未找到，可插入
		NewCell = (Position)malloc(sizeof(struct LNode));
		strcpy(NewCell->Data, Key);
		Pos = Hash( Key, H->TableSize );
		NewCell->Next = H->Heads[Pos].Next;
		H->Heads[Pos].Next = NewCell;
		return 1;
	}
	else {
		printf("key already exists");
		return 0;
	}
}

void DestroyTable( HashTable H )
{
	int i;
	Position P, tmp;
	
	for ( i=0; i<H->TableSize; i++ ){
		P = H->Heads[i].Next;
		while (P) {
			tmp = P->Next;
			free( P );
			P = tmp;
		}
	}
	free(H->Heads);
	free(H);
}