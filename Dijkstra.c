#include <stdio.h>
#include <stdlib.h>
#include "Graph.c" 
 

void Unwighted( LGraph Graph, int dist[], int path[], Vertex S )
{
	Queue Q;
	Vertex V;
	PtrToAdjVNode W;
	
	Q = CreateQueue(Graph->Nv);
	dist[S] = 0;
	AddQ(Q, S);
	
	while ( !IsEmpty(Q) ){
		V = DeleteQ(Q);
		for ( W=Graph->G[V].FirstEdge; W; W=W->Next){
			if (dist[W->AdjV]==-1){
				dist[W->AdjV]=dist[V]+1;
				path[W->AdjV]=V;
				AddQ(Q,W->AdjV);
			}
		}
	}	
}
 
Vertex FindMinDist( MGraph Graph, int dist[], int collected[] )
{ //找出所有已选结点相邻结点中的距离最小的结点
 	Vertex MinV, V;
	int MinDist = INFINITY;
	for (V=0; V<Graph->Nv; V++) {
		if (collected[V]==0 && dist[V]<MinDist) {
			MinDist = dist[V];
			MinV = V;
		}
	}
	if (MinDist<INFINITY)
		return MinV;
	else return ERROR;
}

int Dijkstra( MGraph Graph, int dist[], Vertex path[], Vertex S )
{
 	int collected[MaxVertexNum];
 	Vertex V, W;
 	
 	for ( V=0; V<Graph->Nv; V++ ) {
 		dist[V] = Graph->G[S][V];
 		if ( dist[V]<INFINITY )
 			path[V] = S;
 		else
 			path[V] = -1;
 		collected[V] = 0;
	}
	dist[S] = 0;
	collected[S] = 1;
	
	while (1) {
		V = FindMinDist(Graph, dist, collected);
		if ( V==ERROR ) break;
		collected[V] = 1;
		for ( W=0; W<Graph->Nv; W++ ){
			//在所有点中找到未收录的而且与V相连的
			if ( collected[W]==0 && Graph->G[V][W]<INFINITY )
				if ( Graph->G[V][W]<0 )
					return 0;
				
				//松弛过程
				if ( dist[V]+Graph->G[V][W]<dist[W] ){
					dist[W] = dist[V]+Graph->G[V][W];
					path[W] = V;
				}
		}	
	}
	return 1;
}
 
int main() {
 	return 0;
} 
