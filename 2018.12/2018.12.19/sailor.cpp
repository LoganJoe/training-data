#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define N 50005
#define mod 998244353
using namespace std;
typedef long long ll;
typedef double db;
int n,m,h[N],cnt,f[N][205],g[N][205],p[N][205],np[205],ng[205],sz[N];
vector<int> ve[N];
int xx(int x,int y){return x+y-(x+y<mod?0:mod);}
bool cmp(int x,int y){return sz[x]>sz[y];}
void dfs(int u,int fa)
{
    bool fl=1;int l=ve[u].size();sz[u]=1;
    for(int i=0;i<l;++i) if(ve[u][i]!=fa) dfs(ve[u][i],u),sz[u]+=sz[ve[u][i]];
    if(sz[u]==1){g[u][0]=1;return;}
    for(int i=0;i<m;++i) np[i]=ng[i]=0;
    sort(ve[u].begin(),ve[u].end(),cmp);
    for(int i=0;i<l;++i)
    {
        int v=ve[u][i];
        if(v==fa) continue;
        if(fl)
        {
            fl=0;
            for(int j=0;j<m;++j) p[u][j]=xx(p[u][j],xx(xx(f[v][j],f[v][j]),g[v][j])),g[u][j]=g[v][j];
        }
        else
        {
            for(int j=0;j<m;++j) if(f[v][j]||g[v][j])
            {
                for(int k=0;k<m;++k)
                {
                    int Ne=(j+k)-(j+k<m?0:m);
                    np[Ne]=xx(np[Ne],(ll)xx(xx(f[v][j],f[v][j]),g[v][j])*p[u][k]%mod);
                    ng[Ne]=xx(ng[Ne],xx((ll)xx(p[u][k],g[u][k])*g[v][j]%mod,(ll)xx(xx(f[v][j],f[v][j]),g[v][j])*g[u][k]%mod));
                }
            }
            for(int j=0;j<m;j++) std::cout<<g[u][j]<<" "<<p[u][j]<<"\n";
            for(int j=0;j<m;++j) p[u][j]=np[j],g[u][j]=ng[j],ng[j]=np[j]=0;
             
        }
    }
    for(int i=0;i<m;++i) f[u][i]=xx(f[u][i],(i?g[u][i-1]:g[u][m-1]));
    for(int i=0;i<m;++i) g[u][i]=p[u][i];
    printf ("------#%d-----\n", u);
	for (int i = 0; i < m; i++) std::cout << f[u][i] << " "; puts ("");
	for (int i = 0; i < m; i++) std::cout << g[u][i] << " "; puts ("");
	for (int i = 0; i < m; i++) std::cout << p[u][i] << " "; puts ("");
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1,x,y;i<n;++i) scanf("%d%d",&x,&y),ve[x].push_back(y),ve[y].push_back(x);
    dfs(1,0);
    cout<<xx(f[1][0],g[1][0])<<endl;
    return 0;
}
