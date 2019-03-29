#include<bits/stdc++.h>
#define GG {puts("0");continue;}
#define OK {puts("1");continue;}
#define N 55
int T, n, a, b, cnt/*, f[N][N][N][3][3], ans[N][N][N]*/;
int main ()
{
	freopen ("flow.in", "r", stdin);
	freopen ("flow.out", "w", stdout);
	int Case; scanf ("%d", &Case);
	/*
	f[1][0][0][0][0] = 1, n = 50;
	for (int i = 1; i <= n; i++)
		for (int a = 0; a <= n; a++)
			for (int b = 0; b <= n; b++)
				for (int s1 = 0; s1 < 3; s1++)
					for (int s2 = 0; s2 < 3; s2++) if (f[i][a][b][s1][s2])
					{
						for (int j = 1; i + j <= n; j++)
							for (int c = 0; c <= n; c++)
								for (int d = 0; d <= n; d++)
									for (int t1 = 0; t1 < 3; t1++)
										for (int t2 = 0; t2 < 3; t2++) if (f[j][c][d][t1][t2])
										{
											int n1 = s1 + t1, n2 = s2 + t2;
											if (n1 < 3 && n2 < 3)
												f[i + j][a + c + 1][b + d][n1][n2] |= 1,
												f[i + j][a + c][b + d + 1][n1][n2] |= 1;
											if (n1 > 1 && n2 < 3) f[i + j][a + c + 1][b + d][n1 - 2][n2] |= 1;
											if (n2 > 1 && n1 < 3) f[i + j][a + c][b + d + 1][n1][n2 - 2] |= 1;
											if (n1 > 3 && n2 < 3) f[i + j][a + c + 2][b + d][n1 - 4][n2] |= 1;
											if (n2 > 3 && n2 < 3) f[i + j][a + c][b + d + 2][n1][n2 - 4] |= 1;
											if (n1 > 1 && n2 > 1)
												f[i + j][a + c + 1][b + d + 1][n1 - 2][n2 - 2] |= 1;
											if (n1 > 3 && n2 > 1)
												f[i + j][a + c + 2][b + d + 1][n1 - 4][n2 - 2] |= 1;
											if (n1 > 1 && n2 > 3)
												f[i + j][a + c + 1][b + d + 2][n1 - 2][n2 - 4] |= 1;
											if (n1 > 3 && n2 > 3)
												f[i + j][a + c + 2][b + d + 2][n1 - 4][n2 - 4] |= 1;

										}
						//printf ("%d %d %d %d %d\n", i, a, b, s1, s2);
						if (s2 > 1) f[n][a + 2][b][s1][s2 - 2] = 1;
					}
	for (int i = 1; i <= n; i++)
		for (int a = 0; a <= n; a++)
			for (int b = 0; b <= n; b++)
			{
				ans[i][a][b] |= f[i][a][b][0][0];
				ans[i][a + 2][b] |= ans[i][a][b];
				ans[i][a][b + 2] |= ans[i][a][b];
				ans[i][a + 2][b + 1] |= ans[i][a][b];
			}
	for (scanf ("%d", &T); T--;)
	{
		scanf ("%d%d%d", &n, &a, &b);
		printf ("%d\n", ans[n][a][b]);
		cnt += ans[n][a][b];
	}
	std::cout << cnt << "\n";
	*/
	for (scanf ("%d", &T); T--;)
	{
		scanf ("%d%d%d", &n, &a, &b);
		if (b == 1)
			if (a >= 2) a -= 2, b++;
			else GG;
		if (a == 1 || n > a + b || (n >= a + b && a && b)) GG;
		if (n == 2)
		{
			if (a & 1) GG;
			if (b & 1)
				if (a >= 2) a -= 2, b++;
				else GG;
		}
		OK;
	}
}
/*
0 4
2 2 1
4 2 3 
5 2 3
10 0 10
*/
