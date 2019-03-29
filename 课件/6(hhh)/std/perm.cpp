# include <cstdio>
# include <iostream>
# include <algorithm>
# include <map>
using namespace std;
# define REP(i, n) for (int i = 1; i <= n; i ++)
const int NR = 100100;
# define u t[x]
# define lc ch[0]
# define rc ch[1]
# define ulfc t[u.lc]
# define urtc t[u.rc]
struct Seg {int ch[2], max; bool cov;} t[NR << 2];
map <int, int> pos;
int n, a[NR], tp[NR], sz, q0, fa[NR];
int gf (int x) {return fa[x] == x ? x : (fa[x] = gf (fa[x]));}
inline void Upd (int x)
{
    u.max = 0;
    if (a[ulfc.max] > a[u.max]) u.max = ulfc.max;
    if (a[urtc.max] > a[u.max]) u.max = urtc.max;
}
int Max (int x, int l, int r, int ql, int qr)
{
    if (u.cov) return 0;
    if (ql <= l && r <= qr) return u.max;
    int mid = (l + r) >> 1, ret = 0, tmp;
    if (ql <= mid && a[tmp = Max (u.lc, l, mid, ql, qr)] > a[ret]) ret = tmp; 
    if (qr > mid && a[tmp = Max (u.rc, mid + 1, r, ql, qr)] > a[ret]) ret = tmp; 
    return ret;
}
void Del (int x, int l, int r, int cl, int cr)
{
    if (u.cov) return ;
    if (cl <= l && r <= cr) {u.cov = 1, u.max = 0; return ;}
    int mid = (l + r) >> 1, ret = 0;
    if (cl <= mid) Del (u.lc, l, mid, cl, cr);
    if (cr > mid) Del (u.rc, mid + 1, r, cl, cr);
    Upd (x);
}
int Build (int l, int r)
{
    int x = ++ sz, mid = (l + r) >> 1; u.cov = 0;
    if (l == r) return u.max = l, x;
    return u.lc = Build (l, mid), u.rc = Build (mid + 1, r), Upd (x), x;
}
bool Cmp (int i, int j) {return a[i] < a[j];}
int main ()
{
    freopen("perm.in", "r", stdin);
    freopen("perm.out", "w", stdout);
	    scanf ("%d", &n), sz = 0;
        REP (i, n) scanf ("%d", &a[i]), tp[i] = i, fa[i] = 0;
        sort (tp + 1, tp + n + 1, Cmp), Build (1, n);
        pos.clear (), pos[0] = 0;
        REP (p, n)
        {
            int i = tp[p];
            map <int, int>::iterator it = pos.upper_bound (i); it --;
            char sc = (p == n ? '\n' : ' ');
            if (it->first<it->second) 
            {
                printf ("%d%c", a[i + 1], sc);
                continue;
            }
            if (fa[i])
            {
                int j = gf (i);
                if (i == n || pos.find (i + 1) != pos.end () || a[j] > a[i + 1]) 
                    printf ("%d%c", a[j], sc), pos[i] = j, pos[j] = i;
                else 
                    Del (1, 1, n, i + 1, i + 1), fa[i + 1] = i, printf ("%d%c", a[i + 1], sc);
                continue;
            }
            int j = Max (1, 1, n, it->first + 1, i);
            if (i == n || pos.find (i + 1) != pos.end () || a[j] > a[i + 1])
                Del (1, 1, n, j, i), pos[i] = j, pos[j] = i, printf ("%d%c", a[j], sc);
            else Del (1, 1, n, i, i + 1), fa[i] = i, fa[i + 1] = i, printf ("%d%c", a[i + 1], sc);
        }
    return 0;
}
