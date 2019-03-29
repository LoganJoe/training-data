#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
inline int read()
{
	int x;char c;
	while((c=getchar())<'0'||c>'9');
	for(x=c-'0';(c=getchar())>='0'&&c<='9';)x=x*10+c-'0';
	return x;
}
#define MN 100000
#define MM 200000
#define MX 262144
#define MOD 998244353
struct edge{int nx,t;}e[MM*2+5];
int a[MN+5],r[MN+5],h[MN+5],en=1,z[MN+5],zn,d[MN+5],l[MN+5],cnt,q[MN+5],qn;
int N,RN,R[MX+5],w[MX+5],A[MX+5],B[MX+5],F[MN+5][2],G[MN+5][2];
vector<int> f[MN+5];
struct pol{int n,*x;pol(int n):n(n),x(new int[n+1]){}};
vector<pol> v[MN+5];
inline void ins(int x,int y)
{
	e[++en]=(edge){h[x],y};h[x]=en;++r[x];
	e[++en]=(edge){h[y],x};h[y]=en;++r[y];
}
inline int pw(int x,int y)
{
	int r=1;
	for(;y;y>>=1,x=1LL*x*x%MOD)if(y&1)r=1LL*r*x%MOD;
	return r;
}
void init(int n)
{
	int i,j,k;
	for(N=1;N<=n;N<<=1);RN=pw(N,MOD-2);
	for(i=j=0;i<N;R[++i]=j)for(k=N>>1;(j^=k)<k;k>>=1);
	for(k=pw(3,(MOD-1)/N),w[0]=i=1;i<N;++i)w[i]=1LL*w[i-1]*k%MOD;
}
void fft(int*x,int v)
{
	int i,j,k,p;
	if(v)for(i=0;i<N;++i)if(i<(N-1&N-i))swap(x[i],x[N-1&N-i]);
	for(i=0;i<N;++i)if(i<R[i])swap(x[i],x[R[i]]);
	for(i=1;i<N;i<<=1)for(j=0;j<N;j+=i<<1)for(k=0;k<i;++k)
	{
		p=1LL*x[i+j+k]*w[N/(i<<1)*k]%MOD;
		x[i+j+k]=(x[j+k]+MOD-p)%MOD;
		x[j+k]=(x[j+k]+p)%MOD;
	}
	if(v)for(i=0;i<N;++i)x[i]=1LL*x[i]*RN%MOD;
}
pol solve(vector<pol>&v,int l,int r)
{
	if(l==r)return v[l];
	int mid=l+r>>1,i;
	pol a=solve(v,l,mid),b=solve(v,mid+1,r),c(a.n+b.n);
	init(a.n+b.n);
	for(i=0;i<N;++i)A[i]=i<=a.n?a.x[i]:0,B[i]=i<=b.n?b.x[i]:0;
	fft(A,0);fft(B,0);
	for(i=0;i<N;++i)A[i]=1LL*A[i]*B[i]%MOD;
	fft(A,1);
	for(i=0;i<=c.n;++i)c.x[i]=A[i];
	return c;
}
void dfs(int x,int fa)
{
	z[zn++]=x;d[x]=l[x]=++cnt;
	for(int i=h[x];i;i=e[i].nx)if(i!=fa)
		if(!d[e[i].t])
		{
			dfs(e[i].t,i^1);
			l[x]=min(l[x],l[e[i].t]);
			if(l[e[i].t]>=d[x])
			{
				for(qn=0;z[zn]!=e[i].t;)q[++qn]=z[--zn];
				if(l[e[i].t]>d[x])
				{
					pol A(1);A.x[0]=0;
					for(int j=0;j<a[e[i].t];++j)A.x[0]=(A.x[0]+f[e[i].t][j])%MOD;
					A.x[1]=(A.x[0]+f[e[i].t][a[e[i].t]])%MOD;
					v[x].push_back(A);
					continue;
				}
				F[0][1]=G[0][0]=1;
				for(int j=1;j<=qn;++j)
				{
					int A=0,B=0,C=0;
					for(int k=0;k<=a[q[j]];++k)
						k+1<a[q[j]]?A=(A+f[q[j]][k])%MOD:0,
						k<a[q[j]]?B=(B+f[q[j]][k])%MOD:0,
						C=(C+f[q[j]][k])%MOD;
					F[j][0]=(1LL*F[j-1][0]*B+1LL*F[j-1][1]*A)%MOD;
					F[j][1]=(1LL*F[j-1][0]*C+1LL*F[j-1][1]*B)%MOD;
					G[j][0]=(1LL*G[j-1][0]*B+1LL*G[j-1][1]*A)%MOD;
					G[j][1]=(1LL*G[j-1][0]*C+1LL*G[j-1][1]*B)%MOD;
				}
				pol A(2);
				A.x[0]=F[qn][0];
				A.x[1]=(F[qn][1]+G[qn][0])%MOD;
				A.x[2]=G[qn][1];
				v[x].push_back(A);
			}
		}
		else l[x]=min(l[x],d[e[i].t]);
	if(!v[x].size())f[x][0]=1;
	else
	{
		pol A=solve(v[x],0,v[x].size()-1);
		for(int i=0;i<=a[x]&&i<=A.n;++i)f[x][i]=A.x[i];
	}
}
int main()
{
	freopen("cactus.in","r",stdin);
	freopen("cactus.out","w",stdout);
	int n,m,i,ans=0;
	n=read();m=read();
	while(m--)ins(read(),read());
	for(i=1;i<=n;++i)a[i]=min(r[i],read()),f[i]=vector<int>(a[i]+1,0);
	dfs(1,0);
	for(i=0;i<=a[1];++i)ans=(ans+f[1][i])%MOD;
	printf("%d",ans);
}
