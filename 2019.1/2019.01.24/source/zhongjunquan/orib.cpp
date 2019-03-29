#include<cstring>
#include<cstdio>
#include<algorithm>
#define N 200100
#define fo(i,a,b) for(int i=a,___=b;i<=___;++i)
#define fd(i,a,b) for(int i=a,___=b;i>=___;--i)
using namespace std;

int x[N],y[N],n,m,top=1,ls,c[N],fir[N],nex[N],to[N],dfl[N],dfr[N],rd[N],f[16][N],deep[N],sta[N];
#define lnk(x,y) to[++top]=y,nex[top]=fir[x],fir[x]=top

void dfs(int x){
	dfl[x]=++top;++deep[x];
	for(int i=fir[x];i;i=nex[i])if(f[0][x]^to[i])
		f[0][to[i]]=x,deep[to[i]]=deep[x],dfs(to[i]),rd[to[i]]=i>>1;
	dfr[x]=top;
}

struct LCT{
	int cap[N],siz[N],sm[N],son[N][2],fa[N],pre[N],rev[N],all[N],alv[N];
	void init(){
		fo(i,1,n){
			siz[i]=all[i]=cap[i]=1;sm[i]=alv[i]=0;
			son[i][0]=son[i][1]=fa[i]=pre[i]=0;rev[i]=0;
		}
	}
	int pd(int x){return son[fa[x]][1]==x;}
	void reverse(int x){
		if(!x)return;
		swap(son[x][0],son[x][1]);rev[x]^=1;
	}
	void down(int x){
		if(!x)return;
		if(rev[x])reverse(son[x][0]),reverse(son[x][1]),rev[x]=0;
	}
	void up(int x,int e){
		int T=0;for(;x^e;x=fa[x])sta[++T]=x;while(T)down(sta[T--]);
	}
	void update(int x){
		siz[x]=1+siz[son[x][0]]+siz[son[x][1]];
		cap[x]=all[x]+cap[son[x][0]]+cap[son[x][1]];
		sm[x]=sm[son[x][0]]+sm[son[x][1]]+alv[x];
	}
	void rotate(int x){
		int y=fa[x],w=pd(x);
		fa[x]=fa[y];son[fa[x]][pd(y)]=x;fa[y]=x;pre[x]=pre[y];
		son[y][w]=son[x][w^1];fa[son[y][w]]=y;son[x][w^1]=y;update(y);
	}
	void splay(int x,int e){
		up(x,e);for(;fa[x]^e;rotate(x))
			if(fa[fa[x]]^e)(pd(x)^pd(fa[x]))?rotate(x):rotate(fa[x]);update(x);
	}
	void access(int x){
		int y=0;
		for(;x;y=x,x=pre[x]){
			splay(x,0);pre[son[x][1]]=x;fa[son[x][1]]=0;
			all[x]+=cap[son[x][1]]-cap[y];
			alv[x]+=sm[son[x][1]]-sm[y];
			son[x][1]=y;pre[y]=0;fa[y]=x;update(x);
		}
	}
	void makeroot(int x){
		access(x);reverse(x);splay(x,0);
	}
	void link(int x,int y){
		makeroot(x);makeroot(y);
		pre[x]=y;alv[y]+=sm[x];all[y]+=cap[x];
	}
	void cut(int x,int y){
		makeroot(x);access(y);splay(y,0);splay(x,y);
		son[y][pd(x)]=0;pre[x]=fa[x]=0;update(y);
	}
	int capable(int x){makeroot(x);return cap[x];}
	void add(int x,int v){makeroot(x);alv[x]+=v;sm[x]+=v;}
	int sum(int x){makeroot(x);return sm[x];}
	bool connected(int x,int y){
		makeroot(x);access(y);splay(y,0);
		while(x&&x^y)x=fa[x];return x==y;
	}
}T1,T2;

void change(int r,int w){
	int u=x[r],v=y[r];
	if(w==1){
		if(c[r]==2)T2.link(u,v);else
		if(c[r]==3){
			int a=T1.capable(u),b=T1.capable(v);
			T2.add(u,-b),T2.add(v,-a);
			T2.link(u,v),T1.link(u,v);
		}
	}else if(w==2){
		if(c[r]==1)T2.cut(u,v);else
		if(c[r]==3){
			int a=T1.capable(u),b=T1.capable(v);
			T2.add(u,-b),T2.add(v,-a);T1.link(u,v);
		}
	}else if(w==3){
		int a,b;
		if(c[r]==1){
			T1.cut(u,v);T2.cut(u,v);
			a=T1.capable(u);b=T1.capable(v);
		}else{
			T1.cut(u,v);
			a=T1.capable(u);b=T1.capable(v);
		}T2.add(u,b);T2.add(v,a);
	}c[r]=w;
}
int ask(int s){return T1.capable(s)+T2.sum(s);}
int accessible(int s,int t,int ori){
	if(s==t)return 1;
	if(T1.connected(s,t))return 1;
	int a,b,tx,nx;
	if(dfl[s]<=dfl[t]&&dfr[s]>=dfl[t]){
		tx=t;fd(i,16,0)if(deep[f[i][tx]]>deep[s])tx=f[i][tx];nx=rd[tx];
	}else nx=rd[s];
	if(c[nx]==3)return T2.connected(x[nx]+y[nx]-s,t)?1:0;
	else{
		int tmp=c[nx];
		change(nx,3);b=ask(t);change(nx,tmp);
		return ori==b?0:1;
	}
}

int main(){
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
	scanf("%d %d",&n,&m);
	T1.init();T2.init();
	fo(i,1,n-1){
		int u,v,s;scanf("%d %d %d",&u,&v,&s);
		x[i]=u;y[i]=v;c[i]=s;lnk(u,v);lnk(v,u);
		if(s==1)T2.link(u,v);
		if(s<3) T1.link(u,v);
	}top=0;dfs(1);
	fo(j,1,16)fo(i,1,n)f[j][i]=f[j-1][f[j-1][i]];
	fo(i,1,n-1)if(c[i]==3){
		int a=T1.capable(x[i]),b=T1.capable(y[i]);
		T2.add(x[i],b);T2.add(y[i],a);
	}ls=0;
	fo(i,1,m){
		int r,w,s,t,u,v;scanf("%d %d %d %d",&r,&w,&s,&t);
		r^=ls;w^=ls;s^=ls;t^=ls;ls=0;
		change(r,w);ls=ask(s);
		printf("%d %d\n",ls,accessible(t,s,ls));
	}
}
