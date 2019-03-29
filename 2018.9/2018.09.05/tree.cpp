#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<queue>
#include<vector>
#include<set>
#include<map>
using std::cin;using std::cerr;
using std::max;using std::min;
#define N 50005
#define ll long long
#define db double
#define dbg1(x) cerr<<#x<<"="<<(x)<<" "
#define dbg2(x) cerr<<#x<<"="<<(x)<<"\n"
#define dbg(x) cerr<<__FUNCTION__<<"() L"<<__LINE__<<" "<<#x"="<<(x)<<"\n"
int n,m,a,b,c,ecnt,last[N],L[N],R[N],mid[N];
int cnt[N],size[N],Maxsz[N],totsz,root,vis[N],dist[N],qn,q[N];
struct road{int to,v,nex;}e[N<<1];
void adde(int u,int v,int w) {e[++ecnt]=(road){v,w,last[u]},last[u]=ecnt;}
bool cmp(int t1,int t2) {return dist[t1]<dist[t2];}
void getroot(int x,int fath=0)
{
    size[x]=1,Maxsz[x]=0;
    for(int k=last[x];k;k=e[k].nex)
        if(e[k].to^fath&&!vis[e[k].to])
        {
            getroot(e[k].to,x),size[x]+=size[e[k].to];
            Maxsz[x]=max(Maxsz[x],size[e[k].to]);
        }
    Maxsz[x]=max(Maxsz[x],totsz-size[x]);
    if(Maxsz[x]<Maxsz[root]||!root) root=x;
}
void dfs(int x,int fath=0)
{
    q[++qn]=x;
    for(int k=last[x];k;k=e[k].nex)
        if(e[k].to^fath&&!vis[e[k].to]) dist[e[k].to]=dist[x]+e[k].v,dfs(e[k].to,x);
}
int find(int v)
{
	
    if(v<dist[q[1]]) return 0;
    int l=1,r=qn,md;
    for(;l<r;) md=l+r+1>>1,dist[q[md]]>v?r=md-1:l=md;
    return l;
}
void calans(int x,int d,int v)
{
    dist[x]=d,qn=0,dfs(x);
    std::sort(q+1,q+1+qn,cmp);
    for(int i=1,id;i<=qn;i++)
    {
        id=q[i];
        if(L[id]==R[id]) continue;
        cnt[id]+=find(mid[id]-dist[id])*v;
    }
}
void Solve(int x)
{
    totsz=size[x],root=0,getroot(x),vis[x=root]=1,calans(x,0,1);
    for(int k=last[x];k;k=e[k].nex) if(!vis[e[k].to]) calans(e[k].to,e[k].v,-1);
    for(int k=last[x];k;k=e[k].nex) if(!vis[e[k].to]) Solve(e[k].to);
}
bool Judge()
{
    for(int i=1;i<=n;i++) if(L[i]<R[i]) return 1;
    return 0;
}
void clear() {for(int i=1;i<=n;i++) vis[i]=0;}
int main()
{
    scanf("%d%d",&n,&m),m++; 
    for(int i=1;i<n;i++) scanf("%d%d%d",&a,&b,&c),adde(a,b,c),adde(b,a,c),R[0]+=c;
    for(int i=1;i<=n;i++) R[i]=R[0];
    for(;Judge();clear())
    {
        size[1]=n;
        for(int i=1;i<=n;i++) if(L[i]<R[i]) mid[i]=L[i]+R[i]>>1,cnt[i]=0;
        Solve(1);
		for(int i=1;i<=n;i++) printf("%d ",cnt[i]);
    	puts("");
        for(int i=1;i<=n;i++)
            if(L[i]<R[i]) cnt[i]<m?L[i]=mid[i]+1:R[i]=mid[i];
    	
    }
    for(int i=1;i<=n;i++) printf("%d\n",L[i]);
    return 0;
}
