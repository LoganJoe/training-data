---
title: " DTOJ3575Mathematical Analysis\t\t"
tags:
  - 奇技淫巧
  - 最小生成树
url: 1801.html
id: 1801
categories:
  - Solution
date: 2018-04-29 21:02:23
---

题意即是求曼哈顿距离最小生成树。 这个东西将所有的边全部连出来是O(n^2)的。这个数据范围肯定吃翔了。但是我们可以证明，对于每个点只需要对于其八个半象限中距它最近的点连边即可。这个可以通过三角形不等式证明其选择其他所有点肯定不优。 那么对于一个半象限，我们可以利用排序固定一维坐标，然后用树状数组查询另外一维的最小值，使得$\\delta x+\\delta y$最小。对于其他的半象限，我们可以通过坐标的翻转与变换来实现。由于是无向图，只需要找出其中的一二象限的点即可。 说的十分轻巧然后代码还是吃翔了。

#include<bits/stdc++.h>
using namespace std;
#define N 200005
#define ll long long
#define inf 1e18
int n,m,tot,cnt,head\[N\],f\[N\],l\[N\],lisan\[N\];
long long ans;
struct Point
{   int x,y,id;
    friend bool operator <(Point t1,Point t2){return t1.x<t2.x || t1.x==t2.x && t1.y<t2.y;}
}p\[N\],ts\[N\];
struct node
{   
    int u,v;ll w;
    friend bool operator <(node t1,node t2){return t1.w<t2.w;}
}s\[N<<4\];
void add1(int u,int v,ll w){s\[++tot\]=(node){u,v,w};}
struct edge{int u,v;ll w;int next;}e\[N<<1\];
void add(int u,int v,ll w){e\[++cnt\]=(edge){u,v,w,head\[u\]};head\[u\]=cnt;}
ll dist(int a,int b){return (ll)abs((ll)p\[a\].x-p\[b\].x)+abs((ll)p\[a\].y-p\[b\].y);}
class BIT
{
    ll t\[N\],p\[N\];
    int lowbit(int x) {return x&(-x);}
public:
    void add(int x,int y,int pos){for(int i=x;i;i-=lowbit(i)) if(t\[i\]>y) t\[i\]=y,p\[i\]=pos;}
    int ask(int x){int ret=inf,pos=n+1;for(int i=x;i<=n;i+=lowbit(i)) if(t\[i\]<ret) ret=t\[i\],pos=p\[i\];return pos;}
    void clear(){for(int i=1;i<=n;i++) t\[i\]=inf;} 
}T;
void discrate()
{
    for(int i=1;i<=n;i++) l\[i\]=p\[i\].y-p\[i\].x;
    sort(l+1,l+1+n);
    for(int i=1;i<=n;i++) lisan\[i\]=lower_bound(l+1,l+1+n,p\[i\].y-p\[i\].x)-l;  
}
void solve()  
{  
    sort(p+1,p+1+n); 
    discrate();T.clear();  
    int pos;  
    for(int i=n;i>=1;i--) 
    {  
        pos=T.ask(lisan\[i\]);  
        if(pos!=n+1) add1(p\[i\].id,p\[pos\].id,dist(i,pos));  
        T.add(lisan\[i\],p\[i\].y+p\[i\].x,i);  
    }  
} 
void prepare()
{
    for(int i=1;i<=4;i++)
    {  
        if(i==3)  
            for(int j=1;j<=n;j++)p\[j\].x=n-p\[j\].x;  
        if(i==2||i==4)  
            for(int j=1;j<=n;j++)swap(p\[j\].x,p\[j\].y);  
        solve();  
    }     
     
}
int find(int x){return f\[x\]==x?f\[x\]:f\[x\]=find(f\[x\]);};
void kruscal()
{   
    for(int i=1;i<=n;i++) f\[i\]=i;
    sort(s+1,s+1+tot);
    int tos=0;
    for(int i=1;i<=tot;i++)
    {
        int tx=find(s\[i\].u),ty=find(s\[i\].v);
        if(tx!=ty) add(s\[i\].u,s\[i\].v,s\[i\].w),add(s\[i\].v,s\[i\].u,s\[i\].w),tos++,ans+=s\[i\].w,f\[tx\]=ty;  
        if(tos==n-1) break;
    }
}
int fa\[N\],deep\[N\],pre\[N\]\[20\];
long long Max\[N\]\[20\];
void dfs(int u,int dad)
{
    for(int i=head\[u\];i;i=e\[i\].next)
    {
        int v=e\[i\].v;
        if(v==dad) continue;
        fa\[v\]=u,deep\[v\]=deep\[u\]+1;
        pre\[v\]\[0\]=u,Max\[v\]\[0\]=e\[i\].w;
        dfs(v,u);
    }
}
void init()
{
    deep\[1\]=1;dfs(1,0);
    for(int j=1;j<=19;j++)
        for(int i=1;i<=n;i++) 
        {   
            pre\[i\]\[j\]=pre\[pre\[i\]\[j-1\]\]\[j-1\];
            Max\[i\]\[j\]=max(Max\[pre\[i\]\[j-1\]\]\[j-1\],Max\[i\]\[j-1\]);
        }
}
ll lca(int x,int y)
{
    if(deep\[x\]>deep\[y\]) swap(x,y);
    int tot=0,res=deep\[y\]-deep\[x\];long long ret=0;
    while(res){if(res&1) ret=max(ret,Max\[y\]\[tot\]),y=pre\[y\]\[tot\];res/=2,tot++;}
    tot=0;
    while(x!=y)
        if(pre\[x\]\[tot\]!=pre\[y\]\[tot\] || (tot==0 && pre\[x\]\[tot\]==pre\[y\]\[tot\]))
        {
            ret=max(ret,Max\[x\]\[tot\]),ret=max(ret,Max\[y\]\[tot\]);
            x=pre\[x\]\[tot\],y=pre\[y\]\[tot\];
            tot++;
        }
        else tot--;
    return ret;
}
int main()
{
    //freopen("analysis.in","r",stdin);
    //freopen("analysis.out","w",stdout);
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d%d",&p\[i\].x,&p\[i\].y),p\[i\].id=i,ts\[i\]=p\[i\];
    scanf("%d",&m);
    prepare();
    kruscal();
    init();
    for(int i=1;i<=n;i++) p\[i\]=ts\[i\];
    while(m--)
    {
        int a,b;scanf("%d%d",&a,&b);
        printf("%lld\\n",ans-lca(a,b)+dist(a,b));
    }
    return 0;
}