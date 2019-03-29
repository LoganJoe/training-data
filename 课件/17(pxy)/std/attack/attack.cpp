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
#define N 2009
using namespace std;

int m,n,cnt,tp,q[N],f[N][N],g[N][N]; char ch[N][N];
ll a[N][N],b[N][N],c[N][N],d[N][N],s[N][N]; 
int ksm(int x,int y){
	int z=1;
	for (; y; y>>=1,x=(ll)x*x%mod) if (y&1) z=(ll)z*x%mod;
	return z;
}
int solve(int x,int y){
	int i,j,ans=0;
	for (i=1; i<=m; i++)
		for (j=1; j<=n; j++){
			s[i][j]=s[i-1][j]+s[i][j-1]-s[i-1][j-1]+a[i][j]+b[i+x][j]+c[i][j+y]+d[i+x][j+y];
			ad(ans,ksm(s[i][j]%mod,cnt));
		}
	return ans;
}
int main(){
	freopen("attack.in","r",stdin);
	freopen("attack.out","w",stdout);
	scanf("%d%d%d",&m,&n,&cnt);
	int i,j;
	for (i=1; i<=m; i++) scanf("%s",ch[i]+1);
	for (i=1; i<=m; i++)
		for (j=1; j<=n; j++) f[i][j]=(ch[i][j]=='1'?f[i-1][j]+1:0);
	for (i=m; i; i--)
		for (j=1; j<=n; j++) g[i][j]=(ch[i][j]=='1'?g[i+1][j]+1:0);
	ll sum=0,now;
	for (i=1; i<=m; i++){
		q[tp=1]=n+1; now=0;
		for (j=n; j; j--){
			for (; tp>1 && g[i][j]<=g[i][q[tp]]; tp--)
				now-=(q[tp-1]-q[tp])*g[i][q[tp]];
			now+=(q[tp]-j)*g[i][j]; q[++tp]=j;
			a[i][j]+=now;
		}
		tp=1; now=0;
		for (j=n; j; j--){
			for (; tp>1 && f[i][j]<=f[i][q[tp]]; tp--)
				now-=(q[tp-1]-q[tp])*f[i][q[tp]];
			now+=(q[tp]-j)*f[i][j]; q[++tp]=j;
			b[i+1][j]-=now;
		}
		q[tp=1]=0; now=0;
		for (j=1; j<=n; j++){
			for (; tp>1 && g[i][j]<=g[i][q[tp]]; tp--)
				now-=(q[tp]-q[tp-1])*g[i][q[tp]];
			now+=(j-q[tp])*g[i][j]; q[++tp]=j;
			c[i][j+1]-=now;
		}
		tp=1; now=0;
		for (j=1; j<=n; j++){
			for (; tp>1 && f[i][j]<=f[i][q[tp]]; tp--)
				now-=(q[tp]-q[tp-1])*f[i][q[tp]];
			now+=(j-q[tp])*f[i][j]; q[++tp]=j;
			sum+=now; d[i+1][j+1]+=now;
		}
	}
	int ans=solve(0,0)-solve(0,1)-solve(1,0)+solve(1,1);
	printf("%d\n",(ans%mod+mod)%mod);
	return 0;
}

