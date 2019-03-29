#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
const int mod=998244353;
int f[1005][1005];
int main(){
	int n,k;
	scanf("%d%d",&n,&k);
	f[0][0]=1;
	int ans=0;
	for(int Cur=1;Cur<=n-1;Cur++){
		for(int Slt=k-1;Slt;Slt--)
			for(int S=0;S<=n+2;S++)
				(f[Slt][S]+=f[Slt-1][max(0,S-Cur)])%=mod;	
		(ans+=f[k-1][Cur+2])%=mod;
	}
	printf("%d\n",ans);
	return 0;
}
