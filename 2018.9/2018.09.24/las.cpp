#include<bits/stdc++.h>
#define N 500005
#define mod 998244353
int n,m,val[N],a[N],b[N],qry[N],id,ans[N],f[N],res[N];
int find(int x){return f[x]==x?x:f[x]=find(f[x]);}
int mul(int x){return x>=mod?x-mod:x;}
class segment_tree
{
#define lc t[x].ls
#define rc t[x].rs
#define mid ((l+r)>>1)
	struct tree{int ls,rs,sum,v;}t[N*20];
public:
	int root[N],cnt;
	void pushup(int x)
	{
		t[x].sum=t[lc].sum+t[rc].sum;// total answer_s
		t[x].v=t[lc].v+t[rc].v;//total pointsize
	}
	void insert(int &x,int l,int r,int p)
	{
		if(!x) x=++cnt;
		if(l==r) return (void) (t[x].sum=l,t[x].v=1);
		if(p<=mid) insert(lc,l,mid,p);
		else insert(rc,mid+1,r,p);
		pushup(x);
	}
	void merge(int &x,int y,int l,int r,int suml,int sumr)
	{
		if(!x && !y) return ;
		if(!x && y)
		{
			x=y,ans[id]=mul(ans[id]+1ll*t[y].v*suml%mod);
			return ;
		}
		if(x && !y) 
		{
			ans[id]=mul(ans[id]+1ll*t[x].v*sumr%mod);
			return ;
		}
		if(l==r)
		{
			ans[id]=mul(ans[id]+mul(1ll*sumr*t[x].v%mod+1ll*(t[x].sum+suml)*t[y].v%mod));
			t[x].sum+=t[y].sum,t[x].v+=t[y].v;
			return ;
		}
		merge(t[x].ls,t[y].ls,l,mid,suml+t[t[x].rs].sum,sumr+t[t[y].rs].sum);
		merge(t[x].rs,t[y].rs,mid+1,r,suml,sumr);
		pushup(x);
	}
}T;
int main()
{
	freopen("las.in","r",stdin);
	freopen("las.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&val[i]),ans[i]+=val[i];
	for(int i=1;i<=n;i++) T.insert(T.root[i],1,m,val[i]);
	for(int i=1;i<n;i++) scanf("%d%d",&a[i],&b[i]);
	for(int i=1;i<=n;i++) f[i]=i;
	for(int i=1;i<n;i++) scanf("%d",&qry[i]);
	for(int i=n-1;i;i--)
	{
		int fx=find(a[qry[i]]),fy=find(b[qry[i]]);
		f[fy]=id=fx;
		T.merge(T.root[fx],T.root[fy],1,m,0,0);
		res[i]=ans[id]=mul(ans[id]+ans[fy]);
	}
	for(int i=1;i<n;i++) printf("%d\n",res[i]);
}
/*
5 5
2 3 1 4 5
1 2
1 3
2 4
2 5
4
1
2
3
*/
