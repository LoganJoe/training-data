#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define inf 1000000000
#define infll 1000000000000000000ll
#define pii pair<int,int>
#define pll pair<ll,ll>
#define mpr make_pair
#define fi first
#define se second
#define vi vector<int>
#define pb push_back
#define pq priority_queue
#define up(x,y) ((x<(y))?x=(y):0)
#define dn(x,y) ((x>(y))?x=(y):0)
#define mod 998244353
#define ad(x,y) (x=(x+y)%mod)
#define N 1509
using namespace std;

int n,m,a[N][N]; char ch[N<<1][N<<1];
int ovt(int k){ return k<3?k:7-k; }
int read(){
	int x=0; char ch=getchar(); bool flag=0;
	while (ch<'0' || ch>'9'){ if (ch=='-') flag=1; ch=getchar(); }
	while (ch>='0' && ch<='9'){ x=x*10+ch-'0'; ch=getchar(); }
	return flag?-x:x;
}
int calc(char x,char y,char u,char v){
	if (x=='D' && y=='D') return 1;
	if (u=='D' && v=='D') return 2;
	if (x=='D' && u=='D') return 3;
	if (y=='D' && v=='D') return 4;
	if (x=='.' && y=='.' && u=='.' && v=='.') return 0;
	return -1;	
}
bool check(){
	int i,j,x,y;
	for (i=1; i<=n; i++)
		for (j=1; j<=n; j++){
			x=i<<1; y=j<<1;
			a[i][j]=calc(ch[x-1][y-1],ch[x-1][y],ch[x][y-1],ch[x][y]);
			if (a[i][j]==-1) return 0;
		}
	return 1;
}
struct graph{
	int lf[N],rg[N],p[N][N],f[N][N],g[N][N],s[N][N];
	void init(bool flag){
		int i,j;
		for (i=1; i<=n; i++)
			for (j=1; j<=n; j++) p[i][j]=(flag?ovt(a[i][n-j+1]):a[i][j]);
		for (i=1; i<=n; i++){
			rg[i]=n;
			for (j=1; j<=n; j++){
				if (p[i][j]==1 || p[i][j]==4) rg[i]=min(rg[i],j-1);
				if (p[i][j]==2 || p[i][j]==3) lf[i]=max(lf[i],j);
			}
		//	cerr<<lf[i]<<' '<<rg[i]<<'\n';
		}
		f[0][0]=1;
		for (i=1; i<=n; i++){
			for (j=0; j<=n; j++)
				f[i][j]=(f[i-1][j]+(j?f[i][j-1]:0))%mod;
			for (j=0; j<=n; j++) if (j<lf[i] || j>rg[i]) f[i][j]=0;
		//	for (j=0; j<=n; j++) cerr<<f[i][j]<<' ';cerr<<'\n';
		}
		cerr<<"ans:"<<f[n][n]<<'\n';
		g[n+1][n]=1;
		for (i=n; i; i--){
			for (j=n; j>=0; j--)
				g[i][j]=(g[i+1][j]+(j<n?g[i][j+1]:0))%mod;
			for (j=0; j<=n; j++) if (j<lf[i] || j>rg[i]) g[i][j]=0;	
		}
		for (i=1; i<=n; i++)
			for (j=0; j<=n; j++)
				s[i][j]=((j?s[i][j-1]:0)+(ll)f[i][j]*g[i][j])%mod;
	}
	int calc(int x,int y,int k){
		int l=lf[x],r=rg[x];
		if (k==1 || k==4) r=min(r,y-1); else l=max(l,y);
		//cerr<<l<<' '<<r<<'\n';
		return l<=r?(s[x][r]-(l?s[x][l-1]:0)+mod)%mod:0;
	}
}g0,g1;
int main(){
	//freopen("domino1.in","r",stdin); freopen("domino1.out","w",stdout);
	cerr<<"start:\n";
	int tt=clock(); 
	n=read(); m=read();
	int i,j,k,x,y,u,v;
	for (i=1; i<=n*2; i++) scanf("%s",ch[i]+1);
	cerr<<"?\n";
	if (!check()){
		cerr<<"??????"<<'\n';
		while (m--) puts("0"); return 0;
	}
	g0.init(0); g1.init(1);
	cerr<<"??\n";
	while (m--){
		//cerr<<"ask:";
		x=read(); y=read(); u=read(); v=read();
		assert(abs(x-u)+abs(y-v)==1);
		if (x!=u && ((x+1)^(u+1))!=1){ puts("0"); continue; }
		if (y!=v && ((y+1)^(v+1))!=1){ puts("0"); continue; }
		//cerr<<"ok";
		i=x+1>>1; j=y+1>>1;
		if (a[i][j]){ puts("0"); continue; }
		//cerr<<"ok\n";
		if (x==u) k=(x==i*2-1?1:2); else k=(y==j*2-1?3:4);
		printf("%lld\n",(ll)g0.calc(i,j,k)*g1.calc(i,n-j+1,ovt(k))%mod);
	}
	cerr<<clock()-tt<<'\n';
	return 0;
}

