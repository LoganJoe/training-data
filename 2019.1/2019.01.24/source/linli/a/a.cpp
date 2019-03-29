#include<cstring>
#include<cstdio>
#include<algorithm>
#define fo(i,a,b)for(int i=a,_e=b;i<=_e;i++)
#define min(a,b)(a<b?a:b)
#define ll long long
using namespace std;
const int N=1e3+5,mo=998244353;
int n,k,f[2][10][N],o;
ll ans,s;
ll ksm(ll x,int y){
	ll t=1;
	for(;y;y>>=1,x=x*x%mo)if(y&1)t=t*x%mo;
	return t;
}
int main(){
	scanf("%d%d",&n,&k);
	f[0][0][0]=1;
	fo(i,1,n){
		o^=1;
		memcpy(f[o],f[!o],sizeof f[o]);
		fo(j,0,k-2)
			fo(l,0,n+1)if(f[!o][j][l]) 
				(f[o][j+1][min(l+i,n+1)]+=f[!o][j][l])%=mo;
	}
	fo(i,0,n+1)ans=(ans+(ll)f[o][k-1][i]*(i-k))%mo;
	s=1;
	fo(i,1,k)s=s*(n-i+1)%mo*ksm(i,mo-2)%mo;
	ans=(ans-s*(k-1)%mo+mo)%mo;
	printf("%lld\n",ans);
}
