#include<bits/stdc++.h>
#define ll long long
const int N = 100005, mod = 998244353, g1 = 3, g2 = 332748118;
int n, m, op;
ll Pow (ll x, ll k) { ll t = 1; for (; k; k >>= 1, x = x * x%mod) if (k & 1) t = t * x%mod; return t; }
#define vet std::vector<int>
class NTT
{
	int len, clc, rev[N], invn;
	int tA[N], tB[N];
	void process (int L)
	{
		for (len = 1, clc = 0; len < L; len <<= 1, clc++); invn = Pow (len, mod - 2);
		for (int i = 0; i < len; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << clc - 1);
	}
	void transform (int *s, int op)
	{
		for (int i = 0; i < len; i++) if (i < rev[i]) std::swap (s[i], s[rev[i]]);
		for (int i = 1; i < len; i <<= 1)
		{
			int wn = Pow (op > 0 ? g1 : g2, (mod - 1) / (i << 1));
			for (int j = 0; j < len; j += i << 1)
				for (int k = 0, w = 1; k < i; k++, w = 1ll * w*wn)
				{
					int A = s[j + k], B = 1ll * s[i + j + k] * w%mod;
					s[j + k] = (A + B) % mod, s[i + j + k] = (A - B + mod) % mod;
				}
		}
		if (op < 0) for (int i = 0; i < len; i++) s[i] = 1ll * s[i] * invn % mod;
	}
public:
	void times (vet &A, vet &B, vet &C)
	{
		int n = A.size (), m = B.size (), L = n + m - 1; process (L);
		for (int i = 0; i < n; i++) tA[i] = A[i];
		for (int i = n; i < L; i++) tA[i] = 0;
		for (int i = 0; i < m; i++) tB[i] = B[i];
		for (int i = m; i < L; i++) tB[i] = 0;
		transform (tA, 1), transform (tB, 1);
		for (int i = 0; i < len; i++) tA[i] = 1ll * tA[i] * tB[i] % mod;
		transform (tA, -1);
		C.clear ();
		for (int i = 0; i < L; i++) C.push_back (tA[i]);
	}
}NTT;
namespace solve1
{
	std::map<int, int> E[N];
	std::vector<int> e[N];
	int f[N], ans;
	int find (int x) { return f[x] == x ? f[x] : f[x] = find (f[x]); }
	void merge (int a, int b)
	{
		int x = find (a), y = find (b);
		if (x^y) f[x] = y;
	}
	void Main ()
	{
		for (int i = 1; i <= n; i++) f[i] = i;
		for (int i = 1, u, v; i < n; i++) scanf ("%d%d", &u, &v), E[u][v] = E[v][u] = 1;
		for (int i = 1, u, v; i < n; i++) scanf ("%d%d", &u, &v), e[u].push_back (v);
		for (int u = 1; u <= n; u++)
			for (int j = 0; j < e[u].size (); j++)
			{
				int v = e[u][j];
				if (E[u][v]) merge (u, v);
			}
		for (int i = 1; i <= n; i++) if (f[i] == i) ans++;
		ans = Pow (m, ans);
		printf ("%d\n", ans);
	}
}
namespace solve2
{
	vet tp[N], F; int cnt, invm;
	int deg[N], deg2[N], ans;
	vet e[N];
	void solve (int l, int r, vet &f)
	{
		f.clear ();
		if (l == r)
		{
			f.push_back (deg2[l]), f.push_back (n - deg2[l] - 1);
			return;
		}
		int mid = l + r >> 1, a = ++cnt, b = ++cnt;
		solve (l, mid, tp[a]), solve (mid + 1, r, tp[b]);
		NTT.times (tp[a], tp[b], f);
	}
	int f[N][2]; 
	void dfs (int u, int fa)
	{
		f[u][0] = f[u][1] = 1;
		for (int v : e[u]) if (v != fa)
		{
			dfs (v, u);
			f[u][1] = ((1ll * f[u][0] * f[v][1] % mod + 1ll * f[v][0] * f[u][1] % mod) % mod * invm % mod
					+ 1ll * f[u][1] * f[v][1] % mod * n % mod) % mod;
			f[u][0] = (1ll * f[u][0] * f[v][0] % mod * invm % mod + 1ll * f[u][0] * f[v][1] % mod * n % mod) % mod;
			
		}
	}
	void Main ()
	{
		
		if (n == 3)
		{
			int ans = (m + 2ll * m*m) % mod;
			printf ("%d\n", ans);
			return;
		}
		if (m == 1)
		{
			printf ("%d\n", Pow (n, n - 2));
			return;
		}
		for (int i = 1, u, v; i < n; i++)
		{
			scanf ("%d%d", &u, &v);
			e[u].push_back (v);
			e[v].push_back (u);
		}
		invm = Pow (m, mod - 2) - 1;
		dfs (1, 0);
		ans = 1ll * f[1][1] * Pow (n, mod - 2) % mod;
		printf ("%d\n", (1ll * ans * Pow (m, n) % mod + mod) % mod);
		
		/*
		for (int i = 1, u, v; i < n; i++)
		{
			scanf ("%d%d", &u, &v);
			if (u > v) std::swap (u, v);
			deg[v]++; deg2[u]++, deg2[v]++;
		}
		solve (1, n, F);
		for (int i = 1; i <= n; i++) printf ("%d ", F[i]); puts ("");
		for (int i = 1; i <= n; i++) ans = (1ll * F[i] * Pow (m, i) + ans) % mod;
		printf ("%d\n", ans);
		*/
	}
}
namespace solve3
{
	void Main ()
	{
		if (n == 3)
		{
			int ans = (m + 2ll * m*m) % mod * 3 % mod;
			printf ("%d\n", ans);
			return;
		}
		if (m == 1)
		{
			printf ("%d\n", 1ll * Pow (n, n - 2) * Pow (n, n - 2) % mod);
			return;
		}
	}
}
int main ()
{
	scanf ("%d%d%d", &n, &m, &op);
	if (op == 0) return solve1::Main (), 0;
	if (op == 1) return solve2::Main (), 0;
	if (op == 2) return solve3::Main (), 0;
	return 0;
}
