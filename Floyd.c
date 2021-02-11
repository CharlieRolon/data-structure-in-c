#include <stdlib.h>
#include <stdio.h>
#include "Graph.c"

int Floyd( MGraph Graph, WeightType D[][MaxVertexNum], Vertex path[][MaxVertexNum] )
{
	Vertex i, j, k;
	
	for ( i=0; i<Graph->Nv; i++ )
		for ( j=0; j<Graph->Nv; j++ ) {
			D[i][j] = Graph->G[i][j]; //初始化距离图
			path[i][j] = -1;
		}
	
	for ( k=0; k<Graph->Nv; k++ )
		for ( i=0; i<Graph->Nv; i++ )
			for ( j=0; j<Graph->Nv; j++ )
				if ( D[i][k]+D[k][j] < D[i][j] ) { //松弛过程
					D[i][j] = D[i][k]+D[k][j];
					if ( i==j && D[i][j]<0 )
						return 0;
					path[i][j] = k;
				}
	
	return 1;
}
