#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
 
inline int safeAdd(int a, int b, int m) {
    if ((long long)a + b >= m) {
        return m + ((long long)a + b) % m;
    } else {
        return a + b;
    }
}
 
inline int safeMul(int a, int b, int m) {
    if ((long long)a * b >= m) {
        return m + (long long)a * b % m;
    } else {
        return a * b;
    }
}
 
int powSum(int x, int n, int MOD) {
    if (n == 0) {
        return 0;
    }
    int ret = 0, s = 1, t = 1;
    while (n) {
        if (n & 1) {
            ret = safeAdd(ret, safeMul(s, t, MOD), MOD);
            s = safeMul(s, x, MOD);
        }
        t = safeMul(t, safeAdd(x, 1, MOD), MOD);
        x = safeMul(x, x, MOD);
        n >>= 1;
    }
    return ret;
}
 
int phi(int n) {
    int ret = 1;
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            ret *= (i - 1);
            n /= i;
            while (n % i == 0) {
                ret *= i;
                n /= i;
            }
        }
    }
    if (n != 1) {
        ret *= (n - 1);
        n = 1;
    }
    return ret;
}
 
int l;
 
int getb(int n, int mp, int mq) {
    int m = mp * mq;
    if (n == 1) {
        return 1;
    }
    do {
        int g = __gcd(mq, l - 1);
        if (g == 1) {
            break;
        }
        mp *= g, mq /= g;
    } while (true);
    int bn1;
    if (mq == 1) {
        bn1 = 1;
        for (int i = 2; i < n; ++i) {
            int last = bn1;
            bn1 = safeMul(2, powSum(l, bn1, m), m);
            if (bn1 == last) {
                break;
            }
        }
    } else {
        bn1 = getb(n - 1, mp, phi(mq));
    }
    return safeMul(2, powSum(l, bn1, m), m);
}
 
int main() {
    freopen("sum.in", "r", stdin);
	freopen("sum.out", "w", stdout);
	int n, m;
        int ans;
		scanf("%d%d%d", &n, &m, &l);
        if (n == 0) {
            ans = 1 % m;
        } else if (n == 1) {
            ans = l % m;
        } else {
            int bn = getb(n, 1, m);
            ans = ((long long)(l - 1) * bn + 1) % m;
        }
	printf("%d\n", ans);
    return 0;
}
