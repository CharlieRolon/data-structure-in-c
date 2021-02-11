#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAXTABLESIZE 100000 //允许开辟最大散列长度

typedef int ElementType; //关键词
typedef int Index; //散列地址类型
typedef Index Position; //数据所在位置与散列地址是同一类型
typedef enum { Legitimate, Empty, Deleted } EntryType;
/*散列单元状态类型， 分别对应：有合法元素，空元素、有已删除元素*/
typedef struct HashEntry Cell; //散列表单元类型 
struct HashEntry {
	ElementType Data; //存放元素
	EntryType Info; //单元状态（EntryType）
};

typedef struct TblNode *HashTable; //散列表类型
struct TblNode {
	int TableSize; //表的最大长度单元数据的数组
	Cell *Cells; //存放散列	
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
	H->Cells = (Cell*)malloc(sizeof(Cell)*H->TableSize);
	for ( i=0; i<H->TableSize; i++ )
		H->Cells[i].Info = Empty;
		
	return H;
}

Position Find( HashTable H, ElementType Key )
{
	Position CurrentPos, NewPos;
	int CNum = 0; //冲突计数器
	
	NewPos = CurrentPos = Hash( Key, H->TableSize ); //初始散列位置
	//该位置的单元非空，并且不是要找的元素时，发生冲突
	while( H->Cells[NewPos].Info!=Empty && H->Cells[NewPos].Data!=Key ){
		if ( ++CNum%2 ) { // 若为奇数次冲突
			NewPos = CurrentPos + (CNum+1)*(CNum+1)/4; 
			//平方探测，增量为[(CNum+1)/2]^2
		}
		else {
			NewPos = CurrentPos - CNum*CNum/4;
			//增量为-[CNum/2]^2
			while ( NewPos<0 )
				NewPos += H->TableSize; 	
		}
	}
	return NewPos; //此时NewPos或是Key的位置，或是一个空单元位置(即表示找不到)
}
	
int Insert( HashTable H, ElementType Key )
{
	Position Pos = Find( H, Key ); //检查Key是否存在
	
	if ( H->Cells[Pos].Info != Legitimate ) {
		H->Cells[Pos].Info = Legitimate;
		H->Cells[Pos].Data = Key;
		return 1;
	}
	else {
		printf("key already exists");
		return 0;
	}
	
}