#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#define fo(i,x,y) for(i=x;i<=y;i++)
#define N 200055
#define M 5005
using namespace std;
int n,m,i,j,k,x,y,t,u,v,w,ans,q,tot;
int nxt[N],lst[N],b[N],c[N];
int d[N][2],tr[4][N*4];
bool p,bz[M];
struct edge{int u,v,t;}a[N];
int read()
{
	int x=0;
	char ch=getchar();
	while (ch<'0' || ch>'9') ch=getchar();
	while (ch>='0' && ch<='9') x=x*10+ch-'0',ch=getchar();
	return x;
}
void link(int x,int y,int num)
{
	b[++tot]=y;
	c[tot]=num;
	nxt[tot]=lst[x];
	lst[x]=tot;
}
void change(int p,int x,int l,int r,int q,int v)
{
	if (l==r) tr[p][x]+=v;
	else
	{
		int mid=l+r>>1;
		if (mid>=q) change(p,x+x,l,mid,q,v);
		else change(p,x+x+1,mid+1,r,q,v);
		tr[p][x]=tr[p][x+x]+tr[p][x+x+1];
	}
}
int get(int p,int x,int l,int r,int st,int en)
{
	if (st>en) return 0;
	if (l==st && r==en) return tr[p][x];
	else
	{
		int mid=l+r>>1;
		if (mid>=en) return get(p,x+x,l,mid,st,en);else
		if (mid<st) return get(p,x+x+1,mid+1,r,st,en);else
		return get(p,x+x,l,mid,st,mid)+get(p,x+x+1,mid+1,r,mid+1,en);
	}
}
int main()
{
	//freopen("data.in","r",stdin);
	//freopen("data.out","w",stdout);
	scanf("%d%d",&n,&q);
	p=true;
	fo(i,1,n-1)
	{
		x=read();y=read();t=read();
		if (x+1!=y) p=false;
		link(x,y,i);link(y,x,i);
		a[i].u=x;a[i].v=y;a[i].t=t;
	}
	if (!p)
	{
		fo(i,1,q)
		{
			x=read()^ans;t=read()^ans;
			u=read()^ans;v=read()^ans;
			a[x].t=t;
			t=0;w=1;
			d[w][0]=u;
			d[w][1]=0;
			memset(bz,0,sizeof(bz));
			bz[u]=true;
			while (t<w)
			{
				int now=d[++t][0],l=lst[now];
				while (l)
				{
					int to=b[l],num=a[c[l]].t;
					if (bz[to])
					{
						l=nxt[l];
						continue;
					}
					if (num==1 || num==2 || (num==3 && !d[t][1]))
					{
						d[++w][0]=to;bz[to]=true;
						if (num==1) d[w][1]=d[t][1];
						if (num==2 || num==3) d[w][1]=1;
					}
					l=nxt[l];
				}
			}
			ans=0;
			fo(j,1,n)
				if (bz[j]) ans++;
			printf("%d %d\n",ans,bz[v]);
		}
	}else
	{
		fo(i,1,n-1) change(a[i].t,1,1,n,i+1,1);
		fo(i,1,q)
		{
			x=read()^ans;t=read()^ans;
			u=read()^ans;v=read()^ans;
			change(a[x].t,1,1,n,x+1,-1);
			a[x].t=t;
			change(a[x].t,1,1,n,x+1,1);
			int l=1,r=u,pos=0,mid,p3=0;
			while (l<=r)
			{
				mid=l+r>>1;
				if (get(1,1,1,n,mid+1,u)!=u-mid) l=mid+1,pos=mid;else r=mid-1;
			}
			if (!pos) x=1;else
			{
				l=1;r=pos;
				while (l<=r)
				{
					mid=l+r>>1;
					if (get(3,1,1,n,mid+1,pos)) l=mid+1,p3=mid;else r=mid-1;
				}
				if (p3) x=p3+1;else x=1;
			}
			
			l=u;r=n;pos=0;p3=0;
			while (l<=r)
			{
				mid=l+r>>1;
				if (get(1,1,1,n,u+1,mid)!=mid-u) r=mid-1,pos=mid;else l=mid+1;
			}
			if (!pos) y=n;else
			{
				l=pos+1;r=n;
				while (l<=r)
				{
					mid=l+r>>1;
					if (get(3,1,1,n,pos+1,mid)) r=mid-1,p3=mid;else l=mid+1;
				}
				if (p3) y=p3-1;else y=n;
			}
			//printf("%d %d\n",x,y);
			printf("%d %d\n",y-x+1,(v>=x && v<=y));
		}
	}
	return 0;
}
