#include<cstring>
#include<cstdio>
#define mo 998244353
#define fo(i,a,b) for(int i=a,___=b;i<=___;++i)
using namespace std;

int n,m,t,s[10][2000],c[2000][2000];

int main(){
	s[0][0]=1;
	fo(i,0,7){
		fo(j,0,1500){
			s[i][i+j]=(s[i][i+j]+s[i][j])%mo;
			if(i==0&&j==0)s[i][j]=1;
			s[i+1][j+i+1]=(s[i+1][j+i+1]+s[i][j])%mo;
		}
	}
	fo(i,0,1500){
		c[i][0]=c[i][i]=1;fo(j,1,i-1)c[i][j]=(c[i-1][j]+c[i-1][j-1])%mo;
	}
	scanf("%d %d",&n,&m);
	int ans=c[n][m];
	fo(i,m,n)ans=(ans+mo-1ll*s[m-1][i]*(n-i+1)%mo)%mo;
	printf("%d",ans);
}
