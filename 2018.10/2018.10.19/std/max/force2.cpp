#include <cstdio>
#include <algorithm>
using namespace std;

const int N = 1e7;

int n, m;
int gen, cute1, cute2;

int number() {
    gen = (1LL * gen * cute1) ^ cute2;
    return (gen & (n - 1)) + 1;
}

int t[N << 2];
int a[N], ans[N];

#define mid (l + r >> 1)
#define lc o << 1, l, mid
#define rc o << 1 | 1, mid + 1, r

void build(int o, int l, int r) {
    if (l == r) {
        t[o] = a[l];
        return;
    }
    build(lc);
    build(rc);
    t[o] = max(t[o << 1], t[o << 1 | 1]);
}

int query(int o, int l, int r, int L, int R) {
    if (r < L || R < l) return 0;
    if (L <= l && r <= R) return t[o];
    return max(query(lc, L, R), query(rc, L, R));
}

int main() {
    freopen("max.in", "r", stdin);
    freopen("seq.out", "w", stdout);

    scanf("%d%d", &n, &m);
    scanf("%d%d%d", &gen, &cute1, &cute2);

    for (int i = 1; i <= n; ++i)
        a[i] = number();

    build(1, 1, n);
    for (int i = 1; i <= m; ++i) {
        int l = number(), r = number();
        if (l > r) swap(l, r);
        ans[i] = query(1, 1, n, l, r);
    }

    int sum = 0;
    for (int i = 1; i <= m; ++i)
        (sum += 1LL * ans[i] * cute1 % cute2) %= cute2;
    printf("%d\n", sum);
}