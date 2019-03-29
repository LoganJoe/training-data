#include "tree.h"
#include <bits/stdc++.h>

using namespace std;

namespace __tree_lib {

    const int MAXN = 1005;

    int query_cnt, n, t;
    vector<int> G[MAXN];
    vector<pair<int, int>> edge_origin, edge_submit;

    void submit(int u, int v) {
        if(u > v) swap(u, v);
        edge_submit.push_back(make_pair(u, v));
    }

    int query(int u, int v, bool *s) {
        if(++ query_cnt > t) {
            fprintf(stderr, "Error, Query Times Out of Limit!");
            exit(0);
        }

        static int que[MAXN], pre[MAXN];
        memset(pre, 0xff, sizeof pre);

        int head = 0, tail = 0;
        pre[u] = 0, que[tail ++] = u;

        while(head < tail) {
            int x = que[head ++];
            for(auto y : G[x]) if(!~pre[y]) {
                pre[y] = x;
                que[tail ++] = y;
            }
        }

        int cnt = 0;
        for(int i = v; i; i = pre[i]) {
            cnt += s[i]; 
        }
        
        return cnt;
    }

    bool check() {
        if(edge_origin.size() != edge_submit.size()) {
            return false;
        } else {
            sort(edge_origin.begin(), edge_origin.end());
            sort(edge_submit.begin(), edge_submit.end());

            for(int i = 0; i < (int) edge_origin.size(); ++i) {
                if(edge_origin[i].first != edge_submit[i].first 
                || edge_origin[i].second != edge_submit[i].second) {
                    return false;
                }
            }
        }
        return true;
    }

    void main() {
        scanf("%d%d", &n, &t);
        for(int i = 1; i < n; ++i) {
            static int x, y;
            scanf("%d%d", &x, &y);
            if(x > y) swap(x, y);
            G[x].push_back(y), G[y].push_back(x);
            edge_origin.push_back(make_pair(x, y));
        }

        solve(n, t);

        if(check()) {
            fprintf(stderr, "Correct Answer, Query Times = %d\n", query_cnt);
        } else {
            fprintf(stderr, "Wrong Answer.\n");
        }
    }
}

void submit(int u, int v) { __tree_lib::submit(u, v); }

int query(int u, int v, bool *s) { return __tree_lib::query(u, v, s); }

int main() {

    freopen("tree.in", "r", stdin);
    __tree_lib::main();

    return 0;
}
