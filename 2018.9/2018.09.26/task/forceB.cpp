#include<bits/stdc++.h>
#define N 205
int n,m,E[N][N],mark[N][N],dis[N][N];
struct edge
{
	int v,w,next;
}e[N*N];
int main()
{
	////freopen("journey.in","r",stdin);
	//freopen("journey.ans","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++) scanf("%d",&E[i][j]);
	for(int i=1;i<=n;i++) E[i][i]=1e9;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++) dis[i][j]=E[i][j];
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++) dis[i][j]=std::min(dis[i][j],dis[i][k]+dis[k][j]);
	while(m--)
	{
		int op,x,y;
		scanf("%d%d%d",&op,&x,&y);
		if(op==1)
		{
			E[x][y]=1e9;
			for(int i=1;i<=n;i++)
				for(int j=1;j<=n;j++) dis[i][j]=E[i][j];
			for(int k=1;k<=n;k++)
				for(int i=1;i<=n;i++)
					for(int j=1;j<=n;j++) dis[i][j]=std::min(dis[i][j],dis[i][k]+dis[k][j]);
		}
		else
		{
			printf("%d\n",dis[x][y]==1e9?-1:dis[x][y]);
		}
	}
}
