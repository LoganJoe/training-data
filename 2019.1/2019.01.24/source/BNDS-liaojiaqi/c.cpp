#include <bits/stdc++.h>

const int MAXN = 1e5 + 5;

struct Node {
    int p, x;
    bool operator < (const Node &a) const {
        return x < a.x;
    }
};
std::set<Node> Set;
int N, W[MAXN], L[MAXN], R[MAXN], Fa[MAXN];

int main() {
    int T;
    int opt;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &N);
        memset(W, 0, sizeof W);
        for (int i = 1; i <= N; ++i) {
            scanf("%d", &opt);
            if (opt == -1) {
                scanf("%d%d", &L[i], &R[i]);
                Fa[L[i]] = i;
                Fa[R[i]] = i;
            } else {
                W[i] = opt;
            }
        }
        for (int i = 1; i <= N; ++i) {
            if (W[L[i]] && W[R[i]]) {
                Set.insert((Node) {L[i], W[L[i]]});
                Set.insert((Node) {R[i], W[R[i]]});
            }
        }
        int cur = 0;
        while (!Set.empty()) {
            Node a;
            int fa;
            if (cur & 1) {
                a = *Set.begin();
                fa = Fa[a.p];
                W[fa] = a.x;
                if (W[L[fa]] == a.x) {
                    Set.erase(Set.find((Node) {R[fa], W[R[fa]]}));
                } else {
                    Set.erase(Set.find((Node) {L[fa], W[L[fa]]}));
                }
                Set.erase(Set.begin());

            } else {
                a = *--Set.end();
                fa = Fa[a.p];
                W[fa] = a.x;
                if (W[L[fa]] == a.x) {
                    Set.erase(Set.find((Node) {R[fa], W[R[fa]]}));
                } else {
                    Set.erase(Set.find((Node) {L[fa], W[L[fa]]}));
                }
                Set.erase(--Set.end());
            }
            int ffa = Fa[fa];
            if (W[L[ffa]] && W[R[ffa]]) {
                Set.insert((Node) {L[ffa], W[L[ffa]]});
                Set.insert((Node) {R[ffa], W[R[ffa]]});
            }
            cur = cur ^ 1;
        }
        printf("%d\n", W[1]);
    }

    return 0;
}