#include<bits/stdc++.h>
#define N 3300010
#define ll long long
int mod, inv2, pri[N], vis[N], pcnt, cnt;
ll n, sum[N], lst[N << 1]; int h[N << 1][2], t1[N], t2[N];
ll Pow (ll x, ll k) { ll t = 1; for (; k; k >>= 1, x = x * x%mod) if (k & 1) t = t * x%mod; return t; }
inline int mul (int x) { return x >= mod ? x - mod : x; }
inline int Sum (ll x) { x %= mod; return 1ll * x * (x + 1) % mod * inv2 % mod; }
int mu[N];
void init ()
{
	mu[1] = 1;
	for (int i = 2; i < N; i++)
	{
		sum[i] = sum[i - 1];
		if (!vis[i]) pri[++pcnt] = i, sum[i] += i, mu[i] = -1;
		for (int j = 1; j <= pcnt && i*pri[j] < N; j++)
		{
			vis[i*pri[j]] = 1;
			if (i%pri[j] == 0) { mu[i*pri[j]] = 0; break; }
			mu[i*pri[j]] = -mu[i];
		}
	}
}
int H (ll x) { return x >= N ? h[t2[n / x]][0] : h[t1[x]][0]; }
ll g (ll n, ll m)
{
	if (n == 1 || pri[m] >= n) return 0;
	ll res = mul (H (n) - mul (sum[pri[m]] + m) + mod);
	if (1ll * pri[m] * pri[m] >= n) return res;
	for (int i = m + 1; 1ll * pri[i] * pri[i] <= n; i++)
		for (ll pe = pri[i], e = 1; pe <= n; pe *= pri[i], e++)
			res = (res + (pe + 1) * ((e > 1) + g (n / pe, i))) % mod;
	return res;
}
int SSum (ll x) { x %= mod; if (x < N) return sum[x]; return 1ll * x * (x + 1) % mod * inv2 % mod; }
void solve1 ()
{
	int Sqr = sqrt (n);
	int ans = 0;
	ll pre = 0, tot = 0;
	for (int i = 0; i < N; i++) sum[i] = 1ll * i*(i + 1) / 2 % mod;
	for (int d = 1; d <= Sqr; d++)
	{
		ll T = n / d / d, P = n / d, F;
		if (mu[d] == 0) continue;
		if (T == pre)
		{
			ans = mul (ans + 1ll * d * tot * mu[d] % mod);
			ans = mul (ans + mod);
			continue;
		}
		tot = 0;
		if (T == 0) break;
		for (ll i = 1, j; i <= P; i = j + 1)
		{
			if ((F = T / i) == 0) break;
			j = T / F;
			tot = mul (tot + 1ll * mul (SSum (j) - SSum (i - 1) + mod) * F % mod);
		}
		ans = mul (ans + 1ll * d * tot * mu[d] % mod);
		ans = mul (ans + mod); pre = T;
	}
	std::cout << ans % mod << "\n";
}
int main ()
{
	n = 10000000000000ll, mod = 1000000007;
	//std::cin >> n >> mod;
	inv2 = Pow (2, mod - 2);
	init ();
	if (n > 1e10) return solve1 (), 0;
	for (ll i = 1, j; i <= n; i = j + 1)
	{
		j = n / (n / i); ll t = n / i;
		lst[++cnt] = t; h[cnt][0] = (Sum (t) - 1 + mod) % mod, h[cnt][1] = (t - 1 + mod) % mod;
		t >= N ? t2[n / t] = cnt : t1[t] = cnt;
	}
	for (int i = 1; i <= pcnt; i++)
	{
		if (1ll * pri[i] * pri[i] > n) break;
		for (int j = 1; lst[j] >= 1ll * pri[i] * pri[i]; j++)
		{
			ll t = lst[j] / pri[i], id = t >= N ? t2[n / t] : t1[t];
			h[j][0] = mul (h[j][0] - 1ll * mul (h[id][0] - sum[pri[i - 1]] + mod) * pri[i] % mod + mod);
			h[j][1] = mul (h[j][1] - h[id][1] + (i - 1));
			h[j][1] = mul (h[j][1] + mod);
		}
	}
	for (int i = 1; i <= cnt; i++) h[i][0] = mul (h[i][0] + h[i][1]);
	std::cout << g (n, 0) + 1 << "\n";
}
/*
c
*/

