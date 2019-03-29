#include<cstdio>
#include<algorithm>
using namespace std;
inline int read()
{
	int x;char c;
	while((c=getchar())<'0'||c>'9');
	for(x=c-'0';(c=getchar())>='0'&&c<='9';)x=x*10+c-'0';
	return x;
}
#define MN 100000
#define L (k<<1)
#define R (k<<1|1)
#define up(k) t[k].x=t[L].x+t[R].x
struct data{int lmx,lmn,rmx,rmn;};
inline int mx(int a,int b){return a<0?b:b<0?a:max(a,b);}
inline int mn(int a,int b){return a<0?b:b<0?a:min(a,b);}
data operator+(const data&a,const data&b)
{
	return (data){mx(a.lmx,b.lmx),mn(a.lmn,b.lmn),
				  mx(a.rmx,b.rmx),mn(a.rmn,b.rmn)};
}
data operator~(const data&a)
{
	return (data){a.rmx,a.rmn,a.lmx,a.lmn};
}
struct node{int l,r,rv;data x;}t[MN*4+5];
int v[MN+5],lc[MN+5],rc[MN+5],s[MN+5],fa[MN+5];
int f[MN+5],l[MN+5],r[MN+5],p[MN+5],cnt;
void dfs(int x)
{
	fa[lc[x]]=fa[rc[x]]=x;
	if(lc[x])dfs(lc[x]);if(rc[x])dfs(rc[x]);
	s[x]=s[lc[x]]+s[rc[x]]+1;
}
void build(int x)
{
	p[l[x]=++cnt]=x;
	if(!f[x])f[x]=x;
	if(s[lc[x]]>s[rc[x]])
	{
		f[lc[x]]=f[x];build(lc[x]);
		if(rc[x])build(rc[x]);
	}
	else if(rc[x])
	{
		f[rc[x]]=f[x];build(rc[x]);
		if(lc[x])build(lc[x]);
	}
	r[x]=cnt;
}
void build(int k,int l,int r)
{
	if((t[k].l=l)==(t[k].r=r))
	{
		if((l=p[l])==1)t[k].x=(data){-1,-1,-1,-1};
		else if(lc[fa[l]]==l)t[k].x=(data){-1,-1,v[fa[l]],v[fa[l]]};
		else t[k].x=(data){v[fa[l]],v[fa[l]],-1,-1};
		return;
	}
	int mid=l+r>>1;
	build(L,l,mid);build(R,mid+1,r);up(k);
}
inline void rev(int k){t[k].x=~t[k].x;t[k].rv^=1;}
inline void down(int k){if(t[k].rv)rev(L),rev(R),t[k].rv=0;}
void rev(int k,int l,int r)
{
	if(t[k].l==l&&t[k].r==r){rev(k);return;}
	int mid=t[k].l+t[k].r>>1;down(k);
	if(r<=mid)rev(L,l,r);
	else if(l>mid)rev(R,l,r);
	else rev(L,l,mid),rev(R,mid+1,r);
	up(k);
}
void renew(int k,int x)
{
	if(t[k].l==t[k].r)
	{
		x=p[x];
		if((lc[fa[x]]==x)^t[k].rv)t[k].x=(data){-1,-1,v[fa[x]],v[fa[x]]};
		else t[k].x=(data){v[fa[x]],v[fa[x]],-1,-1};
		return;
	}
	down(k);renew(x>t[k].l+t[k].r>>1?R:L,x);up(k);
}
data query(int k,int l,int r)
{
	if(t[k].l==l&&t[k].r==r)return t[k].x;
	int mid=t[k].l+t[k].r>>1;down(k);
	if(r<=mid)return query(L,l,r);
	if(l>mid)return query(R,l,r);
	return query(L,l,mid)+query(R,mid+1,r);
}
int main()
{
	freopen("farmer.in","r",stdin);
	freopen("farmer.out","w",stdout); 
	int n,m,i,x;
	n=read();m=read();
	for(i=1;i<=n;++i)v[i]=read(),lc[i]=read(),rc[i]=read();
	dfs(1);build(1);
	build(1,1,n);
	while(m--)
	{
		i=read();x=read();
		if(i==1)
		{
			v[x]=read();
			if(lc[x])renew(1,l[lc[x]]);
			if(rc[x])renew(1,l[rc[x]]);
		}
		if(i==2)if(l[x]<r[x])rev(1,l[x]+1,r[x]);
		if(i==3)
		{
			data d=(data){0,0,1e9+1,1e9+1};
			for(i=x;i;i=fa[f[i]])d=d+query(1,l[f[i]],l[i]);
			puts(v[x]>d.lmx&&v[x]<d.rmn?"YES":"NO");
		}
	}
}
