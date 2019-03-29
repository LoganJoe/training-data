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
#define N 150005
#define mod 1000000007
#define ll long long
#define db double
#define dbg1(x) cerr<<#x<<"="<<x<<" "
#define dbg2(x) cerr<<#x<<"="<<x<<"\n"
const db pi=acos(-1);
int n,a,b,ecnt,last[N],cnt[N],Maxd,fac,inv[N],Ans,ans[N];
int size[N],Maxsz[N],totsz,root,vis[N];
struct Complex
{
    db r,i;Complex(){};Complex(db _r,db _i) {r=_r,i=_i;}
    friend Complex operator+(Complex t1,Complex t2) {return Complex(t1.r+t2.r,t1.i+t2.i);}
    friend Complex operator-(Complex t1,Complex t2) {return Complex(t1.r-t2.r,t1.i-t2.i);}
    friend Complex operator*(Complex t1,Complex t2) {return Complex(t1.r*t2.r-t1.i*t2.i,t1.i*t2.r+t2.i*t1.r);}
}A[N];
struct road{int to,nex;}e[N<<1];
void adde(int u,int v) {e[++ecnt]=(road){v,last[u]},last[u]=ecnt;}
int cal(int x) {x-=x<mod?0:mod;return x;}
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
    if(!root||Maxsz[x]<Maxsz[root]) root=x;
}
void dfs(int x,int fath,int d)
{
    cnt[d]++,Maxd=max(Maxd,d);
    for(int k=last[x];k;k=e[k].nex)
        if(e[k].to^fath&&!vis[e[k].to]) dfs(e[k].to,x,d+1);
}
class FFT
{
    int Rank[N];
    void dft(Complex x[],int f)
    {
        Complex w,wn,tmp;
        for(int i=0;i<len;i++) if(i<Rank[i]) std::swap(x[i],x[Rank[i]]);
        for(int i=1;i<len;i<<=1)
        {
            wn=Complex(cos(pi/i),f*sin(pi/i));
            for(int j=0;j<len;j+=i<<1)
            {
                w=Complex(1,0);
                for(int k=0;k<i;w=w*wn,k++)
                    tmp=x[i+j+k]*w,x[i+j+k]=x[j+k]-tmp,x[j+k]=x[j+k]+tmp;
            }
        }
        if(f<0) for(int i=0;i<len;i++) x[i].r/=len; 
    }
public:
    int len,l;
    void Prepare() {for(int i=0;i<len;i++) Rank[i]=(Rank[i>>1]>>1)|((i&1)<<l-1);}
    void multiply(Complex x[])
    {
        dft(x,1);for(int i=0;i<len;i++) printf("%lf ",A[i].r);
        for(int i=0;i<len;i++) x[i]=x[i]*x[i];
		
        dft(x,-1);
    }
}fft;
void calans(int x,int v)
{
    dfs(x,0,v<0);
    for(int i=0;i<=Maxd;i++) A[i].r=cnt[i];
    for(fft.len=1,fft.l=0;fft.len<=Maxd<<1;fft.len<<=1,fft.l++);
    fft.Prepare(),fft.multiply(A);
    
    puts("");
    for(int i=0;i<=Maxd<<1;i++)
        ans[i+1]=v>0?cal(ans[i+1]+(ll)(A[i].r+.5)%mod):cal(ans[i+1]-(ll)(A[i].r+.5)%mod+mod);
    for(int i=0;i<=Maxd;i++) cnt[i]=0;Maxd=0;
    for(int i=0;i<fft.len;i++) A[i]=Complex(0,0);
}
void Solve(int x)
{
    totsz=size[x],root=0,getroot(x),vis[x=root]=1,calans(x,1);
    for(int k=last[x];k;k=e[k].nex) if(!vis[e[k].to]) calans(e[k].to,-1);
    for(int k=last[x];k;k=e[k].nex) if(!vis[e[k].to]) Solve(e[k].to);
}
int main()
{
    scanf("%d",&n),fac=inv[0]=inv[1]=1;
    for(int i=1;i<n;i++) scanf("%d%d",&a,&b),adde(a,b),adde(b,a);
    for(int i=2;i<=n;i++) inv[i]=(ll)(mod-mod/i)*inv[mod%i]%mod,fac=(ll)fac*i%mod;
    size[1]=n,Solve(1);
    for(int i=1;i<=n;i++) Ans=cal(Ans+(ll)ans[i]*inv[i]%mod);
    for(int i=1;i<=n;i++) printf("%d\n",ans[i]);
    printf("%d\n",(ll)Ans*fac%mod);
    return 0;
}
