#include <cstdio>
#include <queue>
#define N 300005
using namespace std;
int n,a[N],p=2;
struct O{int l,r,x;}tmp;
struct T{int l,r;}t[N];
queue<O>q;
void d(int x){
    if (--n) printf("%d ",x);
    else printf("%d\n",x);
    if (t[x].l) d(t[x].l);
    if (t[x].r) d(t[x].r);
}
int main(){
   // freopen("A.in","r",stdin);freopen("A.out","w",stdout);
    scanf("%d",&n);
    for (int i=1;i<=n;i++) scanf("%d",&a[i]);
    tmp.l=1;tmp.r=n;tmp.x=a[1];q.push(tmp);
    while(!q.empty()){
        O w=q.front();q.pop();
        printf("%d %d %d %d\n",w.x,w.l,w.r,a[p]);
        if (a[p]>=w.l && a[p]<w.x){
            tmp.l=w.l;tmp.r=w.x-1;tmp.x=a[p];
            q.push(tmp);t[w.x].l=a[p++];
        }
        printf("%d %d %d %d\n",w.x,w.l,w.r,a[p]);
        if (a[p]>w.x && a[p]<=w.r){
            tmp.l=w.x+1;tmp.r=w.r;tmp.x=a[p];
            q.push(tmp);t[w.x].r=a[p++];
        }
    }
    d(a[1]);return 0;
}
