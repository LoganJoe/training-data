#include<bits/stdc++.h>
#define N 2000005
#define mod 1000000007
int n, m, K, fac[N], inv[N], po[N], ans;
int mul (int x) { return x >= mod ? x - mod : x; }
int C (int a, int b) { return a < b || b < 0 ? 0 : 1ll * fac[a] * inv[b] % mod * inv[a - b] % mod; }
namespace solve1
{
	void Main ()
	{
		K = n + m - K;
		ans = C (K - 1, m);
		for (int i = m; i < K; i++)
			for (int j = 0; j < m; j++)
				ans = mul (ans + 1ll * (K - i - 1) * C (i - j - 2, m - j - 2) % mod);
		std::cout << ans << "\n";
	}
}
namespace solve2
{
	void Main ()
	{
		ans = C (n + m - K - 1, m);
		K = n - K;
		for (int i = 0; i < m - 1; i++) ans = mul (ans + C (i + K, i + 2));
		std::cout << ans << "\n";
	}
}
int main ()
{
	freopen ("perm.in", "r", stdin);
	freopen ("perm.out", "w", stdout);
	scanf ("%d%d%d", &n, &K, &m);
	if (m == 1) return printf ("%d\n", n - K), 0;
	fac[0] = inv[0] = inv[1] = 1;
	for (int i = 1; i <= n; i++) fac[i] = 1ll * fac[i - 1] * i % mod;
	for (int i = 2; i <= n; i++) inv[i] = 1ll * (mod - mod / i) * inv[mod % i] % mod;
	for (int i = 2; i <= n; i++) inv[i] = 1ll * inv[i - 1] * inv[i] % mod;
	if (n <= 1000) return solve1::Main (), 0;
	else return solve2::Main (), 0;
}
