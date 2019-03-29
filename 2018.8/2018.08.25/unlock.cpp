#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#define N 500005
#define mod 998244353
using namespace std;
typedef long long ll;
typedef double db;
int f[N],sum,pre[N],du[N],dfn[N],Index;
int h[N],cnt,T,n,m,ans;
bool flag[N];
struct Edge{int to,Next;}e[2*N];
void adde(int x,int y){e[++cnt]=(Edge){y,h[x]};h[x]=cnt;}
int xx(int x,int y){return x+y-(x+y<mod?0:mod);}
bool dfs(int u)
{
    dfn[u]=++Index;
    for(int i=h[u];i;i=e[i].Next)
    {
        int v=e[i].to;
        if(v==pre[u]) continue;
        if(!dfn[v])  {pre[v]=u;if(dfs(v)) return 1;}
        else if(dfn[v]>dfn[u])
        {
            du[u]-=2;
            for(int j=v;j!=u;j=pre[j])
            {
                if(flag[j]) return 1;
                flag[j]=1;du[j]-=2;
            }
        }
    }
    return 0;
}
int main()
{
    f[0]=f[1]=1;
    for(int i=2;i<=5e5;++i) f[i]=xx(f[i-1],(ll)f[i-2]*(i-1)%mod);
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;++i) h[i]=du[i]=pre[i]=dfn[i]=flag[i]=0;cnt=Index=0;ans=1;
        for(int i=1,x,y;i<=m;++i) scanf("%d%d",&x,&y),adde(x,y),adde(y,x),du[x]++,du[y]++;
        if(dfs(1)) {printf("0\n");continue;}
		for(int i=1;i<=n;++i) printf("%d ",du[i]);puts("");
        for(int i=1;i<=n;++i) ans=(ll)ans*f[du[i]]%mod;
        printf("%d\n",ans);
    }
    return 0;
}

