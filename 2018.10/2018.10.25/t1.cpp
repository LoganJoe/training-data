#include<bits/stdc++.h>
#define N 1005
int A[N][N], n, K, cnt, mark[N][N], tot[10];
int dx[] = { 1,-1,0,0,1,-1,1,-1 }, dy[] = { 0,0,1,-1,1,-1,-1,1 };
bool check (int a, int b, int op, int t)
{
	if (mark[a][b] == t) return 0;
	mark[a][b] = t;
	
	if (A[a][b] == op)
	{
		int res = 0;
		for (int k = 0; k < 4; k++) res |= check (a + dx[k], b + dy[k], op, t);
		return res;
	}
	if (A[a][b] == (op ^ 1)) return 0;
	if (A[a][b] == -1) return 1;
}
void clear (int a, int b, int op)
{
	A[a][b] = -1;
	for (int k = 0; k < 4; k++)
		if (A[a + dx[k]][b + dy[k]] == op) clear (a + dx[k], b + dy[k], op);
}
bool find (int a, int b)
{
	for (int k = 0; k < 8; k++)
	{
		int x = a + dx[k], y = b + dy[k]; tot[k] = 0;
		while (A[x][y] == A[a][b])
			x += dx[k], y += dy[k], tot[k]++;
	}

 	for (int k = 0; k < 8; k++) if (tot[k] + tot[k ^ 1] + 1 >= K) return 1;
	return 0;
}
int main ()
{
	freopen ("fir.in", "r", stdin);
	freopen ("fir.out", "w", stdout);
	scanf ("%d%d", &n, &K);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) A[i][j] = -1;
	for (int i = 1; i <= n; i++)
	{
		int x, y; scanf ("%d%d", &x, &y);
		if (A[x][y] != -1) return puts ("illegal"), 0;
		A[x][y] = i & 1;
		for (int k = 0; k < 4; k++)
		{
			if (A[x + dx[k]][y + dy[k]] != ((i & 1) ^ 1)) break;
			if (!check (x + dx[k], y + dy[k], (i & 1) ^ 1, ++cnt)) clear (x + dx[k], y + dy[k], (i ^ 1) & 1);
		}
		if (!check (x, y, i & 1, ++cnt)) return puts ("illegal"), 0;
		//if(!check(x,y,i&1,++cnt)) 
		if (find (x, y))
		{
			if (i & 1) printf ("ITer %d\n", i);
			else printf ("Kitty %d\n", i);
			return 0;
		}
	/*
	 *	for (int i = 1; i <= 10; i++, puts (""))
	 *		for (int j = 1; j <= 10; j++)
	 *			if (A[i][j] == -1) putchar ('x');
	 *			else printf ("%d", A[i][j]);
	 */
	}
	return puts ("draw"), 0;
}
