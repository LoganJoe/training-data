#include<bits/stdc++.h>

#define ll long long
#define N 200005
#define mod 998244353

ll Pow (ll x, ll k) 
{
	ll t = 1;
	for (; k; k >>= 1, x = x * x%mod) 
		if (k & 1) t = t * x%mod; 
	return t; 
}
int mul (int x) { return x >= mod ? x - mod : x; }

int n, m, A[N], f[N], g[N], fac[N], inv[N];

class NTT
{
public:
	int rev[N], len, clc, g1 = 3, g2 = 332748118, invn;
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
				for (int k = 0, w = 1; k < i; k++, w = 1ll * w * wn%mod)
				{
					int A = s[j + k], B = 1ll * s[i + j + k] * w%mod;
					s[j + k] = mul (A + B), s[i + j + k] = mul (A - B + mod);
				}
		}
		if (op < 0) for (int i = 0; i < len; i++) s[i] = 1ll * s[i] * invn % mod;
	}
	void times (int *a, int *b,int *c,int L)
	{
		process (L << 1);
		for (int i = L; i < len; i++) a[i] = b[i] = 0;
		transform (a, 1), transform (b, 1);
		for (int i = 0; i < len; i++) c[i] = 1ll * a[i] * b[i] % mod;
		transform (c, -1);
		for (int i = L; i < len; i++) c[i] = 0;
	}
	std::vector<int> times (std::vector<int> a, std::vector<int> b)
	{
		process (a.size () + b.size () - 1);
		int lena = a.size (), lenb = b.size ();
		static int x[N], y[N];
		for (int i = 0; i < len; i++) 
			x[i] = i < lena ? a[i] : 0, y[i] = i < lenb ? b[i] : 0;
		times (x, y, x, lena + lenb - 1);
		return std::vector <int> (x, x + lena + lenb - 1);
	}
}F;
void getInv (int *a, int *b, int len)
{
	if (len == 1) return (void)(b[0] = Pow (a[0], mod - 2));
	getInv (a, b, len + 1 >> 1);
	static int tp[N];
	F.process (len << 1);
	for (int i = 0; i < F.len; i++) tp[i] = i < len ? a[i] : 0, b[i] = i < (len+1>>1) ? b[i] : 0;
	F.transform (tp, 1), F.transform (b, 1);
	for (int i = 0; i < F.len; i++) tp[i] = 1ll * b[i] * mul (2 - 1ll * tp[i] * b[i] % mod + mod) % mod;
	F.transform (tp, -1);
	for (int i = 0; i < F.len; i++) b[i] = i < len ? tp[i] : 0;
}
void getDer (int *a, int *b, int len)
{
	for (int i = 0; i < len; i++)
		b[i] = 1ll * a[i + 1] * (i + 1) % mod;
}
void getInt (int *a, int *b, int len)
{
	for (int i = 1; i <= len; i++) 
		b[i] = 1ll * a[i - 1] * Pow (i, mod - 2) % mod;
}
void getLn (int *a, int *b, int len)
{
	static int Der[N], Inv[N];
	for (int i = 0; i < len << 1; i++) Der[i] = Inv[i] = 0;
	getDer (a, Der, len), getInv (a, Inv, len);
	F.times (Der, Inv, Inv, len), getInt (Inv, b, len);
	for (int i = len; i < F.len; i++) b[i] = 0;
}
void getExp (int *a, int *b, int len)
{
	if (len == 1) return (void)(b[0] = 1);
	getExp (a, b, len + 1 >> 1);
	static int tp[N];
	for (int i = 0; i < len << 1; i++) tp[i] = 0;
	getLn (b, tp, len);
	for (int i = 0; i < F.len; i++) tp[i] = i < len ? mul (a[i] + (!i) - tp[i] + mod) : 0;
	F.times (b, tp, tp, len);
	for (int i = 0; i < F.len; i++) b[i] = i < len ? tp[i] : 0;
}
void getsqr (int *a, int *b, int len)
{
	if (len == 1) return (void)(b[0] = sqrt (a[0]));
	getsqr (a, b, len + 1 >> 1);
	static int tp[N], tx[N];
	for (int i = 0; i < len; i++) tx[i] = a[i], tp[i] = 0;
	getInv (b, tp, len);
	F.process (len << 1);
	F.transform (tp, 1); F.transform (tx, 1);
	for (int i = 0; i < F.len; i++) tp[i] = 1ll * tp[i] * tx[i] % mod;
	F.transform (tp, -1);
	for (int i = 0; i < len; i++) b[i] = 1ll * mul (b[i] + tp[i]) * (mod + 1 >> 1) % mod;
	for (int i = 0; i < F.len; i++) tp[i] = 0;
}
std::vector <int> Mul (std::vector <std::vector <int> > &x, int l, int r)
{
	if (l == r - 1) return x[l];
	int mid = l + r >> 1;
	std::vector<int> L = Mul (x, l, mid), R = Mul (x, mid, r);
	return F.times (L, R);
}
std::vector <std::vector <int> > P;
int invg[N], invp[N], tp[N];
int main ()
{
	scanf ("%d%d", &n, &m);
	fac[0] = inv[0] = inv[1] = 1;
	for (int i = 1; i <= m + 1; i++) fac[i] = 1ll * fac[i - 1] * i % mod;
	for (int i = 2; i <= m + 1; i++) inv[i] = 1ll * (mod - mod / i) * inv[mod%i] % mod;
	for (int i = 2; i <= m + 1; i++) inv[i] = 1ll * inv[i - 1] * inv[i] % mod;
	for (int i = 1; i <= n; i++)
	{
		scanf ("%d", &A[i]);
		P.push_back (std::vector <int> {1, mod - A[i]});
	}
	std::vector<int> res = Mul (P, 0, P.size ());
	while (res.size () < m + 1) res.push_back (0);
	for (int i = 0; i < m + 1; i++) f[i] = g[i] = res[i];
	getInv (g, invg, m + 1);
	for (int i = 0; i <= n; i++) f[i] = 1ll * f[i] * (n - i) % mod;
	F.times (f, invg, f, m + 1);
	for (int i = 0; i <= m; i++) invp[i] = inv[i + 1];
	getLn (invp, tp, m + 1);
	for (int i = 0; i <= m; i++) tp[i] = 1ll * tp[i] * f[i] % mod;
	memset (f, 0, sizeof (f));
	getExp (tp, f, m + 1);
	std::cout << 1ll * f[m] * fac[m] % mod << "\n";
}
/*
3 3
1 2 3
*/
