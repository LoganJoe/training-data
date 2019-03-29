#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#define maxn 11
using namespace std;

int n,i,j,k,a[maxn],ans,p[maxn],bz[maxn],lp[maxn];

void dfs(int i,int mx){
	if (mx>ans) return;
	if (i>n){
		if (mx<ans){
			for(int j=1;j<=n;j++) lp[j]=p[j];
			ans=mx;
		}
		return;
	}
	for(int j=1;j<=n;j++) if (!bz[j])
		bz[j]=1,p[i]=j,dfs(i+1,(i==1)?mx:max(a[j]^a[p[i-1]],mx)),bz[j]=0;
}

int main(){
//	freopen("per.in","r",stdin);
//	freopen("per.out","w",stdout);
	scanf("%d",&n);
	for(i=1;i<=n;i++) scanf("%d",&a[i]);
	ans=2e9;
	dfs(1,0);
	for(i=1;i<=n;i++) printf("%d ",lp[i]);
}
