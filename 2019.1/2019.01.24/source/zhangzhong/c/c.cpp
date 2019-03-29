#include<cstdio>
#include<cstring>
#include<algorithm>
#define fo(i,a,b) for(int i=a;i<=b;i++)
#define N 101000
using namespace std;
int n,t[N][2],w[N],tot=1;
int main()
{
//	freopen("c.in","r",stdin);
	int ac;scanf("%d",&ac);
	while(ac--)
	{
		scanf("%d",&n);
		fo(i,1,n)
		{
			int z;scanf("%d",&z);
			if(z>0) w[i]=z;
			else scanf("%d%d",&t[z][0],&t[z][1]);
		}
		int z=0;
		for(int i=n-3;i>=0;i-=2)
		{
			if(z==0) w[i]=max(w[i+2],w[i+3]);
			else w[i]=min(w[i+2],w[i+3]);
			z=1-z;
		}
		printf("%d\n",w[0]);
	}
}