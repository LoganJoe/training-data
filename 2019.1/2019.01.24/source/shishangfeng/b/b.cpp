#include <bits/stdc++.h>
using namespace std;
const int Mod = 998244353;
const int MAXN = 1e5 + 7;
typedef long long ll;
inline int R() { int rt; scanf ( "%d", &rt ); return rt; }
inline int Mop ( int na ) { return na >= Mod ? na - Mod : na; }

int n, q;

namespace BF
{
	struct Edge
	{
		int to, nxt, w;
	}o[MAXN << 1];
	int nu = 1;
	
	struct Node
	{
		int fe;
	}a[MAXN];
	
	void Addedge ( int fm, int de, int nw )
	{
		o[++nu].to = de, o[nu].w = nw, o[nu].nxt = a[fm].fe, a[fm].fe = nu;
		swap ( fm, de );
		o[++nu].to = de, o[nu].w = nw, o[nu].nxt = a[fm].fe, a[fm].fe = nu;
	}

	int ans;
	bool u[MAXN];
	void Dfs ( int nf, int nw )
	{
		u[nf] = true, ++ans;
		for ( int ne = a[nf].fe; ne; ne = o[ne].nxt )
		{
			if ( u[o[ne].to] || nw && o[ne].w == 3 )
				continue;
			Dfs ( o[ne].to, ( o[ne].w == 2 || o[ne].w == 3 ) ? 1 : nw );
		}
	}

	void main()
	{
		for ( int i = 1; i < n; ++i )
		{
			int u = R(), v = R(), w = R();
			Addedge ( u, v, w );
		}
		for ( ; q; --q )
		{
			int x = R() ^ ans, w = R() ^ ans, s = R() ^ ans, t = R() ^ ans;
			o[x << 1].w = w, o[x << 1 | 1].w = w;
			ans = 0;
			for ( int i = 1; i <= n; ++i )
				u[i] = false;
			Dfs ( s, 0 );
			printf ( "%d %d\n", ans, u[t] );
		}
	}
}

namespace Chain
{
	set<int> pos[5];
	int w[MAXN];

	void main()
	{
		for ( int i = 1; i < n; ++i )
		{
			R(), R(), w[i] = R();
			pos[w[i]].insert ( i );
		}
		pos[2].insert ( 0 ), pos[2].insert ( n + 1 );
		pos[3].insert ( 0 ), pos[3].insert ( n + 1 );
		pos[3].insert ( -1 ), pos[3].insert ( n + 2 );
		int ans = 0;
		for ( ; q; --q )
		{
			int x = R() ^ ans, nw = R() ^ ans, s = R() ^ ans, t = R() ^ ans;
			pos[w[x]].erase ( x );
			w[x] = nw;
			pos[w[x]].insert ( x );
			int l = 1, r = n;
			set<int>::iterator r2 = pos[2].lower_bound ( s );
			r2 = pos[3].upper_bound ( *r2 );
			r = min ( r, *r2 );
			set<int>::iterator r3 = pos[3].lower_bound ( s );
			r3 = pos[3].upper_bound ( *r3 );
			r = min ( r, *r3 );
			set<int>::iterator l2 = pos[2].lower_bound ( s );
			--l2, l2 = pos[3].lower_bound ( *l2 ), --l2;
			l = max ( l, *l2 + 1 );
			set<int>::iterator l3 = pos[3].lower_bound ( s );
			--l3, l3 = pos[3].lower_bound ( *l3 ), --l3;
			l = max ( l, *l3 + 1 );
			ans = r - l + 1;
			printf ( "%d %d\n", ans, ( t >= l && t <= r ) ? 1 : 0 );
		}
	}
}

int main()
{
	n = R(), q = R();
	if ( n <= 1000 && q <= 1000 )
		BF::main();
	else
		Chain::main();
	return 0;
}
