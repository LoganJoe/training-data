#include<bits/stdc++.h>
#define N 205
int n,st,L,s[N][N],mark[N][N],tot,t,ans[N*N],res;
struct node
{
	int x,y;
};
std::queue<node>q[2];
int dx[]={1,-1,0,0,1,-1},dy[]={0,0,1,-1,1,-1};
int main()
{
	freopen("hexagon.in","r",stdin);
	freopen("hexagon.out","w",stdout);
	scanf("%d%d%d",&n,&st,&L);
	for(int i=1;i<=n;i++) 
		for(int j=1;j<=i+n-1;j++)
		{
			s[i][j]=++tot,mark[i][j]=1;
			if(tot==st) q[0].push({i,j}); 
		}
	  for (int i=n+1;i<=n*2-1;i++)
        for (int j=i-n+1;j<=n*2-1;j++)
        {
        	s[i][j]=++tot,mark[i][j]=1;
        	if(tot==st) q[0].push({i,j}); 
		}
	for(int i=1;i<=L;i++,t^=1)
		while(!q[t].empty())
		{
			node u=q[t].front();q[t].pop();
			for(int k=0;k<6;k++)
			{
				node v={u.x+dx[k],u.y+dy[k]};
				if(mark[v.x][v.y]==1) q[t^1].push(v),mark[v.x][v.y]=0;
			}
		}
	while(!q[t].empty())
	{
		node p=q[t].front();q[t].pop();
		if(s[p.x][p.y]!=st) ans[++res]=s[p.x][p.y];
	}
	std::sort(ans+1,ans+1+res);
	printf("%d\n",res);
	for(int i=1;i<=res;i++) printf("%d\n",ans[i]);
	return 0;
}
