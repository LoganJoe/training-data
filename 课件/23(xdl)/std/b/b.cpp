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

const int MAXN = 105;

namespace MCMF
{

const int MAXV = MAXN * 2 + 1;
const int MAXE = MAXN * MAXN * 8 + 1;

struct Edge {
    int u, v, next;
    int rsd, cost;
    Edge() { }
    Edge(int u_, int v_, int next_, int rsd_, int cost_): u(u_), v(v_), next(next_), rsd(rsd_), cost(cost_) { }
};

int n, tote, head[MAXV];
Edge edge[MAXE];
LL dis[MAXV];
int st[MAXV], top;
bool vis[MAXV];
vector<int> cir;

void init(int n_) {
    n = n_;
    tote = 1;
    memset(head + 1, 0, sizeof(*head) * n);
}

void addEdge(int u, int v, int cap, int cost) {
    edge[++tote] = Edge(u, v, head[u], cap, cost);
    head[u] = tote;
    edge[++tote] = Edge(v, u, head[v], 0, -cost);
    head[v] = tote;
}

bool dfs(int u, int f) {
    vis[u] = true;
    st[++top] = f;
    for (int i = head[u]; i; i = edge[i].next) {
        Edge &e = edge[i];
        if (e.rsd > 0 && chkmax(dis[e.v], dis[u] + e.cost)) {
            if (vis[e.v]) {
                cir.push_back(i);
                do {
                    cir.push_back(st[top]);
                } while (edge[st[top--]].u != e.v);
                return true;
            } else if (dfs(e.v, i))
                return true;
        }
    }
    --top;
    vis[u] = false;
    return false;
}

int exec() {
    int ret = 0;
    for (;;) {
        memset(dis + 1, -oo, sizeof(*dis) * n);
        memset(vis, 0, sizeof(vis));
        cir.clear();
        top = 0;
        for (int i = 1; i <= n; ++i) {
            dis[i] = 0;
            if (dfs(i, 0))
                break;
        }
        if (SZ(cir) == 0)
            break;
        int cur = 0;
        int flow = +oo;
        for (int i = 0; i < SZ(cir); ++i) {
            chkmin(flow, edge[cir[i]].rsd);
        }
        for (int i = 0; i < SZ(cir); ++i) {
            int x = cir[i];
            // printf(" (%d,%d) ", edge[x].u, edge[x].v);
            edge[x].rsd -= flow;
            edge[x ^ 1].rsd += flow;
            cur += edge[x].cost * flow;
        }
        // puts("");
        // printf("\t%d\n", cur);
        ret += cur;
    }
    return ret;
}

}

int N, M, W;
int T[MAXN], C[MAXN];
Pii E[MAXN * MAXN];

void input() {
    scanf("%d%d%d", &N, &M, &W);
    for (int i = 1; i <= N; ++i) {
        scanf("%d", &T[i]);
    }
    for (int i = 1; i <= N; ++i) {
        scanf("%d", &C[i]);
    }
    for (int i = 1; i <= M; ++i) {
        scanf("%d%d", &E[i].x, &E[i].y);
    }
}

void solve() {
    int l = -1, r = 1e9;

    while (l + 1 < r) {
        int mid = (l + r) >> 1;

        MCMF::init(N * 2 + 1);
        for (int i = 1; i <= N; ++i) {
            MCMF::addEdge(i * 2 - 1, i * 2, C[i], T[i]);
            MCMF::addEdge(i * 2 - 1, i * 2, +oo, 0);
        }
        for (int i = 1; i <= M; ++i) {
            MCMF::addEdge(E[i].x * 2, E[i].y * 2 - 1, +oo, 0);
        }
        for (int i = 1; i <= N; ++i) {
            MCMF::addEdge(i * 2, N * 2 + 1, +oo, -mid);
            MCMF::addEdge(N * 2 + 1, i * 2 - 1, +oo, 0);
        }
        int t = MCMF::exec();

        if (t > W)
            l = mid;
        else
            r = mid;
    }

    printf("%d\n", r);
}

int main() {
    freopen("b.in", "r", stdin);
    freopen("b.out", "w", stdout);

    input();
    solve();
}
