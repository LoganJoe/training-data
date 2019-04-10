#include<bits/stdc++.h>
#define N 1005
int n, m, k, l, len[N][N], A[N][N], mark[N];
char s[N][N];
std::priority_queue<std::pair<int, int> > q;
std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int> >, std::greater<std::pair<int, int> > > S;
int main ()
{
	freopen ("hungry.in", "r", stdin);
	freopen ("hungry.out", "w", stdout); 
	scanf ("%d%d%d%d", &n, &m, &k, &l);
	for (int i = 1; i <= n; i++) scanf ("%s", s[i] + 1);
	for (int i = 1; i <= n; i++)
		for (int j = m; j; j--)
			if (s[i][j] == '1') len[i][j] = len[i][j + 1] + 1;
			else len[i][j] = 0;
	for (int i = 1; i <= n; i++) if (len[i][1]) q.push ({ len[i][1],i });
	if (q.size () < k) return puts ("-1"), 0;
	for (int i = 1, x; i <= k; i++)
	{
		mark[q.top ().second] = 1;
		S.push (q.top ()), q.pop ();
	}
	for (int i = 1; i <= n; i++) A[1][i] = mark[i];
	for (int i = 2; i <= m; i++)
	{
		while (!q.empty ()) q.pop ();
		for (int j = 1; j <= n; j++)
			if (!mark[j] && len[j][i])q.push ({ i + len[j][i] - 1, j });
		int tot = 0;
		for (; !q.empty () && tot<l && q.top ().first > S.top ().first; tot++)
		{
			mark[S.top ().second] = 0, S.pop ();
			S.push (q.top ());
			mark[q.top ().second] = 1; q.pop ();
		}
		if (S.top ().first < i) return puts ("-1"), 0;
		for (int j = 1; j <= n; j++) if (mark[j]) A[i][j] = 1;
	}
	for (int i = 1; i <= m; i++, puts (""))
		for (int j = 1; j <= n; j++) if (A[i][j] == 1) printf ("%d ", j);
}
