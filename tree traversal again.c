#include <stdio.h>
#include <stdlib.h>

int pre[] = {1,2,3,4,5,6};
int in[] = {3,2,4,1,6,5};
int post[6] = {0}; 

void solve (int preL, int inL, int postL, int n)
{
	if (n==0) return ;
	if (n==1) {post[postL]=pre[preL];return;}
	int i, root, L, R;
	root = pre[preL];
	post[postL+n-1] = root; 
	for ( i=0; in[inL+i]!=root; i++);
	L = i;
	R = n-L-1;
	solve(preL+1, inL, postL, L);
	solve(preL+L+1, inL+L+1, postL+L, R);
}

int main()
{
	solve (0, 0, 0, 6);
	return 0;
}
