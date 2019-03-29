---
title: " DTOJ1343Pty的字符串\t\t"
tags:
  - 后缀自动机
url: 6467.html
id: 6467
categories:
  - DTOJ
  - Solution
date: 2019-02-11 09:40:34
---

我们对Trie树建出广义后缀自动机， 一个点可能有多条相同字符的出边，在建广义SAM的时候要注意。 然后我们拿$S$在广义SAM上匹配。 对于$S$的某个前缀，如果它匹配到了某个点，那么这个点的所有祖先表示的字符串在这个前缀都有出现过。如果结点$x$出现过，那么对答案的贡献就是$(mx\[x\]-ma\[fa\[x\]\])\\cdot |right(x)|$。最靠下的那个点比较特殊，因为此时这个点表示的所有字符串不一定有出现。 我们建出广义SAM后，预处理一下某个点所有祖先的贡献，在匹配的时候就可以快速计算了。 具体细节看代码。

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
#define N 1600005
#define ll long long
#define db double
#define dbg1(x) cerr<<#x<<"="<<(x)<<" "
#define dbg2(x) cerr<<#x<<"="<<(x)<<"\\n"
int n,m,pos\[N\];ll ans;char c,s\[N*5\];
class SuffixAutomaton
{
	int tp\[N\],vis\[N\];
	struct node{int fa,ch\[26\],mx,right;ll v;}t\[N\];
public:
	int root,cntnode;
	int insert(int last,int c)
	{
		int y,x=last,od,nw;
		if(t\[x\].ch\[c\])//!!!
		{
			od=t\[x\].ch\[c\];
			if(t\[od\].mx==t\[x\].mx+1) return t\[od\].right++,od;
			t\[nw=++cntnode\]=t\[od\],t\[nw\].right=1;
			t\[nw\].mx=t\[x\].mx+1,t\[od\].fa=t\[y\].fa=nw;
			for(;t\[x\].ch\[c\]==od;x=t\[x\].fa) t\[x\].ch\[c\]=nw;
			return nw;
		}
		t\[y=++cntnode\].mx=t\[x\].mx+1,t\[y\].right=1;
		for(;x&&!t\[x\].ch\[c\];x=t\[x\].fa) t\[x\].ch\[c\]=y;
		if(!x) return t\[y\].fa=1,y;
		od=t\[x\].ch\[c\];
		if(t\[od\].mx==t\[x\].mx+1) return t\[y\].fa=od,y;
		t\[nw=++cntnode\]=t\[od\],t\[nw\].right=0;
		t\[nw\].mx=t\[x\].mx+1,t\[od\].fa=t\[y\].fa=nw;
		for(;t\[x\].ch\[c\]==od;x=t\[x\].fa) t\[x\].ch\[c\]=nw;
		return y;
	}
	void Prepare()
	{
		for(int i=1;i<=cntnode;i++) tp\[t\[i\].mx\]++;
		for(int i=1;i<=n;i++) tp\[i\]+=tp\[i-1\];
		for(int i=cntnode;i;i--) vis\[tp\[t\[i\].mx\]--\]=i;
		for(int i=cntnode,x;i;i--) x=vis\[i\],t\[t\[x\].fa\].right+=t\[x\].right;
		for(int i=1,x;i<=cntnode;i++) x=vis\[i\],t\[x\].v=t\[t\[x\].fa\].v+(ll)(t\[x\].mx-t\[t\[x\].fa\].mx)*t\[x\].right;
	}
	void Solve()
	{
		for(int i=1,x=1,l=0;i<=m;i++)
		{
			if(t\[x\].ch\[s\[i\]-97\]) x=t\[x\].ch\[s\[i\]-97\],l++;
			else
			{
				for(;x&&!t\[x\].ch\[s\[i\]-97\];x=t\[x\].fa);
				if(x) l=t\[x\].mx+1,x=t\[x\].ch\[s\[i\]-97\];
				else l=0,x=1;
			}
			ans+=t\[t\[x\].fa\].v+(ll)(l-t\[t\[x\].fa\].mx)*t\[x\].right;
		}
	}
}SAM;
int main()
{
	scanf("%d",&n),SAM.root=SAM.cntnode=1,pos\[1\]=1;
	for(int i=2,a;i<=n;i++) scanf("%d %c",&a,&c),pos\[i\]=SAM.insert(pos\[a\],c-97);
	scanf("%s",s+1),m=strlen(s+1),SAM.Prepare(),SAM.Solve();
	printf("%lld\\n",ans);
	return 0;
}