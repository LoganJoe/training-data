#include<bits/stdc++.h>
#define N 100005
int Case, n, k, f1[N], f2[N];
char s[N];
class Trie 
{
	struct node
	{
		int son[26];
	}t[N << 1], E;
	int cnt;
public:
	void insert ()
	{
		int len = strlen (s + 1), x = 1;
		for (int i = 1; i <= len; i++)
		{
			int k = s[i] - 'a';
			if (!t[x].son[k]) t[x].son[k] = ++cnt;
			x = t[x].son[k];
		}
	}
	void clear ()
	{
		for (int i = 1; i <= cnt; i++) t[i] = E;
		cnt = 1;
	}
	void dfs (int x)
	{
		f1[x] = f2[x] = 0; int tot = 0;
		for (int k = 0; k < 26; k++) if (t[x].son[k])
		{
			dfs (t[x].son[k]), tot++;
			f1[x] |= f1[t[x].son[k]] ^ 1;
			f2[x] |= f2[t[x].son[k]] ^ 1;
		}
		if (!tot) f2[x] = 1;
	}
}T;
int main ()
{
	freopen ("strgame.in", "r", stdin);
	freopen ("strgame.out", "w", stdout);
	T.clear ();
	for (scanf ("%d", &Case); Case--;T.clear())
	{
		scanf ("%d%d", &n, &k);
		for (int i = 1; i <= n; i++) scanf ("%s", s + 1), T.insert ();
		T.dfs (1);
		if (!f1[1]) puts ("Dirty");
		else if (f1[1] & f2[1]) puts ("Pure");
		else if (k & 1) puts ("Pure");
		else puts ("Dirty");
	
	}
}
