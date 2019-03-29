#include<bits/stdc++.h>
#define N 505
int n,m,K,L,head[N],ecnt,deft[N][N],f[N],dis[N],vis[N],prid[N];
struct edge
{
	int v,w,next;
}e[N*N];
void add(int u,int v,int w)
{
	e[++ecnt]=(edge){v,w,head[u]};head[u]=ecnt;
}
void spfa()
{
	for(int i=1;i<=n;i++) dis[i]=prid[i]=f[i]=1e9,vis[i]=0;
	dis[1]=0,vis[1]=1;std::queue<int>q;q.push(1);
	while(!q.empty())
	{
		int u=q.front();q.pop();vis[u]=0;
		for(int i=head[u];i;i=e[i].next)
		{
			int v=e[i].v;
			if(dis[v]>dis[u]+1)
			{
				dis[v]=dis[u]+1;
				if(!vis[v]) vis[v]=1,q.push(v);
			}
		}
	}
}
struct node
{
	int fa,x,dis,maxw;
	friend bool operator< (node t1,node t2)
	{
		return t1.dis>t2.dis;
	}
};
std::priority_queue<node>q;
void bfs()
{
	q.push((node){0,1,0,0});
	while(!q.empty())
	{
		node u=q.top();q.pop();
		//printf("%d %d %d %d\n",u.fa,u.x,u.dis,u.maxw);
		if(u.dis>dis[u.x]+L || u.dis>n) continue;
		if(u.maxw>=f[u.x] && u.dis>=prid[u.x]) continue;
		if(f[u.x]>u.maxw && u.dis<prid[u.x]) f[u.x]=u.maxw,prid[u.x]=u.dis;
		f[u.x]=std::min(f[u.x],u.maxw);
		for(int i=head[u.x];i;i=e[i].next)
		{
			if(deft[u.fa][u.x]==e[i].v) continue;
			q.push({u.x,e[i].v,u.dis+1,std::max(e[i].w,u.maxw)});
 		}
	}
}
int main()
{
	freopen("return.in","r",stdin);
	freopen("return.out","w",stdout);
	scanf("%d%d%d%d",&n,&m,&K,&L);
	for(int i=1;i<=m;i++) 
	{
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		add(u,v,w),add(v,u,w);
	}
	for(int i=1;i<=K;i++)
	{
		int x,y,z;scanf("%d%d%d",&x,&y,&z);	
		deft[x][y]=z;
	}
	spfa();
	bfs();
	printf("%d\n",f[n]);
}
