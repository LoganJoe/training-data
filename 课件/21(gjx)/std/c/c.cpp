#include <bits/stdc++.h>

#define REP(i, a, b) for (int i = (a), _end_ = (b); i < _end_; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define mp make_pair
#define x first
#define y second
#define pb push_back
#define SZ(x) (int((x).size()))
#define ALL(x) (x).begin(), (x).end()

template<typename T> inline bool chkmin(T &a, const T &b) { return a > b ? a = b, 1 : 0; }
template<typename T> inline bool chkmax(T &a, const T &b) { return a < b ? a = b, 1 : 0; }

typedef long long LL;

const int MOD = 1e9 + 7;
const int oo = 0x3f3f3f3f;
const int maxn = 100000;

int fpm(LL b, int e, int m)
{
	b %= m;
	LL t = 1;
	for ( ; e; e >>= 1, (b *= b) %= m)
		if (e & 1) (t *= b) %= m;
	return t;
}

struct data {
	int x, y, z;

	data() { }
	data(int _z): x(0), y(0), z(_z) { }
	data(int _x, int _y, int _z): x(_x), y(_y), z(_z) { }

	friend data operator+(const data &x, const data &y) { return data((x.x + y.x) % MOD, (x.y + y.y) % MOD, (x.z + y.z) % MOD); }
	friend data operator-(const data &x, const data &y) { return data((x.x - y.x) % MOD, (x.y - y.y) % MOD, (x.z - y.z) % MOD); }
	friend data operator*(const data &x, const int &y) { return data((LL)x.x * y % MOD, (LL)x.y * y % MOD, (LL)x.z * y % MOD); }
};

int n;
int w[maxn + 5];
int fa[maxn + 5];
int val[maxn + 5][2];
int sum_down[maxn + 5], sum[maxn + 5];
int sz[maxn + 5];
std::vector<int> children[maxn + 5];
int inv[maxn + 5];

void calc()
{
	REP(i, 1, n + 1) inv[i] = fpm(i, MOD - 2, MOD);
	static data coe[maxn + 5][2];
	coe[0][0] = coe[0][1] = coe[n][0] = coe[n][1] = data(0, 0, 0);
	coe[1][0] = data(1, 0, 0), coe[1][1] = data(0, 1, 0);
	REP(i, 1, n - 1) {
		coe[i + 1][1] = (coe[i][1] - data((i != 1) * inv[n]) - coe[i - 1][1] * ((LL)(i - 1) * inv[n] % MOD) - coe[i - 1][0] * inv[n]) * ((LL)n * inv[n - i] % MOD);
		coe[i + 1][0] = (coe[i][0] - data(inv[n]) - coe[i + 1][1] * inv[n] - coe[i - 1][0] * ((LL)i * inv[n] % MOD)) * ((LL)n * inv[n - i - 1] % MOD);
	}
	data val0 = coe[n - 1][0] - coe[n - 2][0] * ((LL)(n - 1) * inv[n] % MOD);
	data val1 = coe[n - 1][1] - inv[n] - coe[n - 2][1] * ((LL)(n - 2) * inv[n] % MOD) - coe[n - 2][0] * inv[n];
	int det = ((LL)val0.x * val1.y - (LL)val0.y * val1.x) % MOD;
	assert(det);
	det = fpm(det, MOD - 2, MOD);
	int valx = ((LL)-val0.z * val1.y - (LL)val0.y * -val1.z) % MOD * det % MOD;
	int valy = ((LL)val0.x * -val1.z - (LL)-val0.z * val1.x) % MOD * det % MOD;
	REP(i, 0, n + 1) REP(j, 0, 2) val[i][j] = ((LL)valx * coe[i][j].x + (LL)valy * coe[i][j].y + coe[i][j].z) % MOD;
	REP(i, 0, n + 1) REP(j, 0, 2) (val[i][j] += MOD) %= MOD;
}

int main()
{
	freopen("c.in", "r", stdin);
	freopen("c.out", "w", stdout);

	scanf("%d", &n);

    assert(n >= 3);

	calc();

	static char s[maxn + 5];
	scanf("%s", s);
	int cnt = 0;
	REP(i, 0, n) {
        w[i] = s[i] == '1';
        cnt += w[i];
    }
	fa[0] = -1;
	REP(i, 1, n) {
        scanf("%d", fa + i);
        --fa[i];
        children[fa[i]].pb(i);
    }

	for (int i = n - 1; i >= 0; --i) {
		++sz[i];
        if (fa[i] >= 0)
            sz[fa[i]] += sz[i];
		REP(k, 0, SZ(children[i])) {
			int j = children[i][k];
			(sum_down[i] += sum_down[j] + sz[j]) %= MOD;
		}
	}
	memcpy(sum, sum_down, sizeof sum);
	REP(i, 0, n)
		REP(k, 0, SZ(children[i])) {
			int j = children[i][k];
			(sum[j] += (sum[i] - sum_down[j] + n - (sz[j] << 1)) % MOD) %= MOD;
		}

	int ans = 0;
	REP(i, 0, n) (ans += sum[i]) %= MOD;
	ans = (LL)ans * fpm(n, MOD - 2, MOD) % MOD;
	REP(i, 0, n) (ans += (LL)val[cnt][w[i]] * sum[i] % MOD) %= MOD;
	ans = (LL)ans * fpm(n, MOD - 2, MOD) % MOD;
	(ans += MOD) %= MOD;

	printf("%d\n", ans);
}
