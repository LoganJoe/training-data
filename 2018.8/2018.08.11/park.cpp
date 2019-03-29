#include<bits/stdc++.h>
#define N 100005
#define M 998244353

int n,m,a[N];
std::vector <int> e[N];

int deep[N],fa[N],pos[N],top[N],son[N],Size[N],tim,Rnk[N];
void dfs1(int u,int fath)
{
	Size[u]=1;
	for(auto v:e[u])
	{
		if(v==fath) continue;
		deep[v]=deep[u]+1,fa[v]=u;
		dfs1(v,u),Size[u]+=Size[v];
		if(!son[u] || Size[son[u]]<Size[v]) son[u]=v;
	}
}
void dfs2(int u,int Top)
{
	pos[u]=++tim,top[u]=Top;Rnk[tim]=u;
	if(son[u]) dfs2(son[u],Top);
	for(auto v:e[u]) if(v!=fa[u] && v!=son[u]) dfs2(v,v);
}

struct data
{
	int v,maxl,maxr,max,len;
	friend data operator +(data a,data b)
	{
		data res={a.v+b.v,0,0,0,a.len+b.len};
		res.maxl=std::max(res.maxl,std::max(a.maxl,a.v+b.maxl));
		res.maxr=std::max(res.maxr,std::max(b.maxr,b.v+a.maxr));
		res.max=std::max(res.max,std::max(a.max,b.max));
		res.max=std::max(res.max,a.maxr+b.maxl);
		return res;
	}
	void operator =(int x){v=len*x,maxl=maxr=max=std::max(0,x)*len;}
}t1[N],t2[N],s;
class Segment_Tree
{
#define lc x<<1
#define rc x<<1|1
#define mid ((l+r)>>1)
	data t[N<<2];int tag[N<<2];
	void pushup(int x){t[x]=t[lc]+t[rc];}
	void update(int x,int val){t[x]=val,tag[x]=val;}
	void pushdown(int x){if(tag[x]!=M) update(lc,tag[x]),update(rc,tag[x]),tag[x]=M;}
public:
	void bulid(int x,int l,int r)
	{
		tag[x]=M;t[x]={0,0,0,0,r-l+1};
		if(l==r) return (void)(t[x]=a[Rnk[l]]);
		bulid(lc,l,mid),bulid(rc,mid+1,r);
		pushup(x);
	}
	void modify(int x,int l,int r,int ql,int qr,int v)
	{
		if(ql<=l && r<=qr) return (void)(update(x,v));
		pushdown(x);
		if(ql<=mid) modify(lc,l,mid,ql,qr,v);
		if(qr>mid) modify(rc,mid+1,r,ql,qr,v);
		pushup(x);
	}
	data query(int x,int l,int r,int ql,int qr)
	{
		if(ql<=l && r<=qr) return t[x];
		pushdown(x);
		data res1,res2;
		if(ql<=mid) res1=query(lc,l,mid,ql,qr);
		if(qr>mid) res2=query(rc,mid+1,r,ql,qr);
		if(qr>mid) ql<=mid?res1=res1+res2:res1=res2;
		return res1;
	}
}T;

void change(int x,int y,int v)
{
	while(top[x]!=top[y])
	{
		if(deep[top[x]]<deep[top[y]]) std::swap(x,y);
		T.modify(1,1,n,pos[top[x]],pos[x],v);
		x=fa[top[x]];
	}
	if(deep[x]<deep[y]) std::swap(x,y);
	T.modify(1,1,n,pos[y],pos[x],v);
}
int ask(int x,int y)
{
	int type=0,top1=0,top2=0,res=0;
	while(top[x]!=top[y])
	{
		if(deep[top[x]]<deep[top[y]]) std::swap(x,y),type^=1;
		s=T.query(1,1,n,pos[top[x]],pos[x]);
		if(type) t2[++top2]=s;else t1[++top1]=s;
		x=fa[top[x]];
	}
	if(deep[x]<deep[y]) std::swap(x,y),type^=1;
	s=T.query(1,1,n,pos[y],pos[x]);
	if(type) t2[++top2]=s;else t1[++top1]=s;
	for(int i=1;i<=top2;i++)
		t1[++top1]=t2[top2-i+1],std::swap(t1[top1].maxl,t1[top1].maxr);
	for(int i=1;i<=top1;i++) res=std::max(res,t1[i].max);
	for(int i=1;i<top1;i++)
		for(int j=i+1,sum=t1[i].maxl;j<=top1;j++)
			res=std::max(res,sum+t1[j].maxr),sum+=t1[j].v;
	return res;
}

int main()
{
	freopen("park.in","r",stdin);
	freopen("park.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<n;i++)
	{
		int u,v;scanf("%d%d",&u,&v);
		e[u].push_back(v),e[v].push_back(u);
	}
	deep[1]=1;dfs1(1,0),dfs2(1,1);
	T.bulid(1,1,n);
	scanf("%d",&m);
	while(m--)
	{
		int opt,a,b,c;
		scanf("%d%d%d",&opt,&a,&b);
		if(opt==1) printf("%d\n",ask(a,b));
		else scanf("%d",&c),change(a,b,c);
	}
	return 0;	
}
