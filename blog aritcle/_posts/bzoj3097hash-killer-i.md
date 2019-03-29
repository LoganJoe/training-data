---
title: " BZOJ3097Hash Killer I\t\t"
tags:
  - 奇技淫巧
  - 构造
url: 7111.html
id: 7111
categories:
  - BZOJ
  - Solution
date: 2019-03-24 15:51:35
---

隐约记得hash killer可以用生日攻击过，连交好几发过不去，才发现能过的那题是Hash Killer II…… 题意要求我们构造出一个串，使得这个串有两个长度为$l$的不同子串满足hash值相同。 题目给出的hash方法，是任选$base$然后自然溢出，也就是对$2^{64}$取模。 如果$base$是偶数的话，$base$的若干次方一定是$2^{64}$的倍数，因此某些字符的信息就丢失了。比如说，形如`baaa…aaaa`和`aaaa…aaaa`的两个串，在长度相同，且长度大于$64$的情况下，第一个串中\`b\`的信息就会丢失，算出来两个串的hash值就是一样的了。 如果$base$是奇数的话，那就很麻烦了。（这也体现了出题人的神仙） 我们仍然仅考虑\`a\`和\`b\`两个字符。 设函数$not(S)$表示把字符串$S$中每个位置的\`a\`变成\`b\`，把\`b\`变成\`a\`后形成的字符串。比如not(\`ababaa\`) =\`bababb\`。 strA.strB代表示将字符串strB接在strA后面。比如\`ab\`.\`bba\`=\`abbba\`。 构造若干字符串，$s\_1=$\`a\`，$s\_i=s_{i-1}.\\mathrm{not}(s_{i-1})$。显然$s\_i$的长度为$2^{i-1}$。 记$\\mathrm{hash}(str)$为字符串$str$的hash值（没有取模的情况下）。 那么有 $$\\mathrm {hash}(s\_i) =\\mathrm {hash}(s_{i-1})\\times base ^{2^{i-2}} + \\mathrm {hash}(\\mathrm{not}(s_{i-1}))$$ $$\\mathrm {hash}(\\mathrm {not}(s\_i)) = \\mathrm {hash}(\\mathrm{not}(s\_{i-1})) \\times base ^ {2 ^ {i - 2}} + \\mathrm {hash}(s_{i-1})$$ 两式相减，得到 $$ \\begin{aligned} \\mathrm {hash}(s\_i) -\\mathrm {hash}(\\mathrm {not}(s\_i))&=\\mathrm {hash}(s_{i-1})\\times base ^{2^{i-2}} + \\mathrm {hash}(\\mathrm{not}(s_{i-1}))-\\mathrm {hash}(\\mathrm{not}(s_{i-1})) \\times base ^ {2 ^ {i - 2}} - \\mathrm {hash}(s_{i-1})\\newline &=\[\\mathrm {hash}(s_{i-1})-\\mathrm {hash}(\\mathrm{not}(s_{i-1}))\](base ^ {2 ^ {i - 2}}-1) \\end{aligned} $$ 似乎$\\mathrm {hash}(s\_i) -\\mathrm {hash}(\\mathrm {not}(s\_i))$很有趣。 我们的目的是找到两个字符串$str1,str2$，使得$\\mathrm {hash}(str1)\\equiv \\mathrm {hash}(str2) \\pmod {2^{64}}$。 也就是说，要使得$\\mathrm {hash}(str1) -\\mathrm {hash}(str2)$是$2^{64}$的倍数。 记$f\_i=\\mathrm {hash}(s\_i) -\\mathrm {hash}(\\mathrm {not}(s\_i))$，同时记$g\_i=base^{2^{i-1}}-1$，那么我们得到 $$f\_i=f\_{i-1}\\times g_{i-1}$$ 那么也就有$f\_i=f\_1\\prod\\limits_{j=1}^{i-1}g\_j$。 由于$base$是奇数，那么$g\_i$一定是偶数，那么$2^{i-1}|f\_i$。 那是不是就结束了呢？ 发现当$i=65$时，$s\_i$的长度为$2^{64}$，这是根本不可能做到的…… 重新分析一下。 当$i>1$时，$g\_i=base^{2^{i-1}}-1=(base^{2^{i-2}}+1)(base^{2^{i-2}}-1)=g\[i-1\]\\times (base^{2^{i-2}}+1)$。 而$base^{2^{i-2}}+1$也是一个偶数。也就是说$2^i | g\_i$。 所以其实有$2^{\\frac{i(i-1)}{2}}| f\_i$。 $i\\geq 12$就够了！ 那么，将$s\_{12}$和$\\mathrm{not} s_{12}$接一起即可，也就是$s_{13}$。 由于$base$可能为奇也可能为偶，我们在奇数的构造方式最后再加$64$个\`a\`即可。

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
#define ll long long
#define db double
#define dbg1(x) cerr<<#x<<"="<<(x)<<" "
#define dbg2(x) cerr<<#x<<"="<<(x)<<"\\n"
int n;
char s\[N\];
int main()
{
	s\[1\]='a';
	for(int i=0;i<=11;i++)
		for(int j=1;j<=1<<i;j++)
			s\[j+(1<<i)\]=s\[j\]^'a'?'a':'b';
	n=1<<12;
	for(int i=1;i<=65;i++) s\[++n\]='a';
	printf("%d %d\\n",n,1<<11);
	for(int i=1;i<=n;i++) putchar(s\[i\]);
	return 0;
}