#include<bits/stdc++.h>
#define N 1005
#define mod 998244353
#define ll long long
int n, K, f[2][10][N], ans;
int mul (int x) { return x >= mod ? x - mod : x; }
ll Pow (ll x, ll k) { ll t = 1; for (; k; k >>= 1, x = x * x%mod) if (k & 1) t = t * x%mod; return t; }
int main ()
{
	scanf ("%d%d", &n, &K);
	f[0][0][0] = 1;
	for (int i = 1, p = 1; i <= n; i++, p ^= 1)
	{
		for (int j = 0; j <= K - 1; j++)
			for (int k = 0; k <= n; k++) f[p][j][k] = f[p ^ 1][j][k];
		for (int j = 0; j <= K - 2; j++)
			for (int k = 0; k <= n; k++) if (f[p ^ 1][j][k] && k + i <= n)
				f[p][j + 1][k + i] = mul (f[p][j + 1][k + i] + f[p ^ 1][j][k]);
	}
	for (int i = 0; i <= n; i++) ans = mul (ans + 1ll * f[n & 1][K - 1][i] * (n - i + 1) % mod);
	int C = 1;
	for (int i = 1; i <= K; i++) C = 1ll * C * (n - i + 1) % mod * Pow (i, mod - 2) % mod;
	std::cout << mul (C - ans + mod) << "\n";

}
