#include<bits/stdc++.h>
#define ll long long
#define N 10
#define mod 990804011
int T, n;
ll l[N], r[N], tot = 1, ans;
namespace solve1
{
	ll A[N];
	bool C (ll a, ll b) { return (a & b) == b; }
	void check ()
	{
		ll tot = 0, res = 1;
		for (int i = 1; i <= n; i++) tot += A[i] - 1;
		for (int i = 1; i <= n; i++) res = res * C (tot, A[i] - 1), tot -= A[i] - 1;
		ans = (ans + res) % mod;
	}
	void dfs (int x)
	{
		if (x > n) return check ();
		for (ll i = l[x]; i <= r[x]; i++) A[x] = i, dfs (x + 1);
	}
	void Main () { dfs (1); }
}
namespace solve2
{
	void Main ()
	{
		
	}
}
int main ()
{
	for (scanf ("%d", &T); T--; tot = 1, ans = 0)
	{
		scanf ("%d", &n);
		for (int i = 1; i <= n; i++) 
			std::cin >> l[i] >> r[i], tot = 1ll * tot * (r[i] - l[i] + 1);
			printf("%d\n",tot);
		if (n == 1) { ans = tot % mod; goto END; }
		if (tot <= 1e6) solve1::Main ();
		else solve2::Main ();
	END:
		std::cout << ans << "\n";
	}
}
