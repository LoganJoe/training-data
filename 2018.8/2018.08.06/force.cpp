#include<bits/stdc++.h>
#define N 300005
int n,m,a[N],b[N],top;
long long sum[N],f[22][505],avg,ans=1e9;
long long solve ()
{
	for (int i = 0; i <= m; i++)
		for (int j = 0; j <= n; j++) f[i][j] = 1e18;
	f[0][0] = 0;
	for (int i = 1; i <= m; i++)
	{
		for(int j=i;j<=n;j++)
		{
			for(int k=i-1;k<j;k++) f[i][j]=std::min(f[i][j],f[i-1][k]+(sum[j]-sum[k]-avg)*(sum[j]-sum[k]-avg));
		}
	}
	return f[m][n];
}
int main()
{
	freopen("spaceship.in","r",stdin);
	freopen("spaceship.ans","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]),sum[i]=sum[i-1]+a[i],avg+=a[i];
	for (int i = 1; i <= n; i++)
	{
		top = 0;
		for (int j = i; j <= n; j++) b[++top] = a[j];
		for (int j = 1; j < i; j++) b[++top] = a[j];
		for (int j = 1; j <= n; j++) sum[j] = sum[j - 1] + b[j];
		for (int j = 1; j <= n; j++) sum[j] *= m;
		ans = std::min (ans, solve ());
	}
	std::cout<<ans<<"\n";
} 
