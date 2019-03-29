#include <cstdio>
#include <cstring>
#define REP(x) for(register int x = 1; x <= n; ++x)
#define mset(x, a) memset(x, a, sizeof(x))
#define mcpy(x, y) memcpy(x, y, sizeof(x))
using namespace std;

const int SIZE = 1e7;
char inp[SIZE], *in;
void input() {
	fread(inp, 1, SIZE, stdin);
	in = inp;
}

inline int read() {
	int x = 0, t = 1;
	while(*in < '0' || *in > '9') if(*(in++) == '-') t = -1;
	while(*in >= '0' && *in <= '9') x = x*10+*(in++)-'0';
	return x * t;
}


const int N = 305;
const int L = 7;
const int INF = 1e9;

int n, m, dis[L][N][N];
int f[N][N], g[N][N];
inline void cmin(int &x, int y) {
	x = x > y ? y : x;
}

int p[N][N];
void floyed(int c[][N], int a[][N], int b[][N]) {
	REP(i) REP(j) p[i][j] = INF;
	REP(k) REP(i) if(a[i][k] < INF) REP(j) cmin(p[i][j], a[i][k]+b[k][j]);
	REP(i) REP(j) c[i][j] = p[i][j];
}

bool getans(int a[][N]) {
	for(int i = 1; i <= n; ++i)
		if(a[i][i] < 0) return 1;
	return 0;
}


int ans, flag;
int main() {
	freopen("circle.in", "r", stdin);
	freopen("circle.out", "w", stdout);

	input();
	n = read(), m = read();
	
	mset(dis, 63);
	REP(i) dis[0][i][i] = 0;
	for(int i = 1; i <= m; ++i) {
		int x = read(), y = read();
		dis[0][x][y] = -read();
		dis[0][y][x] = -read();
	}
	
	register int t;
	for(t = 1; t < L; ++t) {
		floyed(dis[t], dis[t-1], dis[t-1]);
		if(getans(dis[t])) {
			flag = 1; 
			break;
		}
	}
	
	mset(f, 63);
	REP(i) f[i][i] = 0;

	for( --t; ~t; --t) {
		mcpy(g, f);
		floyed(g, g, dis[t]);
		if(!getans(g)) {
			ans += 1 << t;
			mcpy(f, g);
		} else flag = 1;
	}
	
	printf("%d\n", !flag ? 0 : ans + 1);
	return 0;
}
