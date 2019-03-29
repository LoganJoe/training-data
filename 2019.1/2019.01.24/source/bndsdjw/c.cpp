#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
using namespace std;
const ll mod=1e9+7;
int read(){
	int x=0,flag=1;
	char ch=getchar();
	while(ch!='-'&&(ch<'0'||ch>'9')) ch=getchar();
	if(ch=='-') flag=-1,ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return x*flag;
}
struct node{
	int ch[2];
	int val;
}t[15];
bool vis[15];
int n;
void readin(){
	n=read();
	int x,y,z;
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=n;i++){
		x=read();
		if(~x) t[i].val=x,vis[i]=true;
		else t[i].ch[0]=read(),t[i].ch[1]=read(),t[i].val=-1;
	}
}
int dfs(bool ty){
	if(vis[1]){
		return t[1].val;
		cout<<t[1].val<<endl;
	}
	int res,x;
	if(!ty) res=0;
	else res=1e9+7;
	for(int i=1;i<=n;i++){
		if(!vis[i]&&(~t[t[i].ch[0]].val)&&(~t[t[i].ch[1]].val)){
			vis[i]=true;
			if(!ty) t[i].val=max(t[t[i].ch[0]].val,t[t[i].ch[1]].val);
			else t[i].val=min(t[t[i].ch[0]].val,t[t[i].ch[1]].val);
			if(!ty) res=max(res,dfs(ty^1));
			else res=min(res,dfs(ty^1));
			vis[i]=false,t[i].val=-1;
		}
	}
	return res;
}
int main(){
	int T=read();
	while(T--){
		readin();
		printf("%d\n",dfs(0));
	}
	return 0;
}
