#include<bits/stdc++.h>
#define N 200005
#define ll long long
int n, A[N], fa[N], Tim; ll ans;
std::vector<int> e[N];
std::multiset<int, std::greater<int> > S[N];
void dfs (int u)
{
	for (int v : e[u])
	{
		dfs (v);
		if (S[v].size () > S[u].size ()) S[u].swap (S[v]);
		std::vector<int> tp;
		for (auto i = S[v].begin (), j = S[u].begin (); i != S[v].end (); i++)
			tp.push_back (std::max (*i, *j)), S[u].erase (j++);
		for (auto x : tp) S[u].insert (x);
	}
	S[u].insert (A[u]);
}
int main ()
{
	freopen ("spring.in", "r", stdin);
	freopen ("spring.out", "w", stdout); 
	scanf ("%d", &n);
	for (int i = 1; i <= n; i++) scanf ("%d", &A[i]);
	for (int i = 2; i <= n; i++) scanf ("%d", &fa[i]), e[fa[i]].push_back (i);
	dfs (1);
	for (int v : S[1]) ans += v;
	std::cout << ans << "\n";
}
