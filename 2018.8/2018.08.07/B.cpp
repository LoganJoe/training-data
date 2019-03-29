#include <cstdio>
#include <cstring>
#include <algorithm>
#define repu(i,x,y) for (int i=x; i<=y; ++i)
#define repe(i,x) for (edge *i=fst[x]; i; i=i->nxt)
#define num(x,y) ((x-1)*m+y)
using namespace std;

const int fx[4]={0,0,1,-1},fy[4]={1,-1,0,0};
int n,m,link[10100],tot,ans[10100][2],flag[10100];
char a[110][110];
struct edge
{
    int v;
    edge *nxt;
} pool[80100],*tp=pool,*fst[10100];

void addedge(int u,int v)
{
    *tp=(edge){v,fst[u]},fst[u]=tp++;
    *tp=(edge){u,fst[v]},fst[v]=tp++;
}

bool hungary(int x)
{
    repe(i,x)
        if (!flag[i->v])
        {
            flag[i->v]=1;
            if (!link[i->v] || hungary(link[i->v]))
            {
                link[i->v]=x,link[x]=i->v;
                return 1;
            }
        }
    return 0;
}

void dfs(int x)
{
    if (flag[x]!=-1)
        return;
    flag[x]=1;
    repe(i,x)
        if (link[i->v])
            dfs(link[i->v]);
}

int main()
{
    scanf("%d%d",&n,&m);
    repu(i,1,n)
        scanf("%s",a[i]+1);
    repu(i,1,n)
        repu(j,1,m)
            if (((i+j)&1) && a[i][j]=='.')
                repu(k,0,3)
                    if (a[i+fx[k]][j+fy[k]]=='.')
                        addedge(num(i,j),num(i+fx[k],j+fy[k]));
    repu(i,1,n)
        repu(j,1,m)
            if (((i+j)&1) && a[i][j]=='.')
            {
                memset(flag,0,sizeof(flag));
                hungary(num(i,j));
            }
    memset(flag,255,sizeof(flag));
    repu(i,1,n)
        repu(j,1,m)
            if (a[i][j]=='.' && !link[num(i,j)])
                dfs(num(i,j));
    repu(i,1,n)
        repu(j,1,m)
            if (flag[num(i,j)]==1)
                ans[++tot][0]=i,ans[tot][1]=j;
    printf("%d\n",tot);
    repu(i,1,tot)
        printf("%d %d\n",ans[i][0],ans[i][1]);
    return 0;
}

