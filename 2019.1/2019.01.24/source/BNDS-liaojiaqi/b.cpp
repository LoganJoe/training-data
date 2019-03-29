#include <bits/stdc++.h>

const int MAXN = 1e5 + 5;

int N, Q;

namespace solve {
struct Edge {
    int v, w, nxt;
} E[MAXN << 1];
int H[MAXN], cntE = 1;
void addEdge(int u, int v, int w) {
    E[++cntE] = (Edge) {v, w, H[u]};
    H[u] = cntE;
    E[++cntE] = (Edge) {u, w, H[v]};
    H[v] = cntE;
}
struct Node {
    int x, wh;
};
std::queue<Node> Que;
bool Vis[MAXN][2];
int bfs(int x, int y) {
    memset(Vis, 0, sizeof Vis);
    Vis[x][1] = 1;
    Que.push((Node) {x, 1});
    while (!Que.empty()) {
        Node a = Que.front(); Que.pop();
        for (int i = H[a.x]; i; i = E[i].nxt) {
            int &v = E[i].v;
            if (E[i].w == 3) {
                if (a.wh) {
                    if (!Vis[v][0]) {
                        Que.push((Node) {v, 0});
                        Vis[v][0] = 1;
                    }
                }
            } else {
                int wh = a.wh & (E[i].w == 1);
                if (!Vis[v][wh]) {
                    Que.push((Node) {v, wh});
                    Vis[v][wh] = 1;
                }
            }
        }
    }
    int ans = 0;
    for (int i = 1; i <= N; ++i) {
        ans += Vis[i][0] | Vis[i][1];
    }
    int ans2 = Vis[y][0] | Vis[y][1];
    printf("%d %d\n", ans, ans2);
    return ans;
}

void main() {
    int u, v, w, x, s, t;
    for (int i = 1; i < N; ++i) {
        scanf("%d%d%d", &u, &v, &w);
        addEdge(u, v, w);
    }
    int ans = 0;
    while (Q--) {
        scanf("%d%d%d%d", &x, &w, &s, &t);
        x ^= ans, w ^= ans, s ^= ans, t ^= ans;
        E[x << 1].w = E[x << 1 | 1].w = w;
        ans = bfs(s, t);
    }
}
}

namespace solve2 {
struct Node {
    int num, sum;
} T[MAXN << 2];
#define LT rt << 1, l, m
#define RT rt << 1 | 1, m + 1, r
void pushUp(int rt) {
    T[rt].num = T[rt << 1].num + T[rt << 1 | 1].num;
    T[rt].sum = T[rt << 1].sum + T[rt << 1 | 1].sum;
}
void modify(int rt, int l, int r, int p, int x) {
    if (l == r) {
        T[rt].sum = x;
        T[rt].num = (x == 3);
        return ;
    }
    int m = (l + r) >> 1;
    if (p <= m) {
        modify(LT, p, x);
    } else {
        modify(RT, p, x);
    }
    pushUp(rt);
}
int querySum(int rt, int l, int r, int a, int b) {
    if (a <= l && r <= b) {
        return T[rt].sum;
    }
    int m = (l + r) >> 1;
    int sum = 0;
    if (a <= m) {
        sum += querySum(LT, a, b);
    }
    if (m < b) {
        sum += querySum(RT, a, b);
    }
    return sum;
}
int queryNum(int rt, int l, int r, int a, int b) {
    if (a <= l && r <= b) {
        return T[rt].num;
    }
    int m = (l + r) >> 1;
    int num = 0;
    if (a <= m) {
        num += queryNum(LT, a, b);
    }
    if (m < b) {
        num += queryNum(RT, a, b);
    }
    return num;
}
int W[MAXN];
void build(int rt, int l, int r) {
    if (l == r) {
        T[rt].sum = W[l];
        T[rt].num = (W[l] == 3);
        return ;
    }
    int m = (l + r) >> 1;
    build(LT);
    build(RT);
    pushUp(rt);
}
int getL(int x) {
    if (x == 1) {
        return 1;
    }
    int l = 1, r = x - 1;
    int ans = 0;
    if (queryNum(1, 1, N - 1, 1, x - 1) == 0) {
        return 1;
    }
    while (l <= r) {
        int m = (l + r) >> 1;
        if (queryNum(1, 1, N - 1, m, x - 1) >= 1) {
            l = m + 1;
            ans = m;
        } else {
            r = m - 1;
        }
    }
    return ans + 1;
}
int getR(int x) {
    if (x == N) {
        return N;
    }
    int l = x, r = N - 1;
    int ans = 0;
    if (queryNum(1, 1, N - 1, x, N - 1) == 0) {
        return N;
    }
    while (l <= r) {
        int m = (l + r) >> 1;
        if (queryNum(1, 1, N - 1, x, m) >= 1) {
            r = m - 1;
            ans = m;
        } else {
            l = m + 1;
        }
    }
    return ans;
}
int expandL(int p, int x) {
    if (p == 1) {
        return 0;
    }
    if (p == x) {
        int p2 = getL(p - 1);
        // fprintf(stderr, "lp2=%d\n", p2);
        return p - p2;
    }
    int sum = querySum(1, 1, N - 1, p, x - 1);
    if (sum == x - p) {
        int p2 = getL(p - 1);
        // fprintf(stderr, "lp2=%d\n", p2);
        return p - p2;
    } else {
        return 0;
    }
}
int expandR(int p, int x) {
    if (p == N) {
        return 0;
    }
    if (p == x) {
        int p2 = getR(p + 1);
        // fprintf(stderr, "rp2=%d\n", p2);
        return p2 - p;
    }
    int sum = querySum(1, 1, N - 1, x, p - 1);
    // fprintf(stderr, "r sum = %d[%d,%d]\n", sum, x, p - 1);
    if (sum == p - x) {
        int p2 = getR(p + 1);
        // fprintf(stderr, "rp2=%d\n", p2);
        return p2 - p;
    } else {
        return 0;
    }
}
int check(int x, int y) {
    if (x > y) {
        int num = queryNum(1, 1, N - 1, y, x - 1);
        if (num == 0) {
            return 1;
        } else if (num > 1) {
            return 0;
        } else {
            int p = getL(x);
            return querySum(1, 1, N - 1, p, x - 1) == x - p;
        }
    } else {
        int num = queryNum(1, 1, N - 1, x, y - 1);
        if (num == 0) {
            return 1;
        } else if (num > 1) {
            return 0;
        } else {
            int p = getR(x);
            return querySum(1, 1, N - 1, x, p - 1) == p - x;
        }
    }
}
void main() {
    int u, v, w, x, s, t;
    for (int i = 1; i < N; ++i) {
        scanf("%d%d%d", &u, &v, &w);
        W[i] = w;
    }
    build(1, 1, N - 1);
    int ans = 0;
    while (Q--) {
        scanf("%d%d%d%d", &x, &w, &s, &t);
        // fprintf(stderr, "\n");
        x ^= ans, w ^= ans, s ^= ans, t ^= ans;
        // fprintf(stderr, "%d %d %d %d\n", x, w, s, t);
        W[x] = w;
        modify(1, 1, N - 1, x, w);
        int p1 = getL(s);
        int p2 = getR(s);
        // fprintf(stderr, "l = %d r = %d\n", p1, p2);
        ans = p2 - p1 + 1;
        ans += expandL(p1, s);
        ans += expandR(p2, s);
        // fprintf(stderr, "ans = %d %d\n", ans, check(s, t));
        printf("%d %d\n", ans, check(s, t));
    }
}
}

int main() {
    scanf("%d%d", &N, &Q);
    if (N <= 1000) {
        solve::main();
    } else {
        solve2::main();
    }
    return 0;
}