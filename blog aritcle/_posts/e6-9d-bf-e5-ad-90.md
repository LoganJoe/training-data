---
title: " [板子]\t\t"
url: 2197.html
id: 2197
comments: false
categories:
  - Others
date: 2018-01-01 00:00:11
tags:
---

大坑。

数据结构
====

### Splay

维护一个长度为$n$的数列，支持区间翻转，区间加，区间求和及区间最大值。

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<queue>
#include<vector>
#include<map>
#include<set>
using std::cin;using std::cerr;
using std::max;using std::min;
#define N 100005
#define ll long long
#define db double
#define dbg1(x) cerr<<#x<<"="<<x<<" "
#define dbg2(x) cerr<<#x<<"="<<x<<"\\n"
int n,m,A\[N\];
class SplayTree
{
#define lc t\[x\].son\[0\]
#define rc t\[x\].son\[1\]
#define pa t\[x\].fa
    struct node{int son\[2\],fa,sz,v,Sum,Max,f,rev;}t\[N\];
    bool getson(int x) {return t\[pa\].son\[1\]==x;}
    void upd(int x,int v) {t\[x\].v+=v,t\[x\].Max+=v,t\[x\].f+=v,t\[x\].Sum+=t\[x\].sz*v;}
    void pushup(int x)
    {
        t\[x\].sz=1,t\[x\].Sum=t\[x\].Max=t\[x\].v;
        if(lc) t\[x\].sz+=t\[lc\].sz,t\[x\].Sum+=t\[lc\].Sum,t\[x\].Max=max(t\[x\].Max,t\[lc\].Max);
        if(rc) t\[x\].sz+=t\[rc\].sz,t\[x\].Sum+=t\[rc\].Sum,t\[x\].Max=max(t\[x\].Max,t\[rc\].Max);
    }
    void pushdown(int x)
    {
        if(t\[x\].f)
        {
            if(lc) upd(lc,t\[x\].f);
            if(rc) upd(rc,t\[x\].f);
            t\[x\].f=0;
        }
        if(t\[x\].rev) std::swap(lc,rc),t\[lc\].rev^=1,t\[rc\].rev^=1,t\[x\].rev=0;
    }
    void rotate(int x)
    {
        int y=pa,z=t\[y\].fa,k=getson(x);
        t\[y\].son\[k\]=t\[x\].son\[!k\],t\[t\[x\].son\[!k\]\].fa=y;
        t\[x\].son\[!k\]=y,t\[y\].fa=x,t\[x\].fa=z;
        if(z) t\[z\].son\[t\[z\].son\[1\]==y\]=x;
        pushup(y);
    }
    void splay(int x,int f=0)
    {
        for(;pa^f;rotate(x))
            if(t\[pa\].fa^f) rotate(getson(x)^getson(pa)?x:pa);
        pushup(x);if(!f) root=x;
    }
    int find(int x,int k)
    {
        pushdown(x);
        if(k==t\[lc\].sz+1) return x;
        return t\[lc\].sz<k?find(rc,k-t\[lc\].sz-1):find(lc,k);
    }
    int split(int x,int y)
    {
        splay(find(root,x)),splay(find(root,y),root);
        return t\[t\[root\].son\[1\]\].son\[0\];
    }
public:
    int root,cntnode;
    void build(int &x,int l,int r)
    {
        x=++cntnode;int mid=l+r>>1;
        if(l<mid) build(lc,l,mid-1),t\[lc\].fa=x;
        if(r>mid) build(rc,mid+1,r),t\[rc\].fa=x;
        t\[x\].v=A\[mid\],pushup(x);
    }
    void reverse(int l,int r) {int x=split(l,r+2);t\[x\].rev^=1;}
    void add(int l,int r,int v) {int x=split(l,r+2);upd(x,v);}
    int askMax(int l,int r) {int x=split(l,r+2);return t\[x\].Max;}
    int askSum(int l,int r) {int x=split(l,r+2);return t\[x\].Sum;}
}T;
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=2;i<=n+1;i++) scanf("%d",&A\[i\]);
    n+=2,T.build(T.root,1,n);
    for(int op,a,b,c;m--;)
    {
        scanf("%d%d%d",&op,&a,&b);
        if(op==1) scanf("%d",&c),T.add(a,b,c);
        if(op==2) T.reverse(a,b);
        if(op==3) printf("%d\\n",T.askMax(a,b));
        if(op==4) printf("%d\\n",T.askSum(a,b)); 
    }
    return 0;
}

### Treap（旋转）

支持插入、删除、查询$x$的排名、查询排名为$x$的数、查询$x$的前驱和后继。

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<queue>
#include<vector>
#include<map>
#include<set>
using std::cin;using std::cerr;
using std::max;using std::min;
#define N 100005
#define inf 1e9
#define ll long long
#define db double
#define dbg1(x) cerr<<#x<<"="<<x<<" "
#define dbg2(x) cerr<<#x<<"="<<x<<"\\n"
int n,op,a;
class Treap
{
#define lc t\[x\].son\[0\]
#define rc t\[x\].son\[1\]
#define pa t\[x\].fa
    struct node{int son\[2\],fa,rk,v,cnt,sz;}t\[N\];
    bool getson(int x) {return t\[pa\].son\[1\]==x;}
    void pushup(int x) {t\[x\].sz=t\[lc\].sz+t\[rc\].sz+t\[x\].cnt;}
    void rotate(int x)
    {
        int y=t\[x\].fa,z=t\[y\].fa,k=getson(x);
        t\[y\].son\[k\]=t\[x\].son\[!k\],t\[t\[x\].son\[!k\]\].fa=y;
        t\[x\].son\[!k\]=y,t\[y\].fa=x,t\[x\].fa=z;
        if(z) t\[z\].son\[t\[z\].son\[1\]==y\]=x;
        if(y==root) root=x;//根发生了变化 
        pushup(y),pushup(x);
    }
public:
    int root,cntnode;
    void insert(int &x,int fa,int v)
    {
        if(!x)
            {t\[x=++cntnode\].fa=fa,t\[x\].v=v,t\[x\].rk=rand(),t\[x\].cnt=t\[x\].sz=1;return;}
        if(t\[x\].v==v) {t\[x\].cnt++,t\[x\].sz++;return;}//sz和cnt都要+1 
        if(t\[x\].v>v)
        {
            insert(lc,x,v);
            if(t\[lc\].rk<t\[x\].rk) rotate(lc);//旋转使得保持堆的性质 
        }
        else
        {
            insert(rc,x,v);
            if(t\[rc\].rk<t\[x\].rk) rotate(rc);//旋转使得保持堆的性质
        }
        pushup(x);
    }
    void Delete(int &x,int v)
    {
        if(!x) return;
        if(t\[x\].v==v)
        {
            if(t\[x\].cnt>1) {t\[x\].cnt--,t\[x\].sz--;return;}//cnt和sz都要-1 
            if(!lc&&!rc) {t\[pa\].son\[getson(x)\]=0;return;}//直接删 
            if(!lc) {t\[rc\].fa=pa,x=rc;return;}//注意要修改rc的父亲 
            if(!rc) {t\[lc\].fa=pa;x=lc;return;}//注意要修改lc的父亲
            rotate(t\[lc\].rk<t\[rc\].rk?lc:rc);//把x往下降一层 
            return Delete(x,v);
        }
        Delete(t\[x\].v>v?lc:rc,v),pushup(x);
    }
    int askRank(int x,int v)//询问v的排名 
    {
        if(v==t\[x\].v) return t\[lc\].sz+1;
        return t\[x\].v>v?askRank(lc,v):t\[lc\].sz+t\[x\].cnt+askRank(rc,v);
    }
    int findRank(int x,int v)//询问排名为v的数 
    {
        if(v>t\[lc\].sz&&v<=t\[lc\].sz+t\[x\].cnt) return t\[x\].v;
        return v<=t\[lc\].sz?findRank(lc,v):findRank(rc,v-t\[lc\].sz-t\[x\].cnt);
    }
    int askpre(int x,int v)//询问v的前驱 
    {
        if(!x) return 0;
        return t\[x\].v<v?max(t\[x\].v,askpre(rc,v)):askpre(lc,v);
    }
    int asknex(int x,int v)//询问v的后继 
    {
        if(!x) return inf;
        return t\[x\].v>v?min(t\[x\].v,asknex(lc,v)):asknex(rc,v);
    }
}T;
int main()
{
    for(scanf("%d",&n);n--;)
    {
        scanf("%d%d",&op,&a);
        if(op==1) T.insert(T.root,0,a);
        if(op==2) T.Delete(T.root,a);
        if(op==3) printf("%d\\n",T.askRank(T.root,a));
        if(op==4) printf("%d\\n",T.findRank(T.root,a));
        if(op==5) printf("%d\\n",T.askpre(T.root,a));
        if(op==6) printf("%d\\n",T.asknex(T.root,a));
    }
    return 0;
}

### Treap（非旋转）

支持插入、删除、查询$x$的排名、查询排名为$x$的数、查询$x$的前驱和后继，同时注明了如果有标记要pushdown的位置。

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<queue>
#include<vector>
#include<map>
#include<set>
using std::cin;using std::cerr;
using std::max;using std::min;
#define N 100005
#define ll long long
#define db double
#define dbg1(x) cerr<<#x<<"="<<x<<" "
#define dbg2(x) cerr<<#x<<"="<<x<<"\\n"
int n,op,a;
class Treap
{
#define lc t\[x\].son\[0\]
#define rc t\[x\].son\[1\]
    struct node{int son\[2\],rk,v,sz;}t\[N\];
    int newnode(int v) {int x=++cntnode;t\[x\].rk=rand(),t\[x\].sz=1,t\[x\].v=v;return x;}
    void pushup(int x) {t\[x\].sz=t\[lc\].sz+t\[rc\].sz+1;}
    int merge(int x,int y)//合并以x为根的Treap和以y为根的Treap并返回合并后的根 
    {
        if(!x||!y) return x+y;
        if(t\[x\].rk<t\[y\].rk) {/\*pushdown(x),\*/rc=merge(rc,y),pushup(x);return x;}
        else {/\*pushdown(y),\*/t\[y\].son\[0\]=merge(x,t\[y\].son\[0\]),pushup(y);return y;}
    }
    void split(int now,int &x,int &y,int v)//将以now为根的Treap按<=v分裂成以x为根和以y为根的Treap
    {
        if(!now) return void(x=y=0);
//      pushdown(now);
        if(t\[now\].v<=v) x=now,split(t\[now\].son\[1\],t\[now\].son\[1\],y,v);
        else y=now,split(t\[now\].son\[0\],x,t\[now\].son\[0\],v);
        pushup(now);
    }
    /\* 
    void split(int now,int &x,int &y,int v)//将以now为根的Treap按size分裂成以x为根和以y为根的Treap
    {
        if(!now) return void(x=y=0);
        if(!v) {x=0,y=now;return;}//加了常数小 
        if(t\[now\].sz==v) {x=now,y=0;return;}//加了常数小
        pushdown(now);
        if(v<=t\[t\[now\].son\[0\]\].sz) y=now,split(t\[now\].son\[0\],x,t\[now\].son\[0\],v);
        else x=now,split(t\[now\].son\[1\],t\[now\].son\[1\],y,v-t\[t\[now\].son\[0\]\].sz-1);
        pushup(now);
    }
    */ 
public:
    int root,cntnode;
    void insert(int v) {int x,y;split(root,x,y,v),root=merge(merge(x,newnode(v)),y);}
    void Delete(int v)
    {
        int x,y,z;
        split(root,x,z,v),split(x,x,y,v-1),y=merge(t\[y\].son\[0\],t\[y\].son\[1\]);
        root=merge(merge(x,y),z);
    }
    int askRank(int v)//询问v的排名 
    {
        int x,y,res;
        split(root,x,y,v-1),res=t\[x\].sz+1,root=merge(x,y);
        return res;
    }
    int findRank(int x,int v)//询问排名为v的数 
    {
        if(v==t\[lc\].sz+1) return t\[x\].v;
        return v<=t\[lc\].sz?findRank(lc,v):findRank(rc,v-t\[lc\].sz-1);
    }
    int askpre(int v)//询问x的前驱 
    {
        int x,y,res;
        split(root,x,y,v-1),res=findRank(x,t\[x\].sz),root=merge(x,y);
        return res;
    }
    int asknex(int v)//询问x的后继 
    {
        int x,y,res;
        split(root,x,y,v),res=findRank(y,1),root=merge(x,y);
        return res;
    }
}T;
int main()
{
    for(scanf("%d",&n);n--;)
    {
        scanf("%d%d",&op,&a);
        if(op==1) T.insert(a);
        if(op==2) T.Delete(a);
        if(op==3) printf("%d\\n",T.askRank(a));
        if(op==4) printf("%d\\n",T.findRank(T.root,a));
        if(op==5) printf("%d\\n",T.askpre(a));
        if(op==6) printf("%d\\n",T.asknex(a));
    }
    return 0;
}

维护一个长度为$n$的数列，支持区间翻转。

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<queue>
#include<vector>
#include<map>
#include<set>
using std::cin;using std::cerr;
using std::max;using std::min;
#define N 100005 
#define ll long long
#define db double
#define dbg1(x) cerr<<#x<<"="<<x<<" "
#define dbg2(x) cerr<<#x<<"="<<x<<"\\n"
int n,m,A\[N\],a,b;
class Treap
{
#define lc t\[x\].son\[0\]
#define rc t\[x\].son\[1\]
    int sta\[N\],top;
    struct node{int son\[2\],rk,v,sz,rev;}t\[N\];
    int newnode(int v) {int x=++cntnode;t\[x\].rk=rand(),t\[x\].v=v,t\[x\].sz=1;return x;}
    void pushup(int x) {t\[x\].sz=t\[lc\].sz+t\[rc\].sz+1;}
    void pushdown(int x)
        {if(t\[x\].rev) std::swap(lc,rc),t\[lc\].rev^=1,t\[rc\].rev^=1,t\[x\].rev=0;}
    int merge(int x,int y)//合并以x为根的Treap和以y为根的Treap并返回合并后的根 
    {
        if(!x||!y) return x+y;
        if(t\[x\].rk<t\[y\].rk) {pushdown(x),rc=merge(rc,y),pushup(x);return x;}
        else {pushdown(y),t\[y\].son\[0\]=merge(x,t\[y\].son\[0\]),pushup(y);return y;}
    }
    void split(int now,int &x,int &y,int v)//将以now为根的Treap按size分裂成以x为根和以y为根的Treap
    {
        if(!now) return void(x=y=0);
        if(!v) {x=0,y=now;return;}//加了常数小 
        if(t\[now\].sz==v) {x=now,y=0;return;}//加了常数小
        pushdown(now);
        if(t\[t\[now\].son\[0\]\].sz>=v) y=now,split(t\[now\].son\[0\],x,t\[y\].son\[0\],v);
        else x=now,split(t\[now\].son\[1\],t\[x\].son\[1\],y,v-t\[t\[now\].son\[0\]\].sz-1);
        pushup(now);
    }
public:
    int root,cntnode;
    void build(int &rt)
    {
        sta\[++top\]=newnode(A\[1\]);
        for(int i=2,x;i<=n;i++)
        {
            x=newnode(A\[i\]);
            for(;top&&t\[x\].rk<t\[sta\[top\]\].rk;top--) pushup(sta\[top\]),t\[x\].son\[0\]=sta\[top\];
            if(top) t\[sta\[top\]\].son\[1\]=x;sta\[++top\]=x;
        }
        for(rt=sta\[1\];top;top--) pushup(sta\[top\]);
    }
    void reverse(int l,int r)
    {
        int x,y,z;split(root,x,z,r),split(x,x,y,l-1);
        t\[y\].rev^=1,root=merge(merge(x,y),z);
    }
    void dfs(int x)
        {pushdown(x);if(lc) dfs(lc);printf("%d ",t\[x\].v);if(rc) dfs(rc);}
}T;
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) A\[i\]=i;
    T.build(T.root);
    for(int i=1;i<=m;i++) scanf("%d%d",&a,&b),T.reverse(a,b);
    T.dfs(T.root);
    return 0;
}

### 可持久化Treap

支持每个历史版本的插入、删除、查询$x$的排名、查询排名为$x$的数、查询$x$的前驱和后继（每一次操作生成一个新的版本）。

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<queue>
#include<vector>
#include<map>
#include<set>
using std::cin;using std::cerr;
using std::max;using std::min;
#define N 500005
#define ll long long
#define db double
#define dbg1(x) cerr<<#x<<"="<<x<<" "
#define dbg2(x) cerr<<#x<<"="<<x<<"\\n"
int n,op,a,b;
class Treap
{
#define lc t\[x\].son\[0\]
#define rc t\[x\].son\[1\]
    struct node{int son\[2\],rk,sz,v;}t\[N*50\];
    void pushup(int x) {t\[x\].sz=t\[lc\].sz+t\[rc\].sz+1;}
    int newnode(int v) {int x=++cntnode;t\[x\].rk=rand(),t\[x\].sz=1,t\[x\].v=v;return x;}
    int merge(int x,int y)//合并以x为根的Treap和以y为根的Treap并返回合并后的根
    {
        if(!x||!y) return x+y;
        int now=++cntnode;//要新建节点 
        if(t\[x\].rk<t\[y\].rk) t\[now\]=t\[x\],t\[now\].son\[1\]=merge(rc,y);
        else t\[now\]=t\[y\],t\[now\].son\[0\]=merge(x,t\[y\].son\[0\]);
        pushup(now);
        return now;
    }
    void split(int now,int &x,int &y,int v)//将以now为根的Treap按<=v分裂成以x为根和以y为根的Treap
    {
        if(!now) return void(x=y=0);//要新建节点
        if(t\[now\].v<=v) t\[x=++cntnode\]=t\[now\],split(rc,rc,y,v),pushup(x);
        else t\[y=++cntnode\]=t\[now\],split(t\[y\].son\[0\],x,t\[y\].son\[0\],v),pushup(y);
    }
public:
    int root\[N\],cntnode;
    void insert(int &rt,int v) {int x=0,y=0;split(rt,x,y,v),rt=merge(merge(x,newnode(v)),y);}
    void Delete(int &rt,int v)
    {
        int x=0,y=0,z=0;
        split(rt,x,z,v),split(x,x,y,v-1);
        y=merge(t\[y\].son\[0\],t\[y\].son\[1\]),rt=merge(merge(x,y),z);
    }
    int askRank(int &rt,int v)//询问v的排名
    {
        int x=0,y=0,res;
        split(rt,x,y,v-1),res=t\[x\].sz+1,rt=merge(x,y);
        return res;
    }
    int findRank(int &x,int v)//询问排名为v的数
    {
        if(t\[lc\].sz+1==v) return t\[x\].v;
        return t\[lc\].sz>=v?findRank(lc,v):findRank(rc,v-t\[lc\].sz-1);
    }
    int askpre(int &rt,int v)//询问x的前驱
    {
        int x=0,y=0,res;split(rt,x,y,v-1);
        if(!x) return -2147483647;
        res=findRank(x,t\[x\].sz),rt=merge(x,y);
        return res;
    }
    int asknex(int &rt,int v)//询问x的后继
    {
        int x=0,y=0,res;split(rt,x,y,v);
        if(!y) return 2147483647;
        res=findRank(y,1),rt=merge(x,y);
        return res;
    }
}T;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d%d",&b,&op,&a),T.root\[i\]=T.root\[b\];
        if(op==1) T.insert(T.root\[i\],a);
        if(op==2) T.Delete(T.root\[i\],a);
        if(op==3) printf("%d\\n",T.askRank(T.root\[i\],a));
        if(op==4) printf("%d\\n",T.findRank(T.root\[i\],a));
        if(op==5) printf("%d\\n",T.askpre(T.root\[i\],a));
        if(op==6) printf("%d\\n",T.asknex(T.root\[i\],a));
    }
    return 0;
}

### Link-Cut-Tree

支持加边和删边以及询问两点连通性，同时注明了如果要维护其他信息应该pushup的位置。

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<queue>
#include<vector>
#include<set>
#include<map>
using namespace std;
#define N 10005
#define ll long long
#define db double
#define dbg1(x) cout<<#x<<"="<<x<<" "
#define dbg2(x) cout<<#x<<"="<<x<<"\\n"
int n,m,a,b;
char s\[9\];
class LinkCutTree
{
#define lc t\[x\].son\[0\]
#define rc t\[x\].son\[1\]
#define pa t\[x\].fa
    struct node{int son\[2\],fa,rev;}t\[N\];
    void pushdown(int x) {if(t\[x\].rev) swap(lc,rc),t\[lc\].rev^=1,t\[rc\].rev^=1,t\[x\].rev=0;}
    bool getson(int x) {return t\[pa\].son\[1\]==x;}
    bool isroot(int x) {return t\[pa\].son\[0\]!=x&&t\[pa\].son\[1\]!=x;}
    void update(int x) {if(!isroot(x)) update(pa);pushdown(x);}
    void rotate(int x)
    {
        int y=pa,z=t\[y\].fa,k=getson(x);
        if(!isroot(y)) t\[z\].son\[t\[z\].son\[1\]==y\]=x;
        t\[y\].son\[k\]=t\[x\].son\[!k\],t\[t\[x\].son\[!k\]\].fa=y;
        t\[x\].son\[!k\]=y,t\[y\].fa=x,t\[x\].fa=z;
        //pushup(y);
    }
    void splay(int x)
    {
        for(update(x);!isroot(x);rotate(x))
            if(!isroot(pa)) rotate(getson(x)^getson(pa)?x:pa);
        //pushup(x); 
    }
    void access(int x) {for(int y=0;x;y=x,x=pa) splay(x),rc=y/\*pushup(x)\*/;}
    void makeroot(int x) {access(x),splay(x),t\[x\].rev^=1;}//将x变成所在LCT的根 
    int findroot(int x) {for(access(x),splay(x);lc;x=lc);return x;}//找这棵LCT的根 
public:
    void Link(int x,int y) {makeroot(x),t\[x\].fa=y,splay(y);}//在x和y之间连一条边 
    void Cut(int x,int y) {makeroot(x),access(y),splay(y),t\[y\].son\[0\]=pa=0;}//删去x和y之间的边 
    bool ask(int x,int y) {return findroot(x)==findroot(y);}//判断x和y是否连通 
}T;
int main()
{
    for(scanf("%d%d",&n,&m);m--;)
    {
        scanf("%s%d%d",s,&a,&b);
        if(s\[0\]=='C') T.Link(a,b);
        if(s\[0\]=='D') T.Cut(a,b);
        if(s\[0\]=='Q') puts(T.ask(a,b)?"Yes":"No");
    }
    return 0;
}

### K-D Tree

有$n$个点，支持查询每个点离其它点最近的曼哈顿距离和最远的曼哈顿距离。

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<queue>
#include<vector>
#include<set>
#include<map>
using std::cin;using std::cerr;
using std::max;using std::min;
#define N 500005
#define inf 1e9
#define ll long long
#define db double
#define dbg1(x) cerr<<#x<<"="<<x<<" "
#define dbg2(x) cerr<<#x<<"="<<x<<"\\n"
int D,n,ans=inf;//D是标记当前以第几维坐标排序 
struct point{int x,y;}p\[N\];
class KDTree
{
#define lc t\[x\].ls
#define rc t\[x\].rs
#define mid (l+r>>1)
    struct node
    {
        int ls,rs,d\[2\],mx\[2\],mn\[2\];
        friend bool operator<(node t1,node t2) {return t1.d\[D\]<t2.d\[D\];}
    }t\[N\];
    int Dist(node x,point p) {return abs(x.d\[0\]-p.x)+abs(x.d\[1\]-p.y);}
    void pushup(int x)
    {
        if(lc)
            for(int i=0;i<2;i++)
                t\[x\].mx\[i\]=max(t\[x\].mx\[i\],t\[lc\].mx\[i\]),t\[x\].mn\[i\]=min(t\[x\].mn\[i\],t\[lc\].mn\[i\]);
        if(rc)
            for(int i=0;i<2;i++)
                t\[x\].mx\[i\]=max(t\[x\].mx\[i\],t\[rc\].mx\[i\]),t\[x\].mn\[i\]=min(t\[x\].mn\[i\],t\[rc\].mn\[i\]);
    }
    void build(int &x,int l,int r,int now)
    {
        if(l>r) return;
        D=now,std::nth_element(t+l,t+mid,t+r+1),x=mid;
        for(int i=0;i<2;i++) t\[x\].mn\[i\]=t\[x\].mx\[i\]=t\[x\].d\[i\];
        build(lc,l,mid-1,now^1),build(rc,mid+1,r,now^1);
        pushup(x);
    }
    int getMax(node x,point p)//p和一片区域最大的曼哈顿距离 
        {return max(abs(x.mx\[0\]-p.x),abs(x.mn\[0\]-p.x))+max(abs(x.mx\[1\]-p.y),abs(x.mn\[1\]-p.y));}
    int getMin(node x,point p)//p和一片区域最小的曼哈顿距离 
        {return max(p.x-x.mx\[0\],0)+max(x.mn\[0\]-p.x,0)+max(p.y-x.mx\[1\],0)+max(x.mn\[1\]-p.y,0);}
public:
    int root;
    void Build()
    {
        for(int i=1;i<=n;i++) t\[i\].d\[0\]=p\[i\].x,t\[i\].d\[1\]=p\[i\].y;
        build(root,1,n,0);
    }
    int askMax(int x,point p)
    {
        int res=Dist(t\[x\],p);
        int dl=lc?getMax(t\[lc\],p):-inf,dr=rc?getMax(t\[rc\],p):-inf;
        //估价后决定先走哪边或者不走（不然时间复杂度会爆炸）
        if(dl>dr)
        {
            if(dl>res) res=max(res,askMax(lc,p));
            if(dr>res) res=max(res,askMax(rc,p));
        }
        else
        {
            if(dr>res) res=max(res,askMax(rc,p));
            if(dl>res) res=max(res,askMax(lc,p));
        }
        return res;
    }
    int askMin(int x,point p)
    {
        int res=Dist(t\[x\],p)?Dist(t\[x\],p):inf;
        int dl=lc?getMin(t\[lc\],p):inf,dr=rc?getMin(t\[rc\],p):inf;
        //估价后决定先走哪边或者不走（不然时间复杂度会爆炸）
        if(dl<dr)
        {
            if(dl<res) res=min(res,askMin(lc,p));
            if(dr<res) res=min(res,askMin(rc,p));
        }
        else
        {
            if(dr<res) res=min(res,askMin(rc,p));
            if(dl<res) res=min(res,askMin(lc,p));
        }
        return res;
    }
}T;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d%d",&p\[i\].x,&p\[i\].y);
    T.Build();
    for(int i=1;i<=n;i++)
        ans=min(ans,T.askMax(T.root,p\[i\])-T.askMin(T.root,p\[i\]));
    printf("%d\\n",ans);
    return 0;
}

### 替罪羊树（待填）

### 可持久化数组

维护一个大小为$n$的数组，支持在某个历史版本的基础上修改某个位置，求某个历史版本某个位置的值（每一次操作生成一个新的版本）。

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<queue>
#include<vector>
#include<map>
#include<set>
using std::cin;using std::cerr;
using std::max;using std::min;
#define N 100005
#define ll long long
#define db double
#define dbg1(x) cerr<<#x<<"="<<x<<" "
#define dbg2(x) cerr<<#x<<"="<<x<<"\\n"
int n,m,A\[N\],op,a,b,c;
class PresidentTree
{
#define lc t\[x\].ls
#define rc t\[x\].rs
#define mid (l+r>>1)
    struct node{int ls,rs,v;}t\[N*20\];
public:
    int root\[N\],cntnode;
    void build(int &x,int l,int r)
    {
        if(!x) x=++cntnode;
        if(l==r) return void(t\[x\].v=A\[l\]);
        build(lc,l,mid),build(rc,mid+1,r);
    }
    void insert(int &x,int y,int l,int r,int p,int v)
    {
        t\[x=++cntnode\]=t\[y\];
        if(l==r) return void(t\[x\].v=v);
        p<=mid?insert(lc,t\[y\].ls,l,mid,p,v):insert(rc,t\[y\].rs,mid+1,r,p,v);
    }
    int ask(int x,int l,int r,int p)
    {
        if(l==r) return t\[x\].v;
        return p<=mid?ask(lc,l,mid,p):ask(rc,mid+1,r,p);
    }
}T;
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&A\[i\]);
    T.build(T.root\[0\],1,n);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d",&a,&op,&b);
        if(op==1)
            scanf("%d",&c),T.insert(T.root\[i\],T.root\[a\],1,n,b,c);
        else T.root\[i\]=T.root\[a\],printf("%d\\n",T.ask(T.root\[a\],1,n,b));
    }
    return 0;
}

### 可持久化并查集

支持合并集合、回到某个版本和查询是否属于同一集合。

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<queue>
#include<vector>
#include<map>
#include<set>
using std::cin;using std::cerr;
using std::max;using std::min;
#define N 200005
#define ll long long
#define db double
#define pii std::pair<int,int>
#define mp std::make_pair
#define fi first
#define se second
#define dbg1(x) cerr<<#x<<"="<<x<<" "
#define dbg2(x) cerr<<#x<<"="<<x<<"\\n"
int n,m,op,a,b;
class PresidentTree
{
#define lc t\[x\].ls
#define rc t\[x\].rs
#define mid (l+r>>1)
    struct node{int ls,rs,v,d;}t\[N*40\];
public:
    int root\[N\],cntnode;
    void build(int &x,int l,int r)
    {
        x=++cntnode;
        if(l==r) return void(t\[x\].v=l);
        build(lc,l,mid),build(rc,mid+1,r);
    }
    void change(int &x,int y,int l,int r,int p,int v)
    {
        t\[x=++cntnode\]=t\[y\];
        if(l==r) return void(t\[x\].v=v);
        p<=mid?change(lc,t\[y\].ls,l,mid,p,v):change(rc,t\[y\].rs,mid+1,r,p,v);
    }
    void add(int &x,int y,int l,int r,int p,int v)
    {
        t\[x=++cntnode\]=t\[y\];//应该是要新开节点的，但不开也不影响正确性，只影响了启发式合并。 
        if(l==r) return void(t\[x\].d+=v);
        p<=mid?add(lc,t\[y\].ls,l,mid,p,v):add(rc,t\[y\].rs,mid+1,r,p,v);
    }
    pii ask(int x,int l,int r,int p)
    {
        if(l==r) return mp(t\[x\].v,t\[x\].d);
        return p<=mid?ask(lc,l,mid,p):ask(rc,mid+1,r,p);
    }
}T;
pii find(int t,int x)
    {pii res=T.ask(T.root\[t\],1,n,x);return res.fi^x?find(t,res.fi):res;}
int main()
{
    scanf("%d%d",&n,&m);
    T.build(T.root\[0\],1,n);
    pii f1,f2;
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&op,&a);
        if(op==1)
        {
            scanf("%d",&b),T.root\[i\]=T.root\[i-1\],f1=find(i,a),f2=find(i,b);
            if(f1.fi^f2.fi)
            {
                if(f1.se>f2.se) std::swap(f1,f2);
                T.change(T.root\[i\],T.root\[i-1\],1,n,f1.fi,f2.fi);
                if(f1.se==f2.se) T.add(T.root\[i\],T.root\[i\],1,n,f2.fi,1);
            }
        }
        if(op==2) T.root\[i\]=T.root\[a\];
        if(op==3)
            scanf("%d",&b),T.root\[i\]=T.root\[i-1\],f1=find(i,a),f2=find(i,b),puts(f1.fi^f2.fi?"0":"1");
    }
    return 0;
}

### 哈夫曼树

$n$种单词用$k$进制Hufuman编码的最小总长度。

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<queue>
#include<vector>
#include<map>
#include<set>
using std::cin;using std::cerr;
using std::max;using std::min;
#define N 100005
#define ll long long
#define db double
#define dbg1(x) cerr<<#x<<"="<<x<<" "
#define dbg2(x) cerr<<#x<<"="<<x<<"\\n"
int n,m,cnt;ll A\[N\],Sum,ans;
struct node
{
    ll v;int d;node(){};node(ll \_v,int \_d) {v=\_v,d=\_d;}
    friend bool operator<(node t1,node t2) {return t1.v>t2.v||t1.v==t2.v&&t1.d>t2.d;} 
};
std::priority_queue<node>H;
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%lld",&A\[i\]),H.push(node(A\[i\],0));
    if(n<=m)
    {
        for(int i=1;i<=n;i++) ans+=A\[i\];
        return !printf("%lld\\n",ans); 
    }
    cnt=(n-1)%(m-1);
    if(cnt) cnt=m-1-cnt;
    for(int i=1;i<=cnt;i++) H.push(node(0,0));
    for(int Max;H.size()>1;)
    {
        Max=Sum=0;
        for(int i=1;i<=m;i++)
        {
            node top=H.top();H.pop();
            Sum+=top.v,Max=max(Max,top.d);
        }
        ans+=Sum,H.push(node(Sum,Max+1));
    }
    printf("%lld\\n",ans);
    return 0;
}

### 左偏树

初始有$n$个小根堆，支持合并两个数所在的堆和删除某个堆的堆顶。

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<queue>
#include<vector>
#include<map>
#include<set>
using std::cin;using std::cerr;
using std::max;using std::min;
#define N 100005
#define ll long long
#define db double
#define dbg1(x) cerr<<#x<<"="<<x<<" "
#define dbg2(x) cerr<<#x<<"="<<x<<"\\n"
int n,m,mark\[N\];
class LeftistTree
{
#define lc t\[x\].ls
#define rc t\[x\].rs
public:
	struct node{int ls,rs,fa,sz,v,d;}t\[N\];
	int merge(int x,int y)
	{
		if(!x||!y) return x+y;
		if(t\[x\].v>t\[y\].v||t\[x\].v==t\[y\].v&&x>y) std::swap(x,y);
		rc=merge(rc,y),t\[rc\].fa=x;
		if(t\[rc\].d>t\[lc\].d) std::swap(lc,rc);
		t\[x\].d=t\[rc\].d+1;
		return x;
	}
	int Delete(int x) {mark\[x\]=1,t\[lc\].fa=t\[rc\].fa=0;return merge(lc,rc);}
}T;
int find(int x) {for(;T.t\[x\].fa;x=T.t\[x\].fa);return x;}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&T.t\[i\].v);
	for(int op,a,b,f1,f2;m--;)
	{
		scanf("%d%d",&op,&a);
		if(op==1)
		{
			scanf("%d",&b);
			if(mark\[a\]||mark\[b\]) continue;
			f1=find(a),f2=find(b);
			if(f1^f2) T.merge(f1,f2);
		}
		else if(mark\[a\]) puts("-1");else f1=find(a),printf("%d\\n",T.t\[f1\].v),T.Delete(f1); 
	}
	return 0;
}

### 笛卡尔树

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<queue>
#include<vector>
#include<set>
#include<map>
using std::cin;using std::cerr;
using std::max;using std::min;
#define N 1000005
#define ll long long
#define db double
#define dbg1(x) cerr<<#x<<"="<<(x)<<" "
#define dbg2(x) cerr<<#x<<"="<<(x)<<"\\n"
int T,n,A\[N\],sta\[N\],top;
struct node{int fa,lc,rc;}t\[N\];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&A\[i\]);
	sta\[top=1\]=1;
	for(int i=2;i<=n;i++)
	{
		for(;top;)
		{
			if(A\[sta\[top\]\]>=A\[i\])
			{
				if(t\[sta\[top\]\].rc)
					t\[t\[sta\[top\]\].rc\].fa=i,t\[i\].lc=t\[sta\[top\]\].rc;
				t\[i\].fa=sta\[top\],t\[sta\[top\]\].rc=i;
				break;
			}
			top--;
		}
		if(!top) t\[i\].lc=sta\[1\],t\[sta\[1\]\].fa=i;
		sta\[++top\]=i;
	}
	return 0;
}

### Old-Driver Tree

随机数据且有区间覆盖的情况下支持区间的各种操作。（板子中支持区间加、区间覆盖、区间第$k$小和区间幂和）

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<string>
#include<algorithm>
#include<queue>
#include<vector>
#include<set>
#include<map>
using std::cin;using std::cerr;
using std::max;using std::min;
#define N 100005
#define ll long long
#define db double
#define IT std::set<node>::iterator
#define dbg1(x) cerr<<#x<<"="<<(x)<<" "
#define dbg2(x) cerr<<#x<<"="<<(x)<<"\\n"
int n,m,K,seed,op,a,b,c,mod;
int rd(int x) {int v=seed%x;seed=(7ll*seed+13)%1000000007;return v;}
int cal(int x) {x-=x<mod?0:mod;return x;}
int Pow(int x,int y) {int res=1;for(;y;x=(ll)x\*x%mod,y>>=1) if(y&1) res=(ll)res\*x%mod;return res;}
class OldDriverTree
{
	struct node
	{
		int l,r;mutable ll v;
		friend bool operator<(node t1,node t2) {return t1.l<t2.l;}
	};
	std::set<node>S;IT it1,it2;
	struct info{int cnt;ll v;}A\[N\];
	IT split(int p)
	{
		if(p>n) return S.end();
		IT it=S.lower_bound({p,0,0});
		if(it!=S.end()&&(*it).l==p) return it;
		it--;int l=(\*it).l,r=(\*it).r;ll v=(*it).v;
		S.erase(it),S.insert({l,p-1,v});
		return S.insert({p,r,v}).first;
	}
public:
	void insert(node x) {S.insert(x);}
	void change(int l,int r,int v) {it1=split(l),it2=split(r+1),S.erase(it1,it2),S.insert({l,r,v});}
	void add(int l,int r,int v) {for(it1=split(l),it2=split(r+1);it1!=it2;it1++) (*it1).v+=v;}
	ll find(int l,int r,int v)
	{
		int An=0;
		for(it1=split(l),it2=split(r+1);it1!=it2;it1++) A\[++An\]={(\*it1).r-(\*it1).l+1,(*it1).v};
		std::sort(A+1,A+1+An,\[\](info t1,info t2){return t1.v<t2.v;});
		for(int i=1;i<=An;i++)
			if(v>A\[i\].cnt) v-=A\[i\].cnt;else return A\[i\].v;
	}
	int ask(int l,int r,int v)
	{
		int res=0;
		for(it1=split(l),it2=split(r+1);it1!=it2;it1++)
			res=cal(res+(ll)Pow((\*it1).v%mod,v)\*((\*it1).r-(\*it1).l+1)%mod);
		return res;
	}
}T;
int main()
{
	scanf("%d%d%d%d",&n,&m,&seed,&K);
	for(int i=1;i<=n;i++) a=rd(K)+1,T.insert({i,i,a});
	for(;m--;)
	{
		op=rd(4)+1,a=rd(n)+1,b=rd(n)+1;if(a>b) std::swap(a,b);
		c=op^3?rd(K)+1:rd(b-a+1)+1;
		if(op==1) T.add(a,b,c);
		if(op==2) T.change(a,b,c);
		if(op==3) printf("%lld\\n",T.find(a,b,c));
		if(op==4) mod=rd(K)+1,printf("%d\\n",T.ask(a,b,c));
	}
	return 0;
}

树套树
---

### 支持单点修改的主席树（树状数组套线段树）

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<queue>
#include<vector>
#include<set>
using namespace std;
#define N 100005
#define lc t\[x\].son\[0\]
#define rc t\[x\].son\[1\]
#define ll long long
int n;
class SegmentTree
{
    int cntnode;
    struct node{int son\[2\],v;}t\[N*400\];
    void pushup(int x) {t\[x\].v=t\[lc\].v+t\[rc\].v;}
public:
    void add(int &x,int l,int r,int p,int v)
    {
        if(!x) x=++cntnode;
        t\[x\].v+=v;
        if(l==r) return;
        int mid=l+r>>1;
        if(p<=mid) add(lc,l,mid,p,v);
        else add(rc,mid+1,r,p,v);
    }
    int ask(int x,int l,int r,int \_l,int \_r)
    {
        if(!x) return 0;
        if(\_l<=l&&r<=\_r) return t\[x\].v;
        int mid=l+r>>1,res=0;
        if(\_l<=mid) res=ask(lc,l,mid,\_l,_r);
        if(\_r>mid) res+=ask(rc,mid+1,r,\_l,_r);
        return res;
    }
}T;
class BIT
{
    int root\[N\];
public:
    void add(int x,int p,int v) {for(;x<=n;x+=x&-x) T.add(root\[x\],1,n,p,v);}
    int ask(int x,int l,int r)
    {
        int res=0;
        for(;x;x-=x&-x) res+=T.ask(root\[x\],1,n,l,r);
        return res;
    }
}B;

 

字符串
===

### KMP

求字符串B在字符串A中出现的位置（开头），以及字符串B的$nex$数组。

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<string>
#include<algorithm>
#include<queue>
#include<vector>
#include<set>
#include<map>
using std::cin;using std::cerr;
using std::max;using std::min;
#define N 1000005
#define ll long long
#define db double
#define dbg1(x) cerr<<#x<<"="<<(x)<<" "
#define dbg2(x) cerr<<#x<<"="<<(x)<<"\\n"
int n,m,nex\[N\];
char A\[N\],B\[N\];
int main()
{
	scanf("%s%s",A+1,B+1),n=strlen(A+1),m=strlen(B+1);
	for(int i=2,j=0;i<=m;i++)
	{
		for(;j&&B\[j+1\]^B\[i\];j=nex\[j\]);
		if(B\[j+1\]==B\[i\]) j++;nex\[i\]=j;
	}
	for(int i=1,j=0;i<=n;i++)
	{
		for(;j&&B\[j+1\]^A\[i\];j=nex\[j\]);
		if(B\[j+1\]==A\[i\]) j++;
		if(j==m) printf("%d\\n",i-m+1),j=nex\[j\];
	}
	for(int i=1;i<=m;i++) printf("%d ",nex\[i\]);puts("");
	return 0;
}

### manacher

求字符串A中的最长回文串的长度。

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<string>
#include<algorithm>
#include<queue>
#include<vector>
#include<set>
#include<map>
using std::cin;using std::cerr;
using std::max;using std::min;
#define N 1000005
#define ll long long
#define db double
#define dbg1(x) cerr<<#x<<"="<<(x)<<" "
#define dbg2(x) cerr<<#x<<"="<<(x)<<"\\n"
int n,m,R\[N<<1\],Max,Maxid,ans;
char A\[N\],B\[N<<1\];
int main()
{
	scanf("%s",A+1),n=strlen(A+1),B\[m=1\]='$';
	for(int i=1;i<=n;i++) B\[++m\]=A\[i\],B\[++m\]='$';
	for(int i=2;i<=m;i++)
	{
		if(i<=Max) R\[i\]=min(R\[Maxid*2-i\],Max-i);else R\[i\]=1;
		for(;i-R\[i\]>0&&B\[i-R\[i\]\]==B\[i+R\[i\]\];) R\[i\]++;
		if(R\[i\]+i-1>Max) Max=R\[i\]+i-1,Maxid=i;
	}
	for(int i=2;i<m;i++) ans=max(ans,R\[i\]-1);
	printf("%d\\n",ans);
	return 0;
}

### AC自动机

有$n$个模式串和$1$个文本串，求有多少个模式串在文本串里出现过。

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<string>
#include<algorithm>
#include<queue>
#include<vector>
#include<set>
#include<map>
using std::cin;using std::cerr;
using std::max;using std::min;
#define N 1000005
#define ll long long
#define db double
#define dbg1(x) cerr<<#x<<"="<<(x)<<" "
#define dbg2(x) cerr<<#x<<"="<<(x)<<"\\n"
int n,m,ans;char s\[N\];
class ACAutomaton
{
	struct node{int son\[26\],nex,v;}t\[N\];
public:
	int root,cntnode;
	void insert(int len)
	{
		int x=root;
		for(int i=1,k;i<=len;i++)
		{
			k=s\[i\]-97;
			if(!t\[x\].son\[k\]) t\[x\].son\[k\]=++cntnode;
			x=t\[x\].son\[k\];
		}
		t\[x\].v++;
	}
	void build()
	{
		std::queue<int>q;q.push(root);
		for(int top;!q.empty();)
		{
			top=q.front(),q.pop();
			if(top^root&&!t\[top\].nex) t\[top\].nex=root;//如果root=1要加这句
			//用Trie图优化
			for(int i=0;i<26;i++)
				if(t\[top\].son\[i\]) t\[t\[top\].son\[i\]\].nex=t\[t\[top\].nex\].son\[i\],q.push(t\[top\].son\[i\]);
				else t\[top\].son\[i\]=t\[t\[top\].nex\].son\[i\];
		}
	}
	void Solve()
	{
		for(int i=1,x=root,k;i<=m;i++)
		{
			k=s\[i\]-97,x=t\[x\].son\[k\];if(!x) x=root;//如果root=1要加这句
			for(int p=x;p&&~t\[p\].v;p=t\[p\].nex) ans+=t\[p\].v,t\[p\].v=-1;//防止重复计算
		}
	}
}ACAM;
int main()
{
	scanf("%d",&n),ACAM.root=ACAM.cntnode=1;
	for(int i=1;i<=n;i++) scanf("%s",s+1),ACAM.insert(strlen(s+1));
	scanf("%s",s+1),m=strlen(s+1);
	ACAM.build(),ACAM.Solve();
	printf("%d\\n",ans);
	return 0;
}

### 后缀数组

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<queue>
#include<vector>
#include<map>
#include<set>
using namespace std;
#define N 20005 
#define ll long long
#define db double
#define dbg1(x) cout<<#x<<"="<<x<<" "
#define dbg2(x) cout<<#x<<"="<<x<<"\\n"
int n,m;char A\[N\];
class SuffixArray
{
    int cnt,Max,Sum\[N\],tp\[N\];
    void Rsort()//基数排序
    {
        for(int i=1;i<=Max;i++) Sum\[i\]=0;
        for(int i=1;i<=n;i++) Sum\[Rank\[tp\[i\]\]\]++;
        for(int i=1;i<=Max;i++) Sum\[i\]+=Sum\[i-1\];
        for(int i=n;i;i--) sa\[Sum\[Rank\[tp\[i\]\]\]--\]=tp\[i\]; 
    }
public:
    int sa\[N\],Rank\[N\],h\[N\];
    //sa\[i\]排第i的是哪个后缀 Rank\[i\]第i个后缀排第几 h\[i\]sa\[i\]与sa\[i-1\]的LCP(最长公共前缀)
    void build()
    {
        for(int i=1;i<=n;i++) Max=max(Max,Rank\[tp\[i\]=i\]=A\[i\]);
        Rsort();if(n==1) return;
        for(int j=1;cnt<n;Max=cnt,j<<=1)
        {
            cnt=0;
            for(int i=n-j+1;i<=n;i++) tp\[++cnt\]=i;
            for(int i=1;i<=n;i++) if(sa\[i\]>j) tp\[++cnt\]=sa\[i\]-j;
            Rsort(),swap(tp,Rank),Rank\[sa\[cnt=1\]\]=1;
            for(int i=2;i<=n;i++)//求当前的Rank 此时tp存的是上一次的Rank
            {
                if(tp\[sa\[i\]\]^tp\[sa\[i-1\]\]||tp\[sa\[i\]+j\]^tp\[sa\[i-1\]+j\]) cnt++;
                Rank\[sa\[i\]\]=cnt;
            }
        }
        //求h\[i\]
        for(int i=1,tmp=0;i<=n;i++)
        {
            if(tmp) tmp--;
            for(;A\[sa\[Rank\[i\]-1\]+tmp\]==A\[i+tmp\];tmp++);
            h\[Rank\[i\]\]=tmp;
        }
    }
}SA;

### 后缀自动机

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<string>
#include<algorithm>
#include<queue>
#include<vector>
#include<set>
#include<map>
using std::cin;using std::cerr;
using std::max;using std::min;
#define N 1000005
#define ll long long
#define db double
#define dbg1(x) cerr<<#x<<"="<<(x)<<" "
#define dbg2(x) cerr<<#x<<"="<<(x)<<"\\n"
//数组要开n的两倍 
int n;ll ans;char s\[N\];
class SuffixAutomaton
{
	int tp\[N\],vis\[N\];
	struct node{int ch\[26\],fa,mx,right;}t\[N\];
public:
	int root,last,cntnode;
	void insert(int c)
	{
		int x=last,y=++cntnode,od,nw;last=y,t\[y\].mx=t\[x\].mx+1,t\[y\].right=1;
		for(;x&&!t\[x\].ch\[c\];x=t\[x\].fa) t\[x\].ch\[c\]=y;
		if(!x) return void(t\[y\].fa=1);
		od=t\[x\].ch\[c\];
		if(t\[od\].mx==t\[x\].mx+1) return void(t\[y\].fa=od);
		t\[nw=++cntnode\]=t\[od\],t\[nw\].right=0;//注意nw的right要清零 
		t\[nw\].mx=t\[x\].mx+1,t\[od\].fa=t\[y\].fa=nw;
		for(;t\[x\].ch\[c\]==od;x=t\[x\].fa) t\[x\].ch\[c\]=nw;
	}
	void Solve()
	{
		for(int i=1;i<=cntnode;i++) tp\[t\[i\].mx\]++;
		for(int i=1;i<=n;i++) tp\[i\]+=tp\[i-1\];
		for(int i=cntnode;i;i--) vis\[tp\[t\[i\].mx\]--\]=i;//求出后缀自动机的拓扑序 
		for(int i=cntnode,x;i;i--) x=vis\[i\],t\[t\[x\].fa\].right+=t\[x\].right;
	}
}SAM;
int main()
{
	scanf("%s",s+1),n=strlen(s+1);
	SAM.root=SAM.last=SAM.cntnode=1;
	for(int i=1;i<=n;i++) SAM.insert(s\[i\]-97);
	SAM.Solve();
	return 0;
}

 

分治
==

树分治（待填）
-------

### 点分治

有一棵$n$个点的树，求有多少点对之间的距离$\\leq m$。

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<queue>
#include<vector>
#include<set>
#include<map>
using std::cin;using std::cerr;
using std::max;using std::min;
#define N 100005
#define ll long long
#define db double
#define dbg1(x) cerr<<#x<<"="<<(x)<<" "
#define dbg2(x) cerr<<#x<<"="<<(x)<<"\\n"
int n,m,a,b,c,ecnt,last\[N\],A\[N\],size\[N\],Maxsz\[N\],totsz,root,vis\[N\],B\[N\],Bn,ans;
struct road{int to,v,nex;}e\[N<<1\];
void adde(int u,int v,int w) {e\[++ecnt\]=(road){v,w,last\[u\]},last\[u\]=ecnt;}
void getroot(int x,int fath=0)
{
    size\[x\]=1,Maxsz\[x\]=0;
    for(int k=last\[x\];k;k=e\[k\].nex)
        if(e\[k\].to^fath&&!vis\[e\[k\].to\])
        {
            getroot(e\[k\].to,x),size\[x\]+=size\[e\[k\].to\];
            Maxsz\[x\]=max(Maxsz\[x\],size\[e\[k\].to\]);
    	}
    Maxsz\[x\]=max(Maxsz\[x\],totsz-size\[x\]);
    if(Maxsz\[x\]<Maxsz\[root\]||!root) root=x;
}
void dfs(int x,int fath,int d)
{
    B\[++Bn\]=d;
    for(int k=last\[x\];k;k=e\[k\].nex) if(!vis\[e\[k\].to\]&&e\[k\].to^fath) dfs(e\[k\].to,x,d+e\[k\].v);
}
void calans(int x,int d,int v)
{
    Bn=0,dfs(x,0,d),std::sort(B+1,B+1+Bn);
	for(int i=1,j=Bn;i<=Bn;i++)
	{
		for(;j&&B\[i\]+B\[j\]>m;j--);
		ans+=min(i-1,j)*v;
	}
}
void Solve(int x)
{
    totsz=size\[x\],root=0,getroot(x),vis\[x=root\]=1,calans(x,0,1);
    for(int k=last\[x\];k;k=e\[k\].nex) if(!vis\[e\[k\].to\]) calans(e\[k\].to,e\[k\].v,-1);
    for(int k=last\[x\];k;k=e\[k\].nex) if(!vis\[e\[k\].to\]) Solve(e\[k\].to);
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<n;i++) scanf("%d%d%d",&a,&b,&c),adde(a,b,c),adde(b,a,c);
	scanf("%d",&m);
    size\[1\]=n,Solve(1);
	printf("%d\\n",ans);
    return 0;
}

### 边分治

$n$个点的树，每个点有点权$A_i$，找一条路径使得点数$\\times $点权最小值最大。（BZOJ2870）

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<string>
#include<algorithm>
#include<queue>
#include<vector>
#include<set>
#include<map>
using std::cin;using std::cerr;
using std::max;using std::min;
#define N 100005
#define inf 1e9
#define ll long long
#define db double
#define pb push_back
#define dbg1(x) cerr<<#x<<"="<<(x)<<" "
#define dbg2(x) cerr<<#x<<"="<<(x)<<"\\n"
int n,A\[N\],a,b,ecnt,last\[N\],size\[N\],totsz,root,Min,mark\[N<<1\],Bn\[2\];ll ans;
std::vector<int>son\[N\];
struct info
{
	int d,v;
	friend bool operator<(info t1,info t2) {return t1.v>t2.v;}
}B\[2\]\[N\];
struct road{int to,v,nex;}e\[N<<1\];
void adde(int u,int v,int w) {e\[++ecnt\]=(road){v,w,last\[u\]},last\[u\]=ecnt;}
void rebuild()
{
	ecnt=1;
	for(int i=1;i<=n;i++) last\[i\]=0;
	for(int i=1,sz,id;i<=n;i++)
	{
		if((sz=son\[i\].size())>2)
		{
			a=++n,b=++n,A\[a\]=A\[b\]=A\[i\];
			adde(i,a,0),adde(a,i,0),adde(i,b,0),adde(b,i,0);
			for(int j=0;j<sz;j++) son\[j&1?a:b\].pb(son\[i\]\[j\]);
		}
		else for(int j=0;j<sz;j++) id=son\[i\]\[j\],adde(i,id,1),adde(id,i,1);
	}
}
void getroot(int x,int fath=0)
{
	size\[x\]=1;
	for(int k=last\[x\],v;k;k=e\[k\].nex)
		if(e\[k\].to^fath&&!mark\[k\])
		{
			getroot(e\[k\].to,x),size\[x\]+=size\[e\[k\].to\];
			v=max(size\[e\[k\].to\],totsz-size\[e\[k\].to\]);
			if(!root||v<Min) root=k,Min=v;
		}
}
void dfs1(int x,int fath=0)
{
	for(int k=last\[x\];k;k=e\[k\].nex)
		if(e\[k\].to^fath) son\[x\].pb(e\[k\].to),dfs1(e\[k\].to,x);
}
void dfs2(int x,int fath,int d,int v,int op)
{
	v=min(v,A\[x\]),B\[op\]\[++Bn\[op\]\]={d,v};
	for(int k=last\[x\];k;k=e\[k\].nex)
		if(e\[k\].to^fath&&!mark\[k\]) dfs2(e\[k\].to,x,d+e\[k\].v,v,op);
}
void Solve(int x,int sz)
{
	if(sz==1) return;
	totsz=sz,root=0,getroot(x),mark\[root\]=mark\[root^1\]=1;
	int u=e\[root\].to,v=e\[root^1\].to;Bn\[0\]=Bn\[1\]=0;
	dfs2(u,v,0,inf,0),dfs2(v,u,0,inf,1);
	std::sort(B\[0\]+1,B\[0\]+1+Bn\[0\]),std::sort(B\[1\]+1,B\[1\]+1+Bn\[1\]);
	for(int i=1,j=1,v=0;i<=Bn\[0\];i++)
	{
		for(;j<=Bn\[1\]&&B\[1\]\[j\].v>=B\[0\]\[i\].v;j++) v=max(v,B\[1\]\[j\].d);
		if(j>1) ans=max(ans,(ll)(B\[0\]\[i\].d+v+1+e\[root\].v)*B\[0\]\[i\].v);
		//j>1与点分治不同，一定要两段路径拼在一起
	}
	for(int i=1,j=1,v=0;i<=Bn\[1\];i++)
	{
		for(;j<=Bn\[0\]&&B\[0\]\[j\].v>=B\[1\]\[i\].v;j++) v=max(v,B\[0\]\[j\].d);
		if(j>1) ans=max(ans,(ll)(B\[1\]\[i\].d+v+1+e\[root\].v)*B\[1\]\[i\].v);
		//j>1与点分治不同，一定要两段路径拼在一起
	}
	int tmp=size\[u\];Solve(u,tmp),Solve(v,sz-tmp);
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&A\[i\]),ans=max(ans,1ll*A\[i\]);
	for(int i=1;i<n;i++) scanf("%d%d",&a,&b),adde(a,b,1),adde(b,a,1);
	dfs1(1),rebuild(),Solve(1,n);
	printf("%lld\\n",ans);
	return 0;
}

### 动态点分治

### 链分治（重链剖分）

### 链分治（长链剖分）

 

计算几何
====

### 半平面交

求$n$个凸多边形交的面积。

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<queue>
#include<vector>
#include<map>
#include<set>
using namespace std;
#define N 12
#define M 52
#define eps 1e-6
#define ll long long
#define db double
#define dbg1(x) cout<<#x<<"="<<x<<" "
#define dbg2(x) cout<<#x<<"="<<x<<"\\n"
int n,m,tot;db ans;
struct point
{
    db x,y;point(){};point(db \_x,db \_y) {x=\_x,y=\_y;}//坐标一定要开db因为直线交点很多情况都不是整点
    friend point operator+(point t1,point t2) {return point(t1.x+t2.x,t1.y+t2.y);}
    friend point operator-(point t1,point t2) {return point(t1.x-t2.x,t1.y-t2.y);}
    friend db operator*(point t1,point t2) {return t1.x\*t2.y-t1.y\*t2.x;}
    friend point operator*(db t1,point t2) {return point(t1\*t2.x,t1\*t2.y);}
}A\[M\],p\[N*M\];
struct line
{
    point p,v;db k;line(){};line(point \_p,point \_v) {p=\_p,v=\_v,k=atan2(v.y,v.x);}
    friend bool operator<(line t1,line t2) {return t1.k<t2.k;}
}li\[N\*M\],q\[N\*M\];
bool Onleft(point p,line l) {return (p-l.p)*l.v<eps;}//p在l的左侧或p在l上返回1
point calpoint(line l1,line l2) {return l1.p+(l2.p-l1.p)\*l2.v/(l1.v\*l2.v)*l1.v;}//计算两条直线的交点
void Hpi()
{
    int l=1,r=0;
    for(int i=1;i<=tot;i++)
    {
        while(l<r&&!Onleft(p\[r-1\],li\[i\])) r--;
        while(l<r&&!Onleft(p\[l\],li\[i\])) l++;
        q\[++r\]=li\[i\];
        while(l<r&&fabs(q\[r\].v*q\[r-1\].v)<eps&&Onleft(q\[r\].p,q\[r-1\])) q\[r-1\]=q\[r\],r--;//共线情况要特判
        if(l<r) p\[r-1\]=calpoint(q\[r-1\],q\[r\]);
    }
    while(l<r&&!Onleft(p\[r-1\],q\[l\])) r--;//把队首的半平面当做一个新的半平面去弹队尾的半平面
    if(r-l>1)
    {
        p\[r\]=calpoint(q\[l\],q\[r\]),p\[r+1\]=p\[l\];
        for(int i=l;i<=r;i++) ans+=p\[i\]*p\[i+1\];
    }
} 
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&m);
        for(int i=1;i<=m;i++) scanf("%lf%lf",&A\[i\].x,&A\[i\].y);
        A\[m+1\]=A\[1\];
        for(int i=1;i<=m;i++) li\[++tot\]=line(A\[i\],A\[i+1\]-A\[i\]);
    }
    sort(li+1,li+1+tot);
    Hpi(),printf("%.3lf\\n",ans*0.5);
    return 0;
}

 

数论
==

### exgcd

求$Ax\\equiv C(mod\\space B)$的最小非负整数解。

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<queue>
#include<vector>
#include<map>
#include<set>
using std::cin;using std::cerr;
using std::max;using std::min;
#define N
#define ll long long
#define db double
#define dbg1(x) cerr<<#x<<"="<<x<<" "
#define dbg2(x) cerr<<#x<<"="<<x<<"\\n"
int A,B,C,G,ansx,ansy;
void exgcd(int a,int b,int &x,int &y)
{
    if(!b) {x=1,y=0;return;}
    exgcd(b,a%b,x,y);
    int t=x;x=y,y=t-a/b*y;
}
int main()
{
    scanf("%d%d%d",&A,&B,&C);
    G=std::__gcd(A,B);
    if(C%G) return puts("-1"),0;
    A/=G,B/=G,C/=G,exgcd(A,B,ansx,ansy);
    ansx=((ll)ansx*C%B+B)%B;
    printf("%d\\n",ansx);
    return 0;
}

### 中国剩余定理（待填）

### Lucas

求$\\binom{n}{m}\\%p$的值，$p$为质数。

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<queue>
#include<stack>
using namespace std;
#define N 10100
#define mod 10007
#define ll long long
int T,fac\[N\],inv\[N\];ll n,m;
int C(int a,int b) {return a<b?0:(ll)fac\[a\]\*inv\[b\]%mod\*inv\[a-b\]%mod;}
int Lucas(ll a,ll b) {return b?(ll)C(a%mod,b%mod)*Lucas(a/mod,b/mod)%mod:1;}
int main()
{
    fac\[1\]=1;
    for(int i=2;i<mod;i++) fac\[i\]=(ll)fac\[i-1\]*i%mod;
    inv\[0\]=inv\[1\]=1;
    for(int i=2;i<mod;i++) inv\[i\]=(ll)(mod-mod/i)*inv\[mod%i\]%mod;
    for(int i=2;i<mod;i++)inv\[i\]=(ll)inv\[i-1\]*inv\[i\]%mod;
    scanf("%d",&T);
    while(T--)
        scanf("%lld%lld",&n,&m),printf("%d\\n",Lucas(n,m));
    return 0;
}

 

多项式
===

### FFT

两个多项式$A$和$B$相乘。

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<queue>
#include<vector>
#include<set>
#include<map>
using namespace std;
#define N 50005
#define ll long long
#define db double
#define dbg1(x) cout<<#x<<"="<<x<<" "
#define dbg2(x) cout<<#x<<"="<<x<<"\\n"
const db pi=acos(-1);
int n,m,A\[N\],B\[N\],Sum,Max,ans;
struct Complex
{
    db r,i;Complex(){};Complex(db \_r,db \_i) {r=\_r,i=\_i;}
    friend Complex operator+(Complex t1,Complex t2) {return Complex(t1.r+t2.r,t1.i+t2.i);}
    friend Complex operator-(Complex t1,Complex t2) {return Complex(t1.r-t2.r,t1.i-t2.i);}
    friend Complex operator*(Complex t1,Complex t2) {return Complex(t1.r\*t2.r-t1.i\*t2.i,t1.i\*t2.r+t1.r\*t2.i);}
}f\[N<<2\],g\[N<<2\];//空间要开大一些
class FFT
{
    int Rank\[N<<2\];//空间要开大一些
    void dft(Complex x\[\],int f)
    {
        Complex w,wn,tmp;
        for(int i=0;i<len;i++) if(i<Rank\[i\]) swap(x\[i\],x\[Rank\[i\]\]);
        for(int i=1;i<len;i<<=1)
        {
            wn=Complex(cos(pi/i),f*sin(pi/i));
            for(int j=0;j<len;j+=i<<1)
            {
                w=Complex(1,0);
                for(int k=0;k<i;w=w*wn,k++)
                    tmp=x\[i+j+k\]*w,x\[i+j+k\]=x\[j+k\]-tmp,x\[j+k\]=x\[j+k\]+tmp;
            }
        }
        if(f<0) for(int i=0;i<len;i++) x\[i\].r/=len;//IDFT最后要除以多项式的项数
    }
public:
    int len,l;
    void Prepare() {for(int i=0;i<len;i++) Rank\[i\]=(Rank\[i>>1\]>>1)|((i&1)<<l-1);}//预处理i二进制拆分后逆序的数是多少
    void multiply(Complex x\[\],Complex y\[\])
    {
        dft(x,1),dft(y,1);
        for(int i=0;i<len;i++) x\[i\]=x\[i\]*y\[i\];
        dft(x,-1);
    }
}fft;
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&A\[i\]);
    for(int i=1;i<=m;i++) scanf("%d",&B\[i\]);
    for(int i=0;i<n;i++) f\[i\]=Complex(A\[i+1\],0);
    for(int i=0;i<m;i++) g\[i\]=Complex(B\[i+1\],0);
    for(fft.len=1;fft.len<n+m;fft.len<<=1,fft.l++);//将多项式的项数补齐到2^k
    fft.Prepare(),fft.multiply(f,g);
    return 0;
}

### NTT

两个多项式$A$和$B$相乘（$mod\\space 998244353$）。

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<string>
#include<algorithm>
#include<queue>
#include<vector>
#include<set>
#include<map>
using std::cin;using std::cerr;
using std::max;using std::min;
#define N 50005
#define mod 998244353
#define ll long long
#define db double
#define dbg1(x) cerr<<#x<<"="<<(x)<<" "
#define dbg2(x) cerr<<#x<<"="<<(x)<<"\\n"
int n,m,A\[N<<2\],B\[N<<2\];//空间要开大一点 
int cal(int x) {x-=x<mod?0:mod;return x;}
int Pow(int x,int y=mod-2) {int res=1;for(;y;x=(ll)x\*x%mod,y>>=1) if(y&1) res=(ll)res\*x%mod;return res;}
class NTT
{
	int g1,g2,inv,Rank\[N<<2\];//空间要开大一些
	void dft(int x\[\],int f)
	{
		for(int i=0;i<len;i++) if(i<Rank\[i\]) std::swap(x\[i\],x\[Rank\[i\]\]);
		for(int i=1,wn;i<len;i<<=1)
		{
			wn=Pow(f>0?g1:g2,(mod-1)/(i<<1));
			for(int j=0;j<len;j+=i<<1)
				for(int k=0,w=1,tmp;k<i;w=(ll)w*wn%mod,k++)
					tmp=(ll)x\[i+j+k\]*w%mod,x\[i+j+k\]=cal(x\[j+k\]-tmp+mod),x\[j+k\]=cal(x\[j+k\]+tmp);
		}
		if(f<0) for(int i=0;i<len;i++) x\[i\]=(ll)x\[i\]*inv%mod;
	}
public:
	int len,l;
	void Prepare()
	{
		g1=3,g2=332748118,inv=Pow(len);//预处理出原根,原根的逆元,多项式项数的逆元
		for(int i=0;i<len;i++) Rank\[i\]=(Rank\[i>>1\]>>1)|((i&1)<<l-1);//预处理i二进制拆分后逆序的数是多少 
	}
	void multiply(int x\[\],int y\[\])
	{
		dft(x,1),dft(y,1);
		for(int i=0;i<len;i++) x\[i\]=(ll)x\[i\]*y\[i\]%mod;
		dft(x,-1);
	}
}ntt;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&A\[i\]);
	for(int i=1;i<=m;i++) scanf("%d",&B\[i\]);
	for(ntt.len=1;ntt.len<n+m;ntt.len<<=1,ntt.l++);//将多项式的项数补齐到2^k
	ntt.Prepare(),ntt.multiply(A,B); 
	return 0;
}

### MTT

两个多项式$A$和$B$相乘$\\%mod$。

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<string>
#include<algorithm>
#include<queue>
#include<vector>
#include<set>
#include<map>
using std::cin;using std::cerr;
using std::max;using std::min;
#define N 300005
#define ll long long
#define db long double
#define dbg1(x) cerr<<#x<<"="<<(x)<<" "
#define dbg2(x) cerr<<#x<<"="<<(x)<<"\\n"
int n,m,mod,block,A\[N\],B\[N\],C\[N\];
int cal(int x) {x-=x<mod?0:mod;return x;}
const db pi=acos(-1);
struct Complex
{
	db r,i;
	friend Complex operator+(Complex t1,Complex t2) {return {t1.r+t2.r,t1.i+t2.i};}
	friend Complex operator-(Complex t1,Complex t2) {return {t1.r-t2.r,t1.i-t2.i};}
	friend Complex operator*(Complex t1,Complex t2) {return {t1.r\*t2.r-t1.i\*t2.i,t1.i\*t2.r+t1.r\*t2.i};}
	friend Complex operator*(Complex t1,db t2) {return {t1.r\*t2,t1.i\*t2};}
	friend Complex operator/(Complex t1,db t2) {return {t1.r/t2,t1.i/t2};}
};
class MTT
{
	Complex A\[N\],B\[N\],C\[N\],D\[N\],a,b,c,d;
	int l,Rank\[N\],len;
	void Prepare(int n)
	{
		for(len=1,l=0;len<n;len<<=1,l++);
		for(int i=0;i<len;i++) Rank\[i\]=(Rank\[i>>1\]>>1)|((i&1)<<l-1);
	}
	void dft(Complex *x,int f)
	{
		for(int i=0;i<len;i++) if(i<Rank\[i\]) std::swap(x\[i\],x\[Rank\[i\]\]);
		Complex w,wn,tmp;
		for(int i=1;i<len;i<<=1)
		{
			wn={cos(pi/i),f*sin(pi/i)};
			for(int j=0;j<len;j+=i<<1)
			{
				w={1,0};
				for(int k=0;k<i;w=w*wn,k++)
					tmp=x\[i+j+k\]*w,x\[i+j+k\]=x\[j+k\]-tmp,x\[j+k\]=x\[j+k\]+tmp;
			}
		}
		if(f<0) for(int i=0;i<len;i++) x\[i\].r/=len;
	}
public:
	void multiply(int n,int \*x,int m,int \*y,int *z)
	{
		Prepare(n+m);
		for(int i=0;i<len;i++) A\[i\]=B\[i\]=C\[i\]=D\[i\]={0,0};
		for(int i=0;i<n;i++) A\[i\].r=x\[i\]/block,B\[i\].r=x\[i\]%block;
		for(int i=0;i<m;i++) C\[i\].r=y\[i\]/block,D\[i\].r=y\[i\]%block;
		dft(A,1),dft(B,1),dft(C,1),dft(D,1);
		for(int i=0;i<len;i++) a=A\[i\],b=B\[i\],c=C\[i\],d=D\[i\],A\[i\]=a\*c,B\[i\]=a\*d,C\[i\]=b\*c,D\[i\]=b\*d;
		dft(A,-1),dft(B,-1),dft(C,-1),dft(D,-1);
		for(int i=0;i<n+m;i++)
		{
			z\[i\]=(ll)(A\[i\].r+.5)%mod\*block%mod\*block%mod;
			z\[i\]=cal(z\[i\]+(ll)(B\[i\].r+.5)%mod*block%mod);
			z\[i\]=cal(z\[i\]+(ll)(C\[i\].r+.5)%mod*block%mod);
			z\[i\]=cal(z\[i\]+(ll)(D\[i\].r+.5)%mod);
		}
	}
}mtt;
int main()
{
	scanf("%d%d%d",&n,&m,&mod),block=32768;
	for(int i=0;i<n;i++) scanf("%d",&A\[i\]);
	for(int i=0;i<m;i++) scanf("%d",&B\[i\]);
	mtt.multiply(n,A,m,B,C);
	for(int i=0;i<n+m-1;i++) printf("%d ",C\[i\]);puts("");
	return 0;
}

### FWT(xor)

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<string>
#include<algorithm>
#include<queue>
#include<vector>
#include<set>
#include<map>
using std::cin;using std::cerr;
using std::max;using std::min;
#define N 50005
#define M 65540
#define mod 1000000007
#define ll long long
#define db double
#define dbg1(x) cerr<<#x<<"="<<(x)<<" "
#define dbg2(x) cerr<<#x<<"="<<(x)<<"\\n"
int n,m,A\[M\],B\[M\];
int cal(int x) {x-=x<mod?0:mod;return x;}
class FWT
{
public:
	int len,inv;
	void Prepare(int n) {for(len=1;len<=n;len<<=1);inv=mod+1>>1;}
	void dft(int *x,int f)
	{
		for(int i=1;i<len;i<<=1)
			for(int j=0;j<len;j+=i<<1)
				for(int k=0,tmp;k<i;k++)
				{
					tmp=x\[i+j+k\],x\[i+j+k\]=cal(x\[j+k\]-tmp+mod),x\[j+k\]=cal(x\[j+k\]+tmp);
					if(f<0) x\[j+k\]=(ll)x\[j+k\]\*inv%mod,x\[i+j+k\]=(ll)x\[i+j+k\]\*inv%mod;
				}
	}
}fwt;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=0;i<=n;i++) scanf("%d",&A\[i\]);
	for(int i=0;i<=m;i++) scanf("%d",&B\[i\]);
	fwt.Prepare(max(n,m)),fwt.dft(A,1),fwt.dft(B,1);
	for(int i=0;i<fwt.len;i++) A\[i\]=(ll)A\[i\]*A\[i\]%mod;
	fwt.dft(A,-1);
	return 0;
}

### FWT(or)

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<string>
#include<algorithm>
#include<queue>
#include<vector>
#include<set>
#include<map>
using std::cin;using std::cerr;
using std::max;using std::min;
#define N 50005
#define M 65540
#define mod 1000000007
#define ll long long
#define db double
#define dbg1(x) cerr<<#x<<"="<<(x)<<" "
#define dbg2(x) cerr<<#x<<"="<<(x)<<"\\n"
int n,m,A\[M\],B\[M\];
int cal(int x) {x-=x<mod?0:mod;return x;}
class FWT
{
public:
	int len;
	void Prepare(int n) {for(len=1;len<=n;len<<=1);}
	void dft(int *x,int f)
	{
		for(int i=1;i<len;i<<=1)
			for(int j=0;j<len;j+=i<<1)
				for(int k=0;k<i;k++)
				{
					if(f>0) x\[i+j+k\]=cal(x\[i+j+k\]+x\[j+k\]);
					else x\[i+j+k\]=cal(x\[i+j+k\]-x\[j+k\]+mod);
				}
	}
}fwt;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=0;i<=n;i++) scanf("%d",&A\[i\]);
	for(int i=0;i<=m;i++) scanf("%d",&B\[i\]);
	fwt.Prepare(max(n,m)),fwt.dft(A,1),fwt.dft(B,1);
	for(int i=0;i<fwt.len;i++) A\[i\]=(ll)A\[i\]*A\[i\]%mod;
	fwt.dft(A,-1);
	return 0;
}

### FWT(and)

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<string>
#include<algorithm>
#include<queue>
#include<vector>
#include<set>
#include<map>
using std::cin;using std::cerr;
using std::max;using std::min;
#define N 50005
#define M 65540
#define mod 1000000007
#define ll long long
#define db double
#define dbg1(x) cerr<<#x<<"="<<(x)<<" "
#define dbg2(x) cerr<<#x<<"="<<(x)<<"\\n"
int n,m,A\[M\],B\[M\];
int cal(int x) {x-=x<mod?0:mod;return x;}
class FWT
{
public:
	int len;
	void Prepare(int n) {for(len=1;len<=n;len<<=1);}
	void dft(int *x,int f)
	{
		for(int i=1;i<len;i<<=1)
			for(int j=0;j<len;j+=i<<1)
				for(int k=0;k<i;k++)
				{
					if(f>0) x\[j+k\]=cal(x\[j+k\]+x\[i+j+k\]);
					else x\[j+k\]=cal(x\[j+k\]-x\[i+j+k\]+mod);
				}
	}
}fwt;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=0;i<=n;i++) scanf("%d",&A\[i\]);
	for(int i=0;i<=m;i++) scanf("%d",&B\[i\]);
	fwt.Prepare(max(n,m)),fwt.dft(A,1),fwt.dft(B,1);
	for(int i=0;i<fwt.len;i++) A\[i\]=(ll)A\[i\]*A\[i\]%mod;
	fwt.dft(A,-1);
	return 0;
}

### 多项式运算

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<string>
#include<algorithm>
#include<queue>
#include<vector>
#include<set>
#include<map>
using std::cin;using std::cerr;
using std::max;using std::min;
#define N 300005
#define mod 998244353
#define ll long long
#define db double
#define dbg1(x) cerr<<#x<<"="<<(x)<<" "
#define dbg2(x) cerr<<#x<<"="<<(x)<<"\\n"
int n,m,A\[N\],B\[N\],C\[N\],inv\[N\];
int cal(int x) {x-=x<mod?0:mod;return x;}
int Pow(int x,int y=mod-2) {int res=1;for(;y;x=(ll)x\*x%mod,y>>=1) if(y&1) res=(ll)res\*x%mod;return res;}
class NTT
{
	int g1,g2,l,inv,Rank\[N\];
public:
	int len;
	void Prepare(int n)
	{
		for(len=1,l=0;len<n;len<<=1,l++);
		g1=3,g2=332748118,inv=Pow(len);
		for(int i=0;i<len;i++) Rank\[i\]=(Rank\[i>>1\]>>1)|((i&1)<<l-1);
	}
	void dft(int *x,int f)
	{
		for(int i=0;i<len;i++) if(i<Rank\[i\]) std::swap(x\[i\],x\[Rank\[i\]\]);
		for(int i=1;i<len;i<<=1)
			for(int j=0,wn=Pow(f>0?g1:g2,(mod+1)/(i<<1));j<len;j+=i<<1)
				for(int k=0,w=1,tmp;k<i;w=(ll)w*wn%mod,k++)
					tmp=(ll)x\[i+j+k\]*w%mod,x\[i+j+k\]=cal(x\[j+k\]-tmp+mod),x\[j+k\]=cal(x\[j+k\]+tmp);
		if(f<0) for(int i=0;i<len;i++) x\[i\]=(ll)x\[i\]*inv%mod;
	}
}ntt;
void multiply(int n,int \*x,int m,int \*y,int *z)
{
	ntt.Prepare(n+m),ntt.dft(x,1),ntt.dft(y,1);
	for(int i=0;i<ntt.len;i++) z\[i\]=(ll)x\[i\]*y\[i\]%mod;
	ntt.dft(z,-1);
}
void Inverse(int n,int \*x,int \*y)//要保证y初始为0
{
	if(n==1) return void(y\[0\]=Pow(x\[0\]));
	Inverse(n+1>>1,x,y),ntt.Prepare(n<<1);
	static int tp\[N\];
	for(int i=0;i<ntt.len;i++) tp\[i\]=0;
	for(int i=0;i<n;i++) tp\[i\]=x\[i\];
	ntt.dft(tp,1),ntt.dft(y,1);
	for(int i=0;i<ntt.len;i++) y\[i\]=(ll)y\[i\]\*cal(2-(ll)tp\[i\]\*y\[i\]%mod+mod)%mod;
	ntt.dft(y,-1);
	for(int i=n;i<ntt.len;i++) y\[i\]=0;
}
void Division(int n,int \*x,int m,int \*y,int *z)
{
	std::reverse(x,x+n),std::reverse(y,y+m);
	static int tx\[N\];
	for(int i=0;i<n;i++) tx\[i\]=x\[i\];
	Inverse(n-m+1,y,z),multiply(n,tx,n-m+1,z,z);
	for(int i=n-m+1;i<ntt.len;i++) z\[i\]=0;
	std::reverse(x,x+n),std::reverse(y,y+m),std::reverse(z,z+n-m+1);
}
void Sqrt(int n,int \*x,int \*y)
{
	if(n==1) return void(y\[0\]=sqrt(x\[0\]));
	Sqrt(n+1>>1,x,y);
	static int tp\[N\],tx\[N\];
	for(int i=0;i<n;i++) tx\[i\]=x\[i\];
	Inverse(n,y,tp),multiply(n,tp,n,tx,tp);
	for(int i=0;i<n;i++) y\[i\]=(ll)cal(y\[i\]+tp\[i\])*(mod+1>>1)%mod;
	for(int i=0;i<ntt.len;i++) tp\[i\]=0;
}
void Dao(int n,int \*x,int \*y) {for(int i=0;i<n;i++) y\[i\]=(ll)x\[i+1\]*(i+1)%mod;}
void Jifen(int n,int \*x,int \*y)
{
	inv\[0\]=inv\[1\]=1,y\[0\]=0;
	for(int i=2;i<=n;i++) inv\[i\]=(ll)(mod-mod/i)*inv\[mod%i\]%mod;
	for(int i=1;i<n;i++) y\[i\]=(ll)x\[i-1\]*inv\[i\]%mod;
}
void Ln(int n,int \*x,int \*y)
{
	static int tp\[N\],res\[N\];
	for(int i=0;i<n<<1;i++) tp\[i\]=0;
	Dao(n,x,res),Inverse(n,x,tp),multiply(n,res,n,tp,res),Jifen(n,res,y);
}
void Exp(int n,int \*x,int \*y)
{
	if(n==1) return void(y\[0\]=1);
	Exp(n+1>>1,x,y),ntt.Prepare(n+(n+1>>1));
	static int tp\[N\];
	for(int i=0;i<ntt.len;i++) tp\[i\]=0;
	Ln(n,y,tp);
	for(int i=0;i<n;i++) tp\[i\]=cal(x\[i\]-tp\[i\]+mod);
	tp\[0\]=1,multiply(n,tp,n+1>>1,y,y);
	for(int i=n;i<ntt.len;i++) y\[i\]=0;
}
int main()
{
	// scanf("%d%d",&n,&m);
	scanf("%d",&n);
	for(int i=0;i<n;i++) scanf("%d",&A\[i\]);
	// for(int i=0;i<m;i++) scanf("%d",&B\[i\]);
	/*
	A有n项,B有m项,C=A*B
	multiply(n,A,m,B,C);
	for(int i=0;i<n+m;i++) printf("%d ",C\[i\]);puts("");
	*/
	
	/*
	A有n项,C为A在%x^n意义下的逆元
	Inverse(n,A,C);
	for(int i=0;i<n;i++) printf("%d ",C\[i\]);puts("");
	*/
	
	/*
	A有n项,B有m项,C=A/B,有n-m+1项
	Division(n,A,m,B,C);
	for(int i=0;i<=n-m;i++) printf("%d ",C\[i\]);puts("");
	A%B=A-B*C,最多有m-1项（不足的补0）
	multiply(m,B,n-m+1,C,C);
	for(int i=0;i<m-1;i++) printf("%d ",cal(A\[i\]-C\[i\]+mod));puts("");
	*/
	
	/*
	A有n项,C*C=A(mod x^n)
	Sqrt(n,A,C);
	for(int i=0;i<n;i++) printf("%d ",C\[i\]);puts("");
	*/
	
	/*
	A有n项,C为A的一阶导
	Dao(n,A,C);
	for(int i=0;i<n;i++) printf("%d ",C\[i\]);puts("");
	*/

	/*
	A有n项，C为A的积分
	Jifen(n,A,C);
	for(int i=0;i<n;i++) printf("%d ",C\[i\]);puts("");
	*/

	/*
	A有n项，ln(A(x))=C(x)
	Ln(n,A,C);
	for(int i=0;i<n;i++) printf("%d ",C\[i\]);puts("");
	*/

	/*
	A有n项，e^A(x)=C(x)
	Exp(n,A,C);
	for(int i=0;i<n;i++) printf("%d ",C\[i\]);puts("");
	*/
	return 0;
}

 

图论
==

### 强连通分量

$n$个点$m$条边的有向图，求出每个点所属的强连通分量的编号。

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<string>
#include<algorithm>
#include<queue>
#include<vector>
#include<set>
#include<map>
using std::cin;using std::cerr;
using std::max;using std::min;
#define N 100005
#define ll long long
#define db double
#define pb push_back
#define dbg1(x) cerr<<#x<<"="<<(x)<<" "
#define dbg2(x) cerr<<#x<<"="<<(x)<<"\\n"
int n,m,a,b,ecnt,last\[N\],idx,dfn\[N\],low\[N\],tot,bel\[N\],top,sta\[N\],ins\[N\];
struct road{int to,nex;}e\[N\];
void adde(int u,int v) {e\[++ecnt\]=(road){v,last\[u\]},last\[u\]=ecnt;}
void tarjan(int x)
{
	dfn\[x\]=low\[x\]=++idx,sta\[++top\]=x,ins\[x\]=1;
	for(int k=last\[x\];k;k=e\[k\].nex)
		if(!dfn\[e\[k\].to\]) tarjan(e\[k\].to),low\[x\]=min(low\[x\],low\[e\[k\].to\]);
		else if(ins\[e\[k\].to\]) low\[x\]=min(low\[x\],dfn\[e\[k\].to\]);
	if(low\[x\]==dfn\[x\])
	{
		tot++;int tmp;
		do tmp=sta\[top--\],bel\[tmp\]=tot,ins\[tmp\]=0;
		while(tmp^x);
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++) scanf("%d%d",&a,&b),adde(a,b);
	for(int i=1;i<=n;i++) if(!dfn\[i\]) tarjan(i);
	for(int i=1;i<=n;i++) printf("%d\\n",bel\[i\]);
	return 0;
}

### 点双连通分量（待填）

### 边双连通分量（待填）

### 割点

$n$个点$m$条边的无向图，从小到大输出每个割点。

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<string>
#include<algorithm>
#include<queue>
#include<vector>
#include<set>
#include<map>
using std::cin;using std::cerr;
using std::max;using std::min;
#define N 100005
#define ll long long
#define db double
#define pb push_back
#define dbg1(x) cerr<<#x<<"="<<(x)<<" "
#define dbg2(x) cerr<<#x<<"="<<(x)<<"\\n"
int n,m,a,b,ecnt,last\[N\],idx,dfn\[N\],low\[N\],cut\[N\];
struct road{int to,nex;}e\[N<<1\];
void adde(int u,int v) {e\[++ecnt\]=(road){v,last\[u\]},last\[u\]=ecnt;}
void tarjan(int x,int fath=0)
{
	dfn\[x\]=low\[x\]=++idx;int son=0;
	for(int k=last\[x\];k;k=e\[k\].nex)
		if(!dfn\[e\[k\].to\])
		{
			tarjan(e\[k\].to,x),low\[x\]=min(low\[x\],low\[e\[k\].to\]),son++;
			if(!fath&&son>1||fath&&low\[e\[k\].to\]>=dfn\[x\]) cut\[x\]=1;
		}
		else low\[x\]=min(low\[x\],dfn\[e\[k\].to\]);
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++) scanf("%d%d",&a,&b),adde(a,b),adde(b,a);
	for(int i=1;i<=n;i++) if(!dfn\[i\]) tarjan(i);
	for(int i=1;i<=n;i++) if(cut\[i\]) printf("%d\\n",i);
	return 0;
}

### 割边（待填）

二分图
---

### 匈牙利

$n$个点$m$条边的最大匹配。

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<queue>
#include<vector>
#include<map>
#include<set>
using std::cin;using std::cerr;
using std::max;using std::min;
#define N 10005
#define ll long long
#define db double
#define dbg1(x) cerr<<#x<<"="<<x<<" "
#define dbg2(x) cerr<<#x<<"="<<x<<"\\n"
int T,n,m,a,b,ecnt,last\[N\],used\[N\],match\[N\];
struct road{int to,nex;}e\[N<<1\];
void adde(int u,int v) {e\[++ecnt\]=(road){v,last\[u\]},last\[u\]=ecnt;}
bool dfs(int x)
{
    for(int k=last\[x\];k;k=e\[k\].nex)
        if(!used\[e\[k\].to\])
        {
            used\[e\[k\].to\]=1;
            if(!match\[e\[k\].to\]||dfs(match\[e\[k\].to\])) {match\[e\[k\].to\]=x;return 1;}
        }
    return 0;
}
int Maxmatch()
{
    int res=0;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++) used\[j\]=0;
        if(dfs(i)) res++;
    }
    return res;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++) scanf("%d%d",&a,&b),adde(a,b);
    printf("%d\\n",Maxmatch());
    return 0;
}

### KM

$n$个点的最大权完备匹配（完美匹配）。

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<queue>
#include<vector>
#include<map>
#include<set>
using std::cin;using std::cerr;
using std::max;using std::min;
#define N 55
#define inf 1e9 
#define ll long long
#define db double
#define dbg1(x) cerr<<#x<<"="<<x<<" "
#define dbg2(x) cerr<<#x<<"="<<x<<"\\n"
int n,m,e\[N\]\[N\],valx\[N\],valy\[N\],slack\[N\],visx\[N\],visy\[N\],match\[N\];
bool dfs(int x)
{
    visx\[x\]=1;
    for(int i=1,tmp;i<=n;i++)
        if(!(tmp=valx\[x\]+valy\[i\]-e\[x\]\[i\])&&!visy\[i\])
        {
            visy\[i\]=1;
            if(!match\[i\]||dfs(match\[i\])) {match\[i\]=x;return 1;}
        }
        else slack\[i\]=min(slack\[i\],tmp);
    return 0;
}
int KM()
{
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++) valx\[i\]=max(valx\[i\],e\[i\]\[j\]);
    for(int i=1,d;i<=n;i++)
    {
        for(int j=1;j<=n;j++) slack\[j\]=inf;
        for(;;)
        {
            for(int j=1;j<=n;j++) visx\[j\]=visy\[j\]=0;
            if(dfs(i)) break;
            d=inf;
            for(int j=1;j<=n;j++) if(!visy\[j\]) d=min(d,slack\[j\]);
            for(int j=1;j<=n;j++) if(visx\[j\]) valx\[j\]-=d;
            for(int j=1;j<=n;j++) visy\[j\]?valy\[j\]+=d:slack\[j\]-=d;
        }
    }
    int res=0;
    for(int i=1;i<=n;i++) res+=e\[match\[i\]\]\[i\];
    return res;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++) scanf("%d",&e\[i\]\[j\]);
    printf("%d\\n",KM());
    return 0;
}

 

杂
=

### 辛普森积分

求$n$个圆的面积并。

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<queue>
#include<stack>
#include<vector>
using namespace std;
#define N 1005
#define eps 1e-9
#define inf 1e9
#define ll long long
#define db double
int n;db L=inf,R;
struct point{db x,y,r;}p\[N\];
struct line
{
    db l,r;
    friend bool operator<(line t1,line t2) {return t1.l<t2.l||t1.l==t2.l&&t1.r<t2.r;}
}A\[N\];
db F(db x)//求x=x这条直线上经过圆的面积并的长度
{
    int cnt=0;db tmp,res=0;
    for(int i=1;i<=n;i++)
        if(fabs(p\[i\].x-x)-p\[i\].r<eps)
            tmp=sqrt(p\[i\].r\*p\[i\].r-(p\[i\].x-x)\*(p\[i\].x-x)),A\[++cnt\]=(line){p\[i\].y-tmp,p\[i\].y+tmp};
    sort(A+1,A+1+cnt),tmp=-inf;
    for(int i=1;i<=cnt;i++)
        if(A\[i\].l>tmp) res+=A\[i\].r-A\[i\].l,tmp=A\[i\].r;
        else if(A\[i\].r>tmp) res+=A\[i\].r-tmp,tmp=A\[i\].r;
    return res;
}
db Simpson(db l,db r,db fl,db fmid,db fr) {return (r-l)/6*(fl+4*fmid+fr);}//Simpson公式
db Solve(db l,db r,db fl,db fmid,db fr,db S,int d)//求并的横坐标在\[l,r\]内的面积
{
    db mid=(l+r)\*0.5,midl=(l+mid)\*0.5,midr=(mid+r)*0.5;
    db fmidl=F(midl),fmidr=F(midr),Sl=Simpson(l,mid,fl,fmidl,fmid),Sr=Simpson(mid,r,fmid,fmidr,fr);
    if(fabs(Sl+Sr-S)<eps&&d>14) return S;//在时间允许的范围内保证精度，即控制迭代次数
    return Solve(l,mid,fl,fmidl,fmid,Sl,d+1)+Solve(mid,r,fmid,fmidr,fr,Sr,d+1);
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%lf%lf%lf",&p\[i\].x,&p\[i\].y,&p\[i\].r),L=min(L,p\[i\].x-p\[i\].r),R=max(R,p\[i\].x+p\[i\].r);
    db fl=F(L),fmid=F((L+R)*0.5),fr=F(R);
    printf("%.3lf\\n",Solve(L,R,fl,fmid,fr,Simpson(L,R,fl,fmid,fr),0));
    return 0;
}

### 线性基

求$n$个数的线性基，并询问和某个数最大的异或是多少。

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<queue>
#include<vector>
#include<set>
#include<map>
using namespace std;
#define N 1000005
#define ll long long
#define db double
#define dbg1(x) cout<<#x<<"="<<x<<" "
#define dbg2(x) cout<<#x<<"="<<x<<"\\n"
#define _(d) while(d((ch=getchar()-48)>=0))
int n,m,a,A\[N\];
struct LinearBasis
{
    int v\[35\];
    void insert(int x)//往线性基里加入一个数x 
    {
        for(int i=30;~i&&x;i--)
            if(x>>i&1) if(v\[i\]) x^=v\[i\];else return void(v\[i\]=x);
    }
    int ask(int x)//查询和v最大的异或 
    {
        for(int i=30;~i;i--) if(v\[i\]&&!(x>>i&1)) x^=v\[i\];
        return x;
    }
}LB;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&A\[i\]),LB.insert(A\[i\]);
    for(scanf("%d",&m);m--;) scanf("%d",&a),printf("%d\\n",LB.ask(a));
    return 0;
}

### 高斯消元

$n$个方程$n$个未知数，$A\[i\]\[j\]$是第$i$个方程中第$j$个未知数前的系数，$A\[i\]\[n+1\]$是第$i$个方程的值。

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<string>
#include<algorithm>
#include<queue>
#include<vector>
#include<set>
#include<map>
using std::cin;using std::cerr;
using std::max;using std::min;
#define N 105
#define eps 1e-9
#define ll long long
#define db double
#define dbg1(x) cerr<<#x<<"="<<(x)<<" "
#define dbg2(x) cerr<<#x<<"="<<(x)<<"\\n"
int n;db A\[N\]\[N\],a\[N\];
void Gauss()
{
	int Max;db tmp;
	for(int i=1;i<=n;i++)
	{
		Max=i;
		for(int j=i+1;j<=n;j++) if(fabs(A\[j\]\[i\])>fabs(A\[Max\]\[i\])) Max=j;
		std::swap(A\[i\],A\[Max\]),tmp=A\[i\]\[i\];
		if(fabs(tmp)<eps) continue;
		for(int j=1;j<=n+1;j++) A\[i\]\[j\]/=tmp;
		for(int j=1;j<=n;j++)
			if(i^j)
			{
				tmp=A\[j\]\[i\];
				for(int k=1;k<=n+1;k++) A\[j\]\[k\]-=A\[i\]\[k\]*tmp;
			}
	}
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n+1;j++) scanf("%lf",&A\[i\]\[j\]);
	Gauss();
	for(int i=1;i<=n;i++) printf("%.3lf ",A\[i\]\[n+1\]);
	return 0;
}

### 异或高斯消元（待填）

### 拉格朗日插值（待填）