#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1e5+5;
int t,n,a[N],ls[N],rs[N],s[N],f[N][2];
int read()
{
	int x=0;
	bool bo=0;
	char ch=getchar();
	for (;(ch<'0' || ch>'9') && ch!='-';) ch=getchar();
	if (ch=='-') bo=1,ch=getchar();
	for (;ch>='0' && ch<='9';ch=getchar()) x=x*10+ch-'0';
	return bo?-x:x;
}
void dg(int x)
{
	if (a[x]!=-1)
	{
		f[x][0]=f[x][1]=a[x];
		s[x]=0;
		return;
	}
	dg(ls[x]),dg(rs[x]);
	int t;
	s[x]=s[ls[x]]+s[rs[x]]+1;
	if (s[ls[x]]&1) 
	{
		if (s[x]&1) f[x][0]=max(f[ls[x]][0],f[rs[x]][1]);
		else f[x][0]=min(f[ls[x]][0],f[rs[x]][1]);
	}
	else 
	{
		if (s[x]&1) f[x][0]=max(f[ls[x]][0],f[rs[x]][0]);
		else f[x][0]=min(f[ls[x]][0],f[rs[x]][0]);
	}
	if (s[rs[x]]&1) 
	{
		if (s[x]&1) t=max(f[rs[x]][0],f[ls[x]][1]);
		else t=min(f[rs[x]][0],f[ls[x]][1]);
		f[x][0]=max(f[x][0],t);
	}
	else 
	{
		if (s[x]&1) t=max(f[ls[x]][0],f[rs[x]][0]);
		else t=min(f[ls[x]][0],f[rs[x]][0]);
		f[x][0]=max(f[x][0],t);
	}
	
	if (s[ls[x]]&1) 
	{
		if (s[x]&1) f[x][1]=min(f[ls[x]][1],f[rs[x]][0]);
		else f[x][1]=max(f[ls[x]][1],f[rs[x]][0]);
	}
	else 
	{
		if (s[x]&1) f[x][1]=min(f[ls[x]][1],f[rs[x]][1]);
		else f[x][0]=max(f[ls[x]][1],f[rs[x]][1]);
	}
	if (s[rs[x]]&1) 
	{
		if (s[x]&1) t=min(f[rs[x]][1],f[ls[x]][0]);
		else t=max(f[rs[x]][1],f[ls[x]][0]);
		f[x][1]=min(f[x][1],t);
	}
	else 
	{
		if (s[x]&1) t=min(f[ls[x]][1],f[rs[x]][1]);
		else t=max(f[ls[x]][1],f[rs[x]][1]);
		f[x][1]=min(f[x][1],t);
	}
}
int main()
{
	//freopen("c.in","r",stdin);
	//freopen("c.out","w",stdout);
	t=read();
	while (t--)
	{
		n=read();
		for (int i=1;i<=n;i++)
		{
			a[i]=read();
			if (a[i]==-1) ls[i]=read(),rs[i]=read();
		}
		dg(1);
		printf("%d\n",f[1][0]);
	}
	return 0;
}

