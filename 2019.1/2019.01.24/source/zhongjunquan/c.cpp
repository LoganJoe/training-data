#include<cstring>
#include<cstdio>
#include<algorithm>
#define N 200100
#define fo(i,a,b) for(int i=a,___=b;i<=___;++i)
#define fd(i,a,b) for(int i=a,___=b;i>=___;--i)
using namespace std;
int a[N],n,l[N],r[N],s[1024];
int main(){
	int _;scanf("%d",&_);
	while(_--){
		scanf("%d",&n);
		fo(i,1,n)a[i]=-1;
		fo(i,1,n){
			int x;scanf("%d",&x);
			if(x<0)scanf("%d %d",&l[x],&r[x]);else a[i]=x;
		}
		fd(i,n/2,2)if(n/2-i&1)a[i*2]=min(a[l[i*2]],a[r[i*2]]);else a[i*2]=max(a[l[i*2]],a[r[i*2]]);
		printf("%d\n",(n/2&1)?max(a[2],a[3]):min(a[2],a[3]));
	}
}
