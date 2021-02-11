#include <stdio.h>
#include <stdlib.h>
#include "Queue.c" 
#define MaxVertexNum 100
#define INFINITY 65535
#define MaxSize 100 
#define ERROR -1

typedef int Vertex;
typedef int WeightType;
typedef char DataType;

typedef struct ENode *PtrToENode;
struct ENode{
	Vertex V1, V2;
	WeightType Weight;
};
typedef PtrToENode Edge;

typedef struct MGNode *PtrToMGNode;
struct MGNode{
	int Nv;
	int Ne;
	WeightType G[MaxVertexNum][MaxVertexNum];
	DataType Data[MaxVertexNum];
};
typedef PtrToMGNode MGraph;

typedef struct AdjVNode *PtrToAdjVNode; 
struct AdjVNode{
	Vertex AdjV;
	WeightType Weight;
	PtrToAdjVNode Next;
};

typedef struct VNode{
	PtrToAdjVNode FirstEdge;
	DataType Data;
} AdjList[MaxVertexNum];

typedef struct LGNode *PtrToLGNode;
struct LGNode{
	int Nv;
	int Ne;
	AdjList G; 
};
typedef PtrToLGNode LGraph;
 
MGraph CreateMGraph( int VertexNum )
{
	Vertex V, W;
	MGraph Graph;
	
	Graph = (MGraph)malloc(sizeof(struct MGNode));
	Graph->Nv = VertexNum;
	Graph->Ne = 0;
	for (V=0; V<Graph->Nv; V++)
		for (W=0; W<Graph->Nv; W++)
			Graph->G[V][W] = INFINITY;
	return Graph;
}

void InsertEdgeM( MGraph Graph, Edge E )
{
	Graph->G[E->V1][E->V2]=E->Weight;
	Graph->G[E->V2][E->V1]=E->Weight;
}

MGraph BuildMGraph()
{                                           
	MGraph Graph;
	Edge E;
	Vertex V;
	int Nv, i;
	
	scanf("%d", &Nv);
	Graph = CreateMGraph(Nv);
	
	scanf("%d", &(Graph->Ne));
	if ( Graph->Ne != 0 ) {
		E = (Edge)malloc(sizeof(struct ENode));
		for (i=0; i<Graph->Ne; i++) {
			scanf("%d %d %d", &E->V1, &E->V2, &E->Weight);
			InsertEdgeM( Graph, E );
		}
	}
	
	for (V=0; V<Graph->Nv; V++)
		scanf(" %c", &(Graph->Data[V]));
		
	return Graph;
}

int IsEdge( MGraph Graph, Vertex V, Vertex W )
{
	return Graph->G[V][W]<INFINITY?1:0;
}

LGraph CreateLGraph( int VertexNum )
{
	Vertex V;
	LGraph Graph;
	
	Graph = (LGraph)malloc(sizeof(struct LGNode));
	Graph->Nv = VertexNum;
	Graph->Ne = 0;
	for (V=0; V<Graph->Nv; V++)
		Graph->G[V].FirstEdge = NULL;
	return Graph;
}

void InsertEdgeL( LGraph Graph, Edge E )
{
	PtrToAdjVNode NewNode;
	NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
	NewNode->AdjV = E->V2;
	NewNode->Weight = E->Weight;
	NewNode->Next = Graph->G[E->V1].FirstEdge;
	Graph->G[E->V1].FirstEdge = NewNode;
 }

LGraph BuildLGraph()
{
	LGraph Graph;
	Edge E;
	Vertex V;
	int Nv, i;
	
	scanf("%d", &Nv);
	Graph = CreateLGraph(Nv);
	
	scanf("%d", &(Graph->Ne));
	if ( Graph->Ne != 0 )
	{
		E = (Edge)malloc(sizeof(struct ENode));
		for (i=0; i<Graph->Ne; i++) {
			scanf("%d %d %d", &E->V1, &E->V2, &E->Weight);
			InsertEdgeL( Graph, E );
		}
	}
	return Graph;
}


void Visit( Vertex V )
{
	printf("%d\n", V );
}

int Visited[MaxVertexNum] = {0};
void DFS( LGraph Graph, Vertex V, void (*Visit)(Vertex) )
{
	PtrToAdjVNode W;
	
	Visit( V );
	Visited[V] = 1;
	
	for ( W=Graph->G[V].FirstEdge; W; W=W->Next )
		if ( !Visited[W->AdjV] )
			DFS( Graph, W->AdjV, Visit );
	
	return ;
}

void BFS( MGraph Graph, Vertex S, void(*Visit)(Vertex))
{
	Queue Q;
	Vertex V, W;
	
	Q = CreateQueue( MaxSize );
	
	Visit(S);
	Visited[S] = 1;
	AddQ(Q, S);
	while ( !IsEmpty(Q) ){
		V = DeleteQ(Q);
		for (W=0; W<Graph->Nv; W++){
			if ( !Visited[W] && IsEdge(Graph, V, W) ) {
				Visit(W);
				Visited[W] = 1;
				AddQ(Q, W);
			}
		}
	}
	return ;
}
