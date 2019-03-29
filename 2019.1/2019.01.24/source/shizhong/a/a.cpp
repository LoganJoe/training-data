#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#include<queue>
#include<cmath>
#include<cstdlib>
#define LL long long
#define LD long double
using namespace std;
const int NN=10000000 +117;
const int MM=1 +117;
const int mod=998244353;
int read(){
	int fl=1,x;char c;
	for(c=getchar();(c<'0'||c>'9')&&c!='-';c=getchar());
	if(c=='-'){fl=-1;c=getchar();}
	for(x=0;c>='0'&&c<='9';c=getchar())
		x=(x<<3)+(x<<1)+c-'0';
	return x*fl;
}
void open(){
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
}
void close(){
	fclose(stdin);
	fclose(stdout);
}

LL ksm(LL a,LL b){
	LL ret=1;
	while(b){
		if(b&1){
			ret=ret*a%mod;
		}
		a=a*a%mod;
		b>>=1;
	}
	return ret;
}
int m,n;
int div(int x){
	int top=sqrt(x);
	for(int i=2;i<=top;++i){
		if(x%i==0){
			printf("%d",i);
			int cnt=0;
			while(x%i==0){
				x/=i;
				++cnt;
			}
			printf("^%d\n",cnt);
		}
	}
	if(x!=1){
		printf("%d\n",x);
	}
}
LL cnt[2][NN]={};
int main(){
	open();
	n=read();
//	div(n);
	int k=read();
	cnt[0][0]=1;
	int now=0;
	for(int i=1;i<k;++i){
		now^=1;
		for(int i=0;i<=n;++i){
			cnt[now][i]=0;
		}
		for(int j=0;j<i;++j){
			LL sum=0;
			for(int t=j;t<=n;t+=i){
				cnt[now][t]=sum;
				sum+=cnt[now^1][t];
				sum%=mod;
			}
		}
	/*	printf("%d:\n",i);
		for(int i=0;i<=n;++i){
			printf("%lld ",cnt[now][i]);
		}
		putchar('\n');*/
	}
	LL ans=1;
	for(int i=1;i<=k;++i){
		ans=ans*(n+1-i)%mod;
		ans=ans*ksm(i,mod-2)%mod;
	}
	for(int i=1;i<=n;++i){
		ans-=cnt[now][i]*(n-i+1);
		ans%=mod;
	}
	ans=(ans+mod)%mod;
	printf("%lld\n",ans);
	close();
	return 0;
}