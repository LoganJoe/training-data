#include<bits/stdc++.h>
#define N 35
int n, m, mod, ans, A[N], B[N], p[N];
void dfs (int x, int num)
{
	if (x > m)
	{
		for (int i = 1; i < n - i + 1; i++) p[n - i + 1] = -p[i];
		for (int i = n; i >= 1; i--) if (i && p[i] < 0) p[i] += 10, p[i - 1]--;
		for (int i = 1; i <= n; i++) A[i] = B[i] = p[i];
		std::sort (A + 1, A + 1 + n);
		std::sort (B + 1, B + 1 + n);
		std::reverse (B + 1, B + 1 + n); 
		for (int i = n; i >= 1; i--)
		{
			B[i] -= A[i];
			if (B[i] < 0) B[i] += 10, B[i - 1]--;
			if (B[i] != p[i]) return;
		}
		long long res = 0;
		for (int i = 1; i <= n; i++) res = (res * 10 + B[i]);
		res %= mod; ans = (ans + 1ll * res * res) % mod;
		return;
	}
	for (int i = num; ~i; i--) p[x] = i, dfs (x + 1, i);
}
int main ()
{
	freopen ("clever.in", "r", stdin);
	freopen ("clever.out", "w", stdout);
	scanf ("%d%d", &n, &mod), m = (n + 1) >> 1;
	dfs (1, 9);
	std::cout << ans << "\n";
}
/*
30 998244353
*/
