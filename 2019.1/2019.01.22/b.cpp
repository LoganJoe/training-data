#include<bits/stdc++.h>
#define N 500005
#define mod 1000109107
int n, m, head[N], ecnt, fa[N], Xor[N], tot[N], get[N], ans;
int mul (int x) { return x >= mod ? x - mod : x; }
struct edge
{
	int v, next;
}e[N << 1];
void add (int u, int v) { e[++ecnt] = { v,head[u] }; head[u] = ecnt; }
void dfs (int u, int fath)
{
	fa[u] = fath;
	for (int i = head[u];i; i = e[i].next)
		if (e[i].v != fath) dfs (e[i].v, u);
}
class Trie
{
	struct tree
	{
		int son[2], v;
	}t[N * 40];
	int cnt;
public:
	void init () { cnt = n; }
	void insert (int x, int v)
	{
		if (!x) return;
		Xor[x] ^= v;
		for (int i = 0; i < 20; i++)
		{
			int k = v >> i & 1;
			if (!t[x].son[k]) t[x].son[k] = ++cnt;
			x = t[x].son[k], t[x].v++;
		}
	}
	void Delete (int x, int v)
	{
		if (!x) return;
		Xor[x] ^= v;
		for (int i = 0; i < 20; i++)
		{
			int k = v >> i & 1;
			x = t[x].son[k], t[x].v--;
		}
	}
	void change (int x)
	{
		if (!x) return;
		int rt = x;
		for (int i = 0; i < 20; i++)
		{
			if (!x) return;
			if (t[t[x].son[0]].v & 1) Xor[rt] ^= (1 << i + 1) - 1;
			std::swap (t[x].son[0], t[x].son[1]);
			x = t[x].son[0];
		}
	}
}T;
int main ()
{
	scanf ("%d%d", &n, &m);
	for (int i = 1, u, v; i < n; i++) scanf ("%d%d", &u, &v), add (u, v), add (v, u);
	dfs (1, 0); T.init ();
	for (int i = 2; i <= n; i++) T.insert (fa[i], 0);
	for (int i = 1; i <= m; i++)
	{
		int x; scanf ("%d", &x); tot[x]++;
		if (x == 1)
		{
			T.change (x);
			ans = mul (ans + 1ll * Xor[x] * i % mod * (i + 1) % mod);
			continue;
		}
		int val = get[fa[x]] + tot[fa[fa[x]]];
		T.Delete (fa[fa[x]], val), T.insert (fa[fa[x]], val + 1);
		get[fa[x]]++;
		T.change (x), ans = mul (ans + 1ll * (Xor[x] ^ (val + 1))*i%mod*(i + 1) % mod);
	}
	printf ("%d\n", ans);
}
