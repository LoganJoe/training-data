#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#define fo(i,j,k) for(int i=j;i<=k;++i)
#define fd(i,j,k) for(int i=j;i>=k;--i)
#define rep(i,x) for(int i=ls[x];i;i=nx[i])
using namespace std;
const int N=1e5+10,M=2e5+10;
int to[M],nx[M],ls[N],vl[M],num=0;
void link(int u,int v,int w){
	to[++num]=v,nx[num]=ls[u],ls[u]=num;
	vl[num]=w;
}
int a[N];
int tf=0;
int t,ans=0;
void dfs(int x,int fr,bool p){
	ans++,tf|=(x==t);
	rep(i,x){
		int v=to[i];
		if(v==fr) continue;
		if(p && vl[i]==3) continue;
		dfs(v,x,p|(vl[i]==2 || vl[i]==3));
	}
}
int tr[N*4],n;
void ins(int x,int v=1,int l=0,int r=n){
	if(l==r) {tr[v]=a[l];return;}
	int mid=(l+r)>>1;
	x<=mid?ins(x,v<<1,l,mid):ins(x,v<<1|1,mid+1,r);
	tr[v]=max(tr[v<<1],tr[v<<1|1]);
}
int findl(int x,int k,int v=1,int l=0,int r=n){
	if(tr[v]<=k) return -1;
	if(l==r) return l;
	int mid=(l+r)>>1;
	if(x<=mid) return findl(x,k,v<<1,l,mid);
	else{
		int p=findl(x,k,v<<1|1,mid+1,r);
		return p>=0?p:findl(x,k,v<<1,l,mid);
	}
}
int findr(int x,int k,int v=1,int l=0,int r=n){
	if(tr[v]<=k) return -1;
	if(l==r) return l;
	int mid=(l+r)>>1;
	if(x>mid) return findr(x,k,v<<1|1,mid+1,r);
	else{
		int p=findr(x,k,v<<1,l,mid);
		return p>=0?p:findr(x,k,v<<1|1,mid+1,r);
	} 
}
int main()
{
	//freopen("b.in","r",stdin);
	//freopen("b.out","w",stdout);
	int q;
	scanf("%d %d",&n,&q);
	fo(i,2,n){
		int u,v,w;
		scanf("%d %d %d",&u,&v,&w);
		a[i-1]=w;
		link(u,v,w),link(v,u,w),tf+=u<v?v-u:u-v;
	}
	if(tf==n-1){
		a[0]=a[n]=3;
		fo(i,0,n) ins(i);
		while(q--){
			int x,w,s;
			scanf("%d %d %d %d",&x,&w,&s,&t)/*,x^=ans,w^=ans,s^=ans,t^=ans*/;
			a[x]=w,ins(x);
			int l=findl(s-1,1);
			if(l>0) l=a[l]==3?(findl(l-1,2)+1):(findl(s-1,2)+1);
			else l=1;
			int r=findr(s,1);
			if(r<n) r=a[r]==3?findr(r+1,2):findr(s,2);
			else r=n;
			ans=r-l+1,tf=(t>=l && t<=r);
			printf("%d %d\n",ans,tf);
		}
		return 0;
	}
	while(q--){
		int x,w,s;
		scanf("%d %d %d %d",&x,&w,&s,&t),x^=ans,w^=ans,s^=ans,t^=ans;
		vl[x*2-1]=vl[x*2]=w;
		ans=tf=0,dfs(s,0,0);
		printf("%d %d\n",ans,tf);
	}
	
}

