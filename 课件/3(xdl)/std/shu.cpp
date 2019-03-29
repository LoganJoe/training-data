# include <cstring>
# include <cstdio>
# include <algorithm>
# include <vector>
# include <string>
# include <set>
# include <map>
# include <cmath>
using namespace std;

# define REP( i, n ) for ( int i = 1; i <= n; i ++ )
# define REP_0( i, n ) for ( int i = 0; i < n; i ++ )
# define REP_0N( i, n ) for ( int i = 0; i <= n; i ++ )
# define REP_S( i, ss ) for ( char *i = ss; *i; i ++ )
# define REP_G( i, u ) for ( int i = pos[ u ]; i; i = g[ i ].frt )
# define FOR( i, a, b ) for ( int i = a; i <= b; i ++ )
# define DWN( i, a, b ) for ( int i = b; i >= a; i -- )
# define RST( a ) memset ( a, 0, sizeof ( a ) )
# define CLR( a, x ) memset ( a, x, sizeof ( a ) )
# define CPY( a, b ) memcpy ( a, b, sizeof ( a ) )
typedef long long LL;
const int inf = 1 << 30;

# define MOD 1000000003
# define NS 500010
int s[ NS ], sa[ NS ], ht[ NS ], st[ 33 ][ NS ], t1[ NS ], t2[ NS ], c[ NS ], lst[ NS ], f[ NS ], rk[ NS ], dst[ NS ], g[ NS ];
int l;
char str[ NS ];

inline void RlxX ( int &x, int y ) { if ( x < y ) x = y; }
int LCP ( int l, int r )
{
	l = rk[ l - 1 ], r = rk[ r - 1 ];
	if ( l > r ) swap ( l, r );
	l ++;
	int k = int ( log2 ( r - l + 1 ) );
	return min ( st[ k ][ l ], st[ k ][ r - ( 1 << k ) + 1 ] );
}
bool Cmp ( int a, int b, int c, int d )
{
	a = lst[ a ], c = lst[ c ];
	if ( a > l ) return false;
	if ( c > l ) return true;
	if ( b - a != d - c ) return b - a < d - c;
	int tl = LCP ( a, c );
	if ( tl >= b - a + 1 ) return false;
	return s[ a + tl ] < s[ c + tl ];
}
void BSA ( int *s, int n, int m )
{
	int *x = t1, *y = t2;
	REP_0 ( i, m ) c[ i ] = 0;
	REP_0 ( i, n ) c[ x[ i ] = s[ i ] ] ++;
	REP ( i, m - 1 ) c[ i ] += c[ i - 1 ];
	DWN ( i, 0, n - 1 ) sa[ -- c[ x [ i ] ] ] = i;
	for ( int j = 1; j <= n; j <<= 1 )
	{
		int p = 0;
		FOR ( i, n - j, n - 1 ) y[ p ++ ] = i;
		REP_0 ( i, n ) if ( sa[ i ] >= j ) y[ p ++ ] = sa[ i ] - j;
		REP_0 ( i, m ) c[ i ] = 0;
		REP_0 ( i, n ) c[ x[ y[ i ] ] ] ++;
		REP ( i, m - 1 ) c[ i ] += c[ i - 1 ];
		DWN ( i, 0, n - 1 ) sa[ -- c[ x[ y[ i ] ] ] ] = y[ i ];
		swap ( x, y );
		p = 1, x[ sa[ 0 ] ] = 0;
		REP ( i, n - 1 ) x[ sa[ i ] ] = y[ sa[ i - 1 ] ] == y[ sa[ i ] ] && y[ sa[ i - 1 ] + j ] == y[ sa[ i ] + j ] ? p - 1 : p ++;
		if ( p >= n ) break;
		m = p;
	}
}
void BH ( int *s, int n )
{
	REP_0N ( i, n ) rk[ sa[ i ] ] = i;
	int k = 0;
	REP_0 ( i, n )
	{
		if ( k ) k --;
		int j = sa[ rk[ i ] - 1 ];
		while ( s[ i + k ] == s[ j + k ] ) k ++;
		ht[ rk[ i ] ] = k;
	}
	int blen = 0;
	while ( ( 1 << blen ) < n ) blen ++;
	REP ( i, n ) st[ 0 ][ i ] = ht[ i ];
	REP ( i, blen ) REP ( j, n ) st[ i ][ j ] = min ( st[ i - 1 ][ j ], st[ i - 1 ][ j + ( 1 << ( i - 1 ) ) ] );
}
int main ()
{
	freopen ( "shu.in", "r", stdin );
	freopen ( "shu.out", "w", stdout );
	scanf ( "%s", str + 1 ), l = strlen ( str + 1 );
	REP ( i, l ) s[ i ] = str[ i ] - '0' + 1;
	BSA ( s + 1, l + 1, 12 ), BH ( s + 1, l ), f[ 1 ] = 1;
	REP ( i, l ) s[ i ] --;
	int lnz = l + 1, dnz = 0;
	DWN ( i, 1, l )
	{
		if ( s[ i ] ) lnz = i;
		lst[ i ] = lnz;
	}
	REP ( i, l )
	{
		dst[ i ] = dnz;
		if ( s[ i ] ) dnz = i;
	}
	f[ 1 ] = 1;
	REP ( i, l - 1 )
	{
		RlxX ( f[ i + 1 ], f[ i ] );
		int ml = lst[ i + 1 ] + i - lst[ f[ i ] ];
		if ( ml < l )
		{
			if ( Cmp ( f[ i ], i, i + 1, ml ) ) RlxX ( f[ ml ], i + 1 );
			else RlxX ( f[ ml + 1 ], i + 1 );
		}
		else if ( ml == l && Cmp ( f[ i ], i, i + 1, ml ) ) RlxX ( f[ l ], i + 1 );
	}


	int lb = dst[ f[ l ] ] + 1;
	FOR ( i, lb, f[ l ] ) g[ i ] = l;
	DWN ( i, 1, f[ l ] )
	{
		int ml = max ( i - 1 - g[ i ] + lst[ i ], 1 );
		if ( Cmp ( ml, i - 1, i, g[ i ] ) ) ml = dst[ ml ] + 1;
		else ml ++;
		while ( lb > ml ) g[ -- lb ] = i - 1;
	}
	int p = 1;
	while ( p <= l )
	{
		int i = p;
		for ( ; i <= g[ p ] && !s[ i ]; i ++ );
		for ( ; i <= g[ p ]; i ++ ) putchar ( s[ i ] + '0' );
		p = g[ p ] + 1, putchar ( ' ' );
	}
	putchar ( '\n' );
	return 0;
}
