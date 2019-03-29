#include<cstring>
#include<cstdio>
#include<algorithm>
#define fo(i,a,b)for(int i=a,_e=b;i<=_e;i++)
#define fd(i,a,b)for(int i=b,_e=a;i>=_e;i--)
#define min(a,b)(a<b?a:b)
#define max(a,b)(a>b?a:b)
#define ll long long
#define link(x,y,w)(b[++js]=(ed){y,w,la[x]},la[x]=js)
#define ff(x)for(int i=la[x];i;i=b[i].ne)
#define gc()(it==is?it=(is=in)+fread(in,1,Q,stdin),(it==is?EOF:*is++):*is++)
using namespace std;
const int N=1e5+5,Q=(1<<21)+1;
int n,q,la[N],x,y,w,s,t,an,bz,js;
struct ed{int y,w,ne;}b[N*2];
char in[Q],*is=in,*it=in,c;
void R(int &n){
	for(n=0;(c=gc())<'0'||c>'9';);
	for(;c<='9'&&c>='0';c=gc())n=n*10+(c&15);
}
void go(int x,int y,int no){
	if(x==t)bz=1;an++;
	ff(x)
		if(b[i].y!=y&&(!no||b[i].w<3))
			go(b[i].y,x,no|(b[i].w>1));
}
int main(){
//	freopen("b.in","r",stdin);
	R(n);R(q);
	fo(i,2,n)R(x),R(y),R(w),link(x,y,w),link(y,x,w);
	for(;q--;){
		R(x);R(w);R(s);R(t);
		x^=an;w^=an;s^=an;t^=an;
		b[x*2-1].w=b[x*2].w=w;
		bz=an=0;
		go(s,0,0);
		printf("%d %d\n",an,bz);
	}
}
