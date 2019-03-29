#include <cstdio>
#include <algorithm>
using namespace std;

#define iter(i, n) for (int i = 1; i <= n; ++i)
#define iter0(i, n) for (int i = 0; i < n; ++i)
#define iter_e(i, x) for (int i = pos[x]; i; i = g[i].frt)
#define forw(i, a, b) for (int i = a; i <= b; ++i)

#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef pair<int, int> pii;
typedef long long i64;

const int NR = 2e5 + 3000;
const int B = 250, T = 900, BR = B + 10;

int n, m, type, dsz, DSZ, ex[NR], ey[NR], ew[NR], S;
int dep[NR], bg[NR], ed[NR], bl[BR], br[BR];
pii drs[NR * 2], st[20][NR * 2];

struct Edge { int y, frt, w; } g[NR << 1];
int pos[NR], gsz;

struct Array0 {
	i64 t0[NR], t1[BR];
	
	inline void inc(int l, int r, i64 d) {
		if (r - l + 1 <= 3 * T) { forw(i, l, r) t0[i] += d; return; }
		int ld = l / T, rd = r / T;
		forw(i, ld + 1, rd - 1) t1[i] += d;
		forw(i, l, br[ld]) t0[i] += d;
		forw(i, bl[rd], r) t0[i] += d;
	}

	inline i64 query(int pos) { return t1[pos / T] + t0[pos]; }
} D;

struct Array1 {
	i64 t0[NR], t1[BR];

	inline void inc(int p, i64 d) { t0[p] += d, t1[p / T] += d; }

	inline i64 query(int p) {
		i64 sum = 0;
		iter0(i, p / T) sum += t1[i];
		forw(i, bl[p / T], p) sum += t0[i];
		return sum;
	}
} t[BR];

void AE(int x, int y, int z) { g[++gsz] = (Edge) { y, pos[x], z }, pos[x] = gsz; }
struct Node { int a[BR > (T+10) ? BR : (T + 10)], tag; } pool[BR*BR], pq[BR];

int plen;

void perinit() {
	forw(i, 0, S) {
		if (i) pq[i] = pq[i - 1];
		forw(k, 0, S) {
			pool[++plen] = pool[pq[i].a[k]];
			pq[i].a[k] = plen;
		}

		forw(k, bl[i], br[i]) {
			forw(p, bg[k] % T, T - 1) ++pool[pq[i].a[bg[k] / T]].a[p];
			forw(p, bg[k] / T + 1, S) ++pool[pq[i].a[p]].tag;
		}
	}
}

inline int perquery(int i, int n) { int id = pq[i].a[n / T]; return pool[id].tag + pool[id].a[n % T]; }

i64 tot[BR];

void modify(int x, int y, i64 d) {
	if (dep[x] < dep[y]) swap(x, y);
	
	D.inc(bg[x], ed[x], d);

	forw(i, 0, S) {
		int s1 = perquery(i, ed[x]) - perquery(i, bg[x] - 1), s2 = br[i] - s1;
		tot[i] += s1 * d;
		t[i].inc(bg[x], (s2 - s1) * d);
		t[i].inc(ed[x] + 1, (s1 - s2) * d);
	}
}

#define v g[i].y

int lg[NR * 2], dn[NR];

inline pii ask(int l, int r) {
	int k = lg[r - l + 1];
	return min(st[k][l], st[k][r - (1 << k) + 1]);
}

inline int lca(int x, int y) { if (dn[x] > dn[y]) swap(x, y); return ask(dn[x], dn[y]).second; }

i64 query(int R, int x) {
	i64 res = R >= T ? t[R / T - 1].query(bg[x]) + tot[R / T - 1] : 0;
	forw(i, bl[R / T], R) {
		res += D.query(bg[i]) + D.query(bg[x]) - 2 * D.query(bg[lca(i, x)]);
	}
	return res;
}

void dfs(int x, int fa) {
	bg[x] = ++dsz; drs[dn[x] = ++DSZ] = pii(dep[x], x);
	iter_e(i, x) if (v != fa) dep[v] = dep[x] + 1, dfs(v, x), drs[++DSZ] = pii(dep[x], x);
	ed[x] = dsz;
}

#include <ctime>

int main() {
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);
	scanf("%d%d%d", &n, &m, &type);
	S = n / T; //debug("%d\n", S);
	forw(i, 0, S) {
		bl[i] = i * T;
		br[i] = (i + 1) * T - 1;
		if (bl[i] == 0) bl[i] = 1;
		if (br[i] > n) br[i] = n;
	}

	iter(i, n - 1) {
		scanf("%d%d%d", &ex[i], &ey[i], &ew[i]);
		AE(ex[i], ey[i], ew[i]); AE(ey[i], ex[i], ew[i]);
	}

	dfs(1, 0);
	perinit();

	iter(i, DSZ) {
		st[0][i] = drs[i];
		lg[i] = lg[i - 1] + ((1 << (lg[i - 1] + 1)) == i);
	}
	iter(k, 19) iter(i, DSZ - (1 << k) + 1) st[k][i] = min(st[k - 1][i], st[k - 1][i + (1 << (k - 1))]);

	iter(id,n-1) modify(ex[id], ey[id], ew[id]);

	int lstans = 0;
	int ccc = 0;
	iter(ii, m) {
		char op[10]; int L, R, x, id, w;
		scanf("%s", op);
		if (op[0] == 'm') {
			scanf("%d%d", &id, &w); id ^= lstans, w ^= lstans;
			
			int cc = clock();
			
			modify(ex[id], ey[id], w - ew[id]), ew[id] = w;
			
			ccc += clock() - cc;
		} else {
			scanf("%d%d%d", &L, &R, &x);
			L ^= lstans, R ^= lstans, x ^= lstans;
			i64 tmp = query(R, x) - query(L - 1, x);
			printf("%lld\n", tmp); lstans = tmp % n;
		}
		if (!type) lstans = 0;
	}
	fprintf(stderr, "%d\n", ccc);
	return 0;
}
