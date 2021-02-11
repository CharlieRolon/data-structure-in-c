#include "Disjoint Set Union.c"
#include "Graph.c"
typedef Vertex ElementType;
typedef Vertex SetName;

void InitializeVSet( SetType S, int N )
{
	ElementType X;
	
	for ( X=0; X<N; X++ ) S[X] = -1;
 } 
 
int CheckCycle( SetType VSet, Vertex V1, Vertex V2 )
{
	Vertex Root1, Root2;
	
	Root1 = Find( VSet, V1 );
	Root2 = Find( VSet, V2 );
	
	if ( Root1==Root2 ) return 0;
	else {
		Union ( VSet, Root1, Root2 );
		return 1;
	}
}


void PercDown( Edge ESet, int p, int N )
{
	//��N��Ԫ�صı�������ESet[p]Ϊ�����Ӷѵ���Ϊ����Weight����С�� 
	int Parent, Child;
	struct ENode X;
	
	X = ESet[p];
	for( Parent=p; (Parent*2+1)<N; Parent=Child ){
		Child = Parent*2 + 1;
		if( (Child!=N-1) && (ESet[Child].Weight)>ESet[Child+1].Weight )
			Child++;
		if( X.Weight <= ESet[Child].Weight ) break;
		
		else ESet[Parent] = ESet[Child];		
	} 
	ESet[Parent] = X;
}

void InitializeESet( LGraph Graph, Edge ESet )
{
	Vertex V;
	PtrToAdjVNode W;
	int ECount;
	
	ECount = 0;

    //�������б�
	for ( V=0; V<Graph->Nv; V++ )
		for ( W=Graph->G[V].FirstEdge; W; W=W->Next )
			if ( V<W->AdjV ){ //�����ظ�¼�� ����ͼ �ı�,ֻ��¼V1<V2�ı� 
				ESet[ECount].V1 = V;
				ESet[ECount].V2 = W->AdjV;
				ESet[ECount++].Weight = W->Weight; 
			}

    //����Ϊ��С��
	for ( ECount=Graph->Ne/2-1; ECount>=0; ECount-- )
		PercDown( ESet, ECount, Graph->Ne );
}

int GetEdge( Edge ESet, int CurrentSize )
{ //������ǰ�ѵĴ�С,����ǰ��С�ߵ�λ�õ�����������
	//����С�ߵ�λ���뵱ǰ�ѵ����һ��λ�ý��� 
	struct ENode* temp;
	temp = (struct ENode*)malloc(sizeof(struct ENode));
	*temp = ESet[0];
	ESet[0] = ESet[CurrentSize-1];
	ESet[CurrentSize-1] = *temp;
	free(temp);
	//��ʣ�µı߼�������Ϊ��С�� 
	PercDown( ESet, 0, CurrentSize-1 ); //���ɾ������ 
	
	return CurrentSize-1; //��С�߽���������λ�� 
}
/*-------------��С�Ѷ������--------------*/ 

int Kruskal( LGraph Graph, LGraph MST )
{ //����С����������Ϊ�ڽӱ��洢��ͼMST,������СȨ�غ�
	WeightType TotalWeight;
	int ECount, NextEdge;
	SetType VSet;  //��������
	Edge ESet; //������
	
	InitializeVSet( VSet, Graph->Nv );
    ESet = (Edge)malloc(sizeof(struct ENode)*Graph->Ne);
	InitializeESet( Graph, ESet );
	MST = CreateLGraph(Graph->Nv);
	TotalWeight = 0;
	ECount = 0;
	
	NextEdge = Graph->Ne; //ԭʼ�߼��ϵĹ�ģ 
	while ( ECount < Graph->Nv-1 ) {
		NextEdge = GetEdge( ESet, NextEdge );
		if (NextEdge<0) break; //�߼���Ϊ�� 
		//�������ɻ�· 
		if ( CheckCycle( VSet, ESet[NextEdge].V1, ESet[NextEdge].V2)){
			InsertEdgeL( MST, ESet+NextEdge ); //����NextEdgeλ�õı� 
			TotalWeight += ESet[NextEdge].Weight;
			ECount++;
		}
	}
	/*���ɹ��̽���*/
	if ( ECount < Graph->Nv-1 )
		TotalWeight = -1;
	
	return TotalWeight;
 } 

int main(){
	LGraph Graph = BuildLGraph();
	LGraph MST;
	int ans = Kruskal(Graph, MST);
	printf("\nTotalWeight = %d", ans);
    system("pause");
}
