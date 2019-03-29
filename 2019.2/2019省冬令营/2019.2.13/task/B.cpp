#include<bits/stdc++.h>
#define ll long long
#define mod 1000000007
#define N 1005
int n, m, q;
std::set<int, std::greater<int> > S[N], choose[N];
ll Pow (ll x, ll k)
{
	ll t = 1;
	for (; k; k >>= 1, x = x * x%mod) if (k & 1) t = t * x%mod;
	return t;
}
int mul (int x) { return x >= mod ? x - mod : x; }
void calc ()
{
	int ans = 0;
	for (int i = 1; i <= n; i++) choose[i].clear ();
	for (int i = 1; i <= n; i++)
	{
		if (!S[i].size ()) return (void)puts ("-1");
		if (i == 1)
		{
			ans += Pow (2, m - *S[i].begin ());
			choose[i].insert (*S[i].begin ());
			continue;
		}

		int mark = -1;
		std::set<int>::iterator it = S[i].begin ();
		if (it != S[i].end () && *it > *choose[i - 1].begin ()) mark = *it;
		for (std::set<int>::iterator it = choose[i - 1].begin (); it != choose[i - 1].end (); it++)
		{
			if (S[i].find (*it) == S[i].end ()) mark = -1;
			std::set<int>::iterator tp = S[i].upper_bound (*it), nxt = it; nxt++;
			if (mark == -1 && tp != S[i].end ())
			{
				if (nxt != choose[i - 1].end () && *nxt == *tp) continue;
				else mark = *tp;
			}
		}
		if (mark == -1)
			return (void) puts ("-1");
		for (std::set<int>::reverse_iterator it = choose[i - 1].rbegin (); it != choose[i - 1].rend (); it++)
			if (*it < mark) ans = mul (Pow (2, m - *it) + ans), choose[i].insert (*it);
			else break;
		ans = mul (ans + Pow (2, m - mark)), choose[i].insert (mark);
	}
	printf ("%d\n", ans);
}
int main ()
{
	freopen ("price.in", "r", stdin);
	freopen ("price.out", "w", stdout);
	scanf ("%d%d%d", &n, &m, &q);
	while (q--)
	{
		int op; scanf ("%d", &op);
		if (op == 1)
		{
			int x, v; scanf ("%d%d", &x, &v);
			if (S[x].find (v) != S[x].end ()) S[x].erase (v);
			else S[x].insert (v);
		}
		else calc ();
	}
}
