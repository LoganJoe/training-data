#include<bits/stdc++.h>
#include<unordered_map>
#define P 19990213
#define ull unsigned long long
#define N 200005
int n, fa[N], A[N], fail[N], deep[N], pre[N][20];
std::vector<int> e[N];
std::map<ull, int> mp;
ull po[N], ha[N];
/*
void make_fail ()
{
	std::queue<int> q;
	for (auto it = e[0].begin (); it != e[0].end (); it++)
		q.push ((*it).second);
	while (!q.empty ())
	{
		int u = q.front (); q.pop ();
		for (auto it = e[u].begin (); it != e[u].end (); it++)
		{
			std::pair<int, int> v = *it;
			fail[v.second] = e[fail[u]][v.first];
			q.push (v.second);
		}
	}
}
*/
void dfs (int u)
{
	for (int v : e[u])
	{
		ha[v] = ha[u] * P + A[v];
		deep[v] = deep[u] + 1;
		dfs (v);
	}
	mp[ha[u]] = u;
}
ull Hash (int u, int v)
{
	return ha[u] - ha[v] * po[deep[u] - deep[v]];
}
int main ()
{
	freopen ("magic.in", "r", stdin);
	freopen ("magic.out", "w", stdout);
	scanf ("%d", &n);
	for (int i = 1; i <= n; i++) scanf ("%d", &fa[i]), e[fa[i]].push_back (i);
	for (int i = 1; i <= n; i++) scanf ("%d", &A[i]);
	//	make_fail ();
	dfs (0);
	po[0] = 1;
	for (int i = 1; i <= n; i++) po[i] = 1ll * po[i - 1] * P;
	for (int i = 1; i <= n; i++) pre[i][0] = fa[i];
	for (int j = 1; j < 20; j++)
		for (int i = 1; i <= n; i++) pre[i][j] = pre[pre[i][j - 1]][j - 1];
	for (int i = 1; i <= n; i++)
	{
		int t = i;
		for (int j = 19; ~j; j--)
			if (mp.find (Hash (i, pre[t][j])) != mp.end () && Hash (i, pre[t][j]) != ha[i]) t = pre[t][j];
		printf ("%d ", mp[Hash (i, t)]);
		//	printf ("%d\n", t == i ? 0 : t);
	}

}