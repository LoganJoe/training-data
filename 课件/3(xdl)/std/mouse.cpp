# include <cstdio>
# include <cassert>

# define FOR(i, a, b) for (int i = a; i <= b; ++ i)
# define REP(i, n) for (int i = 1; i <= n; ++ i)

int K;
int main () {
	freopen("mouse.in", "r", stdin);
	freopen("mouse.out", "w", stdout);
	scanf ("%d", &K);
	printf ("%d\n", 2 * K);
	REP (i, K) {
		int a = 2 * i - 1, b = 2 * i;
		printf ("%d %d\n", a, b);
		REP (j, i - 1) {
			printf ("%d %d\n%d %d\n", a, 2 * j, b, 2 * j - 1);
		}
		
		FOR (j, i + 1, K) {
			printf ("%d %d\n%d %d\n", a, 2 * j - 1, b, 2 * j);
		}
	}
	return 0;
}
