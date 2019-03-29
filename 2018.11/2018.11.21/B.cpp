#include<bits/stdc++.h>
#define N 1005
#define mod 998244353
int n, f[N][N], g[N][N], ans, nxt[N], la[N];
char s[N*N];
int mul (int x) { return x >= mod ? x - mod : x; }
int main ()
{
	scanf ("%s", s + 1); n = strlen (s + 1);
	for (int i = n; i; i--) nxt[i] = la[s[i] - 'a'], la[s[i] - 'a'] = i;
	for (int i = 1; i < n; i++) if (s[i] == s[i + 1]) f[i][i + 1] = 1;
	for (int len = 2; len <= n; len += 2)
		for (int l = 1; l + len - 1 <= n; l++)
		{
			int r = l + len - 1;
			if (s[l] == s[r]) f[l][r] = mul (f[l][r] + g[l + 1][r - 1]);
			g[l][r] = f[l][r];
			for (int k = nxt[l]; k && k < r; k = nxt[k])
				g[l][r] = mul (g[l][r] + 1ll * f[l][k] * g[k + 1][r] % mod);
		}
	for (int i = 1; i <= n; i++)
		for (int j = i + 1; j <= n; j++)
			ans = mul (ans + (g[i][j]?1:0));
	std::cout << ans << "\n";
}
/*
abbabbbab
*/
