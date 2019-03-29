#include<algorithm>
#include<cstring>
#include<cctype>
#include<cstdio>
#define rep(i,x,y) for(LL i=x; i<=y; ++i)

using namespace std;
typedef long long LL;
typedef long double ld;
const int N=100005,M=125;
bool vis;
int k;
LL mod,p,n,lim,s[M],C[M][M],a[M],ans;

LL mul(LL x,LL y,LL mod)
{
	LL t=x*y-(LL)((ld)x/mod*y+0.5)*mod;
	return t<0?t+mod:t;
}

LL getmi(LL a,LL x,LL mod)
{
	LL rt=1;
	while(x)
	{
		if(x&1) rt=mul(rt,a,mod);
		a=mul(a,a,mod),x>>=1;
	}
	return rt;
}

LL get_sum(LL n,LL k,LL mod,LL lim)
{
	LL rt=1;
	rep(i,1,k+1) rt=mul(rt,n+1,mod);
	rt=(rt+mod-1)%mod;
	rep(i,0,k-1) rt=(rt+mod-mul(C[k+1][i],s[i],mod))%mod;
	return mul(rt,getmi(k+1,lim-1,mod),mod);
}

LL f(LL n,LL mod,int k,LL lim)
{
	LL rt=0;
	rep(i,(n/p)*p+1,n)
		rt=(rt+getmi(i,lim-1,mod))%mod;
	
	rep(i,0,k-1) a[i]=0;
	rep(i,1,p-1)
	{
		LL x=getmi(i,lim-1,mod),nw=x;
		rep(j,0,k-1)
		{
			a[j]=(a[j]+nw)%mod;
			nw=mul(nw,x,mod),nw=mul(nw,p,mod),nw=mod-nw;
		}
	}

	rep(i,0,k) C[i][0]=C[i][i]=1;
	rep(i,1,k) rep(j,1,i-1) C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;

	s[0]=(n/p-1)%mod;
	rep(i,1,k-1) s[i]=get_sum(n/p-1,i,mod,lim);
	s[0]=(s[0]+1)%mod;	

	rep(i,0,k-1) rt=(rt+mul(a[i],s[i],mod))%mod;
	return rt;
}

LL F(LL n,LL mod,int k,LL lim)
{
	if(!n) return 0;
	LL rtf=f(n,mod,k,lim),rtF=F(n/p,mod*p,k+1,lim*p);
	if(rtF%p) vis=1;
	rtF/=p;
	return (rtf+rtF)%mod;
}

int main()
{
	freopen("constitution.in","r",stdin);
	freopen("constitution.out","w",stdout);
	scanf("%lld%d%lld",&p,&k,&n);

	mod=1,lim=p-1;
	rep(i,1,k) mod*=p;
	rep(i,1,k-1) lim*=p;

	ans=(2*n-F(n,mod,k,lim))%mod;
	printf("%lld\n",vis?-1:(ans+mod)%mod);
	return 0;
}
