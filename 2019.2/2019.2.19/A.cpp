#include<bits/stdc++.h>
#define N 155
#define M 10000
#define db double
int n, m, A[N], p[N];
const double S = 1.0 / 6.0;
db f[N][N*N], ans[N];
int main ()
{
	freopen ("feixingqi.in", "r", stdin);
	freopen ("feixingqi.out", "w", stdout);
	scanf ("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf ("%d", &A[i]);
	for (int i = 1; i <= m; i++) scanf ("%d", &p[i]);
	if (m == 1) return printf ("%.6lf\n", 1.0), 0;
	f[n][0] = 1;
	for (int j = 1; j <= M; j++)
		for (int i = 1; i < n; i++)
			for (int k = 1; k <= 6; k++)
			{
				if (j == 1 && i + k >= n) f[i][j] += S;
				else f[i][j] += f[A[i + k]][j - 1] * S;
			}
	for (int i = 1; i <= n; i++)
		for (int j = M; j; j--) f[i][j] += f[i][j + 1];
	for (int i = 1; i <= m; i++)
	{
		ans[i] = 1;
		for (int j = 1; j <= m; j++) if (j^i)
		{
			db tp = 0;
			for (int k = 1; k <= M; k++) tp += (f[p[i]][k] - f[p[i]][k + 1]) * ((j < i) ? f[p[j]][k + 1] : f[p[j]][k]);
			ans[i] *= tp;
		}
	}
	for (int i = 1; i <= m; i++) printf ("%.6lf\n", ans[i]);
}
