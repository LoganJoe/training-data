#include<bits/stdc++.h>
#define N 1000005
#define mod 1000000007
char ch[4] = { 'A','C','G','T' };
int tr[150];
char s[N], ans[N];
int m, n, totans;
int mul (int x) { return x >= mod ? x - mod : x; }
void print (int len)
{
	for (int i = 1; i <= len; i++)
		putchar (ans[i]);
	putchar ('\n'); totans++;
}
int nxt[4][N];
class Suffix_AutoMaton
{
public:
	int last, root[N], cnt, f[N << 2];
	struct node
	{
		int son[4], fa, max;
	}t[N << 2];
	void extend (int rt, int c)
	{
		int p = last, np = last = ++cnt, q, nq;
		t[np].max = t[p].max + 1;
		for (; p && !t[p].son[c]; p = t[p].fa) t[p].son[c] = np;
		if (!p) return (void)(t[np].fa = rt);
		if (t[p].max + 1 == t[q = t[p].son[c]].max) return (void)(t[np].fa = q);
		t[nq = ++cnt] = t[q]; t[nq].max = t[p].max + 1;
		t[nq].fa = t[q].fa, t[np].fa = t[q].fa = nq;
		for (; t[p].son[c] == q; p = t[p].fa) t[p].son[c] = nq;
	}
	void init ()
	{
		for (int k = 0; k < 4; k++)
		{
			nxt[k][m] = 0;
			for (int i = m - 1; i; i--)
			{
				nxt[k][i] = nxt[k][i + 1];
				if (t[root[i + 1]].son[k]) nxt[k][i] = i + 1;
			}
		}
	}
	int dfs1 (int id, int u)
	{
		if (f[u]) return f[u];
		f[u] = 1;
		for (int k = 0; k < 4; k++)
		{
			int v = t[u].son[k];
			if (!v)
			{
				v = nxt[k][id];
				if (v) f[u] = mul (f[u] + dfs1 (v, t[root[v]].son[k]));
			}
			else f[u] = mul (f[u] + dfs1 (id, v));
		}
		return f[u];
	}
	void dfs2 (int id, int u, int len)
	{
		print (len);
		for (int k = 0; k < 4; k++)
		{
			int v = t[u].son[k];
			ans[len + 1] = ch[k];
			if (!v)
			{
				v = nxt[k][id];
				if (v) dfs2 (v, t[root[v]].son[k], len + 1);
			}
			else dfs2 (id, v, len + 1);
		}
	}
}SAM;
int main ()
{
	freopen ("copy.in", "r", stdin);
	freopen ("copy.out", "w", stdout);
	tr['A'] = 0, tr['C'] = 1, tr['G'] = 2, tr['T'] = 3;
	scanf ("%d", &m);
	for (int i = 1; i <= m; i++)
	{
		scanf ("%s", s + 1); n = strlen (s + 1);
		SAM.last = SAM.root[i] = ++SAM.cnt;
		for (int j = 1; j <= n; j++) SAM.extend (SAM.root[i], tr[s[j]]);
	}
	SAM.init ();
	int op; scanf ("%d", &op);
	if (!op) std::cout << SAM.dfs1 (1, SAM.root[1]) << "\n";
	else SAM.dfs2 (1, SAM.root[1], 0), std::cout << totans << "\n";
}
