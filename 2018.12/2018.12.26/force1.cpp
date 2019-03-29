#include <bits/stdc++.h>
#define rep(a, b, c) for(int a(b); a <= (c); a++)
#define dec(a, b, c) for(int a(b); a >= (c); a--)
using namespace std;
typedef long long ll;
typedef pair<ll, int> P;
const int INF = 0x3f3f3f3f;
const int MAX_N = 100005;

int N, K;
int k[20], S[20];
vector<int> s[20];

namespace subtask1 {
	ll dis[105][105];
	ll ans;

	void solve () {
		memset (dis, 0x3f, sizeof (dis));
		rep (i, 1, K)
			for (auto j : s[i])
				for (auto l : s[i])
					dis[j][l] = dis[l][j] = k[i];
		rep (i, 1, N)
			dis[i][i] = 0;
		rep (l, 1, N)
			rep (i, 1, N)
			rep (j, 1, N)
			dis[i][j] = min (dis[i][j], dis[i][l] + dis[l][j]);
		rep (i, 1, N)
			rep (j, i + 1, N)
			ans += dis[i][j];
		printf ("%lld\n", ans);
	}
}

namespace subtask2and3 {
	struct node { ll size, val, state; };
	struct edge { ll to, wt; };

	vector<edge> G[1 << 12];
	node v[1 << 12];
	ll id[1 << 12], belong[MAX_N], dis[1 << 12][1 << 12];
	int vCnt;
	ll ans,QAQ;

	ll C (ll n, int m) { return m == 2 ? n * (n - 1) / 2 : 0; }
	ll getWeight (int state) {
		int res = INF;
		rep (i, 1, K)
			if (state & (1 << (i - 1)))
				res = min (res, k[i]);
		return res;
	}
	void solve () {
		rep (i, 1, K)
			for (auto j : s[i])
				belong[j] |= (1 << (i - 1));
		rep (i, 1, N)
			if (id[belong[i]] == 0) {
				id[belong[i]] = ++vCnt;
				v[vCnt].size = 1;
				v[vCnt].val = getWeight (belong[i]);
				v[vCnt].state = belong[i];
			}
			else
				v[id[belong[i]]].size++;
		rep (i, 1, vCnt)
			ans += C (v[i].size, 2) * v[i].val;

		rep (i, 1, vCnt)
			rep (j, i + 1, vCnt)
			if (v[i].state & v[j].state) {
				int edgeWeight = getWeight (v[i].state & v[j].state);
				G[i].push_back ( { j, edgeWeight });
				G[j].push_back ( { i, edgeWeight });
			}
		memset (dis, 0x3f, sizeof (dis));
		rep (src, 1, vCnt) {
			priority_queue< P, vector<P>, greater<P> > q;
			dis[src][src] = 0;
			rep (i, 1, src - 1)
				dis[src][i] = dis[i][src];
			rep (i, 1, src)
				q.push (P (dis[src][i], i));
			while (!q.empty ()) {
				int u = q.top ().second;
				ll d = q.top ().first;
				q.pop ();
				if (d != dis[src][u])
					continue;
				for (auto e : G[u])
					if (QAQ++, dis[src][e.to] > dis[src][u] + e.wt) {
						dis[src][e.to] = dis[src][u] + e.wt;
						q.push (P (dis[src][e.to], e.to));
						
					}
				
			}
		}
		std::cerr<<QAQ<<"\n";
		rep (i, 1, vCnt)
			rep (j, i + 1, vCnt)
			ans += dis[i][j] * v[i].size * v[j].size;
		printf ("%lld\n", ans);
	}
}

int main () {
	freopen ("dist0.in", "r", stdin);
	freopen ("dist0.out", "w", stdout);

	scanf ("%d%d", &N, &K);
	rep (i, 1, K) {
		scanf ("%d%d", &k[i], &S[i]);
		rep (j, 1, S[i]) {
			int temp;
			scanf ("%d", &temp);
			s[i].push_back (temp);
		}
	}

	if (N <= 100)
		subtask1::solve ();
	else if (K <= 10)
		subtask2and3::solve ();
	return 0;
}
