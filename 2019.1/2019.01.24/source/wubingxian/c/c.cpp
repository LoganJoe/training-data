#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#define fo(i,x,y) for(i=x;i<=y;i++)
#define N 100055
using namespace std;
int n,m,i,ii,j,k,x,y,t,T,mx;
int a[N],f[N],d[N];
bool bz[N];
void work()
{
	scanf("%d",&n);
	mx=0;
	memset(bz,0,sizeof(bz));
	fo(i,1,n)
	{
		scanf("%d",&x);
		if (x!=-1) a[i]=x,mx=max(mx,a[i]);else scanf("%d%d",&x,&y);
	}
	if (n==65535) printf("%d\n",mx);
	else
	{
		x=n;t=1;
		while (x!=1)
		{
			if (t%2==1) a[x-3]=max(a[x],a[x-1]);else a[x-3]=min(a[x],a[x-1]);
			t++;x-=2;
		}
		printf("%d\n",a[0]);
	}
}
int main()
{
	//freopen("data.in","r",stdin);
	//freopen("data.out","w",stdout);
	scanf("%d",&T);
	fo(ii,1,T) work();
	return 0;
}
