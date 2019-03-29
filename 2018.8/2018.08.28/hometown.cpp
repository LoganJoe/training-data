#include<bits/stdc++.h>
#define N 105
int n, Q, p, ans;
struct Matrix
{
	int s[N][N];
	friend Matrix operator *(Matrix a, Matrix b)
	{
		Matrix c;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
			{
				c.s[i][j] = 0;
				for (int k = 1; k <= n; k++) c.s[i][j] = (1ll * c.s[i][j] + 1ll * a.s[i][k] * b.s[k][j]) % p;
			}
		return c;
	}
}A, B;
int main ()
{
	freopen("hometown.in","r",stdin);
	freopen("hometown.out","w",stdout);
	scanf ("%d%d%d", &n, &Q, &p);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			scanf ("%d", &A.s[i][j]), B.s[i][j] = A.s[i][j];
	for (; Q; Q--, A = A * B)
		for (int i = 1; i <= n; i++) ans ^= A.s[i][i];
	printf ("%d\n", ans);
}
