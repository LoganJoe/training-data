#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
using namespace std;
const ll mod=998244353;
int read(){
	int x=0,flag=1;
	char ch=getchar();
	while(ch!='-'&&(ch<'0'||ch>'9')) ch=getchar();
	if(ch=='-') flag=-1,ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return x*flag;
}
int n,k;
ll ans;
bool vis[1005];
void dfs(int x,int val,int p){
	if(x==k+1){
		if(val<=n+1) ans++;
		return;
	}
	for(int i=p;i<=n;i++){
		dfs(x+1,val+i,i+1);
	}
}
int f[10][1005];
int main(){ 
//	freopen("t1.in","r",stdin);
//	freopen("t1.out","w",stdout);
	for(int i=1;i<=30;i++) f[1][i]=(ll)i*(i+1)/2;
	for(int i=2;i<=7;i++){
		for(int j=i;j<=30;j++){
			f[i][j]=f[i-1][j-i]+f[i][j-i];
		}
	}
	for(int i=1;i<=7;i++){
		for(int j=1;j<=20;j++){
			cout<<f[i][j+1]<<" ";
		}                              
		cout<<endl;
	}
	cout<<endl;
	for(k=1;k<=7;k++){
		ans=0;                             
		for(n=1;n<=20;n++){
			dfs(1,0,1);
			cout<<ans<<" ";
		} 
		cout<<endl;
	}
	return 0;
}
