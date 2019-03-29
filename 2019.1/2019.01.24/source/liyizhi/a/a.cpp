#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1005,mo=998244353;
int n,k,ans;
int f[N][N*6][7];
int main()
{
	//freopen("a.in","r",stdin);
	scanf("%d%d",&n,&k);
	f[0][0][0]=1;
	int mx=n*(k-1);
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<=mx;j++)
			for(int l=0;l<k;l++) f[i][j][l]=f[i-1][j][l];
		for(int j=i;j<=mx;j++)
			for(int l=1;l<k;l++)
				f[i][j][l]=(f[i][j][l]+f[i-1][j-i][l-1])%mo;
	}
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=mx;j++)
			ans=(ans+f[i-1][j][k-1])%mo;
	printf("%d",ans);
	return 0;
}
