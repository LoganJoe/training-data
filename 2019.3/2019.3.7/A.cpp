#include<bits/stdc++.h>
#define N 1005
#define mod 1000000007
#define ll long long
int n, A[N], K, ans;
ll Pow (ll x, ll k)
{
	ll t = 1;
	for (; k; k >>= 1, x = x * x%mod) if (k & 1) t = t * x % mod;
	return t;
}
struct BIT
{
	int t[N];
public:
	void add (int x, int v) { for (; x <= n; x += x & -x) t[x] += v; }
	int ask (int x) { int res = 0; for (; x > 0; x -= x & -x) res += t[x]; return res; }
	void clear () { for (int i = 1; i <= n; i++) t[i] = 0; }
}T;
void docalc ()
{

	T.clear ();
	for (int i = n; i >= 1; i--)
		ans += T.ask (A[i]), T.add (A[i], 1);
	ans %= mod;
}
void dfs (int x)
{
	if (x > K) return docalc ();
	for (int l = 1; l <= n; l++)
		for (int r = l; r <= n; r++)
		{
			std::reverse (A + l, A + 1 + r);
			dfs (x + 1);
			std::reverse (A + l, A + 1 + r);
		}
}
int main ()
{
	freopen ("inverse.in", "r", stdin);
	freopen ("inverse.out", "w", stdout);
	scanf ("%d%d", &n, &K);
	for (int i = 1; i <= n; i++) scanf ("%d", &A[i]);
	for (int i = 1; i <= n; i++) A[i] = i;
	dfs (1);
	int total = Pow (n*(n + 1) / 2, K);
	printf ("%d\n", 1ll * ans * Pow (total, mod - 2) % mod);
}