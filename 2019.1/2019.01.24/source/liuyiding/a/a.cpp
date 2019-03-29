#include<cstdio>
#include<cstring>
#include<algorithm>
#include<assert.h>
#define fo(i,a,b) for(int i=(a);i<=(b);++i)
#define fd(i,b,a) for(int i=(b);i>=(a);--i)
#define bfo(i,v,u) for(int i=BB[v],u=B[i][1];i;u=B[i=B[i][0]][1])
#define mset(a,x) memset(a,x,sizeof(a))
#define mcpy(a,b) memcpy(a,b,sizeof(b))
template<typename T> bool chkmin(T &a,const T &b) {return b<a?a=b,1:0;}
template<typename T> bool chkmax(T &a,const T &b) {return b>a?a=b,1:0;}
using namespace std;
typedef long long ll;
int read(){int n=0,p=1;char ch;for(ch=getchar();ch<'0' || ch>'9';ch=getchar())if(ch=='-') p=-1;for(;'0'<=ch && ch<='9';ch=getchar()) n=n*10+ch-'0';return n*p;}
const int M=205,mo=998244353;
ll qmi(ll x,ll n)
{
	ll t=1;
	for(x%=mo;n;n>>=1,x=x*x%mo) if(n&1) t=t*x%mo;
	return t;
}
void inc(ll &x,ll y){x=(x+y)%mo;}
int n,m;
ll f[1005][1005][10];
int main()
{
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
	n=read(),m=read();
	ll tot=1,ans=0;
	fo(i,n-m+1,n) tot=tot*i%mo;
	fo(i,1,m) tot=tot*qmi(i,mo-2)%mo;
	fo(i,0,n) f[i][0][0]=1;
	fo(i,1,n)
		fo(j,1,n)
			fo(k,1,m)
			{
				f[i][j][k]=f[i-1][j][k];
				if(j>=i) inc(f[i][j][k],f[i-1][j-i][k-1]);
			}
	fo(i,1,n)
		inc(ans,f[n][i][m-1]*(n-i+1));
	ans=(tot-ans+mo)%mo;
	printf("%lld\n",ans);
	return 0;
}

