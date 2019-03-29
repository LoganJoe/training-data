#include<bits/stdc++.h>
#define N 4005
#define M 100005
int n,m,ecnt,tot,head[N],op,ch[N],res[N];
int fa[N][15],deep[N],dis[N],s[N][N],Min[N];
struct node{int u,v,w;}A[M];
struct edge{int v,w,next;}e[N<<1];
void add(int u,int v,int w){e[++ecnt]=(edge){v,w,head[u]};head[u]=ecnt;}
void dfs(int u,int fath)
{
	deep[u]=deep[fath]+1,fa[u][0]=fath;
	for(int i=head[u];i;i=e[i].next)
		if(e[i].v!=fath) dis[e[i].v]=dis[u]+e[i].w,dfs(e[i].v,u);
}
void process()
{
	dfs(1,0);
	for(int j=1;j<15;j++)
		for(int i=1;i<=n;i++) fa[i][j]=fa[fa[i][j-1]][j-1];	
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++) s[i][j]=1e9;
	for(int i=1;i<=n;i++) Min[i]=res[i]=1e9;
}
int lca(int u,int v)
{
	if(deep[u]<deep[v]) std::swap(u,v);
	for(int i=14;~i;i--)
		if(deep[fa[u][i]]>=deep[v]) u=fa[u][i];
	if(u==v) return u;
	for(int i=14;~i;i--) 
		if(fa[u][i]!=fa[v][i]) u=fa[u][i],v=fa[v][i];
	return fa[u][0];
}
int main()
{
	freopen("shortest.in","r",stdin);
	freopen("shortest.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		tot++;scanf("%d%d%d%d",&A[tot].u,&A[tot].v,&A[tot].w,&op);
		if(op==1) add(A[tot].u,A[tot].v,A[tot].w),add(A[tot].v,A[tot].u,A[tot].w),tot--;
	}
	process();
	for(int i=1;i<=tot;i++)
	{
		int a=A[i].u,b=A[i].v,c=lca(a,b),D=dis[a]+dis[b]+A[i].w;
		s[a][deep[c]+1]=std::min(D,s[a][deep[c]+1]);
		s[b][deep[c]+1]=std::min(D,s[b][deep[c]+1]);
		Min[a]=std::min(Min[a],deep[c]+1);
		Min[b]=std::min(Min[b],deep[c]+1);
	}
	for(int i=2,x;i<=n;i++) if(Min[i]<=deep[i])
	{
		for(x=i;deep[x]>Min[i];x=fa[x][0]) ch[fa[x][0]]=x;
		for(int d=Min[i],val=1e9;;x=ch[x],d++)
		{
			val=std::min(val,s[i][d]);
			res[x]=std::min(res[x],val);
			if(i==x) break;
		}
	}
	for(int i=2;i<=n;i++)
		if(res[i]>=1e9) printf("%d ",-1);
		else printf("%d ",res[i]-dis[i]);
	puts("");
	
}
/*
5 9
3 1 3 1
1 4 2 1
2 1 6 0
2 3 4 0
5 2 3 0
3 2 2 1
5 3 1 1
3 5 2 0
4 5 4 0
*/
