---
title: " DTOJ1628玉蟾宫\t\t"
tags:
  - 单调队列
url: 752.html
id: 752
categories:
  - Solution
date: 2018-02-25 20:22:27
---

固定一个行，然后维护这个行中一块连续的可选土地，能分别向右和向左拓展多少。明显要求这一部分均为F色块。那么我们用单调栈可以O(n)维护每一行的答案。

#include<bits/stdc++.h>
#define N 1005
using namespace std;
int n,m,s\[N\]\[N\],height\[N\]\[N\],l\[N\],r\[N\],stk\[N\],top;
char ch\[N\];
int ans;
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {   scanf("%s",ch+1);
            if(ch\[1\]=='F') s\[i\]\[j\]=1,height\[i\]\[j\]=height\[i-1\]\[j\]+1;
        }
    }
    for(int i=1;i<=n;i++)
    {
        stk\[top=0\]=0;
        for(int j=1;j<=m;j++)
        {
            while(top && height\[i\]\[stk\[top\]\]>=height\[i\]\[j\]) top--;
            l\[j\]=stk\[top\];stk\[++top\]=j;
        }
        stk\[top=0\]=m+1;
        for(int j=m;j>=1;j--)
        {
            while(top && height\[i\]\[stk\[top\]\]>=height\[i\]\[j\]) top--;
            r\[j\]=stk\[top\];stk\[++top\]=j;
        }
        for(int j=1;j<=m;j++)ans=max(ans,(r\[j\]-l\[j\])*height\[i\]\[j\]-height\[i\]\[j\]);
    }
    printf("%d\\n",ans*3);
    return 0;
}