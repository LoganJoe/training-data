#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <algorithm>
using namespace std;

int n, m;
int gen, p1, p2;
int number() {
    gen = (1LL * gen * p1) ^ p2;
    return (gen & (n - 1)) + 1;
}


const int Maxn = 1e7 + 5;
int a[Maxn], l[Maxn], r[Maxn], ans[Maxn];

int main() {
    freopen("max.in", "r", stdin);
    freopen("max.out", "w", stdout);

    scanf("%d%d", &n, &m);
    scanf("%d%d%d", &gen, &p1, &p2);

    for (int i = 1; i <= n; ++i)
        a[i] = number();
    for (int i = 1; i <= m; ++i) {
        l[i] = number(), r[i] = number();
        if (l[i] > r[i]) swap(l[i], r[i]);
    }

    /*
      ...
    */

    long long sum = 0;
    for (int i = 1; i <= m; ++i) {
        (sum += ans[i]) %= p2;
        (sum *= p1) %= p2;
    }
    printf("%lld\n", sum);
}