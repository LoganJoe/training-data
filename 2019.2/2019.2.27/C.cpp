#include<bits/stdc++.h>
#define N 1111111
#define ll long long
int n, m, K, mod1 = 1, ans1, mod2, ans2, A[N], B[N], cnt[10], tot;
int QaQ;
std::vector<std::pair<int, int> > pr;
void exgcd (int a, int b, ll &x, ll &y)
{
	if (!b) return (void)(x = 1, y = 0);
	exgcd (b, a%b, x, y);
	ll t = x; x = y; y = t - a / b * y;
}
ll Pow (ll x, ll k, ll p)
{
	ll t = 1;
	for (; k; k >>= 1, x = x * x%p) if (k & 1) t = t * x%p, QaQ++;
	return t;
}
int inv (int x, int p) 
{
	ll s, t; exgcd (x, p, s, t);
	return (s % p + p) % p;
}
void div (int n, int p, int &s, int &t) 
{
	for (t = 0; n%p == 0; t++, n /= p);
	return (void)(s = n);
}
void solve1 (int p, int q, int mod)
{
	int x = 1, y = 0, res = 0, s, t;
	for (int i = 0; i <= m + 100; i++) 
	{
		A[i] = (i <= n + 2 ? Pow (p, y, mod) * x % mod : 0) - (i == 0);
		if (i < n + 2) 
		{
			div (n + 2 - i, p, s, t);
			x = 1ll * x * s % mod, y += t;
			div (i + 1, p, s, t);
			x = 1ll * x * inv (s, mod) % mod, y -= t;
		}
	}
	for (int i = 0; i <= m; i++) 
		for (int j = i + 2, t = 1; t; j++, t = -2ll * t % mod) 
			B[i] = (1ll * t * A[j] + B[i]) % mod;
	for (int i = 0; i <= m; i++) 
		if (~i & 1) res = (res + B[i]) % mod;
	mod1 = pr[0].second;
	ans1 = (res + mod) % mod;
	pr.erase (pr.begin ());
}
void solve2 ()
{
	int mod = 1, x = 1; ll res = 0;
	for (auto t : pr) mod *= t.second;
	int inv2 = inv (2, mod);
	for (int i = 0; i <= m + 100; i++) 
	{
		int prod = 1;
		for (int i = 0; i < pr.size (); i++)
			prod = 1ll * prod * Pow (pr[i].first, cnt[i], mod) % mod;
		A[i] = (i <= n + 2 ? 1ll * prod * x %mod : 0) - (i == 0);
		if (i < n + 2)
		{
			int a = n + 2 - i, b = i + 1;
			for (int j = 0; j < pr.size (); j++)
			{
				int M = pr[j].first;
				for (; a%M == 0; cnt[j]++, a /= M);
				for (; b%M == 0; cnt[j]--, b /= M);
			}
			x = 1ll * x * a % mod * inv (b, mod) % mod;
		}
	}
	B[0] = 1ll * A[1] * inv2 % mod;
	for (int i = 1; i <= m; i++) B[i] = 1ll * (A[i + 1] - B[i - 1]) * inv2 % mod;
	for (int i = 0; i <= m; i++) if (~i & 1) res = res + B[i];
	mod2 = mod, ans2 = (res % mod + mod) % mod;
}
int main ()
{
	freopen ("sum.in", "r", stdin);
	freopen ("sum.out", "w", stdout);
	scanf ("%d%d%d", &n, &m, &K);
	if (K == 1) return puts ("0"), 0;
	if (n & 1) n--;
	for (int x = 2; 1ll * x * x <= K; x++)  if (K % x == 0)
	{
		int t = K, cnt = 0;
		for (; K % x == 0; K /= x, cnt++);
		pr.push_back ({ x, t / K });
	}
	if (K > 1) pr.push_back ({ K,K });

	if (pr[0].first == 2) 
		solve1 (pr[0].first, pr[0].second, pr[0].second);
	solve2 ();
	ll x, y;
	exgcd (mod1, mod2, x, y);
	x = (x % mod2 * (ans2 - ans1) % mod2 + mod2) % mod2, y = mod1 * mod2;
	int ans = (x * mod1 + ans1) % y, mod = y;
	printf ("%d\n", ans + mod % mod);
}
/*
77 18 28
778266099 998877 549151680
*/
