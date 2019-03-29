#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>

#define x first
#define y second
#define MP std::make_pair
#define SZ(x) ((int)(x).size())
#define ALL(x) (x).begin(), (x).end()
#define DEBUG(...) fprintf(stderr, __VA_ARGS__)

using std::pair;
using std::vector;
using std::string;

typedef long long LL;
typedef pair<int, int> Pii;

const int oo = 0x3f3f3f3f;

template<typename T> inline bool chkmax(T &a, T b) { return a < b ? a = b, true : false; }
template<typename T> inline bool chkmin(T &a, T b) { return b < a ? a = b, true : false; }
// EOT

const int MAXN = 505, MAXM = MAXN * MAXN;
const LL W = (LL)1e9 * MAXN;

struct Edge {
    int u, v;
    LL w;

    Edge() { }
    Edge(int u0, int v0, LL w0): u(u0), v(v0), w(w0) { }
};

int N, M;
Edge E[MAXM];

LL zhuliu(int rt)
{
    static int pre[MAXN], id[MAXN], vis[MAXN];
    static LL in[MAXN];

    LL res = 0;
    for (;;) {
        memset(pre, 0, sizeof(pre));
        memset(in, +oo, sizeof(in));
        for (int i = 1; i <= M; ++i) {
            if (chkmin(in[E[i].v], E[i].w))
                pre[E[i].v] = E[i].u;
        }
        pre[rt] = -1;
        for (int i = 1; i <= N; ++i) {
            if (pre[i] == 0)
                return -1;
        }
        in[rt] = 0;
        for (int i = 1; i <= N; ++i) {
            res += in[i];
        }

        int totc = 0;
        memset(id, 0, sizeof(id));
        memset(vis, 0, sizeof(vis));
        vis[rt] = -1;
        for (int i = 1; i <= N; ++i) {
            int u;
            for (u = i; vis[u] == 0; u = pre[u]) {
                vis[u] = i;
            }
            if (vis[u] == i) {
                id[u] = ++totc;
                for (int v = pre[u]; v != u; v = pre[v]) {
                    id[v] = totc;
                }
            }
        }
        if (totc == 0)
            break;
        for (int i = 1; i <= N; ++i) {
            if (id[i] == 0)
                id[i] = ++totc;
        }

        N = totc;
        rt = id[rt];
        for (int i = 1; i <= M; ++i) {
            int oriv = E[i].v;
            E[i].u = id[E[i].u];
            E[i].v = id[E[i].v];
            if (E[i].u != E[i].v)
                E[i].w -= in[oriv];
            else
                std::swap(E[i--], E[M--]);
        }
    }

    return res;
}

void input() {
    scanf("%d%d", &N, &M);
    for (int i = 1; i <= M; ++i) {
        scanf("%d%d%lld", &E[i].u, &E[i].v, &E[i].w);
        assert(E[i].u != E[i].v);
    }
}

void solve() {
    for (int i = 1; i <= N; ++i) {
        E[++M] = {N + 1, i, W};
    }

    LL ans = zhuliu(++N) - W;
    if (ans >= W)
        ans = -1;

    printf("%lld\n", ans);
}

int main() {
    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);

    input();
    solve();
}
