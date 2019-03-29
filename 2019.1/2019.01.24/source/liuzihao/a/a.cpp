#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#define fo(i,j,k) for(int i=j;i<=k;++i)
#define fd(i,j,k) for(int i=j;i>=k;--i)
using namespace std;
const int N=1010,mo=998244353;
int f[N*N][11];
int main()
{
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
	int n,K;
	scanf("%d %d",&n,&K);
	int ans=0;
	f[0][0]=1;
	fo(i,1,n){
		fo(j,i+1,i*K) ans+=f[j][K-1],ans%=mo;
		fd(j,i*(K-1),i)
		fd(k,K-1,1) f[j][k]+=f[j-i][k-1],f[j][k]%=mo;
	}
	printf("%d",ans);
}

