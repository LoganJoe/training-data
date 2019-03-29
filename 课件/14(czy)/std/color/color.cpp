#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
inline int read()
{
	int x;char c;
	while((c=getchar())<'0'||c>'9');
	for(x=c-'0';(c=getchar())>='0'&&c<='9';)x=x*10+c-'0';
	return x;
}
#define MN 100032
#define K 1563
#define Z 782
typedef unsigned long long ll;
int a[MN+5],t[64],s[1<<16],c[MN+5],cn,p[MN+5];
struct Q{int l,r;}q[MN+5];
bool cmp(const Q&a,const Q&b){return a.l<b.l;}
struct S
{
	ll z[Z];
	void set(int x){z[x>>6]|=1ULL<<(x&63);}
	void rev(int x){z[x>>6]^=1ULL<<(x&63);}
	int count()
	{
		int res=0;
		for(int i=0;i<Z;++i)
			res+=s[z[i]>>48]+s[(z[i]>>32)&65535]+s[(z[i]>>16)&65535]+s[z[i]&65535];
		return res;
	}
}*b[6],B;
void solve(int l,int r)
{
	if(l>r)return;
	int x=t[r-l+1];
	for(int i=0;i<Z;++i)B.z[i]|=b[x][l].z[i]|b[x][r-(1<<x)+1].z[i];
}
void work(int l,int r)
{
	if((l-1)/K==(r-1)/K)for(int i=l;i<=r;++i)B.set(a[i]);
	else
	{
		for(int i=l;i<=(l-1)/K*K+K;++i)B.set(a[i]);
		solve((l-1)/K+1,(r-1)/K-1);
		for(int i=r;i>(r-1)/K*K;--i)B.set(a[i]);
	}
}
int main()
{
	freopen("color.in","r",stdin);
	freopen("color.out","w",stdout); 
	int n,m,o,i,j,k,x,l,r,ans,ls=0;
	n=read();m=read();o=read();
	for(i=2;i<64;++i)t[i]=t[i>>1]+1;
	for(i=1;i<1<<16;++i)s[i]=s[i>>1]+(i&1);
	for(i=1;i<=n;++i)++c[a[i]=read()];
	for(i=1;i<=n;p[i]+=p[i-1],++i)if(c[a[i]]==1)a[i]=0,p[i]=1;
	for(i=1;i<=n;++i)if(a[i])c[++cn]=a[i];
	sort(c+1,c+cn+1);cn=unique(c+1,c+cn+1)-c-1;
	for(i=1;i<=n;++i)if(a[i])a[i]=lower_bound(c+1,c+cn+1,a[i])-c;
	for(i=0,x=K;i<6;++i,x<<=1)
	{
		memset(&B,0,sizeof(B));memset(c,0,sizeof(c));
		for(k=1;k<=x;++k)if(!c[a[k]]++)B.rev(a[k]);
		b[i]=new S[(MN-x)/K+1];b[i][0]=B;
		for(j=K;j+x<=MN;b[i][j/K]=B,j+=K)for(k=0;k<K;++k)
		{
			if(!c[a[j+x-k]]++)B.rev(a[j+x-k]);
			if(!--c[a[j-k]])B.rev(a[j-k]);
		}
	}
	while(m--)
	{
		memset(&B,ans=0,sizeof(B));
		k=read();
		for(i=1;i<=k;++i)
		{
			q[i].l=read();q[i].r=read();
			if(o&&ls)
			{
				q[i].l=(q[i].l^ls)%n+1;q[i].r=(q[i].r^ls)%n+1;
				if(q[i].l>q[i].r)swap(q[i].l,q[i].r); 
			}
		}
		sort(q+1,q+k+1,cmp);
		l=q[1].l;r=q[1].r;
		for(i=2;i<=k;r=max(r,q[i++].r))if(q[i].l>r+1)ans+=p[r]-p[l-1],work(l,r),l=q[i].l;
		ans+=p[r]-p[l-1];work(l,r);
		printf("%d\n",ls=B.count()+ans-(B.z[0]&1));
	}
}
