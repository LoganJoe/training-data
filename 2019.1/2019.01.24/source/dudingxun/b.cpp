#include<cstdio>
#include<algorithm>
#include<set>
using namespace std;
const int N=1e5+5;
int n,q,x,y,z,s,t,l,r,tot,ans,last[N],nex[N<<1],to[N<<1],v[N<<1],tr[N*4];
bool bo[N],h[N][2][2];
set<int>f;
set<int>::iterator it;
int read()
{
	int x=0;
	char ch=getchar();
	for (;ch<'0' || ch>'9';) ch=getchar();
	for (;ch>='0' && ch<='9';ch=getchar()) x=x*10+ch-'0';
	return x;
}
void add(int x,int y,int z)
{
	to[++tot]=y;
	v[tot]=z;
	nex[tot]=last[x];
	last[x]=tot;
}
void dg(int x,int y,bool bz,bool bz1)
{
	if (h[x][bz][bz1]) return;
	h[x][bz][bz1]=1;
	if (!bo[x]) bo[x]=1,ans++;
	for (int i=last[x];i;i=nex[i])
	if (to[i]^y)
	{
		if (!bz)
		{
			if (v[i]==3 && bz1) dg(to[i],x,1,0);
			if (v[i]==2) dg(to[i],x,bz,0);
			if (v[i]==1) dg(to[i],x,0,bz1); 
		}
		else
		{
			if (v[i]<3) dg(to[i],x,1,0);
		}
	}
}
void dg1(int x,int y,bool bz)
{
	if (x==s) z=1;
	for (int i=last[x];i;i=nex[i])
	if (to[i]^y)
	{
		if (!bz)
		{
			if (v[i]==3) dg1(to[i],x,1);
			else dg1(to[i],x,0);
		}
		else
		{
			if (v[i]==1) dg1(to[i],x,1);
		}
	}
}
void change(int x,int l,int r,int y,int z)
{
	if (l==r)
	{
		tr[x]=z;
		return;
	}
	int mid=l+r>>1,v=x<<1;
	if (y<=mid) change(v,l,mid,y,z); else change(v|1,mid+1,r,y,z);
	tr[x]=max(tr[v],tr[v|1]);
}
int find(int x,int l,int r,int ll,int rr)
{
	if (ll>rr) return 0;
	if (l==ll && r==rr) return tr[x];
	int mid=l+r>>1,v=x<<1;
	if (rr<=mid) return find(v,l,mid,ll,rr);
	if (ll>mid) return find(v|1,mid+1,r,ll,rr);
	return max(find(v,l,mid,ll,mid),find(v|1,mid+1,r,mid+1,rr));
}
int main()
{
	//freopen("b.in","r",stdin);
	//freopen("b.out","w",stdout);
	n=read(),q=read();
	for (int i=1;i<n;i++)
	{
		x=read(),y=read(),z=read();
		add(x,y,z),add(y,x,z);
		if (z==3) f.insert(i);
	}
	f.insert(0),f.insert(n);
	if (n<=1000)
	{
		while (q--)
		{
			x=read(),y=read(),s=read(),t=read();
			x^=ans,y^=ans,s^=ans,t^=ans;
			v[x*2-1]=y,v[x*2]=y;
			ans=0;
			for (int i=1;i<=n;i++) 
			{
				bo[i]=0;
				h[i][0][0]=h[i][0][1]=h[i][1][0]=h[i][1][1]=0;
			}
			dg(s,0,0,1);
			z=0;
			dg1(t,0,0);
			printf("%d %d\n",ans,z);
		}
		return 0;
	}
	while (q--)
	{
		x=read(),y=read(),s=read(),t=read();
		x^=ans,y^=ans,s^=ans,t^=ans;
		change(1,1,n,x,y);
		ans=0;
		it=f.lower_bound(s);
		r=*it;
		it--;
		l=*it;
		z=find(1,1,n,l+1,r-1);
		if (z!=1)
		{
			ans=r-l;
		}
		else
		{
			it=f.lower_bound(s);
			if (r!=n)
			{
				it++;
				r=*it;
			}
			it=f.lower_bound(s);
			it--;
			if (l>0)
			{
				it--;
				l=*it;
			}
			ans=r-l;
		}
		if (t>l && t<=r) z=1; else z=0;
		printf("%d %d\n",ans,z);
	}
	return 0;
}

