#include<bits/stdc++.h>
#define ll long long
#define inf 1000000000
#define infll 1000000000000000000ll
#define pii pair<int,int>
#define pll pair<ll,ll>
#define mpr make_pair
#define fi first
#define se second
#define vi vector<int>
#define pb push_back
#define pq priority_queue
#define up(x,y) ((x<(y))?x=(y):0)
#define dn(x,y) ((x>(y))?x=(y):0)
#define ad(x,y) (x=(x+y)%mod)
#define N 1000009
using namespace std;

int n,m,tot,clk,gol,trtot,rt1,rt2,fst[N],cur[N],pnt[N],len[N],nxt[N];
int h[N],d[N],a[N],ans[N],ls[N],rs[N],q[N],nq[N],lb[N],pos[N];
vector<pair<pii,int> >g[N];
void add(int x,int y,int z){
	pnt[++tot]=y; len[tot]=z; nxt[tot]=fst[x]; fst[x]=tot;
}
void ins(int x,int y,int z){ add(x,y,z); add(y,x,0); }
bool bfs(){
	int head=0,tail=1,i,x,y; h[1]=0; d[0]=1; cur[0]=fst[0];
	for (i=1; i<=gol; i++){ d[i]=-1; cur[i]=fst[i]; }
	while (head<tail){
		x=h[++head];
		for (i=fst[x]; i; i=nxt[i]) if (len[i]){
			y=pnt[i];
			if (d[y]==-1){
				d[y]=d[x]+1; h[++tail]=y;
			}
		}
	}
	return d[gol]!=-1;
}
int dfs(int x,int rst){
	if (x==gol || !rst) return rst;
	int &i=cur[x],y,tmp,flow=0;
	for (; i; i=nxt[i]) if (len[i]){
		y=pnt[i];
		if (d[x]+1==d[y]){
			tmp=dfs(y,min(rst,len[i]));
			if (!tmp) continue;
			flow+=tmp; len[i]-=tmp;
			len[i^1]+=tmp; rst-=tmp;
			if (!rst) break;
		}
	}
	if (!flow) d[x]=-1; return flow;
}
void build(int &k,int l,int r,int p){
	if (l==r){ k=l; return; } else k=++trtot;
	int mid=l+r>>1;
	build(ls[k],l,mid,p); build(rs[k],mid+1,r,p);
	if (!p){
		ins(ls[k],k,inf); ins(rs[k],k,inf);	
	} else{
		ins(k,ls[k],inf); ins(k,rs[k],inf);
	}
}
void ins(int k,int l,int r,int x,int y,int z,int p){
	if (x<=l && r<=y){
		if (!p) ins(k,z,inf); else ins(z,k,inf);
		return;
	}
	int mid=l+r>>1;
	if (x<=mid) ins(ls[k],l,mid,x,y,z,p);
	if (y>mid) ins(rs[k],mid+1,r,x,y,z,p);
}
int MX;
void solve(int l,int r,int u,int v){
	if (l>r) return;
	if (u==v){
		for (; l<=r; l++) ans[q[l]]=u; return;
	}
	int mid=u+v>>1,cnt=r-l+1,i,j,k,x,y; clk++;
	for (i=l; i<=r; i++){
		lb[q[i]]=clk; pos[q[i]]=i-l+1;
	}
	tot=1; for (i=0; i<=gol; i++) fst[i]=0;
	trtot=cnt;
	build(rt1,1,cnt,0); build(rt2,1,cnt,1);
	gol=trtot+1;
	for (i=1; i<=cnt; i++)
		if (a[q[i+l-1]]<=mid) ins(0,i,1); else ins(i,gol,1);	
	for (i=l; i<=r; i++)
		for (j=0; j<g[q[i]].size(); j++){
			x=g[q[i]][j].fi.fi; y=g[q[i]][j].fi.se; k=g[q[i]][j].se;
			for (; x<=y && lb[x]!=clk; x++);
			for (; x<=y && lb[y]!=clk; y--);
			g[q[i]][j].fi=mpr(x,y);	
			if (x>y) continue;
			ins(k?rt2:rt1,1,cnt,pos[x],pos[y],i-l+1,k);
		}
	if (u==1 && v==MX) cerr<<tot<<'\n';
	while (bfs()) dfs(0,inf);
	x=l-1; y=r+1;
	for (i=1; i<=cnt; i++) if (d[i]!=-1) nq[++x]=q[i+l-1];
	for (i=cnt; i; i--) if (d[i]==-1) nq[--y]=q[i+l-1];
	for (i=l; i<=r; i++) q[i]=nq[i];
	solve(l,x,u,mid); solve(y,r,mid+1,v);
}
int main(){
	freopen("sequence.in","r",stdin);
	freopen("sequence.out","w",stdout);
	int tt=clock();
	scanf("%d%d",&n,&m);
	int i,x,y,z,mx=0;
	for (i=1; i<=n; i++){
		scanf("%d",&a[i]); mx=max(mx,a[i]);
	}
	while (m--){
		scanf("%d%d%d%d",&i,&x,&y,&z);
		g[z].pb(mpr(mpr(x,y),i));
	}
	for (i=1; i<=n; i++) q[i]=i;
	MX=mx;
	solve(1,n,1,mx);
	int sum=0;
	for (i=1; i<=n; i++) sum+=abs(a[i]-ans[i]);
	printf("%d\n",sum);
	cerr<<clock()-tt<<'\n';
	return 0;
}

