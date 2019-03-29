#include<bits/stdc++.h>
#define N 100005
#define ll long long 
int n, q;
char s[N << 1];

class Suffix_AutoMaton
{
public:
	int last, cnt;ll f[N << 2];
	struct node
	{
		int son[26], fa, max;
	}t[N << 2];
	void extend (int c)
	{
		int p = last, np = last = ++cnt, q, nq;
		t[np].max = t[p].max + 1;
		for (; p && !t[p].son[c]; p = t[p].fa) t[p].son[c] = np;
		if (!p) return (void)(t[np].fa = 1);
		if (t[p].max + 1 == t[q = t[p].son[c]].max) return (void)(t[np].fa = q);
		t[nq = ++cnt] = t[q]; t[nq].max = t[p].max + 1;
		t[nq].fa = t[q].fa, t[np].fa = t[q].fa = nq;
		for (; t[p].son[c] == q; p = t[p].fa) t[p].son[c] = nq;
	}
	void init ()
	{
		for (int i = 1; i <= cnt; i++) t[i] = t[0], f[i] = 0;
		cnt = 0; last = ++cnt;
	}
	ll dfs (int u)
	{
		if (f[u]) return f[u];
		f[u] = 1;
		for (int k = 0; k < 26; k++)
		{
			int v = t[u].son[k];
			if (v) f[u] = f[u] + dfs (v);
		}
		return f[u];
	}
}SAM;
int main ()
{
	freopen ("zifuchuan.in", "r", stdin);
	freopen ("zifuchuan.out", "w", stdout);
	scanf ("%s%d", s + 1, &q); n = strlen (s + 1); int len = n;
	for (int i = 1; len <= N * 2 - 5; i++) s[++len] = s[i];
	while (q--)
	{
		SAM.init ();
		int l, r; scanf ("%d%d", &l, &r);
		r -= l; l = (l - 1) % n + 1; r += l;
		for (int i = l; i <= r; i++) SAM.extend (s[i] - 'a');
		std::cout << SAM.dfs (1) - 1 << "\n";
	}
}
