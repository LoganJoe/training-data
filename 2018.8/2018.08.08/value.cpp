#include<bits/stdc++.h>
#define N 100005
#define ll long long
#define mod 998244353
int n, k, fac[N], inv[N];
int C (int a, int b)
{
	return 1ll * fac[a] * inv[b] % mod * inv[a - b] % mod;
}
ll Pow (ll x, ll k)
{
	ll t = 1;
	for (; k; k >>= 1, x = x * x%mod) if (k & 1) t = t * x%mod;
	return t;
}
int main ()
{
//	freopen("value.in","r",stdin);
//	freopen("value.out","w",stdout);
	scanf ("%d%d", &n, &k);
	
	if (n <= 1e5)
	{
		fac[0] = inv[0] = inv[1] = 1;
		for (int i = 1; i <= n; i++) fac[i] = 1ll * fac[i - 1] * i%mod;
		for (int i = 2; i <= n; i++) inv[i] = 1ll * (mod - mod / i)*inv[mod%i] % mod;
		for (int i = 2; i <= n; i++) inv[i] = 1ll * inv[i - 1] * inv[i] % mod;
		int ans = 0;
		for (int i = 0; i < n; i++) ans = (ans + C (n - 1, i) % mod*Pow (i, k) % mod) % mod;
		ans = 1ll * ans * n % mod * Pow (2, 1ll * (n - 1)*(n - 2) / 2) % mod;
		printf ("%d\n", ans);
	//	return 0;
	}
	if (k == 0)
	{
		int ans = 1ll * n * Pow (2, 1ll * n * (n - 1) / 2) % mod;
		printf ("%d\n", ans);
		return 0;
	}
	if (k == 1)
	{
		int ans = 1ll * n * (n - 1) * Pow (2, 1ll * n *(n - 1) / 2 - 1) % mod;
		printf ("%d\n", ans);
		return 0;
	}
	if (k == 2)
	{
		int ans = 1ll * n * n%mod * (n - 1) % mod * Pow (2, 1ll * (n - 2) * (n + 1) / 2 - 1) % mod;
		printf ("%d\n", ans);
		return 0;
	}
}
