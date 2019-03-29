#include <cstdio>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <assert.h>
using namespace std;
typedef long long LL;
template<class T> inline bool ten(T &x,const T &y){return y<x?x=y,1:0;}
template<class T> inline bool rel(T &x,const T &y){return x<y?x=y,1:0;}
const int inf=1010000000;
const LL infLL=(1LL<<60)-1;
const int maxn=2100005,Alpha=3;
const char Sigma[]="rsp";
int n;
char S[maxn];
LL coef[maxn][3];

namespace ST
{

struct node
{
	node *nex[Alpha];
	node *lnk,*par;
	int l,r;
	
	node(){}
	node(const int &ll,const int &rr):l(ll),r(rr)
	{
		memset(nex,0,sizeof(nex));
		lnk=par=0;
	}
	
}*root,*null,*cur;

int pos;
char *s;

void init()
{
	root=new node(0, 0);
	null=new node(0, 0);
	for(int i=0;i<Alpha;i++)
		null->nex[i]=root;
	root->lnk=root->par=null->lnk=null->par=null;
	cur=root;
	pos=0;
}

void goDown(int l,int r)
{
	if(l>=r)return;
	if (pos == cur->r)
	{
		int c=s[l];
		//assert(cur->to[c]);
		cur=cur->nex[c];
		pos=min(cur->r,cur->l+1);
		l++;
	}
	else
	{
		int length=min(r-l,cur->r-pos);
		l+=length;
		pos+=length;
	}
	goDown(l,r);
}

void goUp() {
	if(pos==cur->r&&cur->lnk)
	{
		cur=cur->lnk;
		pos=cur->r;
		return;
	}
	int l=cur->l,r=pos;
	cur=cur->par->lnk;
	pos=cur->r;
	goDown(l,r);
}

void setParent(node *a,node *b)
{
	a->par=b;
	if(b)
		b->nex[s[a->l]]=a;
}

void addLeaf(int id)
{
	node *x=new node(id,maxn);
	setParent(x,cur);
}

void splitNode()
{
	//assert(pos != cur->r);
	node *mid=new node(cur->l,pos); 
	setParent(mid,cur->par);
	cur->l=pos;
	setParent(cur,mid);
	cur=mid;
}

bool canGo(int c)
{
	if(pos==cur->r)
		return cur->nex[c];
	return s[pos]==c;
}

void fixLink(node *&bad,node *newBad)
{
	if(bad)
		bad->lnk=cur;
	bad=newBad;
}

void addChar(int id)
{
	node *bad = 0;
	while(!canGo(s[id]))
	{
		if(cur->r!=pos)
		{
			splitNode();
			fixLink(bad,cur);
			bad=cur;
		}
		else
		{
			fixLink(bad,0);
		}
		addLeaf(id);
		goUp();
	}
	fixLink(bad,0);
	goDown(id,id+1);
}

int cnt(node *u,int ml)
{
	if(!u)
		return 0;
	int res=min(ml,u->r)-u->l;
	for(int i=0;i<Alpha;i++)
		res+=cnt(u->nex[i],ml);
	return res;
}

void build(char *strptr,int l)
{
	s=strptr;
	init();
	for(int i=0;i<l;i++)
		addChar(i);
}

}

LL dp(ST::node *x,int dep=0,int now=0)
{
	if(!x)return infLL;
	dep+=x->r-x->l;
	dep=min(dep,n);
	LL res=coef[now][1]-coef[dep][1];
	now=dep;
	if(dep>=n)return res;
	LL subscore[Alpha];
	for(int i=0;i<Alpha;i++)
		subscore[i]=dp(x->nex[i],dep,now+1);
	LL best=0;
	for(int sh=0;sh<Alpha;sh++)
	{
		LL minscore=infLL;
		for(int i=0;i<Alpha;i++)
		{
			LL score=coef[dep][(i+sh)%3]-coef[dep+1][(i+sh)%3];
			score+=subscore[i];
			minscore=min(minscore,score);
		}
		best=max(best,minscore);
	}
	res+=best;
	ten(res,infLL);
	return res;
}

int main()
{
	scanf("%d",&n);
	scanf("%s",S);
	for(int i=0;i<n;i++)
		scanf("%lld%lld",&coef[i][1],&coef[i][0]);
	for (int i=n;i>=0;i--)
		for(int j=0;j<Alpha;j++)
			coef[i][j]+=coef[i+1][j];
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<Alpha;j++)
			if(S[i]==Sigma[j])
			{
				S[i]=j;
				break;
			}
		S[i+n]=S[i];
	}
	S[n+n]=0;
	ST::build(S,n+n);
	cout<<dp(ST::root)<<endl;
	return 0;
}