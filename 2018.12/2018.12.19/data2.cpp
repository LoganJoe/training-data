#include<bits/stdc++.h>
#define ll long long
#define mod 998244353
ll n,f[50],A[50];
ll gcd(ll a,ll b){return !b?a:gcd(b,a%b);}
int main()
{
	scanf("%d",&n);
	f[1]=1,f[2]=2;
	for(int i=3;i<=40;i++) f[i]=1ll*f[i-1]*2+1ll*f[i-2]*3;
	for(int i=1;i<=n;i++) scanf("%d",&A[i]);
	ll lcm=1;
	for(int i=1;i<=n;i++)
	{
		lcm=1ll*f[A[i]]*lcm/gcd(lcm,f[A[i]]);
	}
	std::cout<<lcm%mod<<"\n"; 
 } 
