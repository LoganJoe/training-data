#include<bits/stdc++.h>
#define N 25
int n, m, K, A[N][N];
long long ans;
std::vector<int> s[N][2];
void dfs (int x, int y, int op, int cnt,int Xor)
{
	if (cnt == 0)
	{
		if (op == 1) Xor ^= A[x][y];
		else Xor ^= K;
		s[x][op == -1 ? 1 : 0].push_back (Xor);
		return;
	}
	if (x + op >= 1 && x + op <= n) dfs (x + op, y, op, cnt - 1, Xor^A[x][y]);
	if (y + op >= 1 && y + op <= m) dfs (x, op + y, op, cnt - 1, Xor^A[x][y]);
}
int main ()
{
	freopen ("maze.in", "r", stdin);
	freopen ("maze.out", "w", stdout);
	scanf ("%d%d%d", &n, &m, &K);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) scanf ("%d", &A[i][j]);
	dfs (1, 1, 1, n - 1, 0);
	dfs (n, m, -1, m - 1, 0);
	for (int i = 1; i <= n; i++)
	{
		std::sort (s[i][0].begin (), s[i][0].end ());
		std::sort (s[i][1].begin (), s[i][1].end ());
		int last = -1, lastans = -1, p = 0, siz = s[i][1].size ();
		for (int j = 0; j < s[i][0].size (); j++)
		{
			if (s[i][0][j] == last)
			{
				ans += lastans;
				continue;
			}
			last = s[i][0][j], lastans = 0;
			while (p < siz && s[i][1][p] < s[i][0][j]) p++;
			while (p < siz && s[i][1][p] == s[i][0][j]) lastans++, p++;
			ans += lastans;
		}
	}
	//printf ("%d\n", ans);
	std::cout<<ans<<"\n";
}
/*
6 5 3
1 1 5 2 5
2 3 1 4 4
0 4 5 0 4
1 2 3 6 8
2 9 9 3 1
0 2 0 6 6
*/

