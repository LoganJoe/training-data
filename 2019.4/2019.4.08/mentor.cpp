#include<bits/stdc++.h>
#define mod 998244353
#define N 1005
int T, n, m, K, c0, c1, d0, d1, A[N], f[2][N][N], g[2][N][N], h[2][N][N], ban[N];
std::vector<int> S[N];
void add (int &a, int b) { a += b; if (a >= mod) a -= mod; }
void clear ()
{
	for (int i = 1; i <= n; i++) S[i].clear (), A[i] = 0;
}
int main ()
{
	freopen ("mentor.in", "r", stdin);
	freopen ("mentor.out", "w", stdout);
	for (scanf ("%d", &T); T--;clear())
	{
		scanf ("%d%d", &n, &m);
		scanf ("%d%d%d%d", &c0, &c1, &d0, &d1);
		for (int i = 1, x; i <= n; i++)
			scanf ("%d%d", &x, &A[i]), S[x].push_back (i);
		scanf ("%d", &K);
		for (int i = 1; i <= n; i++) ban[i] = -1;
		for (int i = 1, x, p; i <= K; i++)
			scanf ("%d%d", &x, &p), ban[x] = p;
		memset (f, 0, sizeof (f));
		f[0][0][0] = 1;
		int p = 0, sum = 0;
		for (int i = 1; i <= m; i++)
		{
			if (!S[i].size ()) continue;
			int lst = 0, now = sum;
			//memcpy (g[lst], f[p], sizeof (g[lst]));
			for (int a = 0; a <= c0; a++)
				for (int b = 0; b <= d0; b++) g[lst][a][b] = f[p][a][b];
			for (int v : S[i])
			{
				//memset (g[lst ^ 1], 0, sizeof (g[lst ^ 1]));
				for (int a = 0; a <= c0; a++)
					for (int b = 0; b <= d0; b++) g[lst ^ 1][a][b] = 0;
				for (int a = std::max (0, now - c1); a <= c0; a++)
					for (int b = std::max (0, now - d1); b <= d0; b++)
					{
						if (ban[v] ^ 0) add (g[lst ^ 1][a + A[v]][b + A[v]], g[lst][a][b]);
						if (ban[v] ^ 1) add (g[lst ^ 1][a + A[v]][b], g[lst][a][b]);
					}
				lst ^= 1, now += A[v];
			}
			lst = 0, now = sum;
			//memcpy (h[lst], f[p], sizeof (h[lst]));
			for (int a = 0; a <= c0; a++)
				for (int b = 0; b <= d0; b++) h[lst][a][b] = f[p][a][b];
			for (int v : S[i])
			{
				//memset (h[lst ^ 1], 0, sizeof (h[lst ^ 1]));
				for (int a = 0; a <= c0; a++)
					for (int b = 0; b <= d0; b++) h[lst ^ 1][a][b] = 0;
				for (int a = std::max (0, now - c1); a <= c0; a++)
					for (int b = std::max (0, now - d1); b <= d0; b++)
					{
						if (ban[v] ^ 2) add (h[lst ^ 1][a][b + A[v]], h[lst][a][b]);
						if (ban[v] ^ 3) add (h[lst ^ 1][a][b], h[lst][a][b]);
					}
				lst ^= 1, now += A[v];
			}
			//memcpy (f[p ^ 1], g[lst], sizeof (f[p ^ 1]));
			for (int a = 0; a <= c0; a++)
				for (int b = 0; b <= d0; b++) f[p ^ 1][a][b] = g[lst][a][b];
			for (int a = std::max (0, now - c1); a <= c0; a++)
				for (int b = std::max (0, now - d1); b <= d0; b++)
					add (f[p ^ 1][a][b], h[lst][a][b]);
			sum = now, p ^= 1;
		}
		int ans = 0;
		for (int a = std::max (0, sum - c1); a <= c0; a++)
			for (int b = std::max (0, sum - d1); b <= d0; b++)
				add (ans, f[p][a][b]);
		printf ("%d\n", ans);
	}
}
/*
*/
