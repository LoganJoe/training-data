#include<bits/stdc++.h>
#define N 1000005
int n, A[N], f[5005][5005];
int solve (int l, int r)
{
	if (l >= r - 1) return A[l];
	if (f[l][r] != 0) return f[l][r];
	int Min = 1e9;
	for (int i = l; i < r; i++) Min = std::min (Min, std::max (solve (l, i), solve (i + 1, r)) + A[i]);
	return f[l][r] = Min;
}
char ch;
int main ()
{
	freopen ("binary.in", "r", stdin);
	freopen ("binary.out", "w", stdout);
	scanf ("%d", &n); getchar ();
	for (int i = 1; i <= n; i++)scanf ("%c", &ch), A[i] = ch - 48;
	std::cout << solve (1, n + 1) << "\n";
}
