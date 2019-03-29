#include <set>
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;

inline int read() {
    int x = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9') ch = getchar();
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch= getchar();
    }
    return x;
}


const int Maxn = 3e5 + 5;


int n, m;
int a[Maxn];

namespace SegmentTree {

#define ls t[o << 1]
#define rs t[o << 1 | 1]
#define mid (l + r >> 1)
#define lc o << 1, l, mid
#define rc o << 1 | 1, mid + 1, r


struct Node {
    int siz, mx;
    ll sum;
    void sets(int x) {
        mx = sum = x;
    }
} t[Maxn << 2];

void pushup(int o) {
    t[o].mx = max(ls.mx, rs.mx);
    t[o].sum = ls.sum + rs.sum;
}

ll update(int o, int l, int r, int w) {
    if (t[o].mx <= w) return 1LL * w * t[o].siz;
    if (l == r) return t[o].mx;
    if (ls.mx > w) {
        return update(lc, w) + rs.sum;
    } else {
        return 1LL * w * ls.siz + update(rc, w);
    }
}

void build(int o, int l, int r) {
    t[o].siz = r - l + 1;
    if (l == r) {
        return t[o].sets(a[l]);
    }

    build(lc);
    build(rc);
    rs.sum = update(rc, ls.mx);
    pushup(o);
}

void modify(int o, int l, int r, int p) {
    if (l == r) {
        t[o].sets(a[l]);
        return;
    }
    if (p <= mid) modify(lc, p);
    else modify(rc, p);

    rs.sum = update(rc, ls.mx);
    pushup(o);
}

ll query() {
    return t[1].sum;
}

}

int main() {
    freopen("seq.in", "r", stdin);
    freopen("seq.out", "w", stdout);



    n = read();
    for (int i = 1; i <= n; ++i)
        a[i] = read();

    using namespace SegmentTree;
    build(1, 1, n);

    m = read();
    for (int i = 1; i <= m; ++i) {
        int pos = read();
        int val = read();
        a[pos] = val;
        modify(1, 1, n, pos);
        printf("%lld\n", query());
    }
    return 0;
}