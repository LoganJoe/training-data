#include<cstdio>
#include<cstring>
#include<algorithm>
#define fo(i,a,b) for(int i=a;i<=b;i++)
#define N 1010
#define mo 998244353ll
#define ll long long
using namespace std;
int n,K;
ll f[N][N][12],ans=0;
int main()
{
//	freopen("a.in","r",stdin);
	scanf("%d%d",&n,&K);
	f[0][0][0]=1;
	fo(i,0,n-1)
	{
		fo(j,0,n+1)
		{
			fo(k,0,K-2)
			{
				(f[i+1][min(j+i+1,n+1)][k+1]+=f[i][j][k])%=mo;
				(f[i+1][j][k]+=f[i][j][k])%=mo;
			}
			(f[i+1][j][K-1]+=f[i][j][K-1])%=mo;
			if(i+1<j) (f[i][0][K]+=f[i][j][K-1])%=mo;
		}
	}
	fo(i,1,n) ans=(ans+f[i][0][K])%mo;
	printf("%d\n",ans);
}