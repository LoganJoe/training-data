#include<bits/stdc++.h>
#define N 500005
#define ll long long
int n,m,A[N],head[N],ecnt,val[N],in[N],out[N],deep[N],fa[N][20],sta[N],tim;
struct edge
{
	int v,next;
}e[N<<1];
void add(int u,int v)
{
	e[++ecnt]=(edge){v,head[u]};head[u]=ecnt;
}
void dfs(int u,int fath)
{
	in[u]=++tim;deep[u]=deep[fath]+1,fa[u][0]=fath;
	for(int i=head[u];i;i=e[i].next)
		if(e[i].v!=fath) dfs(e[i].v,u);
	out[u]=tim;
}
void process()
{
	for(int j=1;j<20;j++)
		for(int i=1;i<=n;i++) fa[i][j]=fa[fa[i][j-1]][j-1];
}
int lca(int u,int v)
{
	if(deep[u]<deep[v]) std::swap(u,v);
	for(int i=19;~i;i--) if(deep[fa[u][i]]>=deep[v]) u=fa[u][i];
	if(u==v) return u;
	for(int i=19;~i;i--) if(fa[u][i]!=fa[v][i]) u=fa[u][i],v=fa[v][i];
}
bool inson(int p,int x)
{
	return in[p]<=in[x] && in[x]<=out[p];
}
ll ans=0;
ll sum(int x) {return 1ll*x*(x+1)/2;}
int main()
{
	freopen("qt.in","r",stdin);
	freopen("qt.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1,u,v;i<n;i++) scanf("%d%d",&u,&v),add(u,v),add(v,u);
	for(int i=1;i<=n;i++) val[i]=20;
	for(int i=0;i<20;i++) scanf("%d",&A[i]),val[A[i]]=i;
	dfs(1,0),process();
	while(m--)
	{
		int opt,a,b,c,k;
		scanf("%d%d%d",&opt,&a,&b);
		if(opt==0)
		{
			A[val[a]]=b,A[val[b]]=a;
			std::swap(val[a],val[b]);
		}
		else
		{
			scanf("%d",&k);c=lca(a,b);
			int dist=deep[a]+deep[b]-2*deep[c],mark=0;
			int l=dist,r=0,top=0;
			ans=0;
			for(int i=0;i<20;i++) 
			{
				int p=A[i],pos=-1;
				if(inson(c,p)) 
				{
					if(inson(p,a)) pos=deep[a]-deep[p];
					if(inson(p,b)) pos=deep[a]+deep[p]-2*deep[c];
				}
				if(pos==-1) (k&(1<<i))?mark=1:0;
				else
					if(k&(1<<i)) l=std::min(l,pos),r=std::max(r,pos);
					else sta[++top]=pos;
			}
			std::sort(sta+1,sta+1+top);sta[0]=-1,sta[++top]=dist+1;
			if(mark) {puts("0");continue;}
			if(!k) for(int i=1;i<=top;i++) ans+=sum(sta[i]+sta[i-1]-1);
			else 
				for(int i=1;i<=top;i++) 
					if(sta[i-1]<l && r<sta[i]) ans+=1ll*(l-sta[i-1])*(sta[i]-r);
			printf("%lld\n",ans);
		}
		
	}	
}
