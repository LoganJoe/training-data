#include<bits/stdc++.h>
#define N 505
#define mod 998244353 
int n,v[N],p[N],f[N][N],g[N][N],fac[N],inv[N],ans;
int mul(int x){return x>=mod?x-mod:x;}
int A[N],cnt[N];
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
	freopen("super.in","r",stdin);
	freopen("super.out","w",stdout); 
	scanf("%d",&n);
	fac[0]=inv[0]=inv[1]=1;
	for(int i=1;i<=n;i++) fac[i]=1ll*fac[i-1]*i%mod;
	for(int i=2;i<=n;i++) inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
	for(int i=2;i<=n;i++) inv[i]=1ll*inv[i-1]*inv[i]%mod;
	for(int i=1;i<=n;i++) scanf("%d",&v[i]);
	for(int i=1;i<=n;i++) scanf("%d",&p[i]);
	if(n<=8)
	{
		dfs(1);
		std::cout<<ans<<"\n";
		return 0;
	}
	for(int i=0;i<=n;i++) g[i][0]=1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=i;j++)
		{
			f[i][j]=mul(mul(f[i-1][j]+1ll*f[i-1][j-1]*p[i]%mod)+1ll*g[i-1][j-1]*v[i]%mod*p[i]%mod);
			g[i][j]=mul(g[i-1][j]+1ll*g[i-1][j-1]*p[i]%mod);
		}
	for(int i=1;i<=n;i++)
	{
		int res=0;
		for(int j=1;j<=n;j++)
			res=mul(res+mul(1ll*f[n][i]*p[j]%mod+1ll*g[n][i]*v[j]%mod*p[j]%mod));
		res=mul(res+mod-1ll*(n-i+1)*f[n][i+1]%mod);
		ans=mul(ans+1ll*res*fac[n]%mod*inv[n-i+1]%mod);
		//printf("%d\n",1ll*res*fac[n]%mod*inv[n-i+1]%mod*625ll%mod);
	}
	printf("%d\n",64ll*ans%mod);
}
/*
2
1 2
332748118 665496236
*/
