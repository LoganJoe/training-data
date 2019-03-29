---
title: " DTOJ3896Nim z utrudnieniem\t\t"
tags:
  - dp
  - 奇技淫巧
url: 4347.html
id: 4347
categories:
  - DTOJ
  - Solution
date: 2018-10-22 19:10:15
---

显然玩的游戏就是Nim游戏，Nim游戏当所有石子堆的异或和不为$0$时先手必胜。 因此我们要求的就是有多少种方式使得剩下石子堆的异或和为$0$。 注意到$d\\leq 10,m\\leq 10^7$。 考虑dp。 记$f\[i\]\[j\]\[k\]$为前$i$堆石子，取的堆数$\\%d=j$，取的石子堆的异或和为$k$的方案数。 乍一看好像就凉凉了。 直接转移的复杂度是$\\Theta(nda_{max})$的。 但是我们可以按$a\_i$从小到大排序然后再dp。每次转移的时候控制一下$k$的范围。 那么这样的时间复杂度就是$\\Theta(md)$的。 然后你就会觉得开个滚动数组就可以卡过空间过掉此题了。 但是，这题卡滚动数组的空间…… 我们注意到如果$f\[i\]\[j\]\[k\]$可以转移到$f\[i\]\[j\]\[k\\oplus a\_i\]$，那么$f\[i\]\[j\]\[k\\oplus a_i\]$也可以转移到$f\[i\]\[j\]\[k\]$。其中，$\\oplus$表示异或。 那么我们可以同时处理这两种转移，就可以省去滚动数组，具体实现可参考代码。 注意$f\[i\]\[0\]\[k\]$要特殊处理。 那么答案就是$f\[n\]\[0\]\[Xor\]$，其中$Xor$是所有石子堆的异或和。 注意如果$n\\%d=0$，答案应该再减去$1$，因为会把全部取走的方案算进去，但这实际上是不合法的。

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
#define N 525005
#define mod 1000000007 
#define ll long long
#define db double
#define dbg1(x) cerr<<#x<<"="<<(x)<<" "
#define dbg2(x) cerr<<#x<<"="<<(x)<<"\\n"
#define dbg(x) cerr<<\_\_FUNCTION\_\_<<"() L"<<\_\_LINE\_\_<<" "<<#x"="<<(x)<<"\\n"
int n,m,A\[N\],Xor,f\[10\]\[N<<1\],g\[N<<1\],Max=1;
int cal(int x) {x-=x<mod?0:mod;return x;}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&A\[i\]),Xor^=A\[i\];
	std::sort(A+1,A+1+n),f\[0\]\[0\]=1;
	for(int i=1,tmp;i<=n;i++)
	{
		for(;Max<=A\[i\];Max<<=1);
		for(int j=0;j<Max;j++) g\[j\]=cal(f\[0\]\[j\]+f\[m-1\]\[j^A\[i\]\]);
		for(int j=m-1;j;j--)
			for(int k=0;k<Max;k++)
				if(k<=(k^A\[i\]))
					f\[j\]\[k\]=cal(f\[j\]\[k\]+f\[j-1\]\[k^A\[i\]\]),f\[j\]\[k^A\[i\]\]=cal(f\[j\]\[k^A\[i\]\]+f\[j-1\]\[k\]);
		for(int j=0;j<Max;j++) f\[0\]\[j\]=g\[j\];
	}
	printf("%d\\n",n%m?f\[0\]\[Xor\]:cal(f\[0\]\[Xor\]+mod-1));
	return 0;
}