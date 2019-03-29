#include<bits/stdc++.h>
#define mod 1000000007
int n, m, c, totS, A[12][42][4], f[42][1 << 11][42], g[42][1 << 11][42], ans;
int mul (int x) { return x >= mod ? x - mod : x; }
int main ()
{
	scanf ("%d%d%d", &n, &m, &c); totS = (1 << m) - 1;
	for (int i = 1; i <= m; i++)
		for (int j = 1; j <= n; j++)
			for (int k = 0; k <= c; k++) scanf ("%d", &A[i][j][k]);
	for (int i = 1; i <= n; i++)
	{
		f[i][0][0] = 1;
		for (int S = 0; S <= totS; S++)
			for (int j = 0; j <= m * c; j++) if (f[i][S][j])
				for (int k = 1; k <= m; k++) if (!(S >> k - 1 & 1))
					for (int l = 0; l <= c; l++)
						f[i][S | (1 << k - 1)][j + l] = mul (f[i][S | (1 << k - 1)][j + l] + f[i][S][j] * A[k][i][l]);
	}
	g[0][0][0] = 1;
	for (int i = 1; i <= n; i++)
		for (int S = 0; S <= totS; S++)
			for (int T = 0; T <= totS; T++) if ((S&T) == 0)
				for (int j = 0; j <= m * c; j++)
					for (int k = 0; k <= m * c; k++)
						g[i][S^T][std::max (j, k)] = (g[i][S^T][std::max (j, k)] + g[i - 1][S][j] * f[i][T][k]);
	for (int i = 0; i <= m * c; i++) ans = mul (ans + 1ll * i * g[n][totS][i]);
	std::cout << ans << "\n";

}
