#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define mod 998244353
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
#define ad(x,y) (x=(x+y)%mod)
#define N 70009
#define M 5000009
using namespace std;

int n,a[N],b[N],c[N],g[N],w[2][N],pos[N],f[M+5],inv[M];
int ksm(int x,int y){
	int z=1; for (; y; y>>=1,x=(ll)x*x%mod) if (y&1) z=(ll)z*x%mod;
	return z;
}
void pwk(int n){
	int i,x=ksm(3,(mod-1)/n);
	w[0][0]=w[1][0]=1;
	for (i=1; i<n; i++) w[0][i]=w[1][n-i]=(ll)w[0][i-1]*x%mod;
	for (i=1; i<n; i++) pos[i]=pos[i>>1]>>1|((i&1)?n>>1:0);
}
void fft(int *a,int n,int p){
	int i,j,k,l,x,u,v;
	for (i=1; i<n; i++) if (i<pos[i]) swap(a[i],a[pos[i]]);
	for (k=1; k<n; k<<=1)
		for (i=0,x=n/k>>1; i<n; i+=k<<1)
			for (j=i,l=0; j<i+k; j++,l+=x){
				u=a[j]; v=(ll)a[j+k]*w[p][l]%mod;
				a[j]=(u+v)%mod; a[j+k]=(u-v+mod)%mod;
			}
	if (p){
		x=ksm(n,mod-2);
		for (i=0; i<n; i++) a[i]=(ll)a[i]*x%mod;
	}
}
void solve(int l,int r){
	if (l==r){
		g[l]=(mod-f[a[l]])%mod; return;
	}
	int mid=l+r>>1,len=1,i;
	solve(l,mid); solve(mid+1,r);
	for (; len<=r-l+1; len<<=1);
	memset(b,0,sizeof(int)*len); memset(c,0,sizeof(int)*len);
	for (i=l; i<=mid; i++) b[i-l]=g[i]; b[i-l]=1;
	for (i=mid+1; i<=r; i++) c[i-mid-1]=g[i]; c[r-mid]=1;
	pwk(len); fft(b,len,0); fft(c,len,0);
	for (i=0; i<len; i++) b[i]=(ll)b[i]*c[i]%mod;
	fft(b,len,1);
	for (i=l; i<=r; i++) g[i]=b[i-l];
}
int main(){
	int tt=clock();
	f[0]=inv[0]=inv[1]=1;
	int i; ll tmp;
	for (i=2; i<M; i++){
		inv[i]=mod-(ll)mod/i*inv[mod%i]%mod;
		tmp=4ll*(i-3)*f[i-2];
		if (i>2) tmp+=8ll*(i*2-9)*f[i-3];
		if (i>3) tmp+=16ll*(i-6)*f[i-4];
		f[i]=(tmp%mod+mod)*inv[i]%mod;
	}
	for (i=1; i<M; i++) f[i]=mod-f[i];
	f[0]=(ll)f[1]*inv[2]%mod;
	for (i=1; i<M; i++){
		f[i]=(f[i+1]-4ll*f[i-1])%mod;
		if (f[i]<0) f[i]+=mod;
		if (f[i]&1) f[i]=f[i]+mod>>1; else f[i]>>=1;
	}
	scanf("%d",&n);
	for (i=1; i<=n; i++) scanf("%d",&a[i]);
	solve(1,n);
	int ans=0,x;
	for (i=1; i<=n; i++){
		scanf("%d",&x); ad(ans,(ll)x*g[i]);	
	}
	printf("%d\n",(mod-ans)%mod);
	cerr<<clock()-tt<<'\n';
	return 0;
}

