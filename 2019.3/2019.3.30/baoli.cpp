#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<string>
#include<algorithm>
#include<queue>
#include<vector>
#include<set>
#include<map>
using std::cin;using std::cerr;
using std::max;using std::min;
#define N 200005
#define P 19990213
#define mod 998244353
#define mod2 19990817
#define ll long long
#define ull unsigned long long
#define db double
#define lb(x) std::lower_bound(so+1,so+1+tot,x)-so 
#define dbg1(x) cerr<<#x<<"="<<(x)<<" "
#define dbg2(x) cerr<<#x<<"="<<(x)<<"\n"
int n,ecnt,last[N],val[N],po[N],ha[N],l,r,mid,ans[N];
struct road{int to,nex;}e[N];
void adde(int u,int v) {e[++ecnt]=(road){v,last[u]},last[u]=ecnt;}
class HashTable
{
	int ecnt,last[mod2+5];
	struct road{int to,v,nex;}e[N];
public:
	void add(int x,int v) {e[++ecnt]=(road){x,v,last[x%mod2]},last[x%mod2]=ecnt;}
	int ask(int x)
	{
		for(int k=last[x%mod2];k;k=e[k].nex) if(e[k].to==x) return e[k].v;
		return 0;
	}
}H;
int askhash(int l,int r) {return (ha[r]-(ll)ha[l-1]*po[r-l+1]%mod+mod)%mod;}
void dfs1(int x,int h)
{
	if(h) H.add(h,x);
	for(int k=last[x];k;k=e[k].nex) dfs1(e[k].to,((ll)h*P+val[e[k].to])%mod);
}
void dfs2(int x,int d)
{
	if(d>1)
	{
		for(l=2,r=d;l<r;) mid=l+r>>1,H.ask(askhash(mid,d))?r=mid:l=mid+1;
		ans[x]=H.ask(askhash(l,d));
	}
	for(int k=last[x];k;k=e[k].nex) ha[d+1]=((ll)ha[d]*P+val[e[k].to])%mod,dfs2(e[k].to,d+1);
}
int main()
{
	freopen("magic.in","r",stdin);
	freopen("magic.ans","w",stdout);
	scanf("%d",&n),po[0]=1;
	for(int i=1,a;i<=n;i++) scanf("%d",&a),adde(a,i);
	for(int i=1;i<=n;i++) scanf("%d",&val[i]),po[i]=(ll)po[i-1]*P%mod;
	dfs1(0,0),dfs2(0,0);
	for(int i=1;i<=n;i++) printf("%d ",ans[i]);
	return 0;
}
