#include<bits/stdc++.h>
#define N 505
#define mod 998244353 
int n,v[N],p[N],f[N][N],g[N][N],fac[N],inv[N],ans,A[N],cnt[N];
int mul(int x){return x>=mod?x-mod:x;}
void cal(int x)
{
	int pp=1,tot=0;
	for(int i=1;i<x;i++) pp=1ll*pp*p[A[i]]%mod,tot=mul(tot+v[A[i]]);
	ans=mul(ans+1ll*pp*tot%mod);
}
void dfs(int x)
{
	if(cnt[A[x-1]]>1) return cal(x);
	for(int i=1;i<=n;i++) cnt[i]++,A[x]=i,dfs(x+1),cnt[i]--;
}
int main()
{	
	scanf("%d",&n);
	fac[0]=inv[0]=inv[1]=1;
	for(int i=1;i<=n;i++) fac[i]=1ll*fac[i-1]*i%mod;
	for(int i=2;i<=n;i++) inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
	for(int i=2;i<=n;i++) inv[i]=1ll*inv[i-1]*inv[i]%mod;
	for(int i=1;i<=n;i++) scanf("%d",&v[i]);
	for(int i=1;i<=n;i++) scanf("%d",&p[i]);
	dfs(1);
	printf("%d\n",ans);
}
/*
3
2 3 1
748683265 748683265 499122177
*/
