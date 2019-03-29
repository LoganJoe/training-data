#include<bits/stdc++.h>
#define N 5000
#define ll long long
int n, a[N], fac[N];
ll ans;
void dfs (int x, int cnt)
{
	if (x == n) return (void) (ans += fac[cnt]);
	int len = 1 << x, pos[3] = { 0,0,0 };
	for (int i = 1; i <= 1 << n; i += 2 * len)
	{
		if (a[i] + len != a[i + len] && pos[0] == 2)  return;
		if (a[i] + len != a[i + len]) pos[++pos[0]] = i;
	}
	if (pos[0] == 0) dfs (x + 1, cnt);
	if (pos[0] == 1)
	{
		std::swap (a[pos[1]], a[pos[1] + len]);
		if (a[pos[1]] + len == a[pos[1] + len]) dfs (x + 1, cnt + 1);
		std::swap (a[pos[1]], a[pos[1] + len]);
	}
	if (pos[0] == 2)
	{
		std::swap (a[pos[1]], a[pos[2]]);
		if (a[pos[1]] + len == a[pos[1] + len] && a[pos[2]] + len == a[pos[2] + len]) dfs (x + 1, cnt + 1);
		std::swap (a[pos[1]], a[pos[2]]);
		std::swap (a[pos[1] + len], a[pos[2]]);
		if (a[pos[1]] + len == a[pos[1] + len] && a[pos[2]] + len == a[pos[2] + len]) dfs (x + 1, cnt + 1);
		std::swap (a[pos[1] + len], a[pos[2]]);
		std::swap (a[pos[1]], a[pos[2] + len]);
		if (a[pos[1]] + len == a[pos[1] + len] && a[pos[2]] + len == a[pos[2] + len]) dfs (x + 1, cnt + 1);
		std::swap (a[pos[1]], a[pos[2] + len]);
		std::swap (a[pos[1] + len], a[pos[2] + len]);
		if (a[pos[1]] + len == a[pos[1] + len] && a[pos[2]] + len == a[pos[2] + len]) dfs (x + 1, cnt + 1);
		std::swap (a[pos[1] + len], a[pos[2] + len]);
	}
}
int main ()
{
	freopen("sort.in","r",stdin);
	freopen("sort.out","w",stdout);
	scanf ("%d", &n);
	for (int i = 1; i <= 1 << n; i++) scanf ("%d", &a[i]);
	fac[0] = 1; for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i;
	dfs (0, 0);
	std::cout << ans << "\n";
}
