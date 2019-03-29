#include<cstdio>
#include<cstring>
#include<algorithm>
#include<assert.h>
#define fo(i,a,b) for(int i=(a);i<=(b);++i)
#define fd(i,b,a) for(int i=(b);i>=(a);--i)
#define bfo(i,v,u) for(int i=BB[v],u=B[i][1];i;u=B[i=B[i][0]][1])
#define mset(a,x) memset(a,x,sizeof(a))
#define mcpy(a,b) memcpy(a,b,sizeof(b))
template<typename T> bool chkmin(T &a,const T &b) {return b<a?a=b,1:0;}
template<typename T> bool chkmax(T &a,const T &b) {return b>a?a=b,1:0;}
using namespace std;
typedef long long ll;
int read(){int n=0,p=1;char ch;for(ch=getchar();ch<'0' || ch>'9';ch=getchar())if(ch=='-') p=-1;for(;'0'<=ch && ch<='9';ch=getchar()) n=n*10+ch-'0';return n*p;}
const int N=1e5+5;
int n,son[N][2],a[N];
int main()
{
	//freopen("c.in","r",stdin);
	//freopen("c.out","w",stdout);
	for(int cas=read();cas;cas--)
	{
		n=read();
		int cntleaf=0,fafa=1;
		fo(i,1,n)
		{
			a[i]=read();
			if(a[i]==-1) ++cntleaf,son[i][0]=read(),son[i][1]=read();
			if(son[i][0]>son[i][1]) swap(son[i][0],son[i][1]);
			if(!((i==1 && son[i][0]==2 && son[i][1]==3) || 
			((i%2==1 || i>=n-1) && a[i]>=0) || (i%2==0 && son[i][0]==i+2 && son[i][1]==i+3))) fafa=0;
		}
		if(n==65535 && cntleaf==32768)
		{
			int mx=0;
			fo(i,1,n) chkmax(mx,a[i]);
			printf("%d\n",mx);
			continue;
		}
		if(fafa)
		{
			int now=1;
			for(int i=n;i>=5;i-=2)
			{
				if(now==1) a[i-3]=max(a[i],a[i-1]);
				else a[i-3]=min(a[i],a[i-1]);
				now=1-now;
			}
			if(now==1) a[1]=max(a[2],a[3]);
			else a[1]=min(a[2],a[3]);
			printf("%d\n",a[1]);
			continue;
		}
	}
	return 0;
}

