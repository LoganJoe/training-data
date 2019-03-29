#include<bits/stdc++.h>
#define ll long long
#define N 1000005
int n, t[N]; ll A[N], f[N], ans;
std::vector<std::pair<int, ll> > s[N];
class BIT
{
	ll t[N];
public:
	void add (int x, ll v) { for (; x && x <= n; x += x & -x) t[x] = std::max (t[x], v); }
	ll ask (int x) { ll res = 0; for (; x > 0; x -= x & -x) res = std::max (t[x], res); return res; }
}T;
int main ()
{
	freopen ("fc.in", "r", stdin);
	freopen ("fc.out", "w", stdout);
	scanf ("%d", &n);
	for (int i = 1; i <= n; i++) scanf ("%d", &t[i]);
	for (int i = 1; i <= n; i++) scanf ("%d", &A[i]), A[i] = 1ll * A[i] * t[i];
	for (int i = 1; i <= n; i++)
	{
		for (int j = 0; j < s[i].size (); j++) T.add (s[i][j].first, s[i][j].second);
		f[i] = A[i] + T.ask (std::max (0, i - t[i]));
		if (i + t[i] <= n) s[i + t[i]].push_back (std::make_pair (i, f[i]));
		ans = std::max (ans, f[i]);
	}
	std::cout << ans << "\n";
}
