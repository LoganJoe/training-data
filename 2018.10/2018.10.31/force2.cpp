#include<bits/stdc++.h>
#define N 1000005
#define mod 998244353
int Case,n,head[N],ecnt,k,A[N],mark[N],f[N],ans,fac[N];
int fa[N][20],val[N][20],deep[N];
struct edge{int v,w,next;}e[N<<1];
void add(int u,int v,int w){e[++ecnt]={v,w,head[u]};head[u]=ecnt;}
int mul(int x){return x>=mod?x-mod:x;}
int Pow(int x,int k){int t=1;for(;k;k>>=1,x=1ll*x*x%mod) if(k&1) t=1ll*t*x%mod;return t;}
void dfs(int u,int fath)
{
	fa[u][0]=fath;deep[u]=deep[fath]+1;
	for(int i=head[u];i;i=e[i].next)
	{
		int v=e[i].v;
		if(v==fath) continue;
		val[v][0]=e[i].w;
		dfs(v,u);
	}
}
void process()
{
	for(int j=1;j<20;j++)
		for(int i=1;i<=n;i++) 
		fa[i][j]=fa[fa[i][j-1]][j-1],val[i][j]=mul(val[i][j-1]+val[fa[i][j-1]][j-1]);
}
int askdist(int u,int v)
{
	int res=0;
	if(deep[u]<deep[v]) std::swap(u,v);
	for(int i=19;~i;i--) if(deep[fa[u][i]]>=deep[v]) res=mul(res+val[u][i]),u=fa[u][i];
	if(u==v) return res;
	for(int i=19;~i;i--)
		if(fa[u][i]!=fa[v][i]) res=(res+val[u][i]+val[v][i])%mod,u=fa[u][i],v=fa[v][i];
	res=mul(res+val[u][0]+val[v][0]);
	return res;
}
int main()
{
	freopen("path.in","r",stdin);
	freopen("path.ans","w",stdout);
	fac[0]=1;
	for(int i=1;i<N;i++) fac[i]=1ll*fac[i-1]*i%mod;
	scanf("%d",&Case);
	scanf("%d",&n);
	for(int i=1,u,v,w;i<n;i++) scanf("%d%d%d",&u,&v,&w),add(u,v,w),add(v,u,w);
	scanf("%d",&k);
	for(int i=1;i<=k;i++) scanf("%d",&A[i]),mark[A[i]]=1;
	dfs(1,0);
	process();
	for(int i=1;i<=k;i++) f[i]=i;
	do
	{
		int res=0;
		for(int i=1;i<k;i++) res=mul(res+askdist(A[f[i]],A[f[i+1]]));
		//for(int i=1;i<k;i++) printf("%d ",askdist(A[f[i]],A[f[i+1]]));
		//for(int i=1;i<=k;i++) printf("%d ",A[f[i]]);
		//printf("%d\n",res);
		ans=mul(ans+res);
	}while(std::next_permutation(f+1,f+1+k));
	printf("%d\n",1ll*ans*Pow(fac[k],mod-2)%mod);
}
