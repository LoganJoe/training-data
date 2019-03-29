#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
const int N=1e5+10;
int w[N],ne[N],la[N],val[N],n,t;
int vis[N],q,ans,ti;
void link(int x,int y,int z){
	w[++t]=y;
	ne[t]=la[x];
	la[x]=t;
	val[t]=z;
}
int dfs(int x,int s){
	if (vis[x]==ti)return 0;
	int ret=1;vis[x]=ti;
	for (int y=la[x];y;y=ne[y]){
		if (val[y]<3||s==1)ret+=dfs(w[y],max(val[y],s));
	}
	return ret;
}
int main(){
	cin>>n>>q;
	for (int i=1;i<n;i++){
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		link(x,y,z);
		link(y,x,z);
	}
	while (q--){
		int x,w,s,t;
		scanf("%d%d%d%d",&x,&w,&s,&t);
		x^=ans,w^=ans,s^=ans,t^=ans;
		val[x*2]=val[x*2-1]=w;
		ti++;
		ans=dfs(s,1);
		printf("%d %d\n",ans,vis[t]==ti);
	}
}
