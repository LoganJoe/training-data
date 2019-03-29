#include<bits/stdc++.h>
#define N 10000005
#define ll long long
#define mod 1000000007
int n,fac[N],inv[N],Log[N];
ll Pow(ll x,ll k)
{
	ll t=1;
	for(;k;k>>=1,x=x*x%mod) if(k&1) t=t*x%mod;
	return t;
}
ll C(int a,int b)
{
	//return 1ll*fac[a]*inv[b]%mod*inv[a-b]%mod;
	return 1ll*fac[a]*Pow(fac[b],mod-2)%mod*Pow(fac[a-b],mod-2)%mod;
}
int main()
{
	freopen("str.in","r",stdin);
	freopen("str.out","w",stdout);
	scanf("%d",&n);
	fac[0]=inv[0]=inv[1]=1;Log[1]=0;
	for(int i=1;i<=n;i++) fac[i]=1ll*fac[i-1]*i%mod;
	for(int i=2;i<=n;i++) Log[i]=Log[i>>1]+1;
//	for(int i=2;i<=n;i++) inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
//	for(int i=2;i<=n;i++) inv[i]=1ll*inv[i-1]*inv[i]%mod
	int re=Pow(2,Log[n]);
	printf("%d\n",1ll*fac[n]*C(re,n-re)%mod);
}
