#include<bits/stdc++.h>
#define N 1005
int n, A[N], ans[N], f[N][N];
int main ()
{
	freopen ("expensive.in", "r", stdin);
	freopen ("expensive.out", "w", stdout);
	scanf ("%d", &n);
	for (int i = 1; i <= n; i++) scanf ("%d", &A[i]);
	for (int i = 0; i <= n; i++)
		for (int j = 0; j <= n; j++) f[i][j] = -1e9;
	for (int i = 0; i <= n; i++) f[i][0] = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= i; j++)
			f[i][j] = std::max (f[i - 1][j], f[i - 1][j - 1] + (j & 1 ? A[i] : -A[i]));
	for (int i = 1; i <= n; i++) std::cout << f[n][i] << " ";
	puts ("");
}
