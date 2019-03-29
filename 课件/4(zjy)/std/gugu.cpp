#include <cstdio>
#include <algorithm>
#include <vector>
#include <cassert>
#include <iostream>
#include <string>
#include <string.h>
#include <cmath>
#include <set>
#include <map>
#include <bitset>
#include <iomanip>

#define X first
#define Y second
#define mp make_pair
#define pb push_back

typedef long long ll;

using namespace std;

const int MAXN = 11;
const int MOD = 1E9 + 7;
const int L = 1400100;

inline int mod(const long long x) {
    if (x >= 0) {
        return x % MOD;
    }
    return MOD + x % MOD;
}

long long bin(long long x, long long y) {
    if (y == 0) {
        return 1;
    }
    long long u = bin(x, y / 2);
    if (y % 2 == 0) {
        return u*u % MOD;
    }
    else {
        return u*u % MOD * x % MOD;
    }
}

long long inv[15][15];

long long calc(const vector<long long> &x, const vector<long long> &y, int n, long long X) {
    long long res = 0;
    for (int i = 0; i < n; i++) {
        long long cur = 1;
        for (int j = 0; j < n; j++) {
            if (i == j) {
                continue;
            }
            long long num = mod(X - x[j]);
            //long long denum = bin( mod(x[i] - x[j]), MOD - 2 );
            long long denum = inv[i][j];
            cur = cur * num % MOD * denum % MOD;
        }
        res += cur*y[i];
        res %= MOD;
    }
    return res;
}

int n;
int a[MAXN];
int f[L][MAXN];



long long kill(int rem, long long wh, int w) {
    //cerr << rem << endl;
    wh--;
    vector<long long> x, y;
    int s = 0;
    for (int i = 0; i <= n; i++) {
        x.push_back(i);
    }
    for (int i = 0; i <= n; i++) {
        s += f[w*i + rem][n - 1];
        if (s >= MOD) {
            s -= MOD;
        }
        y.push_back(s);
        //cerr << i << " " << s << endl;
    }
    //cerr << " : " << wh << " " << calc(x, y, n, wh) << endl;
    return calc(x, y, n + 1, wh);
}

int fun(long long X) {
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            inv[i][j] = bin(mod(i - j), MOD - 2 );
        }
    }
    int w = 1;
    for (int i = 0; i < n; i++) {
        w *= a[i];
    }
    int res = 0;
    for (int rem = 0; rem < w; rem++) {
        if (rem > X) {
            continue;
        }
        long long wh = X / w + (X % w >= rem);
        res += kill(rem, wh, w);
        if (res >= MOD) {
            res -= MOD;
        }
    }
    return res;
}

int brute(int l, int r) {
    int res = 0;
    for (int i = l; i <= r; i++) {
        res += f[i][n - 1];
        if (res >= MOD) {
            res -= MOD;
        }
        //cerr << f[i][n - 1] << endl;
    }
    return res;
}
const int MAXW = 100000;
int main() {
	freopen("gugu.in","r",stdin);
	freopen("gugu.out","w",stdout);
    cin >> n;
    long long ww = 1;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        ww *= a[i];
        assert(a[i] > 0 && a[i] <= MAXW);
    }
    for (int j = 0; j < n; j++) {
        f[0][j] = 1;
    }
    for (int i = 1; i < L; i++) {
        for (int j = 0; j < n; j++) {
            if (j > 0) {
                f[i][j] = f[i][j - 1];
            }
            if (i >= a[j]) {
                f[i][j] += f[i - a[j] ][j];
                if (f[i][j] >= MOD) {
                    f[i][j] -= MOD;
                }
            }
        }
    }
    long long l, r;
    cin >> l >> r;
    int stupid;
    int ans = mod (fun(r) - fun(l - 1) );
    cout << ans << endl;
    return 0;
}
