#include<cstdio>
#define ll long long
#define fo(i, x, y) for(int i = x; i <= y; i ++)
#define fd(i, x, y) for(int i = x; i >= y; i --)
using namespace std;

const int mo = 998244353;

ll ksm(ll x, ll y) {
    ll s = 1;
    for(; y; y /= 2, x = x * x % mo)
        if(y & 1) s = s * x % mo;
    return s;
}

int n, k, f[7001][7];
ll ans;

int main() {
    // freopen("a.in", "r", stdin);
    scanf("%d %d", &n, &k);
    if(k > n) { printf("0"); return 0;}
    ans = 1; fo(i, n - k + 1, n) ans = ans * i % mo;
    fo(i, 1, k) ans = ans * ksm(i, mo - 2) % mo;
    f[0][0] = 1;
    fo(i, 1, n) {
        fd(k, 6, 1) fo(j, i, 7000)
            f[j][k] = (f[j][k] + f[j - i][k - 1]) % mo;
    }
    fo(j, 0, n) ans = (ans - (ll) (n - j + 1) * f[j][k - 1]) % mo;
    printf("%lld", (ans + mo) % mo);
}