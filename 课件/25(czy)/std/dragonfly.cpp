#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long LL;
const LL M=998244353;
const int N=1010;

int CT,n;
LL f[N][N],fc[N][N],inv[N],fac[N],fnv[N],pwi[N][N],p1[N],p2[N],way[N],pwx[N];
LL f0[N];

vector<int> numa[N],numb[N];

LL fpw(int a,LL b,const LL &c=M)
{
	LL s=1;
	for(;b;b>>=1,a=(LL)a*a%c)
		if(b&1LL)s=s*a%c;
	return s;
}

LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}

void upd(LL &a,LL b){a=(a+b)%M;}

void solve(int m,vector<int> p,LL *res)
{
	int n=p.size();
	for(int i=0;i<=n;i++)
		for(int j=0;j<=m;j++)
			fc[i][j]=0;
	fc[0][0]=1;
	for(int i=1;i<=n;i++)
		for(int j=0;j<=m;j++)
			for (int k=0;k*p[i-1]<=j;k++)
				upd(fc[i][j],fc[i-1][j-k*p[i-1]]*pwi[p[i-1]][k]%M*fnv[k]%M*pwx[k*(p[i-1]-1)]);
	for(int j=0;j<=m;j++)
		res[j]=fc[n][j]*fac[j]%M;
}

int main()
{
	for(scanf("%d",&CT);CT--;)
	{
		LL A,B,C;
		scanf("%d%lld%lld%lld",&n,&A,&B,&C);
		if(A==0&&B==0&&C==0)
		{
			f0[0]=f0[1]=1;
			for(int i=2;i<=n;i++)
				f0[i]=(f0[i-1]+(i-1)*f0[i-2])%M;
			LL ans=f0[n]*fpw(n,n)%M;
			cout<<ans<<endl;
			continue;
		}
		LL K=A+C-B;
		if(K<0)
			K=-K;
		inv[1]=1;
		for(int i=2;i<=n;i++)
			inv[i]=M-(M/i)*inv[M%i]%M;
		fac[0]=fnv[0]=1;
		for(int i=1;i<=n;i++)
			fac[i]=fac[i-1]*i%M,fnv[i]=fnv[i-1]*inv[i]%M;
		for(int i=1;i<=n;i++)
		{
			pwi[i][0]=1;
			for(int j=1;j*i<=n;j++)
				pwi[i][j]=pwi[i][j-1]*inv[i]%M;
		}
		for(int i=1;i<=n;i++)
			numa[i].clear(),numb[i].clear();
		for(int i=1;i<=n;i++)
		{
			int d=gcd(i,K);
			numa[i/d].push_back(d);
			d=gcd(i,2);
			numb[i/d].push_back(d);
		}
		memset(f,0,sizeof(f));
		f[0][0]=1;
		for(int x=1;x<=n;x++)
		{
			pwx[0]=1;
			for(int c=1;c<=n;c++)
				pwx[c]=pwx[c-1]*x%M;
			solve(n/x,numa[x],p1);
			solve(n/x,numb[x],p2);
			for(int c=0;c*x<=n;c++)
				way[c]=p1[c]*p2[c]%M*pwi[x][c]%M*fnv[c]%M;
			for(int i=0;i<=n;i++)
				for (int j=0;j*x<=i;j++) 
					upd(f[x][i],f[x-1][i-j*x]*way[j]);
		}
		f[n][n]=f[n][n]*fac[n]%M;
		cout<<f[n][n]<<endl;
	}
	return 0;
}
