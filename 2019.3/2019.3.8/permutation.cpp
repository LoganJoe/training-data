#include<bits/stdc++.h>
const int N = 500005, mod = 998244353, g1 = 3, g2 = 332748118;
#define vet std::vector<int>
#define ll long long
int n, a, b, fac[N], inv[N];
ll Pow (ll x, ll k)
{
	ll t = 1;
	for (; k; k >>= 1, x = x * x%mod) if (k & 1) t = t * x % mod;
	return t;
}
int mul (int x) { return x >= mod ? x - mod : x; }
class NTT
{
	int invn, len, clc, rev[N];
	void process (int L)
	{
		for (len = 1, clc = 0; len < L; len <<= 1, clc++); invn = Pow (len, mod - 2);
		for (int i = 0; i < len; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << clc - 1);
	}
	void transform (int *s, int op)
	{
		for (int i = 0; i < len; i++) if (i < rev[i]) std::swap (s[i], s[rev[i]]);
		for (int i = 1; i < len; i <<= 1)
		{
			int wn = Pow (op > 0 ? g1 : g2, (mod - 1) / (i << 1));
			for (int j = 0; j < len; j += i << 1)
				for (int k = 0, w = 1; k < i; k++, w = 1ll * w*wn%mod)
				{
					int A = s[j + k], B = 1ll * s[i + j + k] * w%mod;
					s[j + k] = (A + B) % mod, s[i + j + k] = (A - B + mod) % mod;
				}
		}
		if (op < 0)for (int i = 0; i < len; i++) s[i] = 1ll * s[i] * invn%mod;
	}
	int tp1[N], tp2[N];
public:
	void times (int *a, int *b, int *c, int L)
	{
		process (L << 1);
		for (int i = L; i < len; i++) a[i] = b[i] = 0;
		transform (a, 1), transform (b, 1);
		for (int i = 0; i < len; i++) c[i] = 1ll * a[i] * b[i] % mod;
		transform (c, -1);
	}
}F;
int C (int a, int b)
{
	if (a < b || a < 0 || b < 0) return 0;
	return 1ll * fac[a] * inv[b] % mod * inv[a - b] % mod;
}
int A[N], B[N], f[N], g[N];
void getStrling (int n)
{
	if (n < 1) return (void)(f[0] = 1);
	if (n == 1) return (void)(f[1] = 1);
	int mid = n >> 1; getStrling (mid);
	for (int i = 0; i <= mid; i++) A[mid - i] = 1ll * f[i] * fac[i] % mod;
	for (int i = 0; i <= mid; i++) B[i] = 1ll * Pow (mid, i) * inv[i] % mod;
	F.times (A, B, A, mid + 1);
	for (int i = 0; i <= mid; i++) g[i] = 1ll * A[mid - i] * inv[i] % mod;
	F.times (f, g, f, mid + 1);
	if (n & 1)
		for (int i = n; i >= 1; i--) f[i] = mul (f[i - 1] + 1ll * f[i] * (n - 1) % mod);
}
int main ()
{
	freopen("permutation.in","r",stdin);
	freopen("permutation.out","w",stdout);
	scanf ("%d%d%d", &n, &a, &b);
	if (a == 0 || b == 0) return puts ("0"), 0;
	fac[0] = inv[0] = inv[1] = 1;
	for (int i = 1; i < N; i++) fac[i] = 1ll * fac[i - 1] * i%mod;
	for (int i = 2; i < N; i++) inv[i] = 1ll * (mod - mod / i)*inv[mod%i] % mod;
	for (int i = 2; i < N; i++) inv[i] = 1ll * inv[i - 1] * inv[i] % mod;
	getStrling (n - 1);
	int Strling = a + b - 2 < n ? f[a + b - 2] : 0;
	printf ("%d\n", 1ll * Strling * C (a + b - 2, a - 1) % mod);
}
/*
8 4 4
*/
