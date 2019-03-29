#include<bits/stdc++.h>
#define N 100005
std::vector<int>e[N];
int n, Q, fa[N], root, ans[N][3], deep[N], s[N];
void dfs (int u)
{
	for (auto v : e[u])
	{
		deep[v] = deep[u] + 1;
		dfs (v); 
	}
}
int main ()
{
	freopen ("message.in", "r", stdin);
	freopen ("message.ans", "w", stdout);
	scanf ("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf ("%d", &fa[i]);
		if (!fa[i]) root = i;
		else e[fa[i]].push_back (i);
	}
	dfs (root);
	scanf ("%d", &Q);
	for(int i=1;i<=Q;i++)
	{
		int opt, a, b, c;
		scanf ("%d", &opt);
		if (opt == 1)
		{
			scanf ("%d%d%d", &a, &b, &c);
			int res = 0, tot=0;
			while (a != b)
			{
				if (deep[a] < deep[b]) std::swap (a, b);
				if (s[a] && i - s[a] > c) res++; tot++;
				a = fa[a];
				
			}
			if (s[a] && i - s[a] > c) res++; tot++;
			printf ("%d %d\n", tot, res);
		}
		else
		{
			scanf ("%d", &a);
			if(!s[a]) s[a] = i;
		}
	}

	
}
