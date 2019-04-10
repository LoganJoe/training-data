#include<bits/stdc++.h>
#define N 305
#define ll long long
#define mod 1000000007
int n, K, A[N], fac[N], inv[N], f[N][N], cnt[N], tot, num; 
// f[i][j] have i same-color block total point-number is j, forest calc (with out combine between different forest.
ll Pow (ll x, ll k)
{
	ll t = 1;
	for (; k; k >>= 1, x = x * x % mod) if (k & 1) t = t * x % mod;
	return t;
}
int C (int a, int b) { return 1ll * fac[a] * inv[b] % mod * inv[a - b] % mod;}
int main ()
{
	freopen ("tree.in", "r", stdin);
	freopen ("tree.out", "w", stdout);
	scanf ("%d%d", &n, &K);
	fac[0] = inv[0] = inv[1] = 1;
	for (int i = 1; i <= n; i++) fac[i] = 1ll * fac[i - 1] * i % mod;
	for (int i = 2; i <= n; i++) inv[i] = 1ll * (mod - mod / i) * inv[mod % i] % mod;
	for (int i = 2; i <= n; i++) inv[i] = 1ll * inv[i - 1] * inv[i] % mod;
	for (int i = 1; i <= n; i++) scanf ("%d", &A[i]), cnt[A[i]]++;
	f[0][0] = 1;
	for (int i = 1; i <= n; i++) if(cnt[i] >= K)
	{
		for(int j = 0; j <= tot; j++)
			for(int k = j * (K + 1); k <= num; k++)
				for(int l = K + 1; l <= cnt[i]; l++) 
					f[j + 1][k + l] = (f[j + 1][k + l] + 1ll * f[j][k] * C(cnt[i], l) % mod * Pow(l, l - 2)) % mod;
		tot++, num += cnt[i];
	}
	int ans = Pow(n, n - 2);
	for (int i = 1; i <= tot; i++)
		for (int j = i * (K + 1); j <= num; j++) 
		{
			int value = 1ll * j * Pow(n, n - j + i - 2) % mod * f[i][j] % mod;
			if (i & 1) ans = (ans - value + mod) % mod;
			else ans = (ans + value) % mod;
		}
	std::cout << ans << "\n";
}
