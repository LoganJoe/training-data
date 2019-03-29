#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<string>
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
#define dbg1(x) cerr<<#x<<"="<<(x)<<" "
#define dbg2(x) cerr<<#x<<"="<<(x)<<"\n"
int n,A[N],B[N];
namespace Solve1
{
    int f[5005][5005];
    void Main()
    {
        for(int i=1,p;i<=n;i++)
        {
            for(int j=1;j<=n;j++) f[i][j]=f[i-1][j];
            p=B[i];
            for(;p<n&&!f[i][p];p++);
            for(int j=p;j>A[i];j--) f[i][j]=f[i][j-1];
            f[i][A[i]]=1;
        }
        for(int i=1;i<=n;i++) f[n][i]+=f[n][i-1];
        printf("%d\n",f[n][n]);
    }
}
namespace Solve2
{
    class SplayTree
    {
    #define lc t[x].son[0]
    #define rc t[x].son[1]
    #define pa t[x].fa
        struct node{int fa,son[2],sz,v,Sum;}t[N<<1];
        int getson(int x) {return t[pa].son[1]==x;}
        void pushup(int x) {t[x].Sum=t[lc].Sum+t[rc].Sum+t[x].v,t[x].sz=t[lc].sz+t[rc].sz+1;}
        void rotate(int x)
        {
            int y=pa,z=t[y].fa,k=getson(x);
            t[y].son[k]=t[x].son[!k],t[t[x].son[!k]].fa=y;
            t[x].son[!k]=y,t[y].fa=x,t[x].fa=z;
            t[z].son[t[z].son[1]==y]=x;
            pushup(y);
        } public:
        void splay(int x,int f)
        {
            for(;pa^f;rotate(x))
                if(t[pa].fa^f) rotate(getson(x)^getson(pa)?x:pa);
            pushup(x);if(!f) root=x;
        }
        int find(int x,int v)
        {
            if(v==t[lc].sz+1) return x;
            return t[lc].sz>=v?find(lc,v):find(rc,v-t[lc].sz-1);
        }
        int find2(int x)
        {
            if(t[lc].Sum) return find2(lc);
            if(t[x].v) return x;
            return find2(rc);
        }
        int split(int l,int r)
        {
        	int a,b;
            splay(a=find(root,l),0);
			splay(b=find(root,r+2),root);
			std::cout<<a<<" "<<b<<"\n";
            return t[t[root].son[1]].son[0];
        }
   
        int root,cntnode;
        void build(int &x,int l,int r)
        {
            x=++cntnode;
            if(l==r) return void(t[x].sz=1);
            int mid=l+r>>1;
            if(l<mid) build(lc,l,mid-1),t[lc].fa=x;
            if(r>mid) build(rc,mid+1,r),t[rc].fa=x;
            pushup(x);
        }
        int ask(int p)
        {
            int x=split(p,n);
            if(t[x].Sum) return find2(x);
            for(;rc;x=rc);return x;
        }
        void Delete(int p)
        {
            splay(p,0);
            int sz=t[t[p].son[0]].sz,x=split(sz,sz);
            t[pa].son[0]=0,pushup(pa),pa=0;
        }
        void insert(int id,int p)
        {
            splay(find(root,p),0);
            int x=t[root].son[1];for(;lc;x=lc);
            lc=id,t[id].fa=x,t[id].sz=t[id].v=t[id].Sum=1;
            splay(id,0);
        }
        int query() {return t[root].Sum;}
        void debug (int x)
		{
			if (!x) return;
			debug (lc);
			std::cout << x << ": lc=" << lc << " rc=" << rc << " size=" << t[x].sz << " val=" << t[x].v << "\n";
			debug (rc);
		}
    }T;
    void Main()
    {
        T.build(T.root,1,n+2);
        T.debug(T.root);
        for(int i=1,p;i<=n;i++)
		{
			p=T.ask(B[i]),std::cout<<p<<" ";
			T.Delete(p);
			T.debug(T.root);
			T.insert(p,A[i]);
			
			
		}
        printf("%d\n",T.query());
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d%d",&A[i],&B[i]);
    Solve2::Main();
    return 0;
}
