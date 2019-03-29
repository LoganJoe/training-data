#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100005
#define mod 998244353
using namespace std;
typedef long long ll;
typedef double db;
int n,Q,t,st[N],top;
int ch[N][2],fa[N],sz[N],sum[N],f[N][2][2],tag[N];
int xx(int x,int y){return x+y-(x+y<mod?0:mod);}
bool isroot(int x){return ch[fa[x]][0]!=x&&ch[fa[x]][1]!=x;}
int son(int x){return ch[fa[x]][1]==x;}
bool Check(int x){return !ch[x][0]&&!ch[x][1];}
void Up(int x,int l,int r,int f1,int f2)
{
    for(int i=0;i<2;++i)
        for(int j=0;j<2;++j) f[t][i][j]=0;
    for(int i=0;i<2;++i)
        for(int j=0;j<2;++j)
        {
            for(int s1=0;s1<2;++s1)
                for(int s2=0;s2<2;++s2) f[t][i][j]=xx(f[t][i][j],(ll)f[l][i][s1]*f[r][s2][j]%mod);
            f[t][i|f1][j|f2]=xx(f[t][i|f1][j|f2],(ll)f[l][i][0]*f[r][0][j]%mod);
        }
    for(int i=0;i<2;++i)
        for(int j=0;j<2;++j) f[x][i][j]=f[t][i][j];
}
void Updata(int x)
{
    sum[x]=sum[ch[x][0]]+sum[ch[x][1]]+sz[x];
    f[x][0][0]=1,f[x][1][1]=sz[x]-1,f[x][0][1]=f[x][1][0]=0;
    if(ch[x][0])
    {
        if(Check(ch[x][0])) Up(x,ch[x][0],x,1,1);
        else Up(x,ch[x][0],x,0,1);
    }
    if(ch[x][1])
    {
        if(Check(ch[x][1])) Up(x,x,ch[x][1],(ch[x][0]?0:1),1);
        else Up(x,x,ch[x][1],(ch[x][0]?0:1),0);
    }
}
void push_tag(int x)
{
    if(!tag[x]) return;
    swap(ch[x][0],ch[x][1]),tag[x]=0;
    swap(f[ch[x][0]][0][1],f[ch[x][0]][1][0]);
    swap(f[ch[x][1]][0][1],f[ch[x][1]][1][0]);
    tag[ch[x][0]]^=1,tag[ch[x][1]]^=1;
    Updata(x);
}
void Rotate(int x)
{
    int Fa=fa[x],FFa=fa[Fa],s=son(x);
    if(!isroot(Fa)) ch[FFa][son(Fa)]=x;
    ch[Fa][s]=ch[x][s^1],fa[ch[x][s^1]]=Fa;
    ch[x][s^1]=Fa;fa[Fa]=x;fa[x]=FFa;
    Updata(Fa);Updata(x);
}
void splay(int x)
{
    st[top=1]=x;
    for(int i=x;!isroot(i);i=fa[i]) st[++top]=fa[i];
    for(;top;top--) push_tag(st[top]);
    for(;!isroot(x);Rotate(x))
        if(!isroot(fa[x])) Rotate((son(x)^son(fa[x]))?x:fa[x]);
}
void access(int x)
{
    int la=0;
    for(;x;la=x,x=fa[x])
    {
        splay(x);sz[x]+=sum[ch[x][1]];sz[x]-=sum[la];
        ch[x][1]=la;Updata(x);
    }
}
void mrt(int x){access(x);splay(x);tag[x]^=1;push_tag(x);}
void Link(int x,int y)
{
    mrt(x);mrt(y);
    fa[x]=y;sz[y]+=sum[x];sum[y]+=sum[x];
    Updata(x);
}
void Cut(int x,int y)
{
    mrt(y);access(x);splay(y);
    ch[y][1]=fa[x]=0;
    Updata(y);
}
void Ask(int x,int y)
{
    int ans=0;
    mrt(x);access(y);splay(x);
    for(int i=0;i<2;++i)
        for(int j=0;j<2;++j) ans=xx(ans,f[x][i][j]);
    printf("%d\n",ans);
}
int main()
{
    scanf("%d%d",&n,&Q);t=100001;
    for(int i=1;i<=n;++i) sz[i]=sum[i]=1;
    for(int i=1,x,y;i<n;++i) scanf("%d%d",&x,&y),Link(x,y);
    for (int i = 1; i <= n; i++)
			printf ("fa=%d lson=%d rson=%d size=%d sum=%d sumf=%d\n", fa[i], ch[i][0], ch[i][1], sz[i], sum[i], f[i][0][0] + f[i][1][1]);
    while(Q--)
    {
        int op,x,y,x2,y2;
        scanf("%d%d%d",&op,&x,&y);
        if(op==2) Ask(x,y);
        else
        {
            scanf("%d%d",&x2,&y2);
            Cut(x,y);Link(x2,y2);
        }
    }
    return 0;
}
