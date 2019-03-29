#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<queue>
#include<set>
#include<map>
#include<stack>
#include<bitset>
#include<assert.h>

#define pb push_back
#define mp make_pair
#define fi first
#define se second

using namespace std;

template<typename T>inline bool upmin(T &x,T y) { return y<x?x=y,1:0; }
template<typename T>inline bool upmax(T &x,T y) { return x<y?x=y,1:0; }

typedef unsigned int u32;
typedef long long LL;
typedef unsigned long long ULL;
typedef long double lod;
typedef pair<int,int> PR;
typedef vector<int> VI;

const lod pi=acos(-1);
const int oo=1<<30;
const LL OO=1e18;
const int mod=1e9+7;

const int N=5e5+100;

int qpow(int x,int y) {
	int ans=1;
	while (y) {
		if (y&1) ans=1LL*ans*x%mod;
		x=1LL*x*x%mod;y>>=1;
	}
	return ans;
}

int gi() {
	int w=0;bool q=1;char c=getchar();
	while ((c<'0'||c>'9') && c!='-') c=getchar();
	if (c=='-') q=0,c=getchar();
	while (c>='0'&&c <= '9') w=w*10+c-'0',c=getchar();
	return q? w:-w;
}

namespace io {
	const int L=(1<<21)+1;
	char ibuf[L],*iS,*iT,obuf[L],*oS=obuf,*oT=obuf+L-1,c,st[55];int f,tp;
#define gc() (iS==iT?(iT=(iS=ibuf)+fread(ibuf,1,L,stdin),(iS==iT?EOF:*iS++)):*iS++)
	inline void flush() {
		fwrite(obuf,1,oS-obuf,stdout);
		oS=obuf;
	}
	inline void putc(char x) { *oS++=x; if (oS==oT) flush(); }
	template<class I> inline void gi(I&x) {
		for (f=1,c=gc();c<'0'||c>'9';c=gc()) if (c=='-') f=-1;
		for (x=0;c<='9'&&c>='0';c=gc()) x=x*10+(c&15); x*=f;
	}
	template<class I> inline void print(I x) {
		if (!x) putc('0');
		if (x<0) putc('-'),x=-x;
		while (x) st[++tp]=x%10+'0',x/=10;
		while (tp) putc(st[tp--]);
	}
	inline void gs(char*s, int&l) {
		for (c=gc();c<'a'||c>'z';c=gc());
		for (l=0;c<='z'&&c>='a';c=gc()) s[l++]=c;
		s[l]=0;
	}
	inline void ps(const char*s) { for (int i=0,n=strlen(s);i<n;i++) putc(s[i]); }
	struct IOFLUSHER{ ~IOFLUSHER() { flush(); } } _ioflusher_;
};
using io::putc;
using io::gi;
using io::gs;
using io::ps;
using io::print;


inline LL mul(LL x,LL y,LL mod) {
	return ((x*y-(LL)((long double)x/mod*y)*mod)%mod+mod)%mod;
}
inline LL qpow(LL x,LL y,LL mod) {
	LL ans=1;
	while (y) {
		if (y&1) ans=mul(ans,x,mod);
		x=mul(x,x,mod);
		y>>=1;
	}
	return ans;
}
inline bool miller_rubbin(LL n) {
	if (~n&1) return n==2;
	if (n<5) return n==3;
	int T=10,t;
	LL x,y,s;
	while (T--) {
		x=rand()%(n-2)+2;
		for (y=n-1,t=0;~y&1;y>>=1,t++);
		x=qpow(x,y,n);
		if (x==1) continue;
		while (t--) {
			s=mul(x,x,n);
			if (s==1) {
				if (x!=n-1) return false;
				break;
			}
			x=s;
		}
		if (s!=1) return false;
	}
	return true;
}
inline LL gcd(LL x,LL y) {
	return y?gcd(y,x%y):x;
}
inline LL pro(LL n) {
	LL x=rand()%(n-1)+1,c=rand()%(n-1)+1,y=x,g;
	int t=0,k=1;
	while (1) {
		x=(mul(x,x,n)+c)%n;
		if (x==y) return -1;
		if ((g=gcd(x>y?x-y:y-x,n))!=1) return g;
		if (++t==k) k<<=1,y=x;
	}
}
map<LL,int>F;
inline void pallord(LL n) {
	if (n==1) return;
	if (miller_rubbin(n)) {
		++F[n];
		return;
	}
	LL k;
	while ((k=pro(n))==-1);
	pallord(k);
	pallord(n/k);
}

int m,mid,l1,l2;
VI e[N];
LL val[N];
LL p[20];int c[20];
int tot[1000][1000];
LL v1[N],v2[N];
pair<LL,LL>vp[N];
VI u1[1000],u2[1000];
int f[N];
void dfs(int k,int fa) {
	LL ret=k==1;
	int a=lower_bound(v1,v1+l1,vp[k].fi)-v1,b=lower_bound(v2,v2+l2,vp[k].se)-v2;
	for (int &i:u2[b])
		ret+=tot[a][i];
	f[k]=ret%mod;

	for (int &i:u1[a])
		(tot[i][b]+=f[k])%=mod;
	for (int t:e[k])
		if (t!=fa)
			dfs(t,k);
	for (int &i:u1[a])
		(tot[i][b]+=mod-f[k])%=mod;
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("walk.in","r",stdin);
	freopen("walk.out","w",stdout);
#endif
	int mi=oo,t,s,n,m=0,i,k,a,b,cho;gi(n);
	for (i=1;i<n;i++) {
		gi(a),gi(b);
		//a=i,b=i+1;
		e[a].pb(b),e[b].pb(a);
	}
	//LL all;gi(all);pallord(all);
	for (i=1;i<=n;i++) gi(val[i]);//,val[i]=all/val[i];
	pallord(val[1]);
	for (auto &t:F)
		p[m]=t.fi,c[m++]=t.se;
	for (s=0;s<1<<m;s++) {
		a=b=1;
		for (i=0;i<m;i++)
			if (s>>i&1)
				a*=c[i]+1;
			else
				b*=c[i]+1;
		if (max(a,b)<mi)
			mi=max(a,b),cho=s;
	}
	mid=__builtin_popcount(cho);
	for (i=0;i<m;i++)
		if (cho>>i&1) c[i]*=-1;
	for (i=0,a=m;i<a;i++)
		if (c[i]>0)
			swap(c[i],c[--a]),swap(p[i--],p[a]);
	for (i=0;i<mid;i++) c[i]*=-1;
	l1=l2=1;
	for (i=0;i<mid;i++) l1*=c[i]+1;
	for (i=0;i<l1;i++) {
		v1[i]=1;
		for (t=i,k=0;k<mid;t/=c[k++]+1)
			while (t%(c[k]+1)) t--,v1[i]*=p[k];
	}
	for (i=mid;i<m;i++) l2*=c[i]+1;
	for (i=0;i<l2;i++) {
		v2[i]=1;
		for (t=i,k=mid;k<m;t/=c[k++]+1)
			while (t%(c[k]+1)) t--,v2[i]*=p[k];
	}
	for (i=1;i<=n;i++) {
		vp[i].fi=1;
		for (k=0;k<mid;k++)
			while (!(val[i]%p[k]))
				val[i]/=p[k],vp[i].fi*=p[k];
		vp[i].se=val[i];
	}
	sort(v1,v1+l1);
	sort(v2,v2+l2);
	for (i=0;i<l1;i++)
		for (k=0;k<l1;k++)
			if (!(v1[i]%v1[k]))
				u1[i].pb(k);
	for (i=0;i<l2;i++)
		for (k=0;k<l2;k++)
			if (!(v2[k]%v2[i]))
				u2[i].pb(k);
	dfs(1,0);
	for (i=1;i<=n;i++) print(f[i]),putc('\n');
	return 0;
}
