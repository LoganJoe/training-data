#include<bits/stdc++.h>
#define N 100005
int n,fa[N],Size[N],head[N],ecnt=1,ans=-1;
struct edge
{
	int v,next;
}e[N<<1];
void add(int u,int v)
{
	e[++ecnt]=(edge){v,head[u]};head[u]=ecnt;
}
void dfs(int u,int fa)
{
	Size[u]=1;
	for(int i=head[u];i;i=e[i].next)
	{
		int v=e[i].v;if(v==fa) continue;
		dfs(v,u),Size[u]+=Size[v];
	}
	for(int i=head[u];i;i=e[i].next)
		if(Size[e[i].v]==n/2) ans=i>>1;
}
int main()
{
	freopen("div.in","r",stdin);
	freopen("div.out","w",stdout);
	scanf("%d",&n);
	for(int i=1,u,v;i<n;i++) scanf("%d%d",&u,&v),add(u,v),add(v,u);
	if(n&1) return puts("-1"),0;
	dfs(1,0);
	printf("%d\n",ans);
}
	
