---
title: " BZOJ3509[CodeChef]COUNTARI\t\t"
tags:
  - FFT
  - 分块
url: 6458.html
id: 6458
categories:
  - BZOJ
  - Solution
date: 2019-02-09 15:52:30
---

记$M=\\max_{i=1}^n{a_i}$。 移项可以得到$2A\[j\]=A\[i\]+A\[k\]$。 如果没有$i,j,k$大小关系的限制，那么直接搞出个权值生成函数乘一下，即$x^i$前的系数是$i$出现的次数。 有限制后，我们可以枚举$j​$，然后$j​$左边的生成函数和$j​$右边的生成函数乘起来，取$x^{2A\[j\]}​$前的系数加起来即可。 但这样是$\\Theta(NM\\log M)$的，甚至比暴力还差。 解决方法是分块。设块的大小为$B​$。 对于每一块，我们把这块左边的生成函数和这块右边的生成函数乘起来，然后枚举$j$是这块中的哪个数，把对应的方案数加起来。 乘一次是$\\Theta(M\\log M)​$的，总共有$\\frac N B​$块，时间复杂度$\\Theta(\\frac{N}{B}M\\log M)​$。 这样就只剩下$i,k$至少一个也在当前块里的没有被考虑到。由于有至少两个在当前块的，我们可以枚举在当前块的两个，剩下一个直接拿数组记下有多少种可能即可。具体细节参考代码。 暴力计算一次是$\\Theta(B^2)​$的，总共有$\\frac{N}{B}​$块，时间复杂度$\\Theta(NB)​$。 那么这样总时间复杂度是$\\Theta(\\frac{N}{B}M\\log M+NB)​$。 当$\\frac{N}{B}M\\log M=NB$时取得最小值，也就是$B=\\sqrt{M\\log M}$时。这样时间复杂度为$\\Theta(\\sqrt{M\\log M}N)$。 但是由于FFT的常数实在大，我们应该适当让FFT部分的理论复杂度小点。 经过实测，当$B=20\\sqrt{M\\log M}$跑得还是比较快的。

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
#define N 100005
#define M 66005
#define ll long long
#define db double
#define dbg1(x) cerr<<#x<<"="<<(x)<<" "
#define dbg2(x) cerr<<#x<<"="<<(x)<<"\\n"
const db pi=acos(-1);
int n,A\[N\],Max,block,cnt\[M\];ll ans;
struct Complex
{
	db r,i;
	friend Complex operator+(Complex t1,Complex t2) {return {t1.r+t2.r,t1.i+t2.i};}
	friend Complex operator-(Complex t1,Complex t2) {return {t1.r-t2.r,t1.i-t2.i};}
	friend Complex operator*(Complex t1,Complex t2) {return {t1.r\*t2.r-t1.i\*t2.i,t1.r\*t2.i+t2.r\*t1.i};}
}F\[M\],G\[M\];
class FFT
{
	int Rank\[M\];
	void dft(Complex *x,int f)
	{
		Complex w,wn,tmp;
		for(int i=0;i<len;i++) if(i<Rank\[i\]) std::swap(x\[i\],x\[Rank\[i\]\]);
		for(int i=1;i<len;i<<=1)
		{
			wn={cos(pi/i),f*sin(pi/i)};
			for(int j=0;j<len;j+=i<<1)
			{
				w={1,0};
				for(int k=0;k<i;w=w*wn,k++)
					tmp=x\[i+j+k\]*w,x\[i+j+k\]=x\[j+k\]-tmp,x\[j+k\]=x\[j+k\]+tmp;
			}
		}
		if(f<0) for(int i=0;i<len;i++) x\[i\].r/=len;
	}
public:
	int len,l;
	void Prepare(int n)
	{
		for(len=1,l=0;len<=n;len<<=1,l++);
		for(int i=0;i<len;i++) Rank\[i\]=(Rank\[i>>1\]>>1)|((i&1)<<l-1);
	}
	void multiply(int n,Complex \*x,int m,Complex \*y)
	{
		Prepare(n+m),dft(x,1),dft(y,1);
		for(int i=0;i<len;i++) x\[i\]=x\[i\]*y\[i\];
		dft(x,-1);
	}
}fft;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&A\[i\]),Max=max(Max,A\[i\]);
	block=sqrt(Max)*20;
	for(int i=1,j,Max1,Max2;i<=n;i+=block)
	{
		j=min(n,i+block-1);
		if(i>1&&j<n)
		{
			Max1=Max2=0;
			for(int k=1;k<i;k++) F\[A\[k\]\].r++,Max1=max(Max1,A\[k\]);
			for(int k=j+1;k<=n;k++) G\[A\[k\]\].r++,Max2=max(Max2,A\[k\]);
			fft.multiply(Max1,F,Max2,G);
			for(int k=i;k<=j;k++) ans+=(ll)(F\[A\[k\]<<1\].r+.5);
			for(int k=0;k<fft.len;k++) F\[k\]=G\[k\]={0,0};
		}
		for(int k=1;k<i;k++) cnt\[A\[k\]\]++;
		for(int k=i;k<=j;k++)
		{
			for(int l=k+1;l<=j;l++) if(A\[l\]<=A\[k\]<<1) ans+=cnt\[A\[k\]*2-A\[l\]\];
			cnt\[A\[k\]\]++;
		}
		for(int k=1;k<=j;k++) cnt\[A\[k\]\]--;
		for(int k=j+1;k<=n;k++) cnt\[A\[k\]\]++;
		for(int k=j;k>=i;k--)
			for(int l=k-1;l>=i;l--) if(A\[l\]<=A\[k\]<<1) ans+=cnt\[A\[k\]*2-A\[l\]\];
		for(int k=j+1;k<=n;k++) cnt\[A\[k\]\]--;
	}
	printf("%lld\\n",ans);
	return 0;
}