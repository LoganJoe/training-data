#include<bits/stdc++.h>
#define N 20000050
#define mod 998244353
int T, n, Limit, f[N];
int mul (int x) { return x >= mod ? x - mod : x; }
int main ()
{
	freopen ("mex.in", "r", stdin);
	freopen ("mex.out", "w", stdout);
	int Case; scanf ("%d", &Case);
	if (Case < 3) Limit = N / 10;
	else Limit = N;
	f[1] = 2;
	for (int n = 2; n < N; n++)
	{
		int x = sqrt (n), lst = x, tot = 1, sqr = x;
		if (x == n / x) x--;
		for (; x && n / x == lst + 1; lst = n / x, x--, tot++);
		f[n] = mul (f[n - 1] + sqr + tot);
		if (n >= 500000 && n <= 520000)std::cerr << n << " " << sqr + tot << "\n";
	}
	for (scanf ("%d", &T); T--;)
	{
		int l, r; scanf ("%d%d", &l, &r);
		printf ("%d\n", mul (f[r] - f[l - 1] + mod));
	}
}
