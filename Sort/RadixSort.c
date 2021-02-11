#include <stdio.h>
#include <stdlib.h>
#define MaxDigit 4 //位数
#define Radix 10 //进制
//桶排序
//特点: 排序依据元素有限，且数量较少 
//每一个元素建立一个桶

//多关键字排序
//可分次位排序(Least Significant Digit LSD)与主位排序(Most Significant Digit MSD)

//桶元素结点 
typedef struct Node *PtrToNode;
struct Node {
	int key;
	PtrToNode next;
}; 

//桶头结点
struct HeadNode {
	PtrToNode head, tail;
}; 
typedef struct HeadNode Bucket[Radix]; 
//取得倒数第D位的数字
int GetDigit ( int X, int D )
{ //默认次位D=1, 主位D<=MaxDigit 
	int d, i;
	
	for ( i=1; i<=D; i++ ){
		d = X%Radix;
		X /= Radix;
	} 
	return d;
}

//次位排序
void LSDRadixSort( int A[], int N )
{
	int D, Di, i;
	Bucket B;
	PtrToNode tmp, p, List = NULL;
	
	for ( i=0; i<Radix; i++ )  //初始化每个桶为空链表
		B[i].head = B[i].tail = NULL;
	for ( i=0; i<N; i++ ){   //将原始序列逆序存入初始链表List 
		tmp = (PtrToNode)malloc(sizeof(struct Node));
		tmp->key = A[i];
		tmp->next = List;
		List = tmp;
	} 
	//开始排序
	for ( D=1; D<=MaxDigit; D++ ) { //对数据每一位循环处理
		//开始分配(将List中元素分配到对应桶中) 
		p = List;
		while (p) {
			Di = GetDigit(p->key, D);
			
			//从List中摘除
			tmp = p; p = p->next;
			tmp->next = NULL;
			
			//插入B[Di]号桶尾 
			if (B[Di].head == NULL)
				B[Di].head = B[Di].tail = tmp;
			else {
				B[Di].tail->next = tmp;
				B[Di].tail = tmp;
			}
		}
		
		//开始收集(将所有桶中的元素整理至表上)
		List = NULL;
		for ( Di=Radix-1; Di>=0; Di-- ){ //将每个桶的元素收集入List 
			if (B[Di].head) { //若桶不为空
				//整桶插入List表头
				B[Di].tail->next = List;
				List = B[Di].head;
				B[Di].head = B[Di].tail = NULL; //清空
			}
		}
	}
	//排序完成 
	//将List倒入A[]并释放空间
	for ( i=0; i<N; i++ ) {
		tmp = List;
		List = List->next;
		A[i] = tmp->key;
		free(tmp);
	} 
}


void MSD( int A[], int L, int R, int D )
{ //核心递归函数: 对A[L],...,A[R]的第D位数进行排序
	int Di, i, j; 
	Bucket B;
	PtrToNode tmp, p, List = NULL;
	if ( D=0 ) return; //递归出口
	for ( i=0; i<Radix; i++ )
		B[i].head = B[i].tail = NULL;
	for ( i=L; i<=R; i++ ) { //逆序存入
		tmp = (PtrToNode)malloc(sizeof(struct Node));
		tmp->key = A[i];
		tmp->next = List;
		List = tmp;
	}
	p = List;
	while (p) {
		Di = GetDigit(p->key, D);
		tmp = p; p = p->next;
		if (B[Di].head==NULL) B[Di].tail = tmp;
		tmp->next = B[Di].head;
		B[Di].head = tmp;
	}
	i = j = L; /* i, j记录当前要处理的A[]的左右端下标 */
	for (Di=0; Di<Radix; Di++) { /* 对于每个桶 */
		if (B[Di].head) { /* 将非空的桶整桶倒入A[], 递归排序 */
			p = B[Di].head;
			while (p) {
			    tmp = p;
			    p = p->next;
			    A[j++] = tmp->key;
			    free(tmp);
			}
			/* 递归对该桶数据排序, 位数减1 */
			MSD(A, i, j-1, D-1);
			i = j;  /* 为下一个桶对应的A[]左端 */
		} 
	} 
}

void MSDRadixSort( int A[], int N )
{ 
    MSD(A, 0, N-1, MaxDigit); 
}
