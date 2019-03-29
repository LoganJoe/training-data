#include<bits/stdc++.h>
#define N 500500 
using namespace std;
int n,Q,k,x,y,i,t,id,tot,nv,an,fir[N],ne[N*2],la[N*2],F[N][20],d[N],st[N],ed[N],a[N];
struct P{int x,y;}q[N*2];
bool cmp(P a,P b){return a.x<b.x;}
void ins(int x,int y){la[++tot]=y;ne[tot]=fir[x];fir[x]=tot;} 
int lca(int x,int y){
	if(d[x]<d[y])swap(x,y);
	int t=d[x]-d[y],i;
	for(i=19;~i;i--)if(t>>i&1)x=F[x][i];
	for(i=19;~i;i--)if(F[x][i]!=F[y][i])x=F[x][i],y=F[y][i];
	return x==y?x:F[x][0]; 
}
int up(int x,int z){
	for(int i=19;~i;i--)if(z>>i&1)x=F[x][i];
	return x;
}
void dfs(int x){
	int i,y;st[x]=++id;
	for(i=1;i<=19;i++)F[x][i]=F[F[x][i-1]][i-1];
	for(i=fir[x];i;i=ne[i])if(y=la[i],F[x][0]!=y){
		F[y][0]=x;d[y]=d[x]+1;dfs(y);
	}ed[x]=id;
}
void fd(int x,int y){
	int z=lca(x,y),dis=d[x]+d[y]-2*d[z];
	int bl=(dis%2==0)?dis/2-1:dis/2;
	if(d[y]-d[z]>bl){
		y=up(y,bl);
		q[++t]=P{st[y],ed[y]};
	}else{
		x=up(x,dis-bl-1);
		if(st[x]>=2)q[++t]=P{1,st[x]-1};
		if(ed[x]+1<=n)q[++t]=P{ed[x]+1,n};
	}
}
int main(){
	freopen("civilization.in","r",stdin);
	freopen("civilization.out","w",stdout);
	scanf("%d%d",&n,&Q);
	for(i=1;i<n;i++)scanf("%d%d",&x,&y),ins(x,y),ins(y,x);
	dfs(1);
	for(;Q--;){
		scanf("%d",&k);t=0;
		for(i=1;i<=k;i++)scanf("%d",&a[i]);
		for(i=2;i<=k;i++)fd(a[1],a[i]);
		nv=an=0;
		sort(q+1,q+t+1,cmp);
		for(i=1;i<=t;i++){
			if(q[i].x>nv)an+=q[i].x-nv-1;
			nv=max(nv,q[i].y);
		}
		an+=n-nv;
		printf("%d\n",an);
	}
}
