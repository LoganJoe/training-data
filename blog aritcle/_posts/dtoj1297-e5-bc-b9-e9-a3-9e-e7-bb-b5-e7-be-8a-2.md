---
title: " DTOJ1297弹飞绵羊\t\t"
tags:
  - Link-Cut Tree
url: 2106.html
id: 2106
categories:
  - Solution
date: 2018-05-27 19:14:53
---

这题貌似没什么好写的。就是LCT板子。

#include<bits/stdc++.h>
#define N 200005
#define lc t\[x\].son\[0\]
#define rc t\[x\].son\[1\]
using namespace std;
int n,m,s\[N\];
struct LCT
{   
    int rt;
    struct tree{int fa,rev,next,son\[2\],size;}t\[N\];
    void pushup(int x){t\[x\].size=t\[lc\].size+t\[rc\].size+1;}
    void pushdown(int x){if(t\[x\].rev)t\[x\].rev^=1,t\[lc\].rev^=1,t\[rc\].rev^=1,swap(lc,rc);}
    bool isroot(int x){return t\[t\[x\].fa\].son\[0\]!=x&&t\[t\[x\].fa\].son\[1\]!=x;} 
    void rotate(int x)
    {
        int y=t\[x\].fa,z=t\[y\].fa,l,r;
        l=t\[y\].son\[1\]==x,r=l^1;
        if(!isroot(y)) t\[z\].son\[t\[z\].son\[1\]==y\]=x;
        t\[x\].fa=z,t\[y\].fa=x,t\[t\[x\].son\[r\]\].fa=y;
        t\[y\].son\[l\]=t\[x\].son\[r\],t\[x\].son\[r\]=y;
        pushup(y),pushup(x);
    }
    void splay(int x)
    {
        int top=0;s\[++top\]=x;
        for(int i=x;!isroot(i);i=t\[i\].fa) s\[++top\]=t\[i\].fa;
        for(int i=top;i;i--) pushdown(s\[i\]);
        while(!isroot(x))
        {
            int y=t\[x\].fa,z=t\[y\].fa;
            if(!isroot(y))
                if(t\[z\].son\[0\]==y^t\[y\].son\[0\]==x) rotate(y);
                else rotate(x);
            rotate(x);
        }
    }
    void rever(int x){access(x);splay(x),t\[x\].rev^=1;}
    void link(int x,int y){rever(x);t\[x\].fa=y,splay(x);}
    void access(int x)
    {
        for(int y=0;x;y=x,x=t\[x\].fa){splay(x);rc=y;}
    }
    void cut(int x,int y)
    {
        rever(x);access(y);splay(y);
        t\[y\].son\[0\]=t\[x\].fa=0;
    }
public:
    void init()
    {
        rt=n+1,t\[rt\].size=1;
        for(int i=1,x;i<=n;i++) 
            scanf("%d",&x),t\[i\].next=t\[i\].fa=min(rt,x+i),t\[i\].size=1;
    }
    int ask(int x){rever(rt),access(x);splay(x); return t\[lc\].size;}
    void modify(int x,int y){cut(x,t\[x\].next),link(x,y);t\[x\].next=y;}
}T;
int main()
{
    scanf("%d",&n);
    T.init();   
    scanf("%d",&m);
    while(m--)
    {
        int opt,x,y;scanf("%d",&opt);
        if(opt==1) scanf("%d",&x),printf("%d \\n",T.ask(x+1));
        if(opt==2) scanf("%d%d",&x,&y),T.modify(x+1,min(T.rt,x+y+1));
    }
}