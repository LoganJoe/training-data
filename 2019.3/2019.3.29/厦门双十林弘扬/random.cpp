#include<bits/stdc++.h>
#define N 300005
#define mod 998244353
#define ll long long
int n, Q, head[N], ecnt, deep[N], fa[N][20], ans[N], len;
int mul (int x) { return x >= mod ? x - mod : x; }
ll Pow (ll x, ll k)
{
	ll t = 1;
	for (; k; k >>= 1, x = x * x%mod) if (k & 1) t = t * x%mod;
	return t;
}
struct edge
{
	int v, next;
}e[N << 1];
void add (int u, int v)
{
	e[++ecnt] = { v,head[u] }; head[u] = ecnt;
}
void dfs (int u, int fath)
{
	fa[u][0] = fath, deep[u] = deep[fath] + 1;
	for (int i = head[u]; i; i = e[i].next)
		if (e[i].v != fath) dfs (e[i].v, u);
}
void process ()
{
	for (int j = 1; j < 20; j++)
		for (int i = 1; i <= n; i++) fa[i][j] = fa[fa[i][j - 1]][j - 1];
}
int getlca (int u, int v)
{
	if (deep[u] < deep[v]) std::swap (u, v);
	for (int i = 19; ~i; i--) if (deep[fa[u][i]] >= deep[v]) u = fa[u][i];
	if (u == v) return u;
	for (int i = 19; ~i; i--) if (fa[u][i] != fa[v][i]) u = fa[u][i], v = fa[v][i];
	return fa[u][0];
}
char s[1000005];
class Trie
{
	struct node
	{
		int son[10], cnt, v, sum, deg, k, b, tag, fa, size;
	}t[3000005];
public:
	int root[N], cnt;
	void insert (int &x, int fa, int dep, int v)
	{
		
		if (!x) x = ++cnt;
		t[x].fa = fa, t[x].cnt += v;
		if (dep > len) return (void)(t[x].tag += v, pushup (x));
		insert (t[x].son[s[dep] - '0'], x, dep + 1, v);
		pushup (x);
	}
	void debug (int x)
	{
		if (!x) return;
		printf ("%d %d %d\n", x, t[x].cnt, t[x].tag);
		for (int i = 0; i < 10; i++) if (t[x].son[i]) printf ("%d,%d->%d\n", x, i, t[x].son[i]);
		for (int i = 0; i < 10; i++) debug (t[x].son[i]);
	}
	void pushup (int x)
	{
		t[x].k = t[x].b = t[x].sum = t[x].v = 0; t[x].deg = t[x].fa ? 1 : 0, t[x].size = 1;
		for (int k = 0; k < 10; k++) if (t[t[x].son[k]].cnt > 0)
		{
			int v = t[x].son[k];
			t[x].k = mul (t[x].k + t[v].k);
			t[x].b = mul (t[x].b + t[v].b);
			t[x].sum = mul (t[x].sum + t[v].sum);
			t[x].v = mul (t[x].v + t[v].v);
			t[x].deg++, t[x].size += t[v].size;
		}
		if (t[x].tag > 0) t[x].k = t[x].b = 0;
		else
		{
			t[x].k = Pow (mul (t[x].deg + mod - t[x].k), mod - 2);
			t[x].b = 1ll * (t[x].b + t[x].deg) * t [x].k%mod;
		}
		t[x].v = mul (t[x].v + 1ll * t[x].b * t[x].sum % mod);
		t[x].v = mul (t[x].v + t[x].b);
		t[x].sum = mul (t[x].k + 1ll * t[x].k * t[x].sum % mod);
	}
	void merge (int &x, int y)
	{
		if (!t[x].cnt || !t[y].cnt)
		{
			x = t[y].cnt ? y : x;
			return;
		}
		t[x].cnt += t[y].cnt; t[x].tag += t[y].tag;
		for (int k = 0; k < 10; k++)
			merge (t[x].son[k], t[y].son[k]);
		pushup (x);
	}
	int get (int x)
	{
		return 1ll * t[x].v * Pow (t[x].size, mod - 2) % mod;
	}
}T;
void dfs2 (int u, int fath)
{
	for (int i = head[u]; i; i = e[i].next)
		if (e[i].v != fath) dfs2 (e[i].v, u), T.merge (T.root[u], T.root[e[i].v]);
	ans[u] = T.get (T.root[u]);
}
int main ()
{
	freopen ("random.in", "r", stdin);
	freopen ("random.out", "w", stdout);
	scanf ("%d", &n);
	for (int i = 1, u, v; i < n; i++)
		scanf ("%d%d", &u, &v), add (u, v), add (v, u);
	dfs (1, 0); process ();
	for (scanf ("%d", &Q); Q--;)
	{
		int u, v; scanf ("%d%d", &u, &v); 
		int lca = getlca (u, v);
		scanf ("%s", s + 1); len = strlen (s + 1);
		T.insert (T.root[u],0, 1, 1), T.insert (T.root[v], 0, 1, 1);
		T.insert (T.root[lca], 0, 1, -1);
		if (fa[lca][0]) T.insert (T.root[fa[lca][0]], 0, 1, - 1);
	}
	dfs2 (1, 0);
	for (int i = 1; i <= n; i++) printf ("%d\n", ans[i]);
}
/*
3
1 2
1 3
2
1 2
012
1 3
0
*/
