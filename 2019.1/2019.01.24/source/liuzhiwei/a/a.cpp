# include<cstdio>
# include<cstring>
# include<algorithm>
using namespace std;
const int N = 1e3 + 5;
const int mo = 998244353;
typedef long long ll;
int f[N][15],inv[N];
int n,k;
int main()
{
	scanf("%d%d",&n,&k); f[0][0] = 1;
	for (int i = 1 ; i <= n ; ++i)
		for (int j = k ; j ; --j)
			for (int l = n ; l >= i ; --l) f[l][j] = (f[l][j] + f[l - i][j - 1]) % mo;
	int ans = 1; inv[1] = 1;
	for (int i = n ; i >= n - k + 1 ; --i) ans = (ll)ans * i % mo;
	for (int i = 2 ; i <= k ; ++i) inv[i] = (ll)(mo - mo / i) * inv[mo % i] % mo,ans = (ll)ans * inv[i] % mo;
	for (int i = 1 ; i <= n ; ++i) ans = (ans - (ll)(n - i + 1) * f[i][k - 1] % mo + mo) % mo;
	printf("%d\n",ans);
	return 0;
}
