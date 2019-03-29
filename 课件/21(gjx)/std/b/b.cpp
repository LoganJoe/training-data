#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>

#define x first
#define y second
#define MP std::make_pair
#define SZ(x) ((int)(x).size())
#define ALL(x) (x).begin(), (x).end()
#define DEBUG(...) fprintf(stderr, __VA_ARGS__)
#ifdef __linux__
#define getchar getchar_unlocked
#define putchar putchar_unlocked
#endif

using std::pair;
using std::vector;
using std::string;

typedef long long LL;
typedef pair<int, int> Pii;

const int oo = 0x3f3f3f3f;

template<typename T> inline bool chkmax(T &a, T b) { return a < b ? a = b, true : false; }
template<typename T> inline bool chkmin(T &a, T b) { return b < a ? a = b, true : false; }
string procStatus()
{
    std::ifstream t("/proc/self/status");
    return string(std::istreambuf_iterator<char>(t), std::istreambuf_iterator<char>());
}
template<typename T> T read(T &x)
{
    int f = 1;
    char ch = getchar();
    for (; !isdigit(ch); ch = getchar())
        if (ch == '-')
            f = -1;
    for (x = 0; isdigit(ch); ch = getchar())
        x = 10 * x + (ch - '0');
    return x *= f;
}
template<typename T> void write(T x)
{
    if (x == 0) {
        putchar('0');
        return;
    }
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    static char s[20];
    int top = 0;
    for (; x; x /= 10)
        s[++top] = x % 10 + '0';
    while (top)
        putchar(s[top--]);
}
// EOT

const int MAXM = 1e5 + 5, MAXQ = 1e5 + 5, TOTP = MAXM * 3 + MAXQ;

int N, A, B, P, M, Q;
char S[MAXM];
Pii QRY[MAXQ];
int hash[TOTP];
int tothash;

namespace SEGT
{

const int SIZE = (TOTP << 2) + 5;

int sum[SIZE], lazy[SIZE];
int L, R;
int X;

#define LC (u << 1)
#define RC (u << 1 | 1)

inline void pushdown(int u, int len)
{
    if (lazy[u]) {
        sum[LC] += lazy[u] * (len >> 1);
        sum[RC] += lazy[u] * (len - (len >> 1));
        lazy[LC] += lazy[u];
        lazy[RC] += lazy[u];
        lazy[u] = 0;
    }
}

void _add(int u, int l, int r)
{
    if (L <= l && r <= R) {
        sum[u] += X * (r - l);
        lazy[u] += X;
        return;
    }
    pushdown(u, r - l);
    int mid = (l + r) >> 1;
    if (L < mid)
        _add(LC, l, mid);
    if (mid < R)
        _add(RC, mid, r);
    sum[u] = sum[LC] + sum[RC];
}

void _query(int u, int l, int r)
{
    if (l + 1 == r) {
        X += sum[u];
        return;
    }
    pushdown(u, r - l);
    int mid = (l + r) >> 1;
    if (L < mid)
        _query(LC, l, mid);
    else
        _query(RC, mid, r);
}

inline void add(int l, int r, int x)
{
    L = l; R = r; X = x;
    _add(1, 0, tothash);
}

inline int query(int p)
{
    L = p; X = 0;
    _query(1, 0, tothash);
    return X;
}

}

inline int mod(int x)
{
    return x >= N ? x - N : x;
}

inline int find(int x)
{
    return std::lower_bound(hash, hash + tothash, x) - hash;
}

inline void modify(int l, int r, int x)
{
    if (l > r) {
        SEGT::add(find(l), find(N), x);
        SEGT::add(find(0), find(r), x);
    } else
        SEGT::add(find(l), find(r), x);
}

void input()
{
    read(N); read(A); read(B); read(P); read(M);
    scanf("%s", S);
    read(Q);
    for (int i = 0; i < Q; ++i) {
        int type;
        scanf("%d%d", &type, &QRY[i].y);
        QRY[i].x = (type == 1);
    }
}

void solve()
{
    for (int i = 0; i < M; ++i) {
        int d = (LL)A * i % N;
        hash[tothash++] = mod(P - d + N);
        hash[tothash++] = mod(N - d + N);
        hash[tothash++] = mod(0 - d + N);
    }
    for (int i = 0; i < Q; ++i) {
        hash[tothash++] = ((LL)A * QRY[i].y + B) % N;
    }
    std::sort(hash, hash + tothash);
    tothash = std::unique(hash, hash + tothash) - hash;

    for (int i = 0; i < M; ++i) {
        int d = (LL)A * i % N;
        if (S[i] == '0')
            modify(mod(P - d + N), mod(N - d + N), +1);
        else
            modify(mod(0 - d + N), mod(P - d + N), +1);
    }

    for (int i = 0; i < Q; ++i) {
        int p = QRY[i].y;
        if (QRY[i].x) {
            int d = ((LL)A * p + B) % N;
            int ans = SEGT::query(find(d));

            write(ans); putchar('\n');
        } else {
            int d = (LL)A * p % N;
            if (S[p] == '0') {
                S[p] = '1';
                modify(mod(P - d + N), mod(N - d + N), -1);
                modify(mod(0 - d + N), mod(P - d + N), +1);
            } else {
                S[p] = '0';
                modify(mod(0 - d + N), mod(P - d + N), -1);
                modify(mod(P - d + N), mod(N - d + N), +1);
            }
        }
    }
}

int main()
{
    freopen("b.in", "r", stdin);
    freopen("b.out", "w", stdout);

    input();
    solve();

    return 0;
}
