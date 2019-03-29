#include<bits/stdc++.h>
#define N 21
#define M (1<<20)
#define mod 1000000007
#define inv2 500000004
#define ll long long
int n, A[N][N], len, totS, D[M], Log[M], sz[M];
int f[N][M / 2], g[N][M / 2], h[N][M / 2];
//这题他妈的卡空间 
ll Pow (ll x, ll k)
{
	ll t = 1;
	for (; k; k >>= 1, x = x * x%mod) if (k & 1) t = t * x%mod;
	return t;
}
int mul(int x) { return x >= mod ? x - mod : x ; }
void FWT (int *s, int op)
{
	for (int i = 1; i < len; i <<= 1)
		for (int j = 0, p = i << 1; j < len; j += p)
			for (int k = 0; k < i; k++)
				if (op > 0)s[i + j + k] = (s[j + k] + s[i + j + k]) % mod;
				else s[i + j + k] = (s[i + j + k] + mod - s[j + k]) % mod;
}
int main ()
{
	freopen("union.in","r", stdin);
	freopen("union.out","w", stdout);
	scanf ("%d", &n); totS = (1 << n) - 1;
	for (int i = 2; i <= totS; i++) Log[i] = Log[i >> 1] + 1;
	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j++) scanf ("%d", &A[i][j]);
	D[0] = 1;
	for (int s = 1; s <= totS; s++)
	{
		int t = s & -s, x = Log[s & -s];
		D[s] = D[s ^ t];
		for (int i = 0; i < n; i++)
			if ((s^t) >> i & 1) D[s] = 1ll * D[s] * (A[x][i] + 1) % mod;
	}
	for (int s = 1; s <= totS; s++) sz[s] = sz[s >> 1] + (s & 1);
	len = 1 << (n - 1);
	for (int s = 0; s < len; s++)
		g[sz[s]][s] = D[s << 1], h[sz[s]][s] = D[s << 1 | 1];
	for (int i = 0; i < n; i++) FWT (g[i], 1), FWT (h[i], 1);
	for (int s = 0; s < len; s++)
	{
		int inv = pow (g[0][s], mod - 2);
		for (int i = 0; i < n; i++)
		{
			ll t = h[i][s];
			for (int j = 0; j < i; j++) t = (t - 1ll * f[j][s] * g[i - j][s] % mod + mod)%mod;
			f[i][s] = 1ll * t * inv % mod;
		}
	}
	FWT (f[n - 1], -1);
	printf ("%d\n", (f[n - 1][len - 1] + mod) % mod);
}
