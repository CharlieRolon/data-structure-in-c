#include <stdio.h>
#include <stdlib.h>
#include "Graph.c"

int TopSort( LGraph Graph, Vertex TopOrder[] )
{//对Graph进行拓扑排序，TopOrder[]顺序存储排序后的顶点下标
	int Indegree[MaxVertexNum], cnt;
	Vertex V;
	PtrToAdjVNode W;
	Queue Q = CreateQueue( Graph->Nv );
	
	//初始化Indegree[]
	for ( V=0; V<Graph->Nv; V++ )
		Indegree[V] = 0;
		
	for ( V=0; V<Graph->Nv; V++ )
		for ( W=Graph->G[V].FirstEdge; W; W=W->Next )
			Indegree[W->AdjV]++;
	//入度为0的顶点入列
	for ( V=0; V<Graph->Nv; V++ )
		if ( Indegree[V]=0 )
			AddQ(Q, V);
	
	//开始拓扑排序	
	cnt = 0;
	while( !IsEmpty(Q)) {
		V = DeleteQ(Q);
		TopOrder[cnt++] = V;
		for ( W=Graph->G[V].FirstEdge; W; W=W->Next )
			if ( --Indegree[W->AdjV] == 0 )
				AddQ(Q, W->AdjV);
	}
	
	if (cnt!=Graph->Nv)
		return 0;
	else
		return 1;
 } 
