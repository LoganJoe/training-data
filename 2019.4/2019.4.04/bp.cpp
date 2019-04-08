#include<bits/stdc++.h>
#define N 10005
int n, m, mod, f[N][N], fac[N], inv[N], po[N], ans;
int mul (int x) { return x >= mod ? x - mod : x; }
int C (int a, int b) { return 1ll * fac[a] * inv[b] % mod * inv[a - b] % mod; }
int main ()
{
	freopen("bp.in", "r", stdin);
	freopen("bp.out", "w", stdout);
	scanf ("%d%d%d", &m, &n, &mod);
	fac[0] = inv[0] = inv[1] = po[0] = 1;
	for (int i = 1; i <= n; i++) po[i] = po[i - 1] * 2 % mod;
	for (int i = 1; i <= n; i++) fac[i] = 1ll * fac[i - 1] * i % mod;
	for (int i = 2; i <= n; i++) inv[i] = 1ll * (mod - mod / i) * inv[mod%i] % mod;
	for (int i = 2; i <= n; i++) inv[i] = 1ll * inv[i - 1] * inv[i] % mod;
	f[0][0] = 1;
	for (int j = 1; j <= m; j++)
	{
		for (int i = 0; i <= n - m + j - 1; i++)
			for (int k = 1; i + k <= n - m + j; k++)
				f[j][i + k] = (f[j][i + k] + 1ll * f[j - 1][i] * po[i] % mod * C (n - i, k)) % mod;
	}
	for (int i = 1; i <= n; i++) ans = mul (ans + f[m][i]);
	printf ("%d\n", ans);
}
/*
500 500 998244353
*/
