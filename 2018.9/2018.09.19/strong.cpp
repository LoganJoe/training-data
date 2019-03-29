#include<bits/stdc++.h>
#define N 2005
#define mod 1000000007
int n,A[N],fac[N],inv[N],f[N],ans[N],res;
int mul(int x){return x>=mod?x-mod:x;}
class BIT
{
	int t[N];
	int lowbit(int x){return x&(-x);}
public:
	void add(int x,int v){for(int i=x;i<N;i+=lowbit(i)) t[i]=mul(t[i]+v);}
	int ask(int x){int res=0;for(int i=x;i;i-=lowbit(i))res=mul(res+t[i]);return res;}
}T[N];
int main()
{
	freopen("strong.in","r",stdin);
	freopen("strong.out","w",stdout);
	fac[0]=inv[0]=inv[1]=1;
	for(int i=1;i<N;i++) fac[i]=1ll*fac[i-1]*i%mod;
	for(int i=2;i<N;i++) inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
	for(int i=2;i<N;i++) inv[i]=1ll*inv[i]*inv[i-1]%mod;
	scanf("%d",&n); 
	for(int i=1;i<=n;i++) scanf("%d",&A[i]);
	T[0].add(1,1);
	for(int i=1;i<=n;i++) 
		for(int j=i,tp;j>=1;j--)
		tp=T[j-1].ask(A[i]),T[j].add(A[i],tp),ans[j]=mul(ans[j]+tp);
	for(int i=1;i<=n;i++) ans[i]=1ll*ans[i]*fac[n-i]%mod;
	for(int i=n;i;i--)
		for(int j=i-1;j;j--)
			ans[j]=mul(ans[j]+mod-1ll*ans[i]*fac[i]%mod*inv[j]%mod);
	for(int i=1;i<=n;i++) res=mul(res+ans[i]);
	std::cout<<res<<"\n";
}
