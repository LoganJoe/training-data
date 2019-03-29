#include <bits/stdc++.h>
#define rep(i,l,r) for(int i=l;i<=r;i++)
#define per(i,r,l) for(int i=r;i>=l;i--)
#define redge(x,y) if(e[x].size()) for(int i=0,y=e[x][0];i<e[x].size();i++,y=i<e[x].size()?e[x][i]:0) if(!vis[y])
#define ll long long
#define N 100005
int n,q;
std::vector<int> e[N];
int vis[N],sz[N],hv[N],pre[N],ldis[N],dis[N];
std::vector<int> dcnt[N],ldcnt[N];
std::vector<ll> dsum[N],ldsum[N];
std::vector<int> D[N];
void get(int x){
	vis[x]=1;sz[x]=1;hv[x]=-1;
	redge(x,y){
		get(y);
		sz[x]+=sz[y];
		if(hv[x]==-1||sz[y]>sz[hv[x]]) hv[x]=y;
	}
	vis[x]=0;
}
void get2(int c,int x){
	vis[x]=1;
	if(ldis[x]>=0){
		//printf("-%d %d %d\n",c,x,ldis[x]);
		while(ldcnt[c].size()<=ldis[x]) ldcnt[c].push_back(0),ldsum[c].push_back(0);
		ldcnt[c][ldis[x]]++;ldsum[c][ldis[x]]+=ldis[x];
	}ldis[x]=dis[x];
	D[x].push_back(dis[x]);
	//printf("+%d %d %d\n",c,x,dis[x]);
	while(dcnt[c].size()<=dis[x]) dcnt[c].push_back(0),dsum[c].push_back(0);
	dcnt[c][dis[x]]++;dsum[c][dis[x]]+=dis[x];
	redge(x,y){
		dis[y]=dis[x]+1;
		get2(c,y);
	}
	vis[x]=0;
}
void solve(int las,int x){
	//std::cerr<<las<<' '<<x<<std::endl;
	get(x);
	int c=x;
	while(hv[c]>0&&sz[hv[c]]>sz[x]/2) c=hv[c];
	pre[c]=las;
	dcnt[c].clear();dsum[c].clear();
	ldcnt[c].clear();ldsum[c].clear();
	dis[c]=0;get2(c,c);
	rep(i,1,int(dcnt[c].size())-1) dcnt[c][i]+=dcnt[c][i-1],dsum[c][i]+=dsum[c][i-1];
	rep(i,1,int(ldcnt[c].size())-1) ldcnt[c][i]+=ldcnt[c][i-1],ldsum[c][i]+=ldsum[c][i-1];
	
	vis[c]=1;
	redge(c,y) solve(c,y);
}
void S(int x,int d,int _d,int&cnt,ll&sum){
	if(d>=0){
		d=std::min(d,int(dcnt[x].size())-1);
		//printf("?%d %d %d\n",x,d,dcnt[x][d]);
		cnt+=dcnt[x][d];sum+=dsum[x][d];
		sum+=1ll*dcnt[x][d]*_d;
	}
}
void T(int x,int d,int _d,int&cnt,ll&sum){
	if(d>=0){
		d=std::min(d,int(ldcnt[x].size())-1);
		//printf("?%d %d %d\n",x,d,ldcnt[x][d]);
		cnt-=ldcnt[x][d];sum-=ldsum[x][d];
		sum-=1ll*ldcnt[x][d]*_d;
	}
}
int L[233],tot;
void Q(int x,int d,int&cnt,ll&sum){
	//std::cerr<<x<<' '<<d<<std::endl;
	
	L[tot=1]=x;
	while(pre[L[tot]]) L[tot+1]=pre[L[tot]],tot++;
	cnt=0;sum=0;
	rep(i,1,tot){
		int _d=D[x][tot-i];
		S(L[i],d-_d,_d,cnt,sum);
		if(i>1) T(L[i-1],d-_d,_d,cnt,sum);
	}
	
	//std::cerr<<"123\n";
	//printf("%d %d %d %lld\n",x,d,cnt,sum);
}
double f[N];
int bf(int x,int y){
	//std::cerr<<x<<' '<<y<<std::endl;
	int dx=D[x].size()-1,dy=D[y].size()-1;
	if(dx<dy) std::swap(x,y),std::swap(dx,dy);
	int xx=x,yy=y;
	while(dx>dy) dx--,xx=pre[xx];
	while(xx!=yy) dx--,xx=pre[xx],yy=pre[yy];
	//std::cerr<<"fin\n";
	return D[x][dx]+D[y][dx];
}
int main(){
	freopen("branching.in","r",stdin);
	freopen("branching.out","w",stdout);
	
	scanf("%d%d",&n,&q);
	rep(i,1,n) e[i].clear();
	rep(i,1,n-1){
		int x,y;
		scanf("%d%d",&x,&y);
		e[x].push_back(y);
		e[y].push_back(x);
	}
	rep(i,1,n) vis[i]=0;
	rep(i,1,n) ldis[i]=-1;
	rep(i,1,n) D[i].clear();
	solve(0,1);
	rep(i,1,n){
		int L=0,R=n,Mid;
		int t1;ll t2;
		while(L<=R){
			Mid=L+R>>1;
			Q(i,Mid,t1,t2);
			if(1ll*t1*Mid-t2<=n) L=Mid+1,f[i]=Mid+(n-(1.*t1*Mid-t2))/t1;
			else R=Mid-1;
		}
	}
//	rep(i,1,n) printf(i<n?"%.6f ":"%.6f\n",f[i]);
	
	while(q--){
		int x,y;
		scanf("%d%d",&x,&y);
		printf("%.8f\n",std::min(1.*bf(x,y),f[y]));
	}
	
	fclose(stdin);
	fclose(stdout);
	return 0;
}
