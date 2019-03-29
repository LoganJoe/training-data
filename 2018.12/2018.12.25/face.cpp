#include<bits/stdc++.h>
#define N 5005
int n, m, k, vis[N], ans;
std::vector<int>e[N];
void dfs (int u, int cnt)
{
	if (cnt == n) return (void)(ans++);
	for (int v : e[u]) if (!vis[v]) vis[v] = 1, dfs (v, cnt + 1), vis[v] = 0;
}
int main ()
{
	freopen("face.in","r",stdin);
	freopen("face.out","w",stdout);
	scanf ("%d%d%d", &n, &m, &k);
	for (int i = 1, u, v; i <= m; i++) scanf ("%d%d", &u, &v), e[u].push_back (v);
	for (int i = 1; i <= n; i++) vis[i] = 1, dfs (i, 1), vis[i] = 0;
	std::cout << ans << "\n";
}