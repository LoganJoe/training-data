#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define mod 998244353
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
#define N 2000009
using namespace std;

int n,m,tot,trtot,fst[N],pnt[N],nxt[N],fa[N],d[N],sz[N],son[N],anc[N];
int inv[N],ch[N][10],sum[N],res[N],rt[N],tg[N],bg[N],ed[N];
pii f[N],ans[N]; vi h[N],g[N]; char s[N]; bool bo[N];
int read(){
	int x=0; char ch=getchar();
	while (ch<'0' || ch>'9') ch=getchar();
	while (ch>='0' && ch<='9'){ x=x*10+ch-'0'; ch=getchar(); }
	return x;	
}
int getinv(int x){ return x<N?inv[x]:mod-(ll)mod/x*getinv(mod%x)%mod; }
pii operator +(pii u,pii v){
	return mpr((u.fi+v.fi)%mod,(u.se+v.se)%mod);
}
pii operator *(pii u,pii v){
	return mpr((ll)u.fi*v.fi%mod,((ll)u.se*v.fi+v.se)%mod);
}
void add(int x,int y){
	pnt[++tot]=y; nxt[tot]=fst[x]; fst[x]=tot;
}
void dfs(int x){
	int i,y; sz[x]=1;
	for (i=fst[x]; i; i=nxt[i]){
		y=pnt[i];
		if (y!=fa[x]){
			fa[y]=x; d[y]=d[x]+1;
			dfs(y); sz[x]+=sz[y];
			if (sz[y]>sz[son[x]]) son[x]=y;
		}
	}
}
void dvd(int x,int tp){
	int i,y; anc[x]=tp;
	if (son[x]) dvd(son[x],tp);
	for (i=fst[x]; i; i=nxt[i]){
		y=pnt[i];
		if (y!=fa[x] && y!=son[x]) dvd(y,y);	
	}
}
int lca(int x,int y){
	for (; anc[x]!=anc[y]; x=fa[anc[x]])
		if (d[anc[x]]<d[anc[y]]) swap(x,y);
	return d[x]<d[y]?x:y;	
}
void maintain(int k){
	int i,y,tmp=(!bo[k]);
	f[k]=ans[k]=mpr(0,0); sum[k]=0;
	for (i=0; i<10; i++) if (sum[y=ch[k][i]]){
		tmp++;
		ans[k]=ans[k]+ans[y]; f[k]=f[k]+f[y];
		sum[k]+=sum[y];
	}
	sum[k]+=(tg[k]>0 || sum[k]>0);
	//cerr<<k<<' '<<tg[k]<<'\n';
	if (!sum[k]) return;
	if (!tg[k]){
		assert((tmp+mod-f[k].fi)%mod);
		f[k].fi=getinv((tmp+mod-f[k].fi)%mod);
		f[k].se=(ll)(f[k].se+tmp)*f[k].fi%mod;
	} else f[k]=mpr(0,0);
	ans[k]=f[k]+f[k]*ans[k];
}
int mrg(int x,int y){
	if (!sum[x] || !sum[y]) return sum[x]?x:y;
	int i;
	for (i=0; i<10; i++) ch[x][i]=mrg(ch[x][i],ch[y][i]);
	tg[x]+=tg[y]; bo[x]|=bo[y]; maintain(x);
	return x;
}
void ins(int &k,int p,int x,int y,int z){
	if (!k){
		k=++trtot; bo[k]=(x==bg[p]);
	}
	assert(trtot+5<N);
	if (x>y){
		tg[k]+=z; maintain(k); return;
	}
	ins(ch[k][s[x]-'0'],p,x+1,y,z); maintain(k);
}
void solve(int x){
	int i,y;
	for (i=fst[x]; i; i=nxt[i]){
		y=pnt[i];
		if (y!=fa[x]){
			fa[y]=x; solve(y);
			rt[x]=mrg(rt[x],rt[y]);
		}
	}
	for (int p:h[x]) ins(rt[x],p,bg[p],ed[p],1);
	for (int p:g[x]) ins(rt[x],p,bg[p],ed[p],-2);
	res[x]=(ll)ans[rt[x]].se*getinv(sum[rt[x]])%mod;
}
int main(){
	int tt=clock();
	n=read();
	int i,x,y;
	inv[0]=inv[1]=1;
	for (i=2; i<N; i++) inv[i]=mod-(ll)mod/i*inv[mod%i]%mod;
	for (i=1; i<n; i++){
		x=read(); y=read();
		add(x,y); add(y,x);
	}
	d[1]=1; dfs(1); dvd(1,1);
	m=read();
	for (i=1; i<=m; i++){
		x=read(); y=read();
		bg[i]=ed[i-1]+1;
		scanf("%s",s+bg[i]); ed[i]=bg[i]+strlen(s+bg[i])-1;
		h[x].pb(i); h[y].pb(i);
		g[fa[lca(x,y)]].pb(i);
	}
	solve(1);
	for (i=1; i<=n; i++) printf("%d\n",res[i]);
	cerr<<clock()-tt<<'\n';
	return 0;
}

