#include<bits/stdc++.h>
#define N 2005
#define mod 2012
int n,k,f[N][N];
int main()
{
	freopen("permutation.in","r",stdin);
	freopen("permutation.out","w",stdout);
	scanf("%d%d",&n,&k);
	f[1][0]=1;
	for(int i=1;i<=n;i++)
		for(int j=0;j<i && j<=k;j++)
		{
			f[i+1][j]=(f[i+1][j]+f[i][j]*(j+1))%mod;
			f[i+1][j+1]=(f[i+1][j+1]+f[i][j]*(i-j))%mod;
		}
	std::cout<<f[n][k]<<"\n";
}
