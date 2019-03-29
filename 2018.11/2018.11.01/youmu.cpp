#include<bits/stdc++.h>
#define N 500005
#define mod 998244353
#define ll long long
int T, n, f[N];
int mul (int x) { return x >= mod ? x - mod : x; }
int Pow (int x, int k) { int t = 1; for (; k; k >>= 1, x = 1ll * x*x%mod) if (k & 1)t = 1ll * t * x % mod; return t; }
int main ()
{
	freopen("youmu.in","r",stdin);
	freopen("youmu.out","w",stdout);
	f[0] = f[1] = 1;
	for (int i = 2; i < N; i++) f[i] = mul (f[i - 1] + 1ll * f[i - 2] * (i - 1) % mod);
	for (scanf ("%d", &T); T--;)
	{
		scanf ("%d", &n);
		int total = Pow (n, n);
		total = Pow (total, mod - 2);
		printf ("%d\n", 1ll * f[n] * total%mod);
	}
}
