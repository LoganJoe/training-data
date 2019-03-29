#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
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
int n,B0,BB[N],B[N<<1][3];
struct edge
{
	int x,y,w;
}b[N];
void link(int u,int v,int w){B[++B0][1]=v,B[B0][2]=w,B[B0][0]=BB[u],BB[u]=B0;}
int ans,map[1005][1005];
bool bz[N];
void brute(int v,int fr=0,int p2=0,int p3=0)
{
	bz[v]=1;
	bfo(i,v,u) if(u!=fr)
	{
		if((p2 || p3) && map[v][u]==3) continue;
		brute(u,v,p2+(map[v][u]==2),p3+(map[v][u]==3));
	}
}
set<int> S[4];
int fa[N],fa1[N],sm1[N],fa2[N],sz2[N];
int getfa1(int v)
{
	if(!fa1[v]) return v;
	fa1[v]=getfa1(fa1[v]);
	return fa1[v];
}
int getfa2(int v)
{
	if(!fa2[v]) return v;
	fa2[v]=getfa2(fa2[v]);
	return fa2[v];
}
void merge2(int x,int y)
{
	int fx=getfa2(x),fy=getfa2(y);
	if(fx==fy) return;
	fa2[fy]=fx,sz2[fx]+=sz2[fy],sz2[fy]=0;
}
void merge1(int x,int y)
{
	int fx=getfa1(x),fy=getfa1(y);
	if(fx==fy) return;
	fa1[fy]=fx,sm1[fx]+=sm1[fy],sm1[fy]=0;
}
int dep[N],c[N];
void dfs1(int v,int fr=0,int d=1)
{
	dep[v]=d,fa[v]=fr;
	bfo(i,v,u) if(u!=fr)
	{
		c[u]=B[i][2];
		if(B[i][2]<=2) merge2(v,u);
		if(B[i][1]<=1) merge1(v,u);
		dfs1(u,v,d+1);
	}
}
void dfs2(int v,int fr=0)
{
	bfo(i,v,u) if(u!=fr)
	{
		if(B[i][2]==3)
			sm1[getfa1(v)]+=sz2[u];
		dfs2(u,v);
	}
}
int main()
{
	//freopen("b.in","r",stdin);
	//freopen("b.out","w",stdout);
	n=read();int Q=read(),x,y,w;
	bool chain=1;
	fo(i,1,n-1)
	{
		x=read(),y=read(),w=read(),link(x,y,w),link(y,x,w);
		b[i]=(edge){x,y,w};
		if(n<=1000) map[x][y]=map[y][x]=w;
		chain &= (x==i && y==i+1);
	}
	if(n<=1000 && Q<=1000)
	{
		while(Q--)
		{
			int k=read()^ans;w=read()^ans,x=read()^ans,y=read()^ans;
			map[b[k].x][b[k].y]=map[b[k].y][b[k].x]=w;
			ans=0;
			fo(i,1,n) bz[i]=0;
			brute(x);
			fo(i,1,n) if(bz[i]) ++ans;
			printf("%d %d\n",ans,bz[y]);
		}
		return 0;
	}//*/
	if(chain)
	{
		fo(i,1,n-1) S[b[i].w].insert(b[i].x);
		fo(i,1,3) S[i].insert(0),S[i].insert(n);
		while(Q--)
		{
			int k=read()^ans;w=read()^ans,x=read()^ans,y=read()^ans;
			//int k=read();w=read(),x=read(),y=read();
			S[b[k].w].erase(k);
			S[w].insert(k);
			b[k].w=w;
			ans=0;
			int l3 = *(--S[3].upper_bound(x-1));
			int l2 = *(--S[2].upper_bound(x-1));
			int l = l2 > l3 ? (l3+1) : (*(--S[3].upper_bound(l3-1)) + 1);
			if(!l3) l=1;
			
			int r3 = *(S[3].lower_bound(x));
			int r2 = *(S[2].lower_bound(x));
			int r = r2 < r3 ? r3 : *(S[3].lower_bound(r3+1));
			if(r3>=n) r=n;
			
			l = max(l, 1) , r = min(r, n);
			ans = r - l + 1;
			printf("%d %d\n",ans,(l<=y && y<=r));
		}
		return 0;
	}//*/
	fo(i,1,n) sz2[i]=1;
	dfs1(1);
	dfs2(1);
	while(Q--)
	{
		int k=read()^ans;w=read()^ans,x=read()^ans,y=read()^ans;
		int u=b[k].x,v=b[k].y;
		c[v]=w;
		if(dep[u]>dep[v]) swap(u,v);
		if(w==2)
		{
			sm1[getfa1(u)]-=sz2[v];
			merge2(u,v);
		}
		else
		if(w==1)
		{
			merge1(u,v);
		}
		int f1x=getfa1(x),f2x=getfa2(x);
		ans=sz2[f2x]+sm1[f1x];
		if(c[f1x]==3) ans+=sz2[getfa2(fa[f1x])];
		int f1y=getfa1(y),f2y=getfa2(y);
		printf("%d %d\n",ans,(f2y==f2x) || (c[f1y]==3 && getfa1(fa[f1y])==f1x));
	}
	return 0;
}

