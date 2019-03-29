#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define X first
#define Y second

void read(int &x)
{
	char c=getchar();
	int f=1; x=0;
	while ((c<'0'||c>'9')&&c!='-') c=getchar();
	if (c=='-') f=-1,c=getchar();
	while (c>='0'&&c<='9') x=x*10+c-'0',c=getchar();
	x=x*f;
}

void read(LL &x)
{
	char c=getchar();
	int f=1; x=0;
	while ((c<'0'||c>'9')&&c!='-') c=getchar();
	if (c=='-') f=-1,c=getchar();
	while (c>='0'&&c<='9') x=x*10+c-'0',c=getchar();
	x=x*f;
}

const int base=300;
const int maxn=1.5e5+10;
const int maxm=1.5e5+10;

int block(int x) {return (x+base-1)/base;}

struct Point{
	LL x,y;
	double ang;
	int id;
	Point() {}
	Point(LL x,LL y):x(x),y(y) {}
	Point operator + (const Point &p) const {return Point(x+p.x,y+p.y);}
	Point operator - (const Point &p) const {return Point(x-p.x,y-p.y);}
	bool operator < (const Point &p) const {return ang<p.ang;}
}P[maxn];

inline LL Cross(Point A,Point B) {return A.x*B.y-A.y*B.x;}

struct Question{
	int l,r,id;
	bool operator < (const Question &q) const
	{
		if (block(l)==block(q.l))
			return block(r)>block(q.r);
		else
			return block(l)<block(q.l);
	}
}q[maxm];

int n,m,rank[maxn];
LL Ans[maxm];

namespace Chain{
	int last[maxn],next[maxn];
	LL Sum;
	int top;
	pair<int,int> Rlast[maxn],Rnext[maxn];
	LL plus[maxn];
	int tot,pos[maxn+maxm];

	void init()
	{
		int i;
		top=tot=0;
		for (i=n;i>1;i--) last[i]=i-1;
		for (i=1;i<n;i++) next[i]=i+1;
		last[1]=n; next[n]=1;
		for (i=2;i<=n;i++)
			Sum+=Cross(P[i-1],P[i]);
		Sum+=Cross(P[n],P[1]);
	}

	void del(int x)
	{
		plus[++top]=0;
		Rlast[top]=make_pair(next[x],last[next[x]]);
		Rnext[top]=make_pair(last[x],next[last[x]]);
		plus[top]-=Cross(P[last[x]],P[x]);
		plus[top]-=Cross(P[x],P[next[x]]);
		plus[top]+=Cross(P[last[x]],P[next[x]]);
		Sum+=plus[top];
		last[next[x]]=last[x];
		next[last[x]]=next[x];
	}

	int getmark()
	{
		pos[++tot]=top;
		return tot;
	}

	void getback(int p)
	{
		while (top!=pos[p])
		{
			Sum-=plus[top];
			last[Rlast[top].X]=Rlast[top].Y;
			next[Rnext[top].X]=Rnext[top].Y;
			top--;
		}
	}
};

int main()
{
	freopen("convex.in","r",stdin);
	freopen("convex.out","w",stdout);
//	long long ST=clock();
	int i;
	read(n); read(m);
	for (i=1;i<=n;i++)
	{
		read(P[i].x); read(P[i].y);
		P[i].ang=atan2(P[i].y,P[i].x);
		P[i].id=i;
	}
	sort(P+1,P+n+1);
	for (i=1;i<=n;i++) rank[P[i].id]=i;
	for (i=1;i<=m;i++) read(q[i].l),read(q[i].r),q[i].id=i;
	sort(q+1,q+m+1);

//	printf("using time = %lld\n",clock()-ST);
	Chain::init();
	int L=1,R=n;
	int BACK=Chain::getmark();
	for (i=1;i<=m;i++)
	{
//		if (i%10000==0) fprintf(stderr,"i=%d\n",i);
		if (block(L)!=block(q[i].l))
		{
			Chain::getback(BACK);
			R=n;
			while (block(L)!=block(q[i].l))
				Chain::del(rank[L++]);
			BACK=Chain::getmark();
		}
		while (block(R)!=block(q[i].r))
			Chain::del(rank[R--]);
		int back=Chain::getmark();
		while (L!=q[i].l)
			Chain::del(rank[L++]);
		while (R!=q[i].r)
			Chain::del(rank[R--]);
		Ans[q[i].id]=Chain::Sum;
		Chain::getback(back);
		L=(block(L)-1)*base+1;
		R=min(n,block(R)*base);
	}

	for (i=1;i<=m;i++)
		printf("%lld\n",Ans[i]);
//	printf("using time = %lld\n",clock()-ST);
}

