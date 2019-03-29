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
using std::swap;using std::cerr;
using std::max;using std::min;
#define N 200005
#define M 170
#define ll long long
#define db double
#define dbg1(x) cerr<<#x<<"="<<(x)<<" "
#define dbg2(x) cerr<<#x<<"="<<(x)<<"\n"
#define dbg(x) cerr<<__FUNCTION__<<"() L"<<__LINE__<<#x"="<<(x)<<"\n"
int n,m,type,a,b,c,ecnt=1,last[N],block=1200,bel[N],cnt[M][N];ll ans,lastans;
int deep[N],Log[N<<1],ST[N<<1][20],idx,Idx,vis[N<<1],pos[N],posl[N],posr[N];
char s[9];
struct node1
{
    ll v1[N],v2[M];
    void add(int l,int r,int v)
    {
        if(bel[l]==bel[r]) {for(int i=l;i<=r;i++) v1[i]+=v;return;}
        for(int i=bel[l]+1;i<bel[r];i++) v2[i]+=v;
        for(int i=l;i<=bel[l]*block;i++) v1[i]+=v;
        for(int i=(bel[r]-1)*block+1;i<=r;i++) v1[i]+=v;
    }
    ll ask(int x) {return v1[x]+v2[bel[x]];}
}A;
struct node2
{
    ll v1[N],v2[M];
    void add(int x,ll v) {if(x<=n) v1[x]+=v,v2[bel[x]]+=v;}
    ll ask(int x)
    {
        ll res=0;
        for(int i=1;i<bel[x];i++) res+=v2[i];
        for(int i=(bel[x]-1)*block+1;i<=x;i++) res+=v1[i];
        return res;
    }
}B[M];
struct road{int to,v,nex;}e[N<<1];
void adde(int u,int v,int w) {e[++ecnt]=(road){v,w,last[u]},last[u]=ecnt;}
int dmin(int x,int y) {return deep[x]<deep[y]?x:y;}
void dfs(int x,int fath=0)
{
    deep[x]=deep[fath]+1,cnt[bel[x]][x]++,posl[x]=++idx,ST[pos[x]=++Idx][0]=x;
    for(int k=last[x];k;k=e[k].nex)
        if(e[k].to^fath)
        {
            dfs(e[k].to,x),ST[++Idx][0]=x;
            for(int i=1;i<=bel[n];i++) cnt[i][x]+=cnt[i][e[k].to];
        }
    posr[x]=idx;
}
int asklca(int x,int y)
{
    x=pos[x],y=pos[y];
    if(x>y) swap(x,y);
    int t=Log[y-x+1];
    return dmin(ST[x][t],ST[y-(1<<t)+1][t]);
}
void Prepare()
{
    for(int i=2;i<=Idx;i++) Log[i]=Log[i>>1]+1;
    for(int j=1;j<20;j++)
        for(int i=1;i+(1<<j)-1<=Idx;i++)
            ST[i][j]=dmin(ST[i][j-1],ST[i+(1<<j-1)][j-1]);
    for(int i=1;i<=bel[n];i++)
        for(int j=1;j<=n;j++) cnt[i][j]+=cnt[i-1][j];
}
void add(int x,int y,int v)
{
    if(deep[x]<deep[y]) swap(x,y);
    A.add(posl[x],posr[x],v);
    for(int i=1,cnt1,cnt2;i<=bel[n];i++)
    {
        cnt1=cnt[i][x],cnt2=min(n,i*block)-cnt1,B[i].add(1,(ll)v*cnt1);
        B[i].add(posl[x],(ll)(cnt2-cnt1)*v),B[i].add(posr[x]+1,(ll)(cnt1-cnt2)*v);
    }
}
ll ask(int x,int y)
{
    if(!y) return 0;
    ll res=B[bel[y]-1].ask(posl[x]);
    for(int i=(bel[y]-1)*block+1,LCA;i<=y;i++)
        LCA=asklca(x,i),res+=A.ask(posl[x])+A.ask(posl[i])-A.ask(posl[LCA])*2;
    return res;
}
int main()
{
	freopen("a.in","r",stdin);
	freopen("a.ans","w",stdout);
    scanf("%d%d%d",&n,&m,&type);
    for(int i=1;i<n;i++) scanf("%d%d%d",&a,&b,&c),adde(a,b,c),adde(b,a,c);
    for(int i=1;i<=n;i++) bel[i]=(i-1)/block+1;
    dfs(1),Prepare();
    for(int i=2;i<=ecnt;i+=2) add(e[i].to,e[i^1].to,e[i].v);
    for(;m--;)
    {
        scanf("%s%d%d",s,&a,&b);
        if(type) a^=lastans,b^=lastans;
        if(s[0]=='m') a<<=1,add(e[a].to,e[a^1].to,b-e[a].v),e[a].v=e[a^1].v=b; 
        else
        {
            scanf("%d",&c);if(type) c^=lastans;
            printf("%lld\n",lastans=ask(c,b)-ask(c,a-1)),lastans%=n;
			
        }
    }
    return 0;
}
