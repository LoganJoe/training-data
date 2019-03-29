#include<bits/stdc++.h>
#define N 1000005
#define mod 1000000007
#define ll long long
int n, m, k, ans;
std::vector<int>e[N];
ll Pow (ll x, ll k)
{
	ll t = 1;
	for (; k; k >>= 1, x = x * x%mod) if (k & 1) t = t * x%mod;
	return t;
}
int mul (int x) { return x >= mod ? x - mod : x; }
struct edge
{
	int u, v, col;
}s[N];
int A[N], f[N], mark[N];
int find (int x) { return f[x] == x ? f[x] : f[x] = find (f[x]); }
void checkans ()
{
	int res = 0;
	for (int c = 1; c <= m; c++)
	{
		for (int i = 1; i <= n; i++) f[i] = i, mark[i] = 0;
		for (int i = 1; i < n; i++) if (A[i] == c)
		{
			int fx = find (s[i].u), fy = find (s[i].v);
			if (fx == fy) continue;
			f[fx] = fy;
		}
		for (int i = 1; i <= n; i++) if (f[i] != i) mark[find (i)] = 1;
		for (int i = 1; i <= n; i++) if (mark[i]) res++;
	}
	ans = mul (ans + Pow (res, k));
}
void dfs (int x)
{
	if (x >= n) return checkans ();
	for (int i = 1; i <= m; i++) A[x] = i, dfs (x + 1);
}
int main()
{
	freopen ("ranse.in", "r", stdin);
	freopen ("ranse.out", "w", stdout);
	scanf ("%d%d%d", &n, &m, &k);
	for (int i = 1, u, v; i < n; i++)
	{
		scanf ("%d%d", &u, &v), e[u].push_back (v), e[v].push_back (u);
		s[i] = { u,v };
	}
	if (k == 0) return printf ("%d\n", Pow (n - 1, m));
	if (n <= 7 && m <= 7)
	{
		dfs (1);
		std::cout << ans << "\n";
		return 0;
	}
}

