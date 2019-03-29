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
#define N 100005
#define ll long long
#define db double
#define dbg1(x) cerr<<#x<<"="<<x<<" "
#define dbg2(x) cerr<<#x<<"="<<x<<"\n"
int n,m,op,a,b,c,d,ecnt,last[N],root,fa[N],deep[N],size[N],son[N],top[N],idx,vis[N],pos[N];
struct road{int to,nex;}e[N];
void adde(int u,int v) {e[++ecnt]=(road){v,last[u]},last[u]=ecnt;}
void dfs1(int x,int fath=0)
{
    fa[x]=fath,deep[x]=deep[fath]+1,size[x]=1;
    for(int k=last[x];k;k=e[k].nex)
        if(e[k].to^fath)
        {
            dfs1(e[k].to,x),size[x]+=size[e[k].to];
            if(size[e[k].to]>size[son[x]]) son[x]=e[k].to;
        }
}
void dfs2(int x,int topx)
{
    top[x]=topx,vis[pos[x]=++idx]=x;
    if(!son[x]) return;
    dfs2(son[x],topx);
    for(int k=last[x];k;k=e[k].nex)
        if(e[k].to^fa[x]&&e[k].to^son[x]) dfs2(e[k].to,e[k].to);
}
class PresidentTree
{
#define lc t[x].ls
#define rc t[x].rs
#define mid (l+r>>1)
    struct node{int ls,rs,v;}t[N*20];
public:
    int root[N],cntnode;
    void insert(int &x,int y,int l,int r,int p)
    {
        t[x=++cntnode]=t[y],t[x].v++;
        if(l==r) return;
        p<=mid?insert(lc,t[y].ls,l,mid,p):insert(rc,t[y].rs,mid+1,r,p);
    }
    int find(int x,int y,int l,int r,int _l,int _r,int &v)
    {
    	int res=r-l+1-t[y].v+t[x].v;
		printf("%d %d %d %d %d %d %d\n",x,y,l,r,_l,_r,res);
        if(l==r)
        {
            if(res>=v) return vis[l];
            v-=res;return 0;
        }
        if(_l<=l&&r<=_r&&res<v) {v-=res;return 0;}
        res=0;
        if(_r>mid) res=find(rc,t[y].rs,mid+1,r,_l,_r,v);
        if(_l<=mid&&!res) res=find(lc,t[y].ls,l,mid,_l,_r,v);
        return res;
    }
    int ask(int x,int y,int l,int r,int _l,int _r)
    {
        if(_l<=l&&r<=_r) return r-l+1-t[y].v+t[x].v;
        int res=0;
        if(_l<=mid) res=ask(lc,t[y].ls,l,mid,_l,_r);
        if(_r>mid) res+=ask(rc,t[y].rs,mid+1,r,_l,_r);
        return res;
    }
}T;
int Solve(int x,int y,int z,int l,int r)
{
    int res;
    for(;deep[top[x]]>deep[y];x=fa[top[x]])
    {
        res=T.ask(T.root[l],T.root[r],1,n,pos[top[x]],pos[x]);
        if(res>=z)
        {
            printf("%d\n",T.find(T.root[l],T.root[r],1,n,pos[top[x]],pos[x],z));
            return 1;
        }
        z-=res;
    }
    res=T.ask(T.root[l],T.root[r],1,n,pos[y],pos[x]);
    if(res>=z)
    {
        printf("%d\n",T.find(T.root[l],T.root[r],1,n,pos[y],pos[x],z));
        return 1;
    }
    return 0;
}
int main()
{
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a),a?(adde(a,i),1):root=i;
    dfs1(root),dfs2(root,root);
    scanf("%d",&m);
    for(int i=1,LCA,x,y,tot;i<=m;i++)
    {
        scanf("%d%d",&op,&a);
        if(op==1) T.insert(T.root[i],T.root[i-1],1,n,pos[a]);
        else
        {
            scanf("%d%d%d",&b,&c,&d),T.root[i]=T.root[i-1],tot=0;
            for(x=a,y=b;top[x]^top[y];x=fa[top[x]])
            {
                if(deep[top[x]]<deep[top[y]]) std::swap(x,y);
                tot+=T.ask(T.root[d],T.root[i],1,n,pos[top[x]],pos[x]);
            }
            if(deep[x]>deep[y]) std::swap(x,y);
            LCA=x,tot+=T.ask(T.root[d],T.root[i],1,n,pos[x],pos[y]);
            
            if(T.ask(T.root[d],T.root[i],1,n,pos[a],pos[a])) c++;
            if(T.ask(T.root[d],T.root[i],1,n,pos[b],pos[b])) tot--;
            if(tot<c) {puts("-1");continue;}
            if(Solve(a,LCA,c,d,i)) continue;
            
            if(T.ask(T.root[d],T.root[i],1,n,pos[b],pos[b])) tot++;
            Solve(b,LCA,tot-c+1,d,i);
        }
    }
    return 0;
}
