#include<bits/stdc++.h>
#define N 10
int n, m, mod, A[N][N], vis[N][N], ans;
int dx[] = { 1,-1,0,0 }, dy[] = { 0,0,1,-1 };
void df (int x,int y)
{
	vis[x][y] = 1;
	for (int k = 0; k < 4; k++)
	{
		int tx = x + dx[k], ty = y + dy[k];
		if (tx<1 || tx>n || ty<1 || ty>m) continue;
		if (!vis[tx][ty] && !A[tx][ty]) df (tx, ty);
	}
}
void check ()
{
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) vis[i][j] = 0;
	for (int i = 1, mark = 0; i <= n; i++)
		for (int j = 1; j <= m; j++)
			for (int k = 0; k < 4; k++)
			{
				int x = i + dx[k], y = j + dy[k];
				if (A[x][y] & A[i][j]) return;
				if (!A[i][j] && !mark) df (i, j), mark = 1;
			}
	/*
	for (int i = 1; i <= n; i++, puts (""))
		for (int j = 1; j <= n; j++) printf ("%d", A[i][j]);
	for (int i = 1; i <= n; i++,puts(""))
		for (int j = 1; j <= n; j++) printf ("%d", vis[i][j]);
	*/
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) if (!A[i][j] && !vis[i][j]) return;
	ans++;

}
void dfs (int x, int y)
{
	if (y > m) return check ();
	if (x > n) return dfs (1, y + 1);
	A[x][y] = 1, dfs (x + 1, y);
	A[x][y] = 0, dfs (x + 1, y);
}
int main ()
{
	//scanf ("%d%d%d", &n, &m, &mod);
	//scanf ("%d%d", &n, &m);
	for (n = 1; n <= 5; n++)
		for (m = 1; n*m <= 25; m++)
		{
			ans = 0;
			dfs (1, 1);
			std::cout << n << " " << m << " " << ans << "\n";
		}
}
/*
1 1 2
1 2 3
1 3 4
1 4 4

2 1 3
2 2 5
2 3 11
2 4 21
2 5 43
2 6 85
2 7 171
2 8 341
2 9 683
2 10 1280
2 11 4054
2 12 8196

3 1 4
3 2 11
3 3 39
3 4 121
3 5 387
3 6 1237
3 7 3955
3 8 12637

4 1 4
4 2 21
4 3 121
4 4 562
4 5 2749
4 6 13393

5 1 4
5 2 43
5 3 387
5 4 2749
5 5 20297
*/

