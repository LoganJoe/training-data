#include<cstring>
#include<cstdio>
#include<algorithm>
#define fo(i,a,b)for(int i=a,_e=b;i<=_e;i++)
#define fd(i,a,b)for(int i=b,_e=a;i>=_e;i--)
#define min(a,b)(a<b?a:b)
#define max(a,b)(a>b?a:b)
#define ll long long
#define gc()(it==is?it=(is=in)+fread(in,1,Q,stdin),(it==is?EOF:*is++):*is++)
using namespace std;
const int N=1e5+5,Q=(1<<21)+1;
int T,n,fh,a[N],s[N][2],ans,op;
char in[Q],*is=in,*it=in,c;
void R(int &n){
	for(n=0,fh=1;(c=gc())<'0'||c>'9';)if(c=='-')fh=-1;
	for(;c<='9'&&c>='0';c=gc())n=n*10+(c&15);n*=fh;
}
int go(int op){
	if(a[1]>-1)return a[1];
	int ans=op?0:1e9;
	fo(i,1,n)if(a[i]==-1&&a[s[i][0]]>-1&&a[s[i][1]]>-1){
		a[i]=op?max(a[s[i][0]],a[s[i][1]]):min(a[s[i][0]],a[s[i][1]]);
		int k=go(!op);
		ans=op?max(ans,k):min(ans,k);
		a[i]=-1;
	}
	return ans;
}
int main(){
//	freopen("c.in","r",stdin);
	for(R(T);T--;){
		R(n);
		fo(i,1,n){
			R(a[i]);
			if(a[i]==-1)R(s[i][0]),R(s[i][1]);
		}
		if(n>10){
			op=1;
			fd(i,1,n/2-1){
				if(op)a[i]=max(a[i+2],a[i+3]);
				else a[i]=min(a[i+2],a[i+3]);
				op^=1;
			}
			if(op)ans=max(a[2],a[3]);else ans=min(a[2],a[3]);
		}else ans=go(1);
		printf("%d\n",ans);
	}
}
