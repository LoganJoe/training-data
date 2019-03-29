---
title: " BZOJ3513[MUTC2013]idiots\t\t"
tags:
  - FFT
url: 6463.html
id: 6463
categories:
  - BZOJ
  - Solution
date: 2019-02-09 16:05:33
---

显然我们只要求出能拼成三角形的方案数就可以求出概率了。 假如我们选的木棒分别为$a\_i,a\_j,a\_k$，不妨认为$a\_k$是最大的。 那么要满足$a\_i+a\_j>a\_k$才能拼成三角形。 这样的方案数并不好统计。 考虑反过来，求不能拼成三角形的方案数。 也就是要满足$a\_i+a\_j\\leq a\_k$，且$a\_k\\geq \\max(a\_i,a\_j)$的方案数。 发现如果满足$a\_i+a\_j\\leq a\_k$，因为$a\_i,a\_j>0$，那么一定有$a\_k>\\max(a\_i,a\_j)$。 那么我们只用统计出使得$a\_i+a\_j\\leq a\_k$的无序三元组$(i,j,k)$的个数了。 搞出$a\_i$的权值生成函数，即$x^i$前的系数是$i$的出现次数。 然后和自己乘一下，我们就能得知$a\_i+a\_j=x$的方案数。 这样求出的是有序方案，我们先把不合法的方案（选了重复的数）去掉，再$\\div 2$就能得到无序方案的个数。 然后枚举$a\_k$即可。 具体细节参考代码。 记$M=\\max_{i=1}^{N}a_i$。时间复杂度$\\Theta(M\\log M)$。

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
#define M 270000
#define ll long long
#define db double
#define dbg1(x) cerr<<#x<<"="<<(x)<<" "
#define dbg2(x) cerr<<#x<<"="<<(x)<<"\\n"
const db pi=acos(-1);
int T,n,A\[N\],Max,cnt\[N\];ll val,Sum;db ans;
struct Complex
{
	db r,i;Complex(){};Complex(db \_r,db \_i) {r=\_r,i=\_i;}
	friend Complex operator+(Complex t1,Complex t2) {return Complex{t1.r+t2.r,t1.i+t2.i};}
	friend Complex operator-(Complex t1,Complex t2) {return Complex{t1.r-t2.r,t1.i-t2.i};}
	friend Complex operator*(Complex t1,Complex t2) {return Complex{t1.r\*t2.r-t1.i\*t2.i,t1.i\*t2.r+t1.r\*t2.i};}
}B\[M\];
class FFT
{
	int Rank\[M\];
	void dft(Complex *x,int f)
	{
		Complex w,wn,tmp;
		for(int i=0;i<len;i++) if(i<Rank\[i\]) std::swap(x\[i\],x\[Rank\[i\]\]);
		for(int i=1;i<len;i<<=1)
		{
			wn=Complex{cos(pi/i),f*sin(pi/i)};
			for(int j=0;j<len;j+=i<<1)
			{
				w=Complex{1,0};
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
	void multiply(int n,Complex *x)
	{
		Prepare(n<<1),dft(x,1);
		for(int i=0;i<len;i++) x\[i\]=x\[i\]*x\[i\];
		dft(x,-1);
	}
}fft;
void clear()
{
	for(int i=1;i<=n;i++) cnt\[A\[i\]\]--;
	for(int i=0;i<fft.len;i++) B\[i\]=Complex{0,0};
	ans=Sum=Max=0;
}
int main()
{
	for(scanf("%d",&T);T--;clear())
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++) scanf("%d",&A\[i\]),cnt\[A\[i\]\]++,B\[A\[i\]\].r++,Max=max(Max,A\[i\]);
		fft.multiply(Max,B);
		for(int i=1;i<=Max;i++)
		{
			val=(ll)(B\[i\].r+.5);
			if(!val) continue;
			if(~i&1) val-=cnt\[i>>1\];
			val>>=1,Sum+=val;
			ans+=1.\*cnt\[i\]\*Sum;
		}
		ans=6*ans/n/(n-1)/(n-2);
		printf("%.7lf\\n",1-ans);
	}
	return 0;
}