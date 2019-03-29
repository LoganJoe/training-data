// Copyright (C) 2018 __debug.

// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation; version 3

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program; If not, see <http://www.gnu.org/licenses/>.


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

const int oo = 0x7fffffff;

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

const int MAXN = 5e5 + 5;

int N, M;
int A[MAXN];

void input()
{
    read(N); read(M);
    for (int i = 1; i <= N; ++i) {
        read(A[i]);
    }
}

namespace SEGT
{

const int SIZE = MAXN * 4 + 5;

int min[SIZE];
int same[SIZE];
int addt[SIZE];

#define LC (u << 1)
#define RC (u << 1 | 1)

inline void tagAdd(int u, int x)
{
    min[u] += x;
    addt[u] += x;
}

inline void pushdown(int u)
{
    if (addt[u]) {
        tagAdd(LC, addt[u]);
        tagAdd(RC, addt[u]);
        addt[u] = 0;
    }
}

inline void pushup(int u)
{
    min[u] = std::min(min[LC], min[RC]);
    same[u] = ~(min[LC] ^ min[RC]) & same[LC] & same[RC];
}

void build(int u, int l, int r)
{
    if (l == r) {
        min[u] = A[l];
        same[u] = ~0;
        return;
    }
    int mid = (l + r) >> 1;
    build(LC, l, mid);
    build(RC, mid + 1, r);
    pushup(u);
}

void applyAND(int u, int l, int r, int ql, int qr, int x)
{
    if (ql <= l && r <= qr) {
        int s = same[u] & ~x;
        tagAdd(u, -(min[u] & s));
        x |= s;
        if (!~x) return;
    }
    pushdown(u);
    int mid = (l + r) >> 1;
    if (ql <= mid) applyAND(LC, l, mid, ql, qr, x);
    if (mid < qr) applyAND(RC, mid + 1, r, ql, qr, x);
    pushup(u);
}

void applyOR(int u, int l, int r, int ql, int qr, int x)
{
    if (ql <= l && r <= qr) {
        int s = same[u] & x;
        tagAdd(u, ~min[u] & s);
        x ^= s;
        if (!x) return;
    }
    pushdown(u);
    int mid = (l + r) >> 1;
    if (ql <= mid) applyOR(LC, l, mid, ql, qr, x);
    if (mid < qr) applyOR(RC, mid + 1, r, ql, qr, x);
    pushup(u);
}

int queryMin(int u, int l, int r, int ql, int qr)
{
    if (ql <= l && r <= qr)
        return min[u];
    pushdown(u);
    int mid = (l + r) >> 1;
    int ret = +oo;
    if (ql <= mid) chkmin(ret, queryMin(LC, l, mid, ql, qr));
    if (mid < qr) chkmin(ret, queryMin(RC, mid + 1, r, ql, qr));
    return ret;
}

}

void solve()
{
    SEGT::build(1, 1, N);
    while (M--) {
        int tp, l, r, x;
        read(tp); read(l); read(r);
        if (tp == 1) {
            read(x);
            SEGT::applyAND(1, 1, N, l, r, x);
        } else if (tp == 2) {
            read(x);
            SEGT::applyOR(1, 1, N, l, r, x);
        } else if (tp == 3) {
            int ans = SEGT::queryMin(1, 1, N, l, r);
            write(ans); putchar('\n');
        }
    }
}

int main()
{
    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);

    input();
    solve();

    return 0;
}
