#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
const int N=100005;
struct E{
	int to,next;
	int kind;
}edge[N<<1];
int head[N],tot=1;
void addedge(int u,int v,int kind){
	edge[++tot].to=v;
	edge[tot].next=head[u];
	head[u]=tot;
	edge[tot].kind=kind;
}
void fixedge(int eid,int kind){
	edge[eid<<1].kind=kind;
	edge[eid<<1|1].kind=kind;
}
int n;
int ans;
int lastans;
bool vis[N];
void dfs(int u,int fa,bool over){
	vis[u]=1;
	++ans;
	for(int i=head[u];i;i=edge[i].next){
		int v=edge[i].to;
		if(v!=fa){
			if(edge[i].kind==1)
				dfs(v,u,over);
			else if(edge[i].kind==2)
				dfs(v,u,1);
			else if(!over)
				dfs(v,u,1);
		}
	}
}
int main(){
	int q;
	scanf("%d%d",&n,&q);
	for(int i=1;i<n;i++){
		int u,v,kind;
		scanf("%d%d%d",&u,&v,&kind);
		addedge(u,v,kind);
		addedge(v,u,kind);
	}
	while(q--){
		int x,w,s,t;
		scanf("%d%d%d%d",&x,&w,&s,&t);
		x^=lastans;
		w^=lastans;
		s^=lastans;
		t^=lastans;
		fixedge(x,w);
		ans=0;
		memset(vis,0,sizeof(vis));
		dfs(s,s,0);
		printf("%d %d\n",ans,vis[t]);
		lastans=ans;
	}
	return 0;
}
