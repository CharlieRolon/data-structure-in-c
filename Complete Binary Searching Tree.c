#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int A[10] = {0,1,2,3,4,5,6,7,8,9};
int T[10] = {0}; 

int GetLeftLength(int n)
{
	int m = (int)(log(n+1)/log(2));
	int lower = (int)(pow(2,m));
	int x = n - lower + 1;
	x = x<(lower/2)?x:(lower/2);
	return (lower/2)-1+x;
}

void solve( int ALeft, int ARight, int TRoot )
{ 
	int n = ARight - ALeft + 1;
	if (n==0) return ;
	int L = GetLeftLength(n);
	T[TRoot] = A[ALeft + L];
	int LeftTRoot = TRoot * 2 + 1;
	int RightTRoot = LeftTRoot + 1;
	solve(ALeft, ALeft+L-1, LeftTRoot);
	solve(ALeft+L+1, ARight, RightTRoot);
}

int main()
{
	printf("%d\n",GetLeftLength(10));
	solve( 0, 9, 0 );
	int i, *p;
	for (i=0, p=T; i<10; i++, p++ ) printf("%d ", *p);
	return 0;
}
