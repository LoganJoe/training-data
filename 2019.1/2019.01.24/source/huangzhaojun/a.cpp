#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <cstdlib>
#define fo(i,a,b) for(int i=a;i<=b;++i)
#define fod(i,a,b) for(int i=a;i>=b;--i)
#define mo 998244353
#define LL long long
#define N 1005
using namespace std;
LL js[N],ny[N],f[N][N];
int n,m;
LL C(int n,int m)
{
	if(n<m) return 0;
	return js[n]*ny[m]%mo*ny[n-m]%mo; 
}
int main()
{
//	freopen("a.in","r",stdin);
//	freopen("a.out","w",stdout);
	cin>>n>>m;
	js[0]=ny[0]=ny[1]=js[1]=1;
	fo(i,2,n)
	{
		js[i]=js[i-1]*(LL)i%mo;
		ny[i]=(-ny[mo%i]*(LL)(mo/i)%mo+mo)%mo;
	}
	fo(i,2,n) ny[i]=ny[i-1]*ny[i]%mo;
	f[0][0]=1;
	LL ans=0,s=0;
	fo(i,1,n)
	{
		s=(s+f[m-1][i])%mo;
		ans=(ans+C(i-1,m-1)-s+mo)%mo; 
		int l=min(m-1,i);
		fod(j,l,1)
		{
			fod(k,n,i)
			{
				f[j][k]=(f[j][k]+f[j-1][k-i])%mo;
			}
		}
	}
	printf("%lld\n",ans);
}