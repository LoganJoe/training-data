---
title: " DTOJ1363楼房重建\t\t"
tags:
  - 奇技淫巧
  - 线段树
url: 2163.html
id: 2163
categories:
  - DTOJ
  - Solution
date: 2018-05-29 23:20:36
---

这题的解法很玄妙啊。 显然看到的楼与$(0,0)$连线的斜率是单调增大的。那么我们考虑用线段树维护一段区间斜率单调增大的最大长度和最大的斜率（也就是单调增大的末尾的数）。 线段树维护的信息一定要是可以合并的，那么这玩意要怎么合并呢？ 记结点$x$的左儿子为$lc\[x\]$，右儿子为$rc\[x\]$，结点$x$代表的区间的单增序列的最大长度为$len\[x\]$，斜率最大值为$Max\[x\]$。 $Max\[x\]$显然很好维护，现在考虑如何维护$len\[x\]$。 显然有$len\[x\]=max\\{len\[lc\[x\]\],len\[rc\[x\]\]\\}$。但还有一种情况是左儿子的一段接上右儿子的一段。 如果$Max\[rc\[x\]\]\\leqslant Max\[lc\[x\]\]$，那么显然右儿子不能在左儿子后面接。 否则再考虑右儿子的左右儿子。 如果右儿子的左儿子的最大值$\\leqslant Max\[lc\[x\]\]$，即$Max\[lc\[rc\[x\]\]\]\\leqslant Max\[lc\[x\]\]$，那么$x$右儿子的左儿子也不能接在$x$的左儿子的序列后，这个时候我们继续递归往右儿子找；否则，$x$的右儿子的左儿子一定能有一段能接在$x$的左儿子后，求这段的长度是同样的子问题，递归求解，然后加上$len\[rc\[x\]\]-len\[lc\[rc\[x\]\]\]$，即$x$的右儿子的右儿子能接在$x$的右儿子的左儿子后的长度。 好像很绕，看代码吧……

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
using std::cerr;using std::max;using std::min;
#define N 100005
#define ll long long
#define db double
#define dbg1(x) cerr<<#x<<"="<<x<<" "
#define dbg2(x) cerr<<#x<<"="<<x<<"\\n"
int n,m,a,b;
class SegmentTree
{
#define lc x<<1
#define rc x<<1|1
#define mid (l+r>>1)
    struct node{int v;db Max;}t\[N<<2\];
    int ask(int x,int l,int r,db v)
    {
        if(t\[x\].Max<=v) return 0;
        if(l==r) return 1;
        if(t\[lc\].Max>v) return ask(lc,l,mid,v)+t\[x\].v-t\[lc\].v;
        else return ask(rc,mid+1,r,v);
    }
    void pushup(int x,int l,int r)
    {
        t\[x\].Max=max(t\[lc\].Max,t\[rc\].Max);
        t\[x\].v=t\[lc\].v+ask(rc,mid+1,r,t\[lc\].Max);
    }
public:
    void change(int x,int l,int r,int p,db v)
    {
        if(l==r) return void(t\[x\]=(node){1,v});
        p<=mid?change(lc,l,mid,p,v):change(rc,mid+1,r,p,v);
        pushup(x,l,r);
    }
    int ask() {return t\[1\].v;}
}T;
int main()
{
    for(scanf("%d%d",&n,&m);m--;)
        scanf("%d%d",&a,&b),T.change(1,1,n,a,1.*b/a),printf("%d\\n",T.ask());
    return 0;
}

据说还有分块+单调栈的做法。