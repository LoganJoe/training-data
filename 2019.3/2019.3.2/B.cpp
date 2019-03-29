#include<bits/stdc++.h>
#define N 5005
#define ll long long
#define mod 998244353
int Case, n, ans, pre[N], p, cnt[N];
std::vector<int> e[N];
ll Pow (ll x, ll k)
{
	ll t = 1;
	for (; k; k >>= 1, x = x * x%mod) if (k&1) t = t * x%mod;
	return t;
}
int mul (int x) { return x >= mod ? x - mod : x; }
void mark (int u, int fa)
{
	pre[u] = fa;
	for (int v : e[u]) if (v != fa) mark (v, u);
}
void dfs (int m) 
{
	if (m == n) return (void)(ans = mul (ans + m + 1));
	for (int u = 1; u <= n; u++) 
	{
		for (int v = u; v <= n; v++) 
		{
			mark (u, 0);
			bool fl = 1;
			for (int i = v; i; i = pre[i]) 
			{
				if (cnt[i] && fl) 
					ans = (ans + 1ll * (m + 1) * Pow (p, n - m - 1)) % mod, fl = 0;
				cnt[i]++;
			}
			if (fl) dfs (m + 1);
			mark (u, 0);
			for (int i = v; i; i = pre[i]) cnt[i]--;
		}
	}
}
int main ()
{
	freopen("astrology.in","r",stdin);
	freopen("astrology.out","w",stdout); 
	scanf ("%d%d", &Case, &n); p = n * (n + 1) / 2;
	for (int i = 1, u, v; i < n; i++) 
		scanf ("%d%d", &u, &v), e[u].push_back (v), e[v].push_back (u);
	dfs (0);
	std::cout << 1ll * ans * Pow (Pow (p, mod - 2), n) % mod << "\n";
}

