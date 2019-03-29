#include<cstdio>
#include<cstring>
#include<cctype>
using namespace std;
const int N=1e3+5;
struct data
{
	int x,y,z;
}a[N];
int tot,sum;
int first[N],nex[N<<1],en[N<<1],w[N<<1];
bool bz[N];
inline int read()
{
    int X=0,w=0; char ch=0;
    while(!isdigit(ch)) w|=ch=='-',ch=getchar();
    while(isdigit(ch)) X=(X<<3)+(X<<1)+(ch^48),ch=getchar();
    return w?-X:X;
}
inline void insert(int x,int y,int z)
{
	nex[++tot]=first[x];
	first[x]=tot;
	en[tot]=y;
	w[tot]=z;
}
void dfs(int x,int y,int z)
{
	sum++;
	bz[x]=true;
	for(int i=first[x];i;i=nex[i])
	{
		if(en[i]==y) continue;
		if(!z && w[i]==2) continue;
		if(z && w[i]==3)  continue;
		if(w[i]==3 && !z) dfs(en[i],x,1); else
			dfs(en[i],x,z);
	}
}
void dfs1(int x,int y)
{
	if(!bz[x]) sum++,bz[x]=true;
	for(int i=first[x];i;i=nex[i])
	{
		if(en[i]==y || w[i]==3) continue;
		dfs1(en[i],x);
	}
}
int main()
{
	//freopen("b.in","r",stdin);
	int n=read(),q=read();
	for(int i=1;i<n;i++) a[i].x=read(),a[i].y=read(),a[i].z=read();
	while(q--)
	{
		int x=read()^sum,y=read()^sum,s=read()^sum,t=read()^sum;
		a[x].z=y;
		sum=tot=0;
		memset(first,0,sizeof(first));
		memset(bz,false,sizeof(bz));
		for(int i=1;i<n;i++)
		{
			insert(a[i].x,a[i].y,a[i].z);
			insert(a[i].y,a[i].x,a[i].z);
		}
		dfs(s,0,0);
		for(int i=first[s];i;i=nex[i]) dfs1(en[i],s);
		printf("%d %d\n",sum,bz[t]);
	}
	return 0;
}
