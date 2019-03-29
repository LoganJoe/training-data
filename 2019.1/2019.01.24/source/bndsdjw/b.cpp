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
const int MAXN=100005;
int head[MAXN],to[MAXN*2],nxt[MAXN*2],val[MAXN*2],num;
int s1[MAXN],s12[MAXN],ff[MAXN];
int n,q,t;
bool ck;
void add(int u,int v,int z){
	nxt[num]=head[u],head[u]=num,to[num]=v,val[num]=z,num++;
	nxt[num]=head[v],head[v]=num,to[num]=u,val[num]=z,num++;
}
int dfs12(int u,int fa){
//	cout<<"t2"<<" "<<u<<" "<<fa<<endl;
	if(u==t) ck=true;
	int res=1;
	for(int i=head[u];~i;i=nxt[i]){
		if(to[i]!=fa&&val[i]!=3){
			res+=dfs12(to[i],u);
		}
	}
	return res;
}
int dfs(int u,int fa){
//	cout<<"t1"<<" "<<u<<" "<<fa<<endl;
	if(u==t) ck=true;
	int res=1;
	for(int i=head[u];~i;i=nxt[i]){
		if(to[i]!=fa){
			if(val[i]==1) res+=dfs(to[i],u);
			else res+=dfs12(to[i],u);
		}
	}
	return res;
}
void readin(){
	memset(head,-1,sizeof(head));
	memset(nxt,-1,sizeof(nxt));
	n=read(),q=read();
	int x,y,z;
	for(int i=1;i<n;i++){
		x=read(),y=read(),z=read();
		add(x,y,z);
	}
}
void solve(){
	int x,w,s,ans=0;
	for(int i=1;i<=q;i++){
		ck=false;
		x=read()^ans,w=read()^ans,s=read()^ans,t=read()^ans;
		val[x*2-2]=val[x*2-1]=w;
		ans=dfs(s,0);
		printf("%d %d\n",ans,ck);
	}
}
int main(){	
	readin();
	solve();
	return 0;
}
