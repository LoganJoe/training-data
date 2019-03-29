#include<bits/stdc++.h>
#define N 500005
#define ll long long
int n,m,A[N];
ll d,b,lstd;
class Segment_Tree
{
#define lc x<<1
#define rc x<<1|1
#define mid ((l+r)>>1)
	struct tree
	{
		ll v,sum,tag,cov,max,tmx;
	}t[N<<2];
	void pushup(int x)
	{
		t[x].v=t[lc].v+t[rc].v;
		t[x].max=std::max(t[lc].max,t[rc].max);
	}
	void add(int x,ll v)
	{
		t[x].v+=v*t[x].sum;
		t[x].max+=v*t[x].tmx;
		t[x].tag+=v;
	}
	void cover(int x,ll v,int l,int r)
	{
		t[x].tag=0;
		t[x].cov=t[x].max=v;
		t[x].v=1ll*(r-l+1)*v;
	}
	void pushdown(int x,int l,int r)
	{
		if(!lc && !rc) return ;
		if(t[x].cov!=-1)
		{
			cover(lc,t[x].cov,l,mid);
			cover(rc,t[x].cov,mid+1,r);
			t[x].cov=-1;
		}
		if(t[x].tag)
		{
			add(lc,t[x].tag),add(rc,t[x].tag);
			t[x].tag=0;
		}
	}
public:
	void build(int x,int l,int r)
	{
		t[x].cov=-1;
		if(l==r) return (void)(t[x].sum=t[x].tmx=A[l]);
		build(lc,l,mid),build(rc,mid+1,r);
		pushup(x);
		t[x].sum=t[lc].sum+t[rc].sum;
		t[x].tmx=std::max(t[lc].tmx,t[rc].tmx);
	}
	int find(int x,int l,int r,int ql,int qr,ll v)
	{
		if(t[x].max<v) return 0;
		if(l==r) return l;
		pushdown(x,l,r);
		int res=0;
		if(qr>mid) res=find(rc,mid+1,r,ql,qr,v);
		if(ql<=mid && !res) res=find(lc,l,mid,ql,qr,v);
		return res;
	}
	ll query(int x,int l,int r,int ql,int qr)
	{
		if(ql<=l && r<=qr) return t[x].v;
		pushdown(x,l,r);ll res=0;
		if(ql<=mid) res+=query(lc,l,mid,ql,qr);
		if(qr>mid) res+=query(rc,mid+1,r,ql,qr);
		return res;
	}
	void modify(int x,int l,int r,int ql,int qr,ll v)
	{
		if(ql<=l && r<=qr) return cover(x,v,l,r);
		pushdown(x,l,r);
		if(ql<=mid) modify(lc,l,mid,ql,qr,v);
		if(qr>mid) modify(rc,mid+1,r,ql,qr,v);
		pushup(x);
	}
	void change(int x,int l,int r,int ql,int qr,ll v)
	{
		if(ql<=l && r<=qr) return add(x,v);
		pushdown(x,l,r);
		if(ql<=mid) change(lc,l,mid,ql,qr,v);
		if(qr>mid) change(rc,mid+1,r,ql,qr,v);
		pushup(x);
	}
#undef mid
}T;
bool cmp(int t1,int t2){return t1>t2;}
int main()
{
	freopen("A.in","r",stdin);
	freopen("A.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&A[i]);
	std::sort(A+1,A+1+n,cmp);
	T.build(1,1,n);
	while(m--)
	{
		scanf("%lld%lld",&d,&b);
		ll delt=d-lstd;
		//T.debug(1,1,n);
		T.change(1,1,n,1,n,delt);
		int pos=T.find(1,1,n,1,n,b);
		ll ans=pos?(T.query(1,1,n,1,pos)-1ll*pos*b):0;
		if(pos) T.modify(1,1,n,1,pos,b);
		lstd=d;
		printf("%lld\n",ans);
	}
}
