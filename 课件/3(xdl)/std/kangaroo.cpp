# include <cstdio>
# include <cmath>
# include <algorithm>
using namespace std;

# define FOR(i, a, b) for (int i = a; i <= b; ++ i)
# define REP(i, n) FOR (i, 1, n)
# define NR 310
int n, m;
int a[NR][NR];

const int mod = 1000000007; 

int pr (int a, int z) {
	int s = 1; do { if (z & 1) s = 1ll * s * a % mod; a = 1ll * a * a % mod; } while (z >>= 1);
	return s;
} 

int main () {
	freopen("kangaroo.in", "r", stdin);
	freopen("kangaroo.out", "w", stdout);
	scanf ("%d%d", &n, &m);
	if (n < m) { REP (i, n) REP (j, m) scanf ("%d", &a[j][i]); swap (n, m); }
	else REP (i, n) REP (j, m) scanf ("%d", &a[i][j]);
	int ans = 0;
	REP (i, n) REP (j, m) { if (a[i][j] < 0) a[i][j] += mod; }
	//printf ("%d %d\n", n, m);
	REP (i, m) {
		int p = -1;
		if (a[i][i]) p = i;
		else { REP (j, n) if (!a[j][j] && a[j][i]) { p = j; break; } }
		if (p == -1) { ++ ans; continue; }
		REP (j, m) swap (a[i][j], a[p][j]);
		REP (j, n) if (j != i) {
			int z = 1ll * a[j][i] * pr (a[i][i], mod - 2) % mod;
			FOR (k, i, m) a[j][k] = (a[j][k] - 1ll * a[i][k] * z % mod + mod) % mod;
		}
	}
	printf ("%d\n", m - ans);
	return 0;
}
