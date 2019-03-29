#include <bits/stdc++.h>
#define ll long long
#define N 1000005

int T, type;
ll a, b, n, m;
int pri[N], vis[N], cnt, tot[N];
void solve1 ()
{
	int equal = 1ll * a % m * b % m, res = -1;
	for (int i = 0; i < m; i++) if (1ll * i*i%m == equal) { res = i; break; }
	if (res == -1) puts ("dlllhhha");
	else printf ("%d\n", res);
}
ll cal (ll x, ll p) { return x >= p ? x - p : x; }
ll mul (ll x, ll k, ll p)
{
	ll t = 1; 
	for (; k; k >>= 1, x = cal (x + x, p)) if (k & 1) t = cal(t + x, p);
	return t;
}
ll Pow (ll x, ll k, ll p)
{
	ll t = 1;
	for (; k; k >>= 1, x = x * x % p) if (k & 1) t = t * x % p;
	return t;
}
void init ()
{
	for (int i = 2; i < N; i++)
	{
		if (!vis[i]) pri[++cnt] = i;
		for (int j = 1; j <= cnt && i*pri[j] < N; i++)
		{
			vis[i*pri[j]] = 1;
			if (i&pri[j] == 0) break;
		}
	}
}
void deliv (ll x,int opt)
{
	for (int i = 1; i < N && x != 1; i++)
		while (x%pri[i] == 0) x /= pri[i], tot[i] += opt;
}
void solve2 ()
{
	deliv (a, 1), deliv (b, 1);


	deliv (a, -1), deliv (b, -1);
}
int main ()
{
	freopen("math.in","r",stdin);
	freopen("math.out","w",stdout);
	scanf ("%d%d", &T, &type);	
	if (type >= 3) init ();
	while (T--)
	{
		scanf ("%lld%lld%lld%lld", &a, &b, &n, &m);
		if (type >= 3) solve1 ();
		else solve2 ();
	}
}
/*
2 0
299 299 1 300
2 8 9 513

*/
