#include<bits/stdc++.h>
#define N 505
#define mod 998244353 
#define ll long long
int n,v[N],p[N],f[N][N],g[N][N],fac[N],inv[N],ans;
int mul(int x){return x>=mod?x-mod:x;}
ll Pow(ll x,ll k){
	ll t=1;
	for(;k;k>>=1,x=x*x%mod) if(k&1) t=t*x%mod;
	return t;
}
int main()
{
	printf("%d\n",961272344ll*Pow(27,mod-2)%mod);
	printf("%d\n",530317318ll*64%mod);
	printf("%d\n",77987845ll*64%mod);
}
