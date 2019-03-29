#include<cstdio>
using namespace std;
const int mo=998244353;
int n,k,ans,f[1005][7005][8];
int main()
{
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
	scanf("%d%d",&n,&k);
	f[0][0][0]=1;
	for (int i=1;i<=n;i++)
	{
		for (int j=0;j<=n*k;j++)
			for (int p=0;p<=k;p++) f[i][j][p]=f[i-1][j][p];
		for (int j=i;j<=n*k;j++)
			for (int p=1;p<=k;p++)
			f[i][j][p]=(f[i][j][p]+f[i-1][j-i][p-1])%mo;
	}
	for (int i=1;i<=n;i++)
	{
		for (int j=i*2+1;j<=n*k;j++)
			ans=(ans+f[i-1][j-i][k-1])%mo;
	}
	printf("%d\n",ans);
	return 0;
}

