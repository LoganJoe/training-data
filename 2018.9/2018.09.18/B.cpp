#include<bits/stdc++.h>
#define N 1000005
int n,m,A[N],head[N],ecnt,fath[N];
struct edge
{
	int v,next;
}e[N<<1];
void add(int u,int v)
{
	e[++ecnt]={v,head[u]};head[u]=ecnt;
}
int ansl[N],ansr[N],ans;
int check(int x,int c)
{
	int res=0;
	for(int i=head[x];i;i=e[i].next)
	{
		int v=e[i].v;if(v==fath[x]) continue;
		if(ansl[v]<=c && c<=ansr[v]) continue;
		res+=std::min(abs(c-ansl[v]),abs(c-ansr[v]));
	}
	return res;
}
void dfs(int u,int fa)
{
	fath[u]=fa;
	for(int i=head[u];i;i=e[i].next) if(e[i].v!=fa && e[i].v>m) dfs(e[i].v,u);
	int l=0,r=500000;
	while(r-l>3)
	{
		int midl=(l+r)>>1,midr=(midl+r)>>1;
		if(check(u,midl)<=check(u,midr)) r=midr;
		else l=midl;
	}
	while(check(u,l+1)<check(u,l)) l++; 
	int L=l,R=500000;
	while(L<R)
	{
		int mid=(L+R+1)>>1;
		if(check(u,mid)>check(u,L)) R=mid-1;
		else L=mid;
	}
	ansl[u]=l,ansr[u]=L;
	ans+=check(u,l);
}
int main()
{
	freopen("B.in","r",stdin);
	freopen("B.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1,u,v;i<n;i++) scanf("%d%d",&u,&v),add(u,v),add(v,u);
	for(int i=1;i<=m;i++) scanf("%d",&A[i]),ansl[i]=ansr[i]=A[i];
	dfs(m+1,0);
	//for(int i=1;i<=n;i++) printf("%d %d\n",ansl[i],ansr[i]);
	printf("%d\n",ans);
}
