#include<bits/stdc++.h>
#define N 1000005
#define mod 998244353
int Case,n,head[N],ecnt,k,A[N],mark[N],f[N],dis[N],ans,total,fac[N];
struct edge{int v,w,next;}e[N<<1];
void add(int u,int v,int w){e[++ecnt]={v,w,head[u]};head[u]=ecnt;}
int mul(int x){return x>=mod?x-mod:x;}
int Pow(int x,int k){int t=1;for(;k;k>>=1,x=1ll*x*x%mod) if(k&1) t=1ll*t*x%mod;return t;}
void dfs(int u,int fa)
{
	f[u]=mark[u];
	for(int i=head[u];i;i=e[i].next)
	{
		int v=e[i].v;if(v==fa) continue;
		dis[v]=mul(dis[u]+e[i].w),dfs(v,u);
		ans=mul(ans+1ll*f[u]*f[v]%mod*dis[u]%mod);
		f[u]+=f[v];
	}
}
int main()
{
	freopen("path.in","r",stdin);
	freopen("path.out","w",stdout);
	fac[0]=1;
	for(int i=1;i<N;i++) fac[i]=1ll*fac[i-1]*i%mod;
	scanf("%d",&Case);
	scanf("%d",&n);
	for(int i=1,u,v,w;i<n;i++) scanf("%d%d%d",&u,&v,&w),add(u,v,w),add(v,u,w);
	scanf("%d",&k);
	for(int i=1;i<=k;i++) scanf("%d",&A[i]),mark[A[i]]=1;
	dfs(1,0);ans=1ll*4*ans*fac[k-1]%mod;
	for(int i=1;i<=k;i++) 
		total=mul(total+1ll*dis[A[i]]*2ll*(k-1)%mod*fac[k-1]%mod);
	printf("%d\n",1ll*mul(total-ans+mod)*Pow(fac[k],mod-2)%mod);
}
/*
2
6
1 2 3
1 3 4
2 4 5
4 5 2
4 6 3
4 1 2 5 6 
*/
