#include <bits/stdc++.h>
using namespace std;
const int Mod = 998244353;
typedef long long ll;
inline int R() { int rt; scanf ( "%d", &rt ); return rt; }
inline int Mop ( int na ) { return na >= Mod ? na - Mod : na; }

int dp[107][9][107];
inline ll Pow ( ll base, int t )
{
	ll rt = 1;
	for ( ; t; t >>= 1, base = base * base % Mod )
		if ( t & 1 )
			rt = rt * base % Mod;
	return rt;
}

int main()
{
	int n = R(), k = R();
	if ( n < k )
	{
		puts ( "0" );
		return 0;
	}
	dp[0][0][0] = 1;
	for ( int i = 1; i <= n; ++i )
		for ( int j = 0; j <= k; ++j )
			for ( int s = 0; s <= n; ++s )
			{
				dp[i][j][s] = Mop ( dp[i][j][s] + dp[i - 1][j][s] );
				if ( j && s - i >= 0 )
					dp[i][j][s] = Mop ( dp[i][j][s] + dp[i - 1][j - 1][s - i] );
			}
	for ( int i = 1; i <= n; ++i )
		for ( int j = 1; j <= k; ++j )
			for ( int s = 1; s <= n; ++s )
				dp[i][j][s] = Mop ( dp[i][j][s] + dp[i][j][s - 1] );
	ll ans = n;
	for ( int i = n - k + 1; i < n; ++i )
		ans = ans * i % Mod;
	for ( int i = 2; i <= k; ++i )
		ans = ans * Pow ( i, Mod - 2 ) % Mod;
	for ( int i = k; i <= n; ++i )
		ans = Mop ( ans + Mod - dp[i - 1][k - 1][i] );
	printf ( "%lld\n", ans );
	return 0;
}
