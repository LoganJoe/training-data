#include<bits/stdc++.h>
#define N 100005
#define mod 323232323
#define ll long long
int n, m, K, sqr, pm, A[N], fac[N], inv[N], s1[N], dot[N << 1], udt[N << 1], F[N], G[N];
int C (int a, int b) { return 1ll * fac[a] * inv[b] % mod * inv[a - b] % mod; }
ll Pow (ll x, ll k) { ll t = 1; for (; k; k >>= 1, x = x * x%mod) if (k & 1) t = t * x%mod; return t; }
int mul (int x) { return x >= mod ? x - mod : x; }
unsigned long long tp[N];
int Udt (int x) { return x <= sqr ? x : 2 * sqr - n / x + 1; }
int Dot (int x) { return x <= sqr ? x : n / (2 * sqr - x + 1); }
void doMulti (int *A, int *B, int *C)
{
	for (int i = 1; i <= sqr << 1; i++) tp[i] = 0;
	for (int i = 1; dot[i] <= pm; i++)
		for (int j = 1, u; dot[i] * dot[j] <= pm; j++)
		{
			tp[u = Udt (dot[i] * dot[j])] += 1ll * (A[i] - A[i - 1] + mod) * (B[j] - B[j - 1] + mod);
			if (tp[u] >= 1e19) tp[u] %= mod;
		}
	for (int i = 1; dot[i] <= pm; i++) tp[i] = mul (tp[i] % mod + tp[i - 1]);
	for (int i = sqr << 1; dot[i] > pm; tp[i--] = 0);
	for (int i = sqr << 1; dot[i] > pm; tp[i--] %= mod)
		for (int j = 1, nxt; j <= i; j = nxt + 1)
		{
			nxt = std::max (j, Udt (dot[i] / (dot[i] / dot[j])));
			tp[i] += 1ll * (A[nxt] - A[j - 1] + mod) * B[Udt (dot[i] / dot[j])];
			if (tp[i] >= 1e19) tp[i] %= mod;
		}
	for (int i = 1; i <= sqr << 1; i++) C[i] = tp[i];
}
int g (int p, int x)
{
	int res = 0, k = p;
	for (int i = x; ~i; i--)
	{
		res = mul (res + 1ll * C (x + 1, i) * s1[i] % mod * k % mod);
		k = 1ll * k * p % mod;
	}
	return 1ll * res * Pow (x + 1, mod - 2) % mod;
}
int vis[N], s[35][N];
void solve (int x)
{
	if (vis[x]) return; vis[x] = 1;
	for (int i = 1; i <= x >> 1; i++)
		if (vis[x - i]) { solve (i), doMulti (s[i], s[x - i], s[x]); return; }
	solve (x >> 1), solve (x - (x >> 1)), doMulti (s[x >> 1], s[x - (x >> 1)], s[x]);
}
int main ()
{
	scanf ("%d%d%d", &n, &m, &K), sqr = sqrt (n), pm = pow (n, 2. / 3) / 2;
	for (int i = 0; i <= K; i++) scanf ("%d", &A[i]);
	fac[0] = inv[0] = inv[1] = 1;
	for (int i = 1; i <= K + 1; i++) fac[i] = 1ll * fac[i - 1] * i % mod;
	for (int i = 2; i <= K + 1; i++) inv[i] = 1ll * (mod - mod / i)*inv[mod%i] % mod;
	for (int i = 2; i <= K + 1; i++) inv[i] = 1ll * inv[i - 1] * inv[i] % mod;
	for (int i = 1; i <= sqr << 1; i++) udt[i] = i <= sqr ? i : 2 * sqr - n / i + 1;
	for (int i = 1; i <= sqr << 1; i++) dot[i] = i <= sqr ? i : n / (2 * sqr - i + 1);
	s1[0] = 1;
	for (int i = 1; i <= K; i++)
	{
		for (int j = 0; j < i; j++)
			s1[i] = mul (s1[i] - 1ll * C (i + 1, j) * s1[j] % mod + mod);
		s1[i] = 1ll * s1[i] * Pow (i + 1, mod - 2) % mod;
	} s1[1]++;
	for (int i = 1; i <= sqr << 1; i++)
		for (int j = 0; j <= K; j++)
			F[i] = mul (F[i] + 1ll * g (dot[i], j) * A[j] % mod);
	for (int i = 1; i <= sqr << 1; i++) G[i] = dot[i];
	doMulti (F, G, s[1]), vis[1] = 1;
	solve (m);
	std::cout << s[m][sqr << 1] << "\n";
}
