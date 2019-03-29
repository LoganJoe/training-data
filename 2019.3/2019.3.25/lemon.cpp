#include<bits/stdc++.h>
#define N 500005
int n, d[N], A[N], fa[N], bel[N], mark, tp[N];
std::vector<int> e[N], t;
std::multiset<int> S;
void dfs (int u, int top)
{
	if (d[u] < d[top]) top = u;
	bel[u] = top;
	for (int v : e[u]) dfs (v, top);
	std::multiset<int>::iterator it = S.upper_bound (d[top]);
	if (it != S.begin ()) it--;
	if (*it > d[top])
		if (!mark || mark == top) mark = top;
	S.erase (it);
}
/*
bool check (int u)
{
	int res = 1;
	for (int v : e[u]) res &= check (v);
	if (!res) return 0;
	std::multiset<int>::iterator it = S.upper_bound (d[bel[u]]);
	if (it != S.begin ())  it--;
	if (*it > d[bel[u]]) return 0;
	S.erase (it);
	return 1;
}
*/
bool check (int u)
{
	for (int i = 1; i <= n; i++) tp[i] = d[bel[i]];
	std::sort (tp + 1, tp + 1 + n);
	//std::sort (A + 1, A + 1 + n);
	for (int i = 1; i <= n; i++) if (tp[i] < A[i]) return 0;
	return 1;
}

int main ()
{
	freopen ("lemon.in", "r", stdin);
	freopen ("lemon.out", "w", stdout);
	scanf ("%d", &n);

	for (int i = 1; i <= n; i++)
	{
		scanf ("%d%d%d", &d[i], &A[i], &fa[i]);
		if (fa[i]) e[fa[i]].push_back (i);
	}
	for (int i = 1; i <= n; i++) S.insert (A[i]);
	d[0] = 1e9, dfs (1, 1);
	for (int i = 1; i <= n; i++) if (bel[i] == mark) t.push_back (i);
	int l = d[mark], r = d[fa[mark]], res = 1e9, source = d[mark];
	std::sort (A + 1, A + 1 + n);
	while (l <= r)
	{
		int mid = l + r >> 1;
		d[mark] = mid;
		//	S.clear ();
		//	for (int i = 1; i <= n; i++) S.insert (A[i]);
		check (1) ? (r = mid - 1, res = mid) : l = mid + 1;
	}
	if (res == 1e9) return puts ("-1"), 0;
	else return printf ("%d\n", res - source);
}
