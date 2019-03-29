#include<bits/stdc++.h>
#define N 200005
#define ll long long
int n, s[N];
ll ans;
class SAM
{
	int last, cnt;
	struct node
	{
		int fa, max, val;
		std::map<int, int> son;
	}t[N];
public:
	void init () { last = ++cnt; }
	void extend (int c)
	{
		int p = last, np = last = ++cnt, q, nq;
		t[np].max = t[p].max + 1, t[np].val = 1;
		while (!t[p].son[c] && p) t[p].son[c] = np, p = t[p].fa;
		if (!p) return (void)(t[np].fa = 1);
		if (t[p].max + 1 == t[q = t[p].son[c]].max) return (void)(t[np].fa = q);
		t[nq = ++cnt].max = t[p].max + 1;
		t[nq].son = t[q].son; t[nq].fa = t[q].fa, t[np].fa = t[q].fa = nq;
		while (t[p].son[c] == q) t[p].son[c] = nq, p = t[p].fa;
	}
	int incremental ()
	{
		return t[last].max - t[t[last].fa].max;
	}
}SAM;
int main ()
{
	freopen("incantation.in","r",stdin);
	freopen("incantation.out","w",stdout);
	scanf ("%d", &n); SAM.init ();
	for (int i = 1; i <= n; i++) scanf ("%d", &s[i]);
	for (int i = 1; i <= n; i++) SAM.extend (s[i]), printf ("%lld\n", ans += SAM.incremental ());
}
