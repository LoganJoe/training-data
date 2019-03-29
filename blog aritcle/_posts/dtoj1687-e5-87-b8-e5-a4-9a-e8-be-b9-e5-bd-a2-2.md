---
title: " DTOJ1687凸多边形\t\t"
tags:
  - 半平面交
url: 1880.html
id: 1880
categories:
  - Solution
date: 2018-05-06 21:21:34
---

两个凸包的交也是一个凸包，那么相当于将两个凸包上面的所有边取出来做一次半平面交即可求出最后的交。

#include<bits/stdc++.h>
using namespace std;
#define db double
#define N 1005
int n,m,cnt,que\[N\];db ans;
struct P
{
    db x,y;
    P operator +(const P &a) const {return (P){x+a.x,y+a.y};}
    P operator -(const P &a) const {return (P){x-a.x,y-a.y};}
    P operator *(const db &a) const {return (P){x\*a,y\*a};}
    db operator *(const P &a) const {return x\*a.y-y\*a.x;}
}a\[N\];
struct L{P p,v;db a;L(){}L(P x,P y){p=x,v=y,a=atan2(v.y,v.x);}}s\[N\];
bool comp_(L a,P b){return a.v*(b-a.p)>0;}
bool cmp(L t1,L t2){return t1.a<t2.a || t1.a==t2.a && comp_(t1,t2.p);}
P Point(L a,L b)
{
    P ts=a.p-b.p;
    db k=(b.v\*ts)/(a.v\*b.v);
    return a.p+a.v*k;
}                               
void HPI()
{
    int tmp=1,l,r;
    sort(s+1,s+1+cnt,cmp);
    for(int i=2,j=1;i<=cnt;i++) if(fabs(s\[i\].a-s\[j\].a)>0) s\[tmp=++j\]=s\[i\]; 
    cnt=tmp;que\[l=1\]=1,que\[r=2\]=2;
    for(int i=3;i<=cnt;i++)
    {
        while(l<r && comp_(s\[i\],Point(s\[que\[r-1\]\],s\[que\[r\]\]))) r--;
        while(l<r && comp_(s\[i\],Point(s\[que\[l+1\]\],s\[que\[l\]\]))) l++;
        que\[++r\]=i;
    }
    while(l<r && comp_(s\[l\],Point(s\[que\[r-1\]\],s\[que\[r\]\]))) r--;
    que\[r+1\]=que\[l\];
    for(int i=l;i<=r;i++) a\[i\]=Point(s\[que\[i\]\],s\[que\[i+1\]\]);
    a\[r+1\]=a\[l\];
    for(int i=l;i<=r;i++) ans+=a\[i\]*a\[i+1\];
    if(r-l<2) ans=0;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) 
    {
        scanf("%d",&m);
        for(int j=1;j<=m;j++) scanf("%lf%lf",&a\[j\].x,&a\[j\].y);
        a\[m+1\]=a\[1\];
        for(int j=1;j<=m;j++) s\[++cnt\]=L(a\[j+1\],a\[j\]-a\[j+1\]);
    }
    HPI();
    printf("%.3lf\\n",ans/2);
}