#include<bits/stdc++.h>
#define N 205
#define ll long long
int n, mod, f[N][N][N], g[N][N], ans;
int mul (int x) { return x >= mod ? x - mod : x; }
ll Pow (ll x, ll k) { ll t = 1; for (; k; k >>= 1, x = x * x%mod) if (k & 1) t = t * x%mod; return t; }
int A[25];
void dfs (int x, int h, int p)
{
	if (x > n)
	{
		ans = mul (ans + 1ll * h * p%mod);
		return;
	}
	for (int i = 0; i <= h; i++)
		if (A[i]) A[i + 1]++, dfs (x + 1, std::max (h, i + 1), 1ll * p * Pow (x - 1, mod - 2) % mod * A[i] % mod), A[i + 1]--;
}
void slove1 ()
{
	A[0] = 1;
	dfs (2, 0, 1);
}
void slove2 ()
{
	f[1][0][0] = g[1][0] = 1;
	for (int i = 1; i < n; i++)
		for (int j = 0; j <= i; j++)
		{
			f[i][j][0] = g[i][j];
			int invi = Pow (i, mod - 2), invg = Pow (g[i][j], mod - 2);
			g[i + 1][j] = mul (g[i + 1][j] + 1ll * g[i][j] * mul (i - 1ll * f[i][j][j] * invg % mod + mod) % mod * invi % mod);
			g[i + 1][j + 1] = mul (g[i + 1][j + 1] + 1ll * g[i][j] * f[i][j][j] % mod * invi % mod * invg % mod);
			for (int k = 1; k <= j; k++)
			{
				f[i + 1][j][k] = mul (f[i + 1][j][k] + 1ll * f[i][j][k] * mul (i - 1ll * f[i][j][j] * invg % mod - 1ll * f[i][j][k - 1] * invg%mod + mod));
				f[i + 1][j][k] = mul (mul(f[i + 1][j][k] + mod) + 1ll * (f[i][j][k] + 1) * f[i][j][k - 1] % mod * invi%mod);
				f[i + 1][j + 1][k] = mul (f[i + 1][j + 1][k] + 1ll * f[i][j][k] * f[i][j][j] % mod * invi%mod);
			}
			f[i + 1][j + 1][j + 1] = mul (f[i + 1][j + 1][j + 1] + 1ll * f[i][j][j] * invi%mod);
		}
	for (int i = 1; i <= n; i++) ans = mul (ans + 1ll * g[n][i] * i % mod);
}
int main ()
{
	freopen("toy.in","r",stdin);
	freopen("toy.out","w",stdout);
	scanf ("%d%d", &n, &mod);
	if (n <= 14) slove1 ();
	else slove2 ();
	printf ("%d\n", ans);
}
/*
3 998244353
*/
