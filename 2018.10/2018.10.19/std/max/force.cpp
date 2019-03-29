#include <cstdio>
#include <algorithm>
using namespace std;

const int N = 1e7;

int n, m;
int gen, cute1, cute2;
int number() {
    gen = 1LL * gen * cute1 % cute2;
    return gen % n + 1;
}

int a[N], l[N], r[N], ans[N];

int main() {
    freopen("max.in", "r", stdin);
    freopen("bf.out", "w", stdout);

    scanf("%d%d", &n, &m);
    scanf("%d%d%d", &gen, &cute1, &cute2);

    for (int i = 1; i <= n; ++i)
        a[i] = number();
    for (int i = 1; i <= m; ++i) {
        l[i] = number(), r[i] = number();
        if (l[i] > r[i]) swap(l[i], r[i]);
    }


    for (int i = 1; i <= m; ++i) {
        int mx = 0;
        for (int j = l[i]; j <= r[i]; ++j)
            mx = max(mx, a[j]);
        ans[i] = mx;
    }

    int sum = 0;
    for (int i = 1; i <= m; ++i)
        sum = 1LL * ans[i] * cute1 % cute2;
    printf("%d\n", sum);
}