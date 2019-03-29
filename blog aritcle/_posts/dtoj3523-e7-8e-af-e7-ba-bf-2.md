---
title: " DTOJ3523环线\t\t"
tags:
  - 分治
  - 数学
  - 矩阵
url: 712.html
id: 712
categories:
  - Solution
date: 2018-02-20 13:47:00
---

计算走不超过k步后回到自己的路径条数 列出矩阵，（i，j）=1表示从i到j有一条边。记当前矩阵为A。 那么将矩阵$A,A^2,A^3...A^{k-1}$的对角线之和累加起来即是答案。 但是这样求解复杂度很大。 我们思考一种利用等比数列思想的分拆方法： 如果k为偶数 $$Ans\_k=\\sum\_{i=1}^{k}A\_i=\\sum\_{i=1}^{\\frac{k}{2}}A\_i+A^{\\frac{k}{2}}(\\sum\_{i=1}^{\\frac{k}{2}}A\_i)=(A^{\\frac{k}{2}}+1)Ans\_{\\frac{k}{2}}$$ 如果k为奇数 $$Ans\_k=\\sum\_{i=1}^{k}A\_i=\\sum\_{i=1}^{\\frac{k}{2}}A\_i+A^{\\frac{k}{2}}(\\sum\_{i=1}^{\\frac{k}{2}}A\_i)=(A^{\\frac{k}{2}}+1)Ans\_{\\frac{k}{2}}$$ 不断分拆下去即可。 给出另外一种写法的代码，利用虚拟点统计+稀疏矩阵优化，卡过时限。

#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<string>
#include<cstdlib>
#include<cmath>
#define ll long long
using namespace std;
#define N 205
int n,k,p,cnt;
int a\[N\]\[N\],b\[N\]\[N\];
char ch\[105\];
long long ans;
void calc(int a\[N\]\[N\],int b\[N\]\[N\],int c\[N\]\[N\])
{
    int tmp\[N\]\[N\];
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++) tmp\[i\]\[j\]=0; 
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            for(int k=1;k<=n && a\[i\]\[j\];k++)
                tmp\[i\]\[k\]=(tmp\[i\]\[k\]+(ll)a\[i\]\[j\]*b\[j\]\[k\])%p;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++) c\[i\]\[j\]=tmp\[i\]\[j\];
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%s",ch+1);
        for(int j=1;j<=n;j++)
            if(ch\[j\]=='Y') a\[i\]\[j\]=a\[i\]\[j+n\]=1;
        b\[i\]\[i\]=b\[n+i\]\[n+i\]=1;
        a\[n+i\]\[n+i\]=1;
    }n*=2;
    scanf("%d%d",&k,&p);k--;
    while(k)
    {
        if(k&1) calc(b,a,b);
        calc(a,a,a);
        k>>=1;
    }
    for(int i=1;i<=n/2;i++) ans=(ans+b\[i\]\[i+n/2\])%p;
    cout<<ans<<endl;
    return 0;
}