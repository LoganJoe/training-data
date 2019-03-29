---
title: " BZOJ2817波浪\t\t"
tags:
  - dp
  - 奇技淫巧
url: 6832.html
id: 6832
categories:
  - BZOJ
  - Solution
date: 2019-03-04 22:54:59
---

考虑用合法方案数去除总方案数，就可以得到概率。 考虑波动强度拆成一段一段算，即对于每个形如$\[x,x+1\]$的区间计算有多少个$|P\_i-P\_{i-1}|$包含了$\[x,x+1\]$。 由于涉及到大小关系，我们考虑从小到大往序列里塞数。 考虑dp。 记$f\[i\]\[j\]\[k\]\[0/1/2\]​$前$i​$个数（$1\\sim i​$）在序列中形成了$k+1​$段，当前的波动强度为$j​$，开头/结尾的数已经有$0/1/2​$个定下来的方案数。 无论$i+1​$放在哪，序列中的$2k​$个位于段边缘的数，和相邻的数的差一定会包含$\[i,i+1\]​$，也就是这一段一定会被计算$2k$次，如果开头/结尾还有$x​$个没确定，那么还会再多算$x​$次。 因此$f\[i\]\[j\]\[k\]\[0/1/2\]$一定是转移到$f\[i+1\]\[j+2k+x\]\[k'\]\[0/1/2\]$。 考虑$k'​$和$k​$的关系。 $k'=k$，那么$i+1$一定是放在段边缘，有$2k+x$种方法。 $k'=k-1$，那么$i+1$一定是在两段的中间（合并了两段），有$k$种方法。 $k'=k+1$，那么$i+1$一定是自己形成新的一段，有$k+x$种方法。 再考虑$i+1$放的位置是不是开头，转移到不同的$k'$和$0/1/2$的状态。 时间复杂度$\\Theta(N^4)$。具体细节参考代码。 保留小数我们手动写个输出即可。 精度不够我们可以用黑科技__float128，但好像空间大速度慢，可能要根据$K$的大小决定用哪种。

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
#define N 105
#define M 5005
#define ll long long
#define db double
#define DB __float128
#define dbg1(x) cerr<<#x<<"="<<(x)<<" "
#define dbg2(x) cerr<<#x<<"="<<(x)<<"\\n"
int n,m,K;
namespace Solve1
{
	int Max;db f\[2\]\[M\]\[N\]\[3\],val,ans;
	void Print()
	{
		printf("0.");
		for(;K--;)
		{
			ans=(ans-(int)ans)*10;if(!K) ans+=.5;
			printf("%d",(int)ans);
		}
	}
	void Main()
	{
		f\[1\]\[0\]\[0\]\[0\]=f\[1\]\[0\]\[0\]\[2\]=1,f\[1\]\[0\]\[0\]\[1\]=2;
		for(int i=1,nj;i<n;i++)
			for(int j=Max;~j;j--)
				for(int k=0;k<i;k++)
					for(int l=0;l<3;l++)
					{
						val=f\[i&1\]\[j\]\[k\]\[l\]/i,f\[i&1\]\[j\]\[k\]\[l\]=0,nj=j+2*k+2-l,Max=max(Max,nj);
						f\[~i&1\]\[nj\]\[k+1\]\[l\]+=val*(k+2-l);
						f\[~i&1\]\[nj\]\[k\]\[l\]+=val*(2*k+2-l);
						if(k) f\[~i&1\]\[nj\]\[k-1\]\[l\]+=val*k;
						if(!l) f\[~i&1\]\[nj\]\[k+1\]\[1\]+=val\*2,f\[~i&1\]\[nj\]\[k\]\[1\]+=val\*2;
						if(l==1)  f\[~i&1\]\[nj\]\[k+1\]\[2\]+=val,f\[~i&1\]\[nj\]\[k\]\[2\]+=val;
					}
		for(int i=m;i<=Max;i++) ans+=f\[n&1\]\[i\]\[0\]\[2\]/n;
		Print();
	}
}
namespace Solve2
{
	int Max;DB f\[2\]\[M\]\[N\]\[3\],val,ans;
	void Print()
	{
		printf("0.");
		for(;K--;)
		{
			ans=(ans-(int)ans)*10;if(!K) ans+=.5;
			printf("%d",(int)ans);
		}
	}
	void Main()
	{
		f\[1\]\[0\]\[0\]\[0\]=f\[1\]\[0\]\[0\]\[2\]=1,f\[1\]\[0\]\[0\]\[1\]=2;
		for(int i=1,nj;i<n;i++)
			for(int j=Max;~j;j--)
				for(int k=0;k<i;k++)
					for(int l=0;l<3;l++)
					{
						val=f\[i&1\]\[j\]\[k\]\[l\]/i,f\[i&1\]\[j\]\[k\]\[l\]=0,nj=j+2*k+2-l,Max=max(Max,nj);
						f\[~i&1\]\[nj\]\[k+1\]\[l\]+=val*(k+2-l);
						f\[~i&1\]\[nj\]\[k\]\[l\]+=val*(2*k+2-l);
						if(k) f\[~i&1\]\[nj\]\[k-1\]\[l\]+=val*k;
						if(!l) f\[~i&1\]\[nj\]\[k+1\]\[1\]+=val\*2,f\[~i&1\]\[nj\]\[k\]\[1\]+=val\*2;
						if(l==1)  f\[~i&1\]\[nj\]\[k+1\]\[2\]+=val,f\[~i&1\]\[nj\]\[k\]\[2\]+=val;
					}
		for(int i=m;i<=Max;i++) ans+=f\[n&1\]\[i\]\[0\]\[2\]/n;
		Print();
	}
}
int main() {scanf("%d%d%d",&n,&m,&K);return K<9?Solve1::Main():Solve2::Main(),0;}