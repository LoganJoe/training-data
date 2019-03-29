#include<bits/stdc++.h>
#define mod 1000109107
#define N 5005
int S, T, n, m, f[N][N];
int mul (int x) { return x >= mod ? x - mod : x; }
int main ()
{
	scanf ("%d%d%d%d", &S, &T, &n, &m);
	f[0][0] = 1;
	for (int i = 1; i <= m; i++)
	{
		int Lim = i <= n ? T : S;
		for (int j = 1; j <= S; j++)
		{
			int Max = std::min (j, Lim);
			for (int k = 1; k <= Max; k++)
				f[i][j] = mul (f[i][j] + f[i - 1][j - k]);
		}
	}
	for (int i = 1; i <= S; i++) f[m][i] += f[m][i - 1];
	std::cout << f[m][S] << "\n";

}
