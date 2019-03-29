#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;
typedef long long ll;
const int mo = 998244353, N = 1010, KE = 210;
ll ans,n,K;
ll f[KE][N];
ll ksm(ll x,ll y) {
	ll ret = 1;
	for (; y; y>>=1) {
		if (y & 1) ret = ret * x % mo;
		x = x * x % mo;
	}
	return ret;
}
ll C(ll n,ll m) {
	if (n < m) return 0;
	ll ret = 1;
	for (int i = 1; i <= m; i++)
		ret = ret * (n - i + 1) % mo;
	for (int i = 1; i <= m; i++) ret = ret * ksm(i, mo - 2) % mo;
	return ret;
}
ll add(ll &x,ll y){
	x=x+y; if (x>=mo) x%=mo;
}
int main() {
	// freopen("a.in","r",stdin);
	cin>>n>>K;
	ans = C(n,K);
	if (n >= N || K >= KE) {
		cout<<ans<<endl;
		return 0;
	}
	f[0][0]=1;
	for (int i = 0; i < K; i++) {
		for (int j = 0; j <= n; j++) {
			if (i != 0 && i + j <= n) {
				add(f[i][i+j], f[i][j]);
			}
			if (i+j+1<=n && i<K)
				add(f[i+1][i+j+1], f[i][j]);
		}
	}
	// for (int i = 1; i <= K; i++) {
	// 	for (int j = 0; j <= 20; j++)  printf("%3lld ",f[i][j]);
	// 	printf("\n");
	// }
	// ll KK = K;
	// for (K = 1; K < KK; K++) {
		// ll re = 0;
		for (int i = 1; i <= n; i++) {
			add(ans, mo - f[K-1][i] * (n-i+1) % mo);
			// add(re, f[K-1][i] * (n-i+1) % mo);
		}
		// cout<<K<<" "<<re<<endl;
	// }
	cout<<ans<<endl;
}