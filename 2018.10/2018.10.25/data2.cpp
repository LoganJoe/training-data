#include<bits/stdc++.h>
int main()
{
	freopen("maze.in","w",stdout);
	srand(time(0));
	int N=20,M=20,K=rand()%16;
	printf("%d %d %d\n",N,M,K);
	for(int i=1;i<=N;i++,puts(""))
		for(int j=1;j<=M;j++) 
		{
			if(i==1 && j==1 || i==N && j==M) printf("%d ",rand()%15+1);
			else printf("%d ",rand()%16);
		}
	
}
