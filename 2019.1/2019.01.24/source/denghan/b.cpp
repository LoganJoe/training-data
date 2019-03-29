#include<cstdio>
#include<algorithm>
#define pr printf
#define fo(i, x, y) for(int i = x; i <= y; i ++)
using namespace std;

const int N = 2e5 + 5;

int n, Q, x, y, z;

int t[N][2], fa[N], pf[N], rev[N], dd[N];
int lr(int x) {return t[fa[x]][1] == x;}
struct nod {
    int a1, a2, y;
    int z, co, s1, s2;
} a[N], b[N];

int f[4][4] = {{0, 0, 0, 0}, {0, 0, 1, 1}, {0, 0, 2, 2}, {0, 1, 2, 3}};

void up(nod &t, nod t0, nod t1) {
    if(t.co == 1) t.y = 3; else
    if(t.co == 2) t.y = 2; else
    if(t.co == 3) t.y = 1;
    t.y = f[t0.y][t.y];
    if(t.y == 0) t.a1 = t0.a1, t.a2 = t0.a2; else
    if(t.y == 1) {
        t.a1 = t1.a2 + t.s2 + t.z + t0.a1;
        t.a2 = t0.a2;
    } else
    if(t.y == 2) {
        t.a1 = t0.a1;
        t.a2 = t1.a2 + t.s2 + t.z + t0.a2;
    } else {
        t.a1 = t1.a1 + t.s1 + t0.a1;
        t.a2 = t1.a2 + t.s2 + t.z + t0.a2;
    }
    t.y = f[t.y][t1.y];
}
void upd(int x) {
    up(a[x], a[t[x][0]], a[t[x][1]]);
    up(b[x], b[t[x][1]], b[t[x][0]]);
}
void fan(int x) { if(x) swap(t[x][0], t[x][1]), swap(a[x], b[x]), rev[x] ^= 1; }
void down(int x) { if(rev[x]) fan(t[x][0]), fan(t[x][1]), rev[x] = 0;}
void rotate(int x) {
    int y = fa[x], k = lr(x);
    t[y][k] = t[x][!k]; if(t[x][!k]) fa[t[x][!k]] = y;
    fa[x] = fa[y]; if(fa[y]) t[fa[y]][lr(y)] = x;
    fa[y] = x; t[x][!k] = y; pf[x] = pf[y];
    upd(y); upd(x);
}
void xc(int x) {
    for(; x; x = fa[x]) dd[++ dd[0]] = x;
    while(dd[0]) down(dd[dd[0] --]);
}
void splay(int x, int y) {
    xc(x);
    for(; fa[x] != y; rotate(x)) if(fa[fa[x]] != y)
        rotate(lr(x) == lr(fa[x]) ? fa[x] : x);
}
void add(int x, int y, int f) {
    a[x].s1 += a[y].a1 * f;
    a[x].s2 += a[y].a2 * f;
    b[x].s1 += a[y].a1 * f;
    b[x].s2 += a[y].a2 * f;
}
void access(int x) {
    for(int y = 0; x; upd(x), y = x, x = pf[x]) {
        splay(x, 0); fa[t[x][1]] = 0; pf[t[x][1]] = x;
        add(x, t[x][1], 1);
        add(x, y, -1);
        t[x][1] = y; fa[y] = x; pf[y] = 0;
    }
}
void mroot(int x) {
    access(x); splay(x, 0);
    fan(x);
}
void link(int x, int y) {
    mroot(x); pf[x] = y;
    add(y, x, 1); access(x);
}

int ans;

int main() {
    // freopen("b.in", "r", stdin);
    // freopen("b.out", "w", stdout);
    a[0].y = b[0].y = 3;
    scanf("%d %d", &n, &Q);
    fo(i, 1, n) a[i].z = b[i].z = a[i].co = b[i].co = 1;
    fo(i, 1, n - 1) {
        scanf("%d %d %d", &x, &y, &z);
        a[i + n].co = b[i + n].co = z;
        link(x, i + n); link(i + n, y);
    }
    fo(ii, 1, Q) {
        scanf("%d %d", &x, &z);
        x ^= ans; z ^= ans;
        x += n;
        mroot(x); splay(x, 0);
        a[x].co = b[x].co = z;
        upd(x);
        scanf("%d %d", &x, &y);
        x ^= ans; y ^= ans;
        mroot(x); access(y); splay(x, 0);
        ans = a[x].a2 + a[x].a1; splay(y, 0);
        printf("%d %d\n", ans, a[y].y != 0);
    }
}