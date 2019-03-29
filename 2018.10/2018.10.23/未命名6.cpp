#include<bits/stdc++.h>
#define N 505
#define mod 998244353 
int n,v[N],p[N],f[N][N],g[N][N],fac[N],inv[N],ans;
int mul(int x){return x>=mod?x-mod:x;}
int main()
{
	scanf("%d",&n);
	fac[0]=inv[0]=inv[1]=1;
	for(int i=1;i<=n;i++) fac[i]=1ll*fac[i-1]*i%mod;
	for(int i=2;i<=n;i++) inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
	for(int i=2;i<=n;i++) inv[i]=1ll*inv[i-1]*inv[i]%mod;
	for(int i=1;i<=n;i++) scanf("%d",&v[i]);
	for(int i=1;i<=n;i++) scanf("%d",&p[i]);
	for(int i=0;i<=n;i++) g[i][0]=1;
	for(int k=1;k<=n;k++)
	{
		for(int i=1;i<=n;i++)
			for(int j=1;j<=i;j++) f[i][j]=g[i][j]=0;
		std::swap(v[k],v[n]);
		std::swap(p[k],p[n]);	
		for(int i=1;i<n;i++)
			for(int j=1;j<=i;j++)
			{
				f[i][j]=mul(mul(f[i-1][j]+1ll*f[i-1][j-1]*p[i]%mod)+1ll*g[i-1][j-1]*v[i]%mod*p[i]%mod);
				g[i][j]=mul(g[i-1][j]+1ll*g[i-1][j-1]*p[i]%mod);
			}
		
		for(int j=1;j<=n;j++)
		{
			f[n][j]=mul(1ll*f[n-1][j-1]*p[n]%mod+1ll*g[n-1][j-1]*v[n]%mod*p[n]%mod);
			g[n][j]=1ll*g[n-1][j-1]*p[n]%mod;
		}
		int res=0;
		for(int i=n;i<=n;i++)
		{
			res=mul(mod-res+1ll*f[n][i]*p[n]%mod+1ll*g[n][i]*v[n]%mod*p[n]%mod);
			ans=mul(ans+1ll*res*fac[n]%mod*inv[n-i]%mod);
		}
		std::swap(v[k],v[n]);
		std::swap(p[k],p[n]);
	}
	printf("%d\n",ans%mod);
}
/*
2
1 2
332748118 665496236
*/
