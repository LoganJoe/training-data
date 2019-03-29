#include<cstdio>
#include<cstring>
#include<algorithm>
#define fo(i,a,b) for(int i=a;i<=b;i++)
#define N 101000
using namespace std;
int n,e[N][3],las[N],nxt[N*2],to[N*2],bl[N*2],tot=1,ans=0,T,ans1,f[N][3],fa[N],dep[N];
void putin(int x,int y,int z)
{
	nxt[++tot]=las[x];las[x]=tot;to[tot]=y;bl[tot]=z;
}
void dg(int x,int fa,int z)
{
	ans++;
	if(x==T) ans1=1;
	for(int i=las[x];i;i=nxt[i])
	{
		int y=to[i];
		if(y==fa) continue;
		if(z==1&&e[bl[i]][2]==3) continue;
		dg(y,x,e[bl[i]][2]>1?1:z);
	}
}
int main()
{
//	freopen("b.in","r",stdin);
	int ac;scanf("%d%d",&n,&ac);
	fo(i,1,n-1)
	{
		scanf("%d%d%d",&e[i][0],&e[i][1],&e[i][2]);
		putin(e[i][0],e[i][1],i);
		putin(e[i][1],e[i][0],i);
	}
	dep[1]=1;
	while(ac--)
	{
		int z,w,x,y;scanf("%d%d%d%d",&z,&w,&x,&y);
		z^=ans,w^=ans,x^=ans,y^=ans;
		e[z][2]=w;
		T=y,ans1=0,ans=0;dg(x,0,0);
		printf("%d %d\n",ans,ans1);
	}
}