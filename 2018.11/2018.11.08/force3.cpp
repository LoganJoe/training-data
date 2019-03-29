#include<bits/stdc++.h>
#define N 1005
int n,Q,A[N],B[N],dis[N][N][2],vis[N][N][2];
struct node
{
	int x,y,t;
};
void spfa(int sx,int sy)
{
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
				dis[i][j][0]=dis[i][j][1]=1e9;
	dis[sx][sy][0]=dis[sx][sy][1]=0;
	std::queue<node>q;q.push({sx,sy,0}),q.push({sx,sy,1});
	while(!q.empty())
	{
		node u=q.front();q.pop();vis[u.x][u.y][u.t]=0;
		node v;
		if(u.t!=0)
		{
			v={u.x+1,u.y,0};
			if(dis[v.x][v.y][v.t]>dis[u.x][u.y][u.t]+A[u.x+1])
			{
				if(v.x<1 || v.x>n || v.y<1 || v.y>n) continue;
				dis[v.x][v.y][v.t]=dis[u.x][u.y][u.t]+A[u.x+1];
				if(!vis[v.x][v.y][v.t]) vis[v.x][v.y][v.t]=1,q.push(v);
			}
			v={u.x-1,u.y,0};
			if(dis[v.x][v.y][v.t]>dis[u.x][u.y][u.t]+A[u.x])
			{
				if(v.x<1 || v.x>n || v.y<1 || v.y>n) continue;
				dis[v.x][v.y][v.t]=dis[u.x][u.y][u.t]+A[u.x];
				if(!vis[v.x][v.y][v.t]) vis[v.x][v.y][v.t]=1,q.push(v);
			}
		}
		else
		{
			v={u.x,u.y+1,1};
			if(dis[v.x][v.y][v.t]>dis[u.x][u.y][u.t]+B[u.y+1])
			{
				if(v.x<1 || v.x>n || v.y<1 || v.y>n) continue;
				dis[v.x][v.y][v.t]=dis[u.x][u.y][u.t]+B[u.y+1];
				if(!vis[v.x][v.y][v.t]) vis[v.x][v.y][v.t]=1,q.push(v);
			}
			v={u.x,u.y-1,1};
			if(dis[v.x][v.y][v.t]>dis[u.x][u.y][u.t]+B[u.y])
			{
				if(v.x<1 || v.x>n || v.y<1 || v.y>n) continue;
				dis[v.x][v.y][v.t]=dis[u.x][u.y][u.t]+B[u.y];
				if(!vis[v.x][v.y][v.t]) vis[v.x][v.y][v.t]=1,q.push(v);
			}
		}
	}
//	for(int i=1;i<=n;i++,puts(""))
//		for(int j=1;j<=n;j++)
//			printf("%d ",std::min(dis[i][j][0],dis[i][j][1]));	
}
int main()
{
	freopen("c.in","r",stdin);
	freopen("c.ans","w",stdout);
	scanf("%d%d",&n,&Q);
	for(int i=2;i<=n;i++) scanf("%d",&A[i]);
	for(int i=2;i<=n;i++) scanf("%d",&B[i]);
	while(Q--)
	{
		int sx,sy,tx,ty;
		scanf("%d%d%d%d",&sx,&sy,&tx,&ty);
		spfa(sx,sy);
		printf("%d\n",std::min(dis[tx][ty][0],dis[tx][ty][1]));
	}
}
