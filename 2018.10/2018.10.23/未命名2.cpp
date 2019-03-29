#include<bits/stdc++.h>
#define mod 1000000007
#define N 100005
int n,A[N],fac[N],inv[N],ans;
int C(int a,int b){return 1ll*fac[a]*inv[b]%mod*inv[a-b]%mod;}
int mul(int x){return x>=mod?x-mod:x;}
int main()
{
	freopen("fickle.in","r",stdin);
	freopen("fickle.out","w",stdout); 
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&A[i]);
	fac[0]=inv[0]=inv[1]=1;
	for(int i=1;i<=n;i++) fac[i]=1ll*fac[i-1]*i%mod;
	for(int i=2;i<=n;i++) inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
	for(int i=2;i<=n;i++) inv[i]=1ll*inv[i-1]*inv[i]%mod;
	for(int i=1;i<=n;i++) ans=mul(ans+mul(mod+1ll*((i&1)?1:-1)*C(n,i)*A[i]%mod));
	std::cout<<ans<<"\n";
}
/*
3
10 3 1
*/
