---
title: " JZOJ6008Sequence\t\t"
tags:
  - 奇技淫巧
  - 矩阵
url: 6164.html
id: 6164
categories:
  - Solution
  - 其他OJ
date: 2019-01-24 13:56:27
---

先考虑暴力。对于每次询问，我们把$\[l,r\]$的字符抓出来形成新的串，然后求答案。 具体地，记$f\[i\]$表示前$i$位不同的子序列个数，那么有 $$ f\[i\]=2f\[i-1\]-f\[pre\_i-1\] $$ 其中$pre\_i$为前一个和第$i$位相同的字符的位置。 这样dp有乘有减，好像并不好优化。 我们考虑换一种dp方法。 记$f\[i\]\[j\]$位前$i$位中以第$j$种字符结尾的不同子序列个数（$j\\in\[0,52\]$，其中$0$代表空）。 那么有 $$ f\[i\]\[j\]= \\begin{cases} \\sum_{k=0}^{52}f\[i-1\]\[k\] & j=s\_i\\newline f\[i-1\]\[j\] & j\\neq s\_i \\end{cases} $$ 这样虽然增加了状态数，但是避免了减掉重复的。 容易发现，我们可以把转移写成矩阵的形式。 记 $$ A\_i=\\begin{bmatrix} 1 & 0 & 0 &\\cdots & 1 & \\cdots & 0\\newline 0 & 1 & 0 &\\cdots & 1 & \\cdots & 0\\newline 0 & 0 & 1 &\\cdots & 1 & \\cdots & 0\\newline \\vdots & \\vdots &\\vdots & \\ddots & 1 & \\ddots &\\vdots \\newline 0 & 0 & 0 & \\cdots & 1& \\cdots & 1\\newline \\end{bmatrix} $$ 也就是单位矩阵的第$s\_i$列全部改成$1$。 记 $$ A\_i^{-1}=\\begin{bmatrix} 1 & 0 & 0 &\\cdots & -1 & \\cdots & 0\\newline 0 & 1 & 0 &\\cdots & -1 & \\cdots & 0\\newline 0 & 0 & 1 &\\cdots & -1 & \\cdots & 0\\newline \\vdots & \\vdots &\\vdots & \\ddots & 1 & \\ddots &\\vdots \\newline 0 & 0 & 0 & \\cdots & -1& \\cdots & 1\\newline \\end{bmatrix} $$ 即$A\_i$的逆元。 记$B\_i=A\_1\\times A\_2\\times A\_3\\times …\\times A\_i$，$B\_i^{-1}=A\_i^{-1}\\times A\_{i-1}^{-1}\\times A_{i-2}^{-1}\\times …\\times A\_1^{-1}$。其中$\\times$是矩阵乘，注意矩阵乘法满足结合律不满足交换律。 那么我们的答案就是 $$ \\begin{bmatrix} 1 & 0 & 0 & \\cdots & 0 \\end{bmatrix} \\times B\_{l-1}^{-1}\\times B\_r $$ 这个$1\\times n$的矩阵中所有数的和。 我们观察一下这个矩阵乘。 $\\begin{bmatrix} 1 & 0 & 0 & \\cdots & 0 \\end{bmatrix} \\times B\_{l-1}^{-1}$得到的实际上就是$B_{l-1}^{-1}$的第一行。 拿第一行去$\\times B\_r$，得到的矩阵所有数的和，实际上是$B\_{l-1}^{-1}$第一行第$i$个数乘上$B\_r$第$i$行的和的乘积和。 那么我们只用维护出每个$B\_i^{-1}$的第一行以及每个$B\_i$每行的和。 先考虑求出$B\_i$每行的和。 $B\_i=B\_{i-1}\\times A\_i$，由于$A\_i$这个矩阵的特殊性，我们发现$B\_i$与$B\_{i-1}$相比，只有第$s\_i$列会发现变化。 我们暴力更新一下第$s\_i$列以及每行的和即可。 再考虑求出$B\_i^{-1}$的第一行。 同样地，$B\_i^{-1}=A\_i^{-1}\\times B\_{i-1}^{-1}$，由于$A\_i^{-1}$这个矩阵的特殊性，除了第$s\_i$行，每列都减去了一个数。 我们给每一列打个标记，再暴力去除对第$s_i$行的影响即可。 时间复杂度$\\Theta(53n)$。 具体细节参考代码。

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
#define M 55
#define mod 998244353
#define ll long long
#define db double
#define dbg1(x) cerr<<#x<<"="<<(x)<<" "
#define dbg2(x) cerr<<#x<<"="<<(x)<<"\\n"
int n,m,id\[N\],Sum\[M\],a,b,P,Q,R,ans;
char s\[N\];
int cal(int x) {x-=x<mod?0:mod;return x;}
struct info{int v\[M\];}A\[N\],B\[N\],C\[M\];
int main()
{
	freopen("sequence.in","r",stdin);
	freopen("sequence.out","w",stdout);
	scanf("%s",s+1),n=strlen(s+1);
	scanf("%d%d%d%d%d%d",&m,&a,&b,&P,&Q,&R);
	for(int i=1;i<=n;i++) id\[i\]=s\[i\]<='Z'?s\[i\]-'A'+1:s\[i\]-'a'+27;
	for(int i=0;i<53;i++) A\[0\].v\[i\]=C\[i\].v\[i\]=1;
	for(int i=1,v;i<=n;i++)
	{
		for(int j=0;j<53;j++)
			v=C\[j\].v\[id\[i\]\],C\[j\].v\[id\[i\]\]=A\[i-1\].v\[j\],A\[i\].v\[j\]=cal(2*A\[i-1\].v\[j\]%mod-v+mod);
	}
	for(int i=0;i<53;i++)
	{
		for(int j=0;j<53;j++) C\[i\].v\[j\]=0;
		C\[i\].v\[i\]=1;
	}
	B\[0\].v\[0\]=1;
	for(int i=1,v;i<=n;i++)
		for(int j=0;j<53;j++)
		{
			v=C\[id\[i\]\].v\[j\],B\[i\].v\[j\]=cal(B\[i-1\].v\[j\]+Sum\[j\]),B\[i\].v\[j\]=cal(B\[i\].v\[j\]-v+mod);
			C\[id\[i\]\].v\[j\]=cal(C\[id\[i\]\].v\[j\]+v),C\[id\[i\]\].v\[j\]=cal(C\[id\[i\]\].v\[j\]-Sum\[j\]+mod),Sum\[j\]=v;
		}
	for(int l,r,ta,tb;m--;)
	{
		ta=((ll)P\*a+(ll)Q\*b+ans+R)%mod;
		tb=((ll)P\*b+(ll)Q\*a+ans+R)%mod;
		a=ta,b=tb,l=a%n+1,r=b%n+1,ans=0;
		if(l>r) std::swap(l,r);
		for(int i=0;i<53;i++) ans=cal(ans+(ll)B\[l-1\].v\[i\]*A\[r\].v\[i\]%mod);
	}
	printf("%d\\n",ans);
	return 0;
}