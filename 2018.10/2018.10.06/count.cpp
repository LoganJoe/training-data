#include<bits/stdc++.h>
#define N 1000010
#define mod 998244353
#define ll long long
int A[N*3],B[N*3],clc,len,rev[N*3],g1,g2,invn,fac[N],inv[N],ine[N];
int L,R,K;
ll Pow(ll x,ll k)
{
	int t=1;
	for(;k;k>>=1,x=x*x%mod) if(k&1)t=t*x%mod;
	return t; 
}
int mul(int x){return x>=mod?x-mod:x;}
void NTT(int *s,int opt)
{
	for(int i=1;i<len;i++) if(i<rev[i]) std::swap(s[i],s[rev[i]]);
	for(int i=1;i<len;i<<=1)
	{
		int wn=Pow(opt>0?g1:g2,(mod-1)/(i<<1));
		for(int j=0;j<len;j+=i<<1)
			for(int k=0,w=1;k<i;w=1ll*w*wn%mod,k++)
			{
				int A=s[j+k],B=1ll*s[i+j+k]*w%mod;
				s[j+k]=mul(A+B),s[i+j+k]=mul(A-B+mod);
			}
	}
	if(opt<0) for(int i=0;i<len;i++) s[i]=1ll*s[i]*invn%mod;
}
void process()
{
	for(len=1;len<=K<<1;len<<=1,clc++);
	g1=3,g2=Pow(3,mod-2),invn=Pow(len,mod-2);
	for(int i=0;i<=len;i++) rev[i]=(rev[i>>1]>>1)|((i&1)<<clc-1);
	fac[0]=inv[0]=inv[1]=1;
	for(int i=1;i<=K+2;i++) fac[i]=1ll*fac[i-1]*i%mod;
	for(int i=2;i<=K+2;i++) ine[i]=inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
	for(int i=2;i<=K+2;i++) inv[i]=1ll*inv[i-1]*inv[i]%mod;
	//warning::n-:k
}
void getstrling()
{
	for(int i=0;i<=K;i++) A[i]=Pow(i,K)*inv[i]%mod,B[i]=i&1?(mod-inv[i])%mod:inv[i];
	NTT(A,1),NTT(B,1);
	for(int i=0;i<len;i++) A[i]=1ll*A[i]*B[i]%mod;	
	NTT(A,-1);
}
int C(int a,int b){return 1ll*fac[a]*inv[b]%mod*inv[a-b]%mod;}
int solve(int n)
{
	if(n<=0) return 0;
	int res=0;
	for(int i=0,bim=n+1;i<=std::min(n+1,K);i++,bim=1ll*bim*(n-i+1)%mod*ine[i+1]%mod)
		res=mul(res+1ll*A[i]*fac[i]%mod*bim%mod);
	return res+1;
}
int main()
{
	freopen("count.in","r",stdin);
	freopen("count.out","w",stdout);
	scanf("%d%d%d",&L,&R,&K);
	process();
	getstrling();
	printf("%d\n",mul(solve(R)-solve(L-1)+mod));
}
