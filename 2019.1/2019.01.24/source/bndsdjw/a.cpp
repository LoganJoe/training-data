#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
using namespace std;
const ll mod=998244353;
const int MAXN=100005;
int read(){
	int x=0,flag=1;
	char ch=getchar();
	while(ch!='-'&&(ch<'0'||ch>'9')) ch=getchar();
	if(ch=='-') flag=-1,ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return x*flag;
}
int n,m;
ll f[205][100005],ans;
int mop(int x,int y){
	return x+y>=mod?x+y-mod:x+y;
}
ll ksm(ll x,ll k){
	ll res=1;
	while(k){
		if(k%2!=0) res=res*x%mod;
		k/=2,x=x*x%mod;
	}
	return res;
}
ll c[MAXN],inc[MAXN];
void init(){
	c[0]=1;
	for(int i=1;i<=n;i++) c[i]=c[i-1]*i%mod;
	inc[n]=ksm(c[n],mod-2);
	for(int i=n-1;i>=0;i--) inc[i]=inc[i+1]*(i+1)%mod;
}
ll calc(ll x,ll y){
	return c[x]*inc[y]%mod*inc[x-y]%mod;
}
int main(){
	n=read(),m=read();
	init();
	if(m>=n){
		printf("0\n");
		return 0;
	}
	for(int i=1;i<=n;i++) f[1][i]=(ll)i*(i+1)/2;
	for(int i=2;i<m;i++){
		for(int j=i;j<=n;j++){
			f[i][j]=mop(f[i-1][j-i],f[i][j-i]);        
		} 
	}
	ans=calc(n,m)-f[m-1][n];
	if(ans<0) ans+=mod;
	printf("%lld\n",ans); 
	return 0;
}                                                                                                                                                                                                                                                                                                                                                                               
