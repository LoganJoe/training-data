#include<bits/stdc++.h>
using namespace std;
template<class T>void gi(T &x){
	int f;char c;
	for(f=1,c=getchar();c<'0'||c>'9';c=getchar())if(c=='-')f=-1;
	for(x=0;c<='9'&&c>='0';c=getchar())x=x*10+(c&15);x*=f;
}
typedef unsigned long long ll;
const int N=2e5+10;
int n,m,head[N],nxt[N*4],to[N*4],num=0,Head[N],b[N],a[N];
ll s[N],ss[N],A,B,C,ans=0,in[N];
inline void link(int x,int y){nxt[++num]=head[x];to[num]=y;head[x]=num;}
inline void Link(int x,int y){nxt[++num]=Head[x];to[num]=y;Head[x]=num;}
int main(){
	freopen("girls.in","r",stdin);
	freopen("girls.out","w",stdout);
	int x,y;
	cin>>n>>m>>A>>B>>C;
	for(int i=1;i<=m;i++)gi(x),gi(y),link(x,y),link(y,x),in[x]++,in[y]++;
	for(int i=0,u;i<n;i++)
		for(int j=head[i];j;j=nxt[j])
			if(in[u=to[j]]>in[i]|| (in[u]==in[i] && u>i))Link(i,u);
	//+0						  
	for(int i=0;i<n;i++){
		s[i]=s[i-1]+i*A;
		ss[i]=ss[i-1]+s[i-1]+B*i*i;
		ans+=ss[i-1]+1ll*i*(i-1)/2*C*i;
	}
	for(int i=0;i<n;i++){
		m=0;
		for(int j=head[i];j;j=nxt[j])b[a[++m]=to[j]]=i+1;
		sort(a+1,a+m+1);s[m+1]=0;
		//-1
		for(int j=1;j<=m && a[j]<i;j++){
			ans-=(a[j]*A+i*B)*(n-i-1)+1ll*(i+n)*(n-i-1)/2*C;
			ans-=(a[j]*A+i*C)*(i-a[j]-1)+1ll*(a[j]+i)*(i-a[j]-1)/2*B;
			ans-=(a[j]*B+i*C)*a[j]+1ll*a[j]*(a[j]-1)/2*A;
		}
		//+2
		for(int j=1;j<=m && a[j]<i;j++){
			s[j]=s[j-1]+a[j];
			ans+=s[j-1]*A+(j-1)*(a[j]*B+C*i);
		}
		for(int j=m;j>=1 && a[j]>i;j--){
			s[j]=s[j+1]+a[j];
			ans+=s[j+1]*C+(m-j)*(a[j]*B+A*i);
		}
		for(int j=1;j<m;j++)
			if(a[j]<i && a[j+1]>i)ans+=s[j]*A*(m-j)+i*B*j*(m-j)+s[j+1]*C*j;
		//-3
		for(int j=Head[i];j;j=nxt[j])
			for(int k=Head[to[j]];k;k=nxt[k]){
				if(b[to[k]]!=i+1)continue;
				int c[3]={i,to[j],to[k]};
				sort(c,c+3);
				ans-=A*c[0]+B*c[1]+C*c[2];
			}  
	}
	cout<<ans<<endl;
	return 0;
}
