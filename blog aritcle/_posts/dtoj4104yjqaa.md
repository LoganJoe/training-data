---
title: " DTOJ4104yjqaa\t\t"
tags:
  - 思路
  - 数位dp
url: 6254.html
id: 6254
categories:
  - DTOJ
  - Solution
date: 2019-01-27 20:58:00
---

先考虑$f(x,y)$怎么求。 我们看$x$和$y$的二进制位。 我们从低位到高位找到最后一个$x$为$0$且$y$为$1$的位，然后继续往高位找到第一个$x$为$1$且$y$为$0$的位。分别记为第$a$位和第$b$位。 如果不存在$a$，那么$f(x,y)$就等于$x$为$1$且$y$为$0$的位的个数。 否则$f(x,y)$等于$b$位高位的$x$为$1$且$y$为$0$的位的个数加上$b$位更低位$x$为$1$的位数和$y$为$0$的位数再$+1$。 知道了这个后，我们考虑枚举$b$位计算答案。不存在$a$的单独计算。 $b$位将所有位分成了两段，我们两段分开考虑。 考虑数位dp。 记$f\[i\]\[0/1\]$为填完前$i$位（从高到低）的所有没有出现$x$为$0$且$y$为$1$的位的方案中，$x$为$1$且$y$为$0$的位数总和，$0/1$表示当前$x$填的数是否和$N$的前$i$位相同。 为了求出$f\[i\]\[0/1\]$，我们还得记一个$F\[i\]\[0/1\]$表示$f\[i\]\[0/1\]$中对应的方案数。 那么我们枚举接下来的一位$x$和$y$分别要填啥转移即可。 记$g\[i\]\[0/1\]\[0/1\]$为填完第$i$位及后面的所有方案中，$x$为$1$的位数以及$y$为$0$的位数的和。第一个$0/1$表示是否出现过了$x$为$0$且$y$为$1$的位置并且更高位没有$x$为$1$且$y$为$0$的位，第二个$0/1$当前$x$填的数是否$>N$的对应位。 同样地，为了求出$g\[i\]\[0/1\]\[0/1\]$，我们还得记一个$G\[i\]\[0/1\]\[0/1\]$表示$g\[i\]\[0/1\]\[0/1\]$中对应的方案数。 同样枚举接下来的一位$x$和$y$分别要填啥转移即可。 计算答案我们就把两部分合起来即可，在计算$f\[i\]\[0/1\]$时合并较为方便。 不存在$a$的答案就是$f\[m\]\[0\]+f\[m\]\[1\]$，$m$为$N$的二进制位数。 时间复杂度$\\Theta(m)$。 具体细节参考代码。

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
#define N 505
#define mod 1000000007
#define ll long long
#define db double
#define dbg1(x) cerr<<#x<<"="<<(x)<<" "
#define dbg2(x) cerr<<#x<<"="<<(x)<<"\\n"
int n,f\[N\]\[2\],F\[N\]\[2\],g\[N\]\[2\]\[2\],G\[N\]\[2\]\[2\],ans;
char s\[N\];
int cal(int x) {x-=x<mod?0:mod;return x;}
int main()
{
	scanf("%s",s+1),n=strlen(s+1);
	F\[0\]\[1\]=G\[n+1\]\[0\]\[0\]=1;
	for(int i=n+1,S1,S2;i>1;i--)
		for(int j=0;j<2;j++)
			for(int k=0;k<2;k++) if(G\[i\]\[j\]\[k\])
				for(int x=0;x<2;x++)
					for(int y=0;y<2;y++)
					{
						S1=x&&!y?0:j|(!x&&y),S2=k;
						if(x&&s\[i-1\]=='0') S2=1;
						if(!x&&s\[i-1\]=='1') S2=0;
						G\[i-1\]\[S1\]\[S2\]=cal(G\[i-1\]\[S1\]\[S2\]+G\[i\]\[j\]\[k\]);
						g\[i-1\]\[S1\]\[S2\]=cal(g\[i-1\]\[S1\]\[S2\]+g\[i\]\[j\]\[k\]);
						if(x) g\[i-1\]\[S1\]\[S2\]=cal(g\[i-1\]\[S1\]\[S2\]+G\[i\]\[j\]\[k\]);
						if(!y) g\[i-1\]\[S1\]\[S2\]=cal(g\[i-1\]\[S1\]\[S2\]+G\[i\]\[j\]\[k\]);
					}
	for(int i=0,S;i<n;i++)
		for(int j=0;j<2;j++) if(F\[i\]\[j\])
			for(int x=0;x<2;x++)
			{
				if(j&&x&&s\[i+1\]=='0') continue;
				for(int y=0;y<2;y++)
				{
					if(!x&&y) continue;
					S=j&(s\[i+1\]-48==x);
					F\[i+1\]\[S\]=cal(F\[i+1\]\[S\]+F\[i\]\[j\]);
					f\[i+1\]\[S\]=cal(f\[i+1\]\[S\]+f\[i\]\[j\]);
					if(x&&!y)
					{
						f\[i+1\]\[S\]=cal(f\[i+1\]\[S\]+F\[i\]\[j\]);
						if(S)
						{
							ans=cal(ans+(ll)f\[i\]\[j\]*G\[i+2\]\[1\]\[0\]%mod); 
							ans=cal(ans+(ll)F\[i\]\[j\]*g\[i+2\]\[1\]\[0\]%mod);
							ans=cal(ans+(ll)F\[i\]\[j\]*G\[i+2\]\[1\]\[0\]%mod);
						}
						else
						{
							ans=cal(ans+(ll)f\[i\]\[j\]*cal(G\[i+2\]\[1\]\[0\]+G\[i+2\]\[1\]\[1\])%mod);
							ans=cal(ans+(ll)F\[i\]\[j\]*cal(g\[i+2\]\[1\]\[0\]+g\[i+2\]\[1\]\[1\])%mod);
							ans=cal(ans+(ll)F\[i\]\[j\]*cal(G\[i+2\]\[1\]\[0\]+G\[i+2\]\[1\]\[1\])%mod);
						}
					}
				}
			}
	ans=cal(ans+cal(f\[n\]\[0\]+f\[n\]\[1\]));
	printf("%d\\n",ans);
	return 0;
}