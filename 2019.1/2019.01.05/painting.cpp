#include<bits/stdc++.h>
#define N 100005
#define M 5005
int n, m, l[N], r[N], fst[N], f[M][M], sta[N], top, ans;
std::vector<int>t[N];
int main ()
{
	freopen ("painting.in", "r", stdin);
	freopen ("painting.out", "w", stdout);
	scanf ("%d%d", &n, &m);
	for (int i = 1, x; i <= n; i++)
	{
		scanf ("%d", &x);
		l[x] = l[x] ? std::min (l[x], i) : i;
		r[x] = r[x] ? std::max (r[x], i) : i;
		t[x].push_back (i);
	}
	for (int i = 1; i <= m; i++) fst[l[i]] = i;
	for (int i = 1; i <= n; i++) if (fst[i])
	{
		top = 0;
		for (int j = i; j <= n && fst[j];)
		{
			sta[++top] = r[fst[j]] - l[fst[j]] + 1;
			int t = fst[j]; fst[j] = 0, j = r[t] + 1;
		}
		for (int j = 1; j <= top; j++) sta[j] += sta[j - 1];
		for (int d = 1; d <= n; d++)
			for (int l = 1, r = l + d - 1; r <= n; r++)
				f[l][r] = std::max (f[l + 1][r], f[l][r - 1]) + sta[r] - sta[l - 1];
		ans += f[1][top];
	}
	std::cout << ans << "\n";
}


