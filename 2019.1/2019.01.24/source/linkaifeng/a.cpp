#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
typedef long long ll;
const int N=1010,mo=998244353;
int f[N][N][10],q[N][N][10],g[N][N][10],n,K;
ll ans;
int main(){
	cin>>n>>K;
	f[0][0][0]=q[0][0][0]=g[0][0][0]=1;
	for (int i=1;i<=n;i++)q[0][i][0]=g[0][i][0]=1;
	for (int k=1;k<K;k++){
		for (int i=1;i<=n;i++)
		for (int j=1;j<=i;j++)
			f[i][j][k]=q[i-j][j-1][k-1];
		int i=n+1;
		for (int j=1;j<=n;j++)
			f[i][j][k]=g[i-j][j-1][k-1];
		for (int i=n+1;i>=1;i--)
		for (int j=1;j<=n;j++)q[i][j][k]=(q[i][j-1][k]+f[i][j][k])%mo,g[i][j][k]=(q[i][j][k]+g[i+1][j][k])%mo;
	}
	for (int i=1;i<=n+1;i++)
	for (int j=1;j<i;j++)
		ans=(ans+(ll)f[i][j][K-1]*(i-j-1))%mo;
	cout<<ans<<endl;
}
