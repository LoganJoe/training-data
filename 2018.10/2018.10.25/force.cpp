#include<bits/stdc++.h>
#define N 25
int n, m, K, A[N][N], ans;
void dfs (int x, int y, int op, int cnt,int Xor)
{
	if(x==n && y==m)
	{
		Xor^=A[n][m];		
		ans+=(Xor==K);
		return ;
	}
	if (x + op >= 1 && x + op <= n) dfs (x + op, y, op, cnt - 1, Xor^A[x][y]);
	if (y + op >= 1 && y + op <= m) dfs (x, op + y, op, cnt - 1, Xor^A[x][y]);
}
int main ()
{
	//freopen("maze.in","r",stdin);
	//freopen("maze.ans","w",stdout);
	scanf ("%d%d%d", &n, &m, &K);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) scanf ("%d", &A[i][j]);
	dfs (1, 1, 1, n+m-2, 0);
	printf ("%d\n", ans);
}
/*

*/
