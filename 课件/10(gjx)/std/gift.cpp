#include<bits/stdc++.h>
using namespace std;
const int N=2010,mod=998244353;
int n,a[N*2],b[N*2],to[N*2],in[N*2],cnt[4];bool vis[N*2];
inline void dfs(int x,int last){
	vis[x]=1;
	if(to[x]){
		if(!vis[to[x]])dfs(to[x],last);
		else cnt[2]++;
	}
	else{
		if(x>n && last>n)cnt[3]++;
		else if(x<=n && last>n)cnt[0]++;
		else if(x>n && last<=n)cnt[1]++;
	}
}
int c[N][N],s[N][N],A[N][N],f[N],g[N],dp[N],ans[N];
inline void calc(int *f,int n){
	for(int i=0;i<=n;i++)
		for(int j=i;j<=n;j++)
			f[i]=(f[i]+1ll*c[n][j]*s[j][i]%mod*A[cnt[3]+n-j][n-j])%mod;
	for(int i=0,t=0;i<=n;i++){
		for(int j=i;j<=n;j++)
			t=(t+1ll*((j-i)&1?-1:1)*f[j]*c[j][i]%mod+mod)%mod;
		f[i]=t;t=0;
	}
}
inline void priwork(){
	c[0][0]=s[0][0]=A[0][0]=1;
	for(int i=1;i<=n;i++){
		c[i][0]=A[i][0]=1;
		for(int j=1;j<=i;j++){
			c[i][j]=(c[i-1][j-1]+c[i-1][j])%mod;
			s[i][j]=(s[i-1][j-1]+1ll*s[i-1][j]*(i-1))%mod;
			A[i][j]=1ll*A[i][j-1]*(i-j+1)%mod;
		}
	}
}
int main(){
  freopen("gift.in","r",stdin);
  freopen("gift.out","w",stdout);
  cin>>n;
  for(int i=1;i<=n;i++)cin>>a[i];
  for(int i=1;i<=n;i++)cin>>b[i];
  memset(vis,1,sizeof(vis));
  for(int i=1;i<=n;i++){
	  int x=a[i]?a[i]:i+n,y=b[i]?b[i]:i+n;
	  vis[x]=vis[y]=0;
	  if(x<=n || y<=n)to[x]=y,in[y]++;
  }
  for(int i=n<<1;i;i--)if(!vis[i] && !in[i])dfs(i,i);
  for(int i=n<<1;i;i--)if(!vis[i])dfs(i,i);
  priwork();
  calc(f,cnt[0]);calc(g,cnt[1]);
  for(int i=0;i<=n;i++)
	  for(int j=0;j<=i;j++)dp[i]=(dp[i]+1ll*f[j]*g[i-j])%mod;
  for(int i=0;i<=n;i++){
	  for(int j=0;j<=i;j++)ans[i]=(ans[i]+1ll*dp[j]*s[cnt[3]][i-j])%mod;
	  ans[i]=1ll*ans[i]*A[cnt[3]][cnt[3]]%mod;
  }
  for(int i=0;i<n;i++)printf("%d ",n-i-cnt[2]>=0?ans[n-i-cnt[2]]:0);
  return 0;
}
