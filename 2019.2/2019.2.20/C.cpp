#include<bits/stdc++.h>
#define N 1000005
int n, A[N], B[N], b[N], tot, f[N], cnt[N], ans;
int find (int x) { return f[x] == x ? f[x] : f[x] = find (f[x]); }
int getid (int x)
{
	return std::lower_bound (b + 1, b + 1 + n, x) - b;
}
int main ()
{
	freopen ("banzhuan.in", "r", stdin);
	freopen ("banzhuan.out", "w", stdout);
	scanf ("%d", &n);
	for (int i = 1; i <= n; i++) scanf ("%d", &A[i]), B[i] = b[i] = A[i];
	std::sort (b + 1, b + 1 + n);
	tot = std::unique (b + 1, b + 1 + n) - b - 1;
	std::sort (B + 1, B + 1 + n);
	for (int i = 1; i <= tot; i++) f[i] = i;
	for (int i = 1; i <= n; i++) if(A[i]^B[i])
	{
		ans++, cnt[getid (B[i])]++;
		int fx = find (getid (A[i])), fy = find (getid (B[i]));
		if (fx != fy) f[fx] = fy;
	}
	for (int i = 1; i <= tot; i++)
		if (f[i] ^ i) cnt[find (i)] = std::max (cnt[find (i)], cnt[i]);
	for (int i = 1; i <= tot; ++i) 
		if (f[i] == i) ans -= cnt[i];
	std::cout << ans << "\n";
}
