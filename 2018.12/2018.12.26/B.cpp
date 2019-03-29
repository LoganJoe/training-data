#include<bits/stdc++.h>
#include<tr1/unordered_map>
#define N 100005
#define ll long long
int n, m; ll k, r, ar, br, s, as, bs; ll ans;
int QAQ;
std::tr1::unordered_map<int, int> mp[N];
std::vector<int> t[N];
ll sum (int x) { return 1ll * x*(x + 1) / 2; }
int main ()
{
	freopen("seat.in","r",stdin);
	freopen("seat.out","w",stdout);
	scanf ("%d%d%lld", &n, &m, &k);
	scanf ("%lld%lld%lld", &r, &ar, &br);
	scanf ("%lld%lld%lld", &s, &as, &bs);
	for (int i = 1; i <= k; i++)
	{
		if (mp[r][s]) break;
		mp[r][s] = 1; t[r].push_back (s);
		r = (ar*r + br) % n;
		s = (as*s + bs) % m;
	}
	for (int i = 0; i < n; i++)
		if (!t[i].size ()) ans += sum (m);
		else
		{
			std::sort (t[i].begin (), t[i].end ());
			for (int j = 1; j < t[i].size (); j++) ans += sum (t[i][j] - t[i][j - 1] - 1);
			ans += sum (t[i].front ()); ans += sum (m - t[i].back () - 1);
		}
	std::cout << ans << "\n";
}
