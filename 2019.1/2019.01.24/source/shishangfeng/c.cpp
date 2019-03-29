#include <bits/stdc++.h>
using namespace std;
const int Mod = 998244353;
const int MAXN = 1e5 + 7;
typedef long long ll;
inline int R() { int rt; scanf ( "%d", &rt ); return rt; }
inline int Mop ( int na ) { return na >= Mod ? na - Mod : na; }

int s[MAXN][2];
int val[MAXN];

int main()
{
	for ( int T = R(); T; --T )
	{
		int n = R();
		for ( int i = 1; i <= n; ++i )
		{
			val[i] = R();
			if ( val[i] == -1 )
				s[i][0] = R(), s[i][1] = R();
		}
		int op = 1;
		for ( int i = n; i; --i )
		{
			if ( val[i] == -1 )
			{
				if ( op == 1 )
					val[i] = max ( val[s[i][0]], val[s[i][1]] );
				else
					val[i] = min ( val[s[i][0]], val[s[i][1]] );
				op ^= 1;
			}
		}
		printf ( "%d\n", val[1] );
	}
	return 0;
}
