---
title: " DTOJ4059s\t\t"
tags:
  - 奇技淫巧
  - 贪心
url: 5415.html
id: 5415
categories:
  - DTOJ
  - Solution
date: 2018-12-10 20:26:28
---

原题是Codeforces321D。 这是道神仙题。 记$a\[i\]\[j\]$表示最后格子$(i,j)$是否被翻转。记$m=\\frac{n+1}{2}$。 有个结论是：$a\[i\]\[j\]\\oplus a\[i\]\[m\]\\oplus a\[i\]\[m+j\]=0,a\[i\]\[j\]\\oplus a\[m\]\[j\]\\oplus a\[m+i\]\[j\]=0$。其中$\\oplus$表示异或。 反正我是发现不了 大概解释一下，一次操作范围为$m\\times m$，一定会覆盖式子三者中的两者，所以异或起来为$0$。 那么整个$n\\times n$的格子，就会被第$m$行和第$m$列分成四部分，每部分对应的一组格子和其他组是独立的。 如下图 ![](http://www.dtenomde.com/wp-content/uploads/2018/12/186425FD-371E-4295-AE5E-2D685479ADA6.jpg) 四个紫色格子为一组，与其他组直接是独立的。 也就是说，如果我们确定了第$m$行和第$m$列的$a$的值，就可以在每组内贪心取最优解。 但是这样时间复杂度还是太高了。 其实每行每列之间也是独立的，假如我们确定了第$m$列的$a$的值，我们将第$i$列和第$i+m$列分成一大组，一共有$m-1$大组。 每一大组都是独立的。那么我们只需要确定这一大组中第$m$行的$a$的值，就可以贪心取最得整组的最优解。 那么我们尝试一下每组中的$a\[m\]\[i\]$要$=0$还是$=1$，两种情况取最优的就是答案了。 具体参考代码。 时间复杂度$\\Theta(m^22^m)$。

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
#define N 35
#define ll long long
#define db double
#define dbg1(x) cerr<<#x<<"="<<(x)<<" "
#define dbg2(x) cerr<<#x<<"="<<(x)<<"\\n"
int n,m,A\[N\]\[N\],B\[N\]\[N\],ans=-1e9;
int F(int x,int y) {return B\[x\]\[y\]?-A\[x\]\[y\]:A\[x\]\[y\];}
int ask(int x,int y)
{
	int res;
	B\[x\]\[y\]=0,B\[x\]\[y+m\]=B\[x\]\[y\]^B\[x\]\[m\],B\[x+m\]\[y\]=B\[x\]\[y\]^B\[m\]\[y\],B\[x+m\]\[y+m\]=B\[x+m\]\[y\]^B\[x+m\]\[m\];
	res=F(x,y)+F(x,y+m)+F(x+m,y)+F(x+m,y+m);
	B\[x\]\[y\]=1,B\[x\]\[y+m\]=B\[x\]\[y\]^B\[x\]\[m\],B\[x+m\]\[y\]=B\[x\]\[y\]^B\[m\]\[y\],B\[x+m\]\[y+m\]=B\[x+m\]\[y\]^B\[x+m\]\[m\];	
	return max(res,F(x,y)+F(x,y+m)+F(x+m,y)+F(x+m,y+m));
}
int Solve(int S)
{
	int res=0,val1,val2;
	for(int i=1;i<=m;i++) B\[i\]\[m\]=S>>i-1&1;
	for(int i=1;i<m;i++) B\[i+m\]\[m\]=B\[i\]\[m\]^B\[m\]\[m\],res+=F(i,m)+F(i+m,m);
	res+=F(m,m);
	for(int i=1;i<m;i++)
	{
		B\[m\]\[i\]=0,B\[m\]\[i+m\]=B\[m\]\[m\],val1=F(m,i)+F(m,i+m);
		for(int j=1;j<m;j++) val1+=ask(j,i);
		B\[m\]\[i\]=1,B\[m\]\[i+m\]=B\[m\]\[m\]^1,val2=F(m,i)+F(m,i+m);
		for(int j=1;j<m;j++) val2+=ask(j,i);
		res+=max(val1,val2);
	}
	return res;
}
int main()
{
	scanf("%d",&n),m=n+1>>1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++) scanf("%d",&A\[i\]\[j\]);
	for(int i=0;i<1<<m;i++) ans=max(ans,Solve(i));
	printf("%d\\n",ans);
	return 0;
}