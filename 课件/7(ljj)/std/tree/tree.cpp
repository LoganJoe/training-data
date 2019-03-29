#include <bits/stdc++.h>

#define pb push_back
#define getchar getchar_unlocked
#define For(i, j, k) for(int i = j; i <= k; i++)
#define Forr(i, j, k) for(int i = j; i >= k; i--)

using namespace std;

int Read() {
	int sig = 1; char c = getchar();
	while (c > '9' || c < '0') sig = c == '-' ? -1 : sig, c = getchar();
	int x = c - '0'; c = getchar();
	while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
	return x * sig;
}

typedef long long LL;

const int N = 3e5 + 10;

int A[N], val[N];

struct Segment_Tree{

	LL addv[N << 2], sum[N << 2];

	#define lc (o << 1)
	#define rc (o << 1 | 1)
	#define M ((L + R) >> 1)

	void build(int o, int L, int R) {
		if(L == R) sum[o] = val[L];
		else build(lc, L, M), build(rc, M + 1, R), sum[o] = sum[lc] + sum[rc];
	}

	void add(int o, int L, int R, int l, int r, LL w) {
		if(l <= L && R <= r) addv[o] += w, sum[o] += (R - L + 1) * w;
		else {
			sum[o] += w * (min(R, r) - max(L, l) + 1);
			if(l <= M) add(lc, L, M, l, r, w);
			if(r > M) add(rc, M + 1, R, l, r, w);
		}
	}

	LL query(int o, int L, int R, int l, int r) {
		if(l <= L && R <= r) return sum[o];
		else {
			LL ret = addv[o] * (min(R, r) - max(L, l) + 1);
			if(l <= M) ret += query(lc, L, M, l, r);
			if(r > M) ret += query(rc, M + 1, R, l, r);
			return ret;
		}
	}

}T;

vector<int> G[N];
int fa[N][20], dep[N];
int L[N], R[N], n;

void DFS_init(int o) {
	static int dfn = 0;
	L[o] = ++dfn;
	for (int v : G[o]) {
		if (v == fa[o][0]) continue;
		fa[v][0] = o;
		dep[v] = dep[o] + 1;
		For(i, 1, 18) fa[v][i] = fa[fa[v][i - 1]][i - 1];
		DFS_init(v);
	}
	R[o] = dfn;
}

int find(int u, int d) {
	for(int i = 18; i >= 0 && d; --i) if(d & (1 << i)) u = fa[u][i];
	return u;
}

int lca(int u, int v) {
	if (dep[u] < dep[v]) swap(u, v);
	u = find(u, dep[u] - dep[v]);
	if (u == v) return u;
	Forr(i, 18, 0) if (fa[u][i] ^ fa[v][i]) u = fa[u][i], v = fa[v][i];
	return fa[u][0];
}

int getch(int u, int f) {
	return find(u, dep[u] - dep[f] - 1);
}

int root = 1;

int main(){

	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);

	int q;
	n = Read(), q = Read();
	For(i, 1, n) A[i] = Read();
	For(i, 2, n) {
		int u = Read(), v = Read();
		G[u].pb(v), G[v].pb(u);
	}
	dep[1] = 1;
	DFS_init(1);
	For(i, 1, n) val[L[i]] = A[i];
	T.build(1, 1, n);

	while (q--) {
		int op = Read();

		if (op == 1) root = Read();
		else if(op == 2) {
			int u = Read(), v = Read(), w = Read();

			int o = lca(u, v);
			if (L[o] <= L[root] && L[root] <= R[o]) {
				int x = lca(u, root), y = lca(v, root);
				T.add(1, 1, n, 1, n, w);
				if (x != root && y != root) {
					if (dep[x] < dep[y]) swap(x, y);
					x = getch(root, x);
					T.add(1, 1, n, L[x], R[x], -w);
				}
			}
			else T.add(1, 1, n, L[o], R[o], w);

		} else {
			int u = Read();
			LL ans = 0;

			if (L[u] <= L[root] && L[root] <= R[u]) {
				ans += T.query(1, 1, n, 1, n);
				if (u != root) {
					int o = getch(root, u);
					ans -= T.query(1, 1, n, L[o], R[o]);
				}
			} else {
				ans = T.query(1, 1, n, L[u], R[u]);
			}
			printf("%lld\n", ans);
		}
	}

	return 0;
}
