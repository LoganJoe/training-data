#include<bits/stdc++.h>
#define N 205
#define M 405
#define mod 1000000007
#define ll long long
int n, m, K, A[N][N], a[N][N], f[N][N][55], fac[M], inv[M], ans, po[N][N][55], F[N];
int C (int a, int b) { return 1ll * fac[a] * inv[b] % mod * inv[a - b] % mod; }
ll Pow (ll x, ll k)
{
	ll t = 1;
	for (; k; k >>= 1, x = x * x % mod) if (k & 1) t = t * x % mod;
	return t;
}
int mul (int x) { return x >= mod ? x - mod : x; }
void solve ()
{
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
		{
			po[i][j][0] = 1;
			for (int k = 1; k <= K; k++)
				po[i][j][k] = 1ll * po[i][j][k - 1] * A[i][j] % mod;
		}
	for (int i = 1; i <= m; i++)  F[i] = 0;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 0; j <= m; j++) f[j][0][0] = 1;
		for (int j = 1; j <= m; j++)
			for (int k = 1; k <= j; k++)
				for (int l = 0; l <= K; l++)
				{
					f[j][k][l] = f[j - 1][k][l];
					for (int t = 0; t <= l; t++)
						f[j][k][l] = (1ll * po[i][j][l - t] * f[j - 1][k - 1][t] % mod * C (l, t) + f[j][k][l]) % mod;
				}
		for (int j = 1; j <= m; j++) F[j] = mul (F[j] + f[m][j][K]);
	}
	for (int i = 1; i <= m; i++)
		for (int j = 0; j < n; j++)
			ans = mul (ans + 1ll * F[i] * C (n - 1, j) % mod  * fac[n + i - j - 1] % mod * fac[m - i + j] % mod);
}
int main ()
{
	freopen("eat.in", "r", stdin);
	freopen("eat.out", "w", stdout);
	fac[0] = inv[0] = inv[1] = 1;
	for (int i = 1; i < M; i++) fac[i] = 1ll * fac[i - 1] * i % mod;
	for (int i = 2; i < M; i++) inv[i] = 1ll * (mod - mod / i) * inv[mod%i] % mod;
	for (int i = 2; i < M; i++) inv[i] = 1ll * inv[i - 1] * inv[i] % mod;
	scanf ("%d%d%d", &n, &m, &K);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) scanf ("%d", &A[i][j]);
	if (K == 1)
	{
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				ans = mul(ans + A[i][j]);
		return printf("%d\n", ans);
	}
	solve ();
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			a[j][i] = A[i][j];
	std::swap (n, m);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) A[i][j] = a[i][j];
	solve ();
	printf ("%d\n", 1ll * ans * inv[n + m] % mod);
}