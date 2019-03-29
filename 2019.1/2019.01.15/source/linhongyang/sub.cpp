#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#define maxn 3005
#define maxm 6005
using namespace std;

int n,m,a[maxn],i,j,k,p,q,f[2][maxm],ans;

void dg(int x,int sum,int len){
	if (x>n){
		if (sum==0) 
			ans=max(ans,len);
		return;
	}
	dg(x+1,sum^a[x],len+1);
	dg(x+1,sum,len);
}

int main(){
//	freopen("sub.in","r",stdin);
//	freopen("sub.out","w",stdout);
	scanf("%d",&n);
	for(i=1;i<=n;i++) scanf("%d",&a[i]),m=max(m,1<<(int)log2(a[i])+1);
	if (n<=20){
		ans=0;
		dg(1,0,0);
		printf("%d\n",ans);
		return 0;
	} 
	f[0][0]=0; for(i=1;i<=m;i++) f[0][i]=-1;
	for(i=0;i<n;i++){
		p=i&1,q=p^1;
		for(j=0;j<=m;j++) f[q][j]=f[p][j];
		for(j=0;j<=m;j++) if (f[p][j]!=-1) 
			f[q][j^a[i+1]]=max(f[q][j^a[i+1]],f[p][j]+1);
	}	
	printf("%d\n",f[n&1][0]);
}

