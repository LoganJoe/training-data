#include<bits/stdc++.h>
#define N 500005
#define ull unsigned long long
#define P 19260817
#define mod 998244353
int n, m, c, p[N], A[N], ans[N];
namespace solve1
{
	void Main ()
	{
		for (int i = 1; i <= m - n + 1; i++)
		{
			int mark = 1;
			for (int j = 1; j <= n; j++)
				if (A[i + j - 1] != A[i + p[j] - 1]) { mark = 0; break; }
			ans[i] = mark;
		}
		for (int i = 1; i <= n; i++) printf ("%d", ans[i]);
	}
}
namespace solve2
{
//fake kmp
	int vis[N], lst[N], nxt[N], pre[N], tot, pa[N];
	void Main ()
	{
		for (int i = 1; i <= n; i++)
		{
			if (vis[i]) continue; tot++;
			for (int j = i; !vis[j]; j = p[j]) vis[j] = tot;
		}
		for (int i = 1; i <= n; i++)
			lst[i] = pre[vis[i]] ? pre[vis[i]] : i, nxt[pre[vis[i]]] = i, pre[vis[i]] = i;
		for (int i = 1; i <= c; i++) nxt[pre[i]] = pre[i];
		for (int i = 2, j = 0; i <= n; i++)
		{
			while (j && j + 1 - lst[j + 1] != i - lst[i]) j = pa[j];
			if (j + 1 - lst[j + 1] == i - lst[i]) j++;
			pa[i] = j;
		}
		for (int i = 1, j = 0; i <= m; i++)
		{
			while (j && A[i - j - 1 + lst[j + 1]] != A[i]) j = pa[j];
			if (A[i] == A[i - j - 1 + lst[j + 1]]) j++;
			if (j == n) ans[i - n + 1] = 1, j--;
		}
		for (int i = 1; i <=m-n+1; i++) printf ("%d", ans[i]);
	}
}
namespace solve3
{
	int a[N<<2], b[N<<2], g1 = 3, g2 = 332748118, len, clc, invn, rev[N<<2];
	int lst[N], po[N<<2];
	int mul (int x) { return x >= mod ? x - mod : x; }
	int Pow (int x, int k) { int t = 1; for (; k; k >>= 1, x = 1ll * x*x%mod) if (k & 1) t = 1ll * t*x%mod; return t; }
	void NTT (int *s, int opt)
	{
		for (int i = 1; i < len; i++) if (i < rev[i]) std::swap (s[i], s[rev[i]]);
		for (int i = 1; i < len; i <<= 1)
		{
			int wn = Pow (opt > 0 ? g1 : g2, (mod - 1) / (i << 1));
			for (int j = 0; j < len; j += i << 1)
				for (int k = 0, w = 1; k < i; w = 1ll * w*wn%mod, k++)
				{
					int A = s[j + k], B = 1ll * s[i + j + k] * w%mod;
					s[j + k] = mul (A + B), s[i + j + k] = mul (A - B + mod);
				}
		}
		if (opt < 0) for (int i = 0; i < len; i++) s[i] = 1ll * s[i] * invn%mod;
	}
	void Main ()
	{
		po[0] = 1; for (int i = 1; i <= n; i++) po[i] = 1ll * po[i - 1] * P%mod;
		for (int i = 1; i <= n; i++) lst[p[i]] = i;
		for (int i = 0; i < n; i++) b[i] = po[lst[n - i]];
		for (int i = 1; i <= m; i++) a[i] = A[i];
		for (len = 1; len <= m << 1; len <<= 1, clc++);
		for (int i = 0; i <= len; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << clc - 1);
		invn = Pow (len, mod - 2);
		NTT (a, 1), NTT (b, 1);
		for (int i = 0; i < len; i++) a[i] = 1ll * a[i] * b[i] % mod;
		NTT (a, -1);
		int re = 0;
		for (int i = m, j = 1; j <= n; j++, i--) re = mul(1ll * re * P % mod + A[i]);
		re = 1ll * re * P % mod;
		for (int i = m,j = m - n; i; i--,j--)
		{
			if (a[i] == re) ans[i - n + 1] = 1;
			if(j==0) break;
			re = mul(re - 1ll * po[n] * A[i] % mod + mod);
			re = mul(1ll * re * P % mod + 1ll * A[j] * P % mod);
		}
		for (int i = 1; i <= m-n+1; i++) printf ("%d", ans[i]);
	}
}
int main ()
{
	scanf ("%d%d%d", &n, &m, &c);
	for (int i = 1; i <= n; i++) scanf ("%d", &p[i]);
	for (int i = 1; i <= m; i++) scanf ("%d", &A[i]);
	
//	if (m <= 2000) return solve1::Main (), 0;
	return solve3::Main (), 0;

}
