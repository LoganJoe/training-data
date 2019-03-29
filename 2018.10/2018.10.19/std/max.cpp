#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 1e7 + 5;

int n, m;
int gen, cute1, cute2;
int number() {
    gen = (1LL * gen * cute1) ^ cute2;
    return (gen & (n - 1)) + 1;
}


int hd[N], nxt[N], id[N], to[N], cnt;
int ans[N], a[N], p[N], q[N];

int add(int x, int y, int i) {
    ++cnt;
    nxt[cnt] = hd[x];
    to[cnt] = y;
    id[cnt] = i;
    hd[x] = cnt;
}


int getfa(int x, int y) {
    int fa = x;
    for (int i = x; i; i = p[i])
        if (p[i] < y || p[i] == i) {
            fa = i;
            break;
        }
    for (int j, i = x; i != fa; i = j) {
        j = p[i], p[i] = fa;
    }
    return fa;
}

int main() {

    scanf("%d%d", &n, &m);
    scanf("%d%d%d", &gen, &cute1, &cute2);

    for (int i = 1; i <= n; ++i)
        a[i] = number();
    for (int i = 1; i <= m; ++i) {
        int l = number(), r = number();
        if (l > r) swap(l, r);
        add(l, r, i);
    }
    double t1;
    fprintf(stderr, "%lf\n", t1 = (double)clock()/CLOCKS_PER_SEC);

    int ind = 0;
    for (int i = 1; i <= n; ++i) {
        while (ind && a[q[ind]] <= a[i]) --ind;
        if (ind) p[i] = q[ind];
        else p[i] = i;
        q[++ind] = i;
    }

    for (int i = n; i; --i) {
        for (int j = hd[i]; j; j = nxt[j])
            ans[id[j]] = a[getfa(to[j], i)];
    }

    
    fprintf(stderr, "%lf\n", (double)clock()/CLOCKS_PER_SEC - t1);

    int sum = 0;
    for (int i = 1; i <= m; ++i)
        (sum += 1LL * ans[i] * cute1 % cute2) %= cute2;
    printf("%d\n", sum);
}
