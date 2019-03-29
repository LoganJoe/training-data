#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
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
#define N 300009
using namespace std;

int n,m,tot=1,cnt,tp,bg[N],ed[N],val[N],p[N],blk[N],num[N],ch[N][26],d[N],lf[N],rg[N];
ll A,B,C,ans,sum[N]; pii h[N]; pll b[N]; pair<int,pii > q[N]; char s[N];
ll calc(int x){ return (ll)x*(x+1)>>1; } 
int counter; 
struct node{ int x,y,id; }a[N];
bool cmp(node u,node v){
	return blk[u.x]<blk[v.x] || blk[u.x]==blk[v.x] && u.y>v.y;
}
void dlt(int x){
	int l=h[x].fi,r=h[x].se;
	ans+=calc(r-l-1)-calc(x-l-1)-calc(r-x-1);
	q[++tp]=mpr(l,h[l]); q[++tp]=mpr(r,h[r]);
	h[l].se=r; h[r].fi=l;
}
void ins(int k,int x){
	x*=val[k];
	int i,j,tmp,c,now=1;
	for (i=bg[k],j=1; i<=ed[k]; i++,j++){
		c=s[i]-'a';
		if (!ch[now][c]) d[ch[now][c]=++tot]=d[now]+1; now=ch[now][c];
		tmp=-(sum[now]>0 && A*j+B*sum[now]>=C);
		sum[now]+=x;
		tmp+=(sum[now]>0 && A*j+B*sum[now]>=C);
		if (tmp<0)
			if (!(--num[p[j]])){ counter++; dlt(p[j]); }
		if (tmp>0){ counter++; num[p[j]]++; }
	}
}
ll gcd(ll x,ll y){ return y?gcd(y,x%y):x; }
void opt(ll x,ll y){
	ll z=gcd(x,y);
	printf("%lld/%lld\n",x/z,y/z);
}
int main(){
	freopen("string.in","r",stdin);
	freopen("string.out","w",stdout);
	scanf("%d%lld%lld%lld",&n,&A,&B,&C);
	int i,j,k,l,mx=0,tt=clock();
	for (i=1; i<=n; i++) scanf("%d",&val[i]);
	for (i=1; i<=n; i++){
		bg[i]=ed[i-1]+1;
		scanf("%s",s+bg[i]); ed[i]=bg[i]+strlen(s+bg[i])-1;
		mx=max(mx,ed[i]-bg[i]+1);
	}
	for (i=1; i<=mx; i++) scanf("%d",&p[i]);
	scanf("%d",&m);
	for (i=1; i<=m; i++){
		scanf("%d%d",&a[i].x,&a[i].y); a[i].id=i;	
	}
	blk[1]=1;
	int sz=ceil(1.*ed[n]/sqrt(m));
	for (i=2,j=1; i<=n; i++){
		blk[i]=blk[i-1];
		if (ed[i]-bg[j]+1>sz){
			blk[i]++; j=i;
		}
	}
	sort(a+1,a+m+1,cmp);
	cnt=blk[n];
	cerr<<"cnt:"<<cnt<<"\n";
	for (i=1; i<=n; i++){
		k=blk[i];
		if (!lf[k]) lf[k]=i; rg[k]=i;
	}
	num[mx+1]=1;
	int last; ll now,all=calc(mx); 
	for (i=k=1; i<=cnt; i++){
		for (j=lf[i]; j<=n; j++) ins(j,1);
		ans=0;
		for (j=1,last=0; j<=mx+1; j++) if (num[j]){
			h[j].fi=last; h[last].se=j;
			ans+=calc(j-last-1); last=j;	
		}
		for (j=n; k<=m && blk[a[k].x]==i; k++){
			while (j>a[k].y) ins(j--,-1);
			tp=0; now=ans;
			for (l=lf[i]; l<a[k].x; l++) ins(l,-1);
			b[a[k].id]=mpr(all-ans,all);
			for (l=lf[i]; l<a[k].x; l++) ins(l,1);
			for (; tp; tp--) h[q[tp].fi]=q[tp].se;
			ans=now;
		}
		while (j>=lf[i]) ins(j--,-1);
		//for (j=1; j<=tot; j++) assert(sum[j]==0);
		//for (j=1; j<=mx; j++) assert(num[j]==0);
	}
	for (i=1; i<=m; i++) opt(b[i].fi,b[i].se);
	cerr<<"time: "<<clock()-tt<<'\n';
	cerr<<"cnt: "<<counter<<'\n';
	return 0;
}

