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
	printf("%d %d %d %d %d\n",l,r,ql,qr,u.max);
    if (u.cov) return 0;
    if (ql <= l && r <= qr) return u.max;
    int mid = (l + r) >> 1, ret = 0, tmp;
    if (ql <= mid && a[tmp = Max (u.lc, l, mid, ql, qr)] > a[ret]) ret = tmp; 
    if (qr > mid && a[tmp = Max (u.rc, mid + 1, r, ql, qr)] > a[ret]) ret = tmp; 
    return ret;
}
void Del (int x, int l, int r, int cl, int cr)
{
	if(x==1) printf("del::[%d %d]\n",cl,cr);
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
	    scanf ("%d", &n), sz = 0;
        REP (i, n) scanf ("%d", &a[i]), tp[i] = i, fa[i] = 0;
        sort (tp + 1, tp + n + 1, Cmp), Build (1, n);
        pos.clear (), pos[0] = 0;
        REP (sd, n)
        {
            int p = tp[sd];
            map <int, int>::iterator it = pos.upper_bound (p); it --;
            printf ("(%d %d %d)\n", p, it->first, it->second);
            char sc = (sd == n ? '\n' : ' ');
            if (it->first<it->second) 
            {
                printf ("%d%c", a[p + 1], sc);
                continue;
            }
            if (fa[p])
            {
                int j = gf (p);
				printf("[%d]\n",j);
                if (p == n || pos.find (p + 1) != pos.end () || a[j] > a[p + 1]) 
                    printf ("%d%c", a[j], sc), pos[p] = j, pos[j] = p;
                else 
                    Del (1, 1, n, p + 1, p + 1), fa[p + 1] = p, printf ("%d%c", a[p + 1], sc);
                continue;
            }
            int j = Max (1, 1, n, it->first + 1, p);
            
            if (p == n || pos.find (p + 1) != pos.end () || a[j] > a[p + 1])
                Del (1, 1, n, j, p), pos[p] = j, pos[j] = p, printf ("%d%c", a[j], sc);
            else Del (1, 1, n, p, p + 1), fa[p] = p, fa[p + 1] = p, printf ("%d%c", a[p + 1], sc);
        }
    return 0;
}
