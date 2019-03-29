// HXH orz
#include<algorithm>
#include<iostream>
#include<cstring>
#include<climits>
#include<cstdlib>
#include<cstdio>
#include<queue>
#include<cmath>
#define MAXN 100010
using namespace std;
long long n,K,dp[1010][1010][10],g[1010][1010][10],ans,sum=1,rev[MAXN];
const long long Mod=998244353;
long long q_p(long long x,long long k)
{
	long long res=1;
	while(k)
	{
		if(k&1) res=(res*x)%Mod;
		x=(x*x)%Mod;
		k/=2;
	}
	return res;
}
int main()
{
	for(long long i=1;i<=200;i++) rev[i]=q_p(i,Mod-2);
	scanf("%lld%lld",&n,&K);sum=1;ans=0;dp[0][0][0]=1;
	for(long long i=n;i>n-K;i--) sum=(sum*i)%Mod;
	for(long long i=2;i<=K;i++) sum=(sum*rev[i])%Mod;
	for(long long k=1;k<K;k++)
	{
	    for(long long i=0;i<=n;i++)
	    {
	    	for(long long j=0;j<=n;j++) g[i][j][k-1]=(dp[i][j][k-1]+g[i][j-1][k-1])%Mod;;
	    	for(long long j=0;j<=n;j++) if(i+j<=n)dp[i+j][j][k]=(dp[i+j][j][k]+g[i][j-1][k-1])%Mod;
		}
	}
	for(long long i=1;i<=n;i++)
		for(long long j=1;j<=n;j++)
			ans+=(dp[i][j][K-1]*(n-i+1))%Mod,ans%=Mod;
	printf("%lld\n",((sum-ans)%Mod+Mod)%Mod);
    return 0;
}



