#include<cstdio>
#include<algorithm>
#define fo(i, x, y) for(int i = x; i <= y; i ++)
#define max(a, b) ((a) > (b) ? (a) : (b))
using namespace std;

const int N = 1e5 + 5;

int T, n, t[N][2], v[N], bz[N];

int dg(int x) {
    if(bz[1]) return v[1];
    int ans = x ? 0 : 2e9;
    fo(i, 1, n) if(!bz[i]) {
        if(bz[t[i][0]] && bz[t[i][1]]) {
            if(x) v[i] = max(v[t[i][0]], v[t[i][1]]); else
            v[i] = min(v[t[i][0]], v[t[i][1]]);
            bz[i] = 1;
            bz[t[i][0]] = bz[t[i][1]] = 0;
            if(x) ans = max(ans, dg(!x)); else
            ans = min(ans, dg(!x));
            bz[t[i][0]] = bz[t[i][1]] = 1;
            bz[i] = 0;
        }
    }
    return ans;
}

int main() {
    // freopen("c.in", "r", stdin);
    scanf("%d", &T);
    fo(ii, 1, T) {
        scanf("%d", &n);
        fo(i, 1, n) bz[i] = 0;
        fo(i, 1, n) {
            scanf("%d", &v[i]);
            if(v[i] == -1) scanf("%d %d", &t[i][0], &t[i][1]); else
            bz[i] = 1, t[i][0] = t[i][1] = 0;
        }
        if(n <= 10) {
            printf("%d\n", dg(1));
        } else {
            int x = 1;
            while(n > 1) {
                if(x) v[n - 3] = max(v[n - 1], v[n]); else
                v[n - 3] = min(v[n - 1], v[n]);
                x = !x;
                n -= 2;
            }
            printf("%d\n", v[0]);
        }
    }
}