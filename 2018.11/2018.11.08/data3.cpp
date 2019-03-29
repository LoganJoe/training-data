#include<bits/stdc++.h>
int n=1000,Q=10;
int main()
{
	srand(time(0));
	freopen("c.in","w",stdout);
	printf("%d %d\n",n,Q);
	for(int i=1;i<n;i++) printf("%d ",rand()%2?1:5);puts("");
	for(int i=1;i<n;i++) printf("%d ",rand()%2?1:5);puts("");
	while(Q--)
	{
		printf("%d %d %d %d\n",rand()%n+1,rand()%n+1,rand()%n+1,rand()%n+1);
	}
	
}
