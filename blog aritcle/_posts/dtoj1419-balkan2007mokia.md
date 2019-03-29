---
title: " DTOJ1419[Balkan2007]Mokia\t\t"
tags:
  - CDQ分治
url: 1274.html
id: 1274
categories:
  - Solution
date: 2018-03-29 18:59:13
---

数据范围比较大，并且带修改。 那么我们考虑CDQ分治。这是一个三维带修改问题。我们可以考虑\[l,mid\]内修改对于\[mid+1,r\]的影响。 首先对于询问，我们可以根据二位前缀和的思想，拆分成四个子询问，每次询问（1，1）到（x,y）这个方阵中的值。明显对于一个询问只会影响所有后面x,y比它小的方阵。我们固定x,用树状数组维护y，然后CDQ分治计算修改在\[l,mid\],查询在\[mid+1,r\]的所有涉及到的答案。

#include<bits/stdc++.h>
using namespace std;
#define N 200005
int s,w,m,ans\[N\],cnt,res;
struct quer
{
    int x,y,v,pos,opt,id;
    friend bool operator <(quer t1,quer t2)
    {return t1.x<t2.x||t1.x==t2.x&&t1.y<t2.y||t1.x==t2.x&&t1.y==t2.y&&t1.opt<t2.opt;}
}a\[N\],tmp\[N\];
class BIT
{
    int t\[N*10\];
    int lowbit(int x){return x&-x;}public:
    void add(int x,int v){for(int i=x;i<=w;i+=lowbit(i)) t\[i\]+=v;}
    int ask(int x){int res=0;for(int i=x;i;i-=lowbit(i)) res+=t\[i\];return res;}
}T;
void add()
{
    int x\_1,y\_1,x\_2,y\_2;scanf("%d%d%d%d",&x\_1,&y\_1,&x\_2,&y\_2);res++;
    a\[++cnt\]=(quer){x\_1-1,y\_1-1, 1,res,1,cnt};
    a\[++cnt\]=(quer){x\_2  ,y\_2  , 1,res,1,cnt};
    a\[++cnt\]=(quer){x\_1-1,y\_2  ,-1,res,1,cnt};
    a\[++cnt\]=(quer){x\_2  ,y\_1-1,-1,res,1,cnt};
}
void solve(int l,int r)
{
    if(l==r) return ;
    int mid=(l+r)>>1,m1=l,m2=mid+1;
    for(int i=l;i<=r;i++)
    {
        if(a\[i\].id<=mid && !a\[i\].opt)T.add(a\[i\].y,a\[i\].v) ;
        if(a\[i\].id>mid && a\[i\].opt)  ans\[a\[i\].pos\]+=a\[i\].v*T.ask(a\[i\].y);
    }
    for(int i=l;i<=r;i++) if(a\[i\].id<=mid && !a\[i\].opt) T.add(a\[i\].y,-a\[i\].v);
    for(int i=l;i<=r;i++) tmp\[(a\[i\].id<=mid)?(m1++):(m2++)\]=a\[i\];
    for(int i=l;i<=r;i++) a\[i\]=tmp\[i\];
    solve(l,mid),solve(mid+1,r);
}
int main()
{
    scanf("%d%d",&s,&w);
    while(1)
    {
        int opt,x,y,v;scanf("%d",&opt);
        if(opt==3) break;
        if(opt==1) scanf("%d%d%d",&x,&y,&v),a\[++cnt\]=(quer){x,y,v,0,0,cnt};
        if(opt==2) add();
    }
    sort(a+1,a+cnt+1);
    solve(1,cnt);
    for(int i=1;i<=res;i++) printf("%d\\n",ans\[i\]);
}