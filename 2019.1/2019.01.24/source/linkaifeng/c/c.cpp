#include<cstdio>
#include<iostream>
#include<cstring>
#define x1 c[x][0]
#define x2 c[x][1]
using namespace std;
const int N=1e5+10;
int n,f[N][2],c[N][2],T,s[N];
void dfs(int x){
	s[x]=0;
	if (!x1)return;
	dfs(x1);dfs(x2);
	s[x]=s[x1]^s[x2]^1;
	if (s[x]){
		if (s[x1])
			f[x][0]=max(max(f[x1][0],f[x1][1]),max(f[x2][0],f[x2][1])),
			f[x][1]=min(min(f[x1][0],f[x1][1]),min(f[x2][0],f[x2][1]));
		else 
			f[x][0]=max(f[x1][0],f[x2][0]);
			f[x][1]=min(f[x1][1],f[x2][1]);
	}
	else {
		f[x][0]=max(min(f[x1][0],f[x2][1]),min(f[x1][1],f[x2][0]));
		f[x][1]=min(max(f[x1][0],f[x2][1]),max(f[x1][1],f[x2][0]));
	}
}
int main(){
	for (cin>>T;T--;){
		memset(f,0,sizeof f);
		memset(c,0,sizeof c);
		memset(s,0,sizeof s);
		cin>>n;
		int can=1;
		for (int i=1;i<=n;i++){
			int x;scanf("%d",&x);
			if (x==-1)scanf("%d%d",&c[i][0],&c[i][1]);
			else f[i][0]=f[i][1]=x,c[i][0]=c[i][1]=0;
			if (i==1){if (c[i][0]!=2||c[i][1]!=3)can=0;}
			else {
				if ((i&1)&&(x==-1))can=0;
				if (!(i&1)&&(c[i][0]!=i+2&&c[i][1]!=i+3)&&i+2<n)can=0;
			}
		}
		dfs(1);
		if (can){
			for (int x=n-3,j=1;x>=0;x-=2,j^=1){
				if (x==0)x=1;
				if (j)f[x][0]=max(f[x1][0],f[x2][0]);
				else f[x][0]=min(f[x1][0],f[x2][0]);
			}
		}
		cout<<f[1][0]<<endl;
	}
}
