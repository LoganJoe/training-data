#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;

int n,q,ans,x,y,s,t,w,f[100010],e[200010][3],cnt,to[100010][3];
bool vis[100010];

void dfs(int p,int no){
	vis[p] = 1;
	int u;
	for(int i = f[p];i;i = e[i][1]){
		if(no && e[i][2] == 3){
			continue;
		}
		u = e[i][0];
		if(vis[u]){
			continue;
		}
		if(e[i][2] != 1){
			dfs(u,1);
		}else{
			dfs(u,no);
		}
	}
}

int main(){
	cin >> n >> q;
	for(int i = 1;i < n;i++){
		scanf("%d%d%d",&x,&y,&w);
		cnt++;
		to[i][1] = cnt;
		e[cnt][0] = y;
		e[cnt][1] = f[x];
		e[cnt][2] = w;
		f[x] = cnt;
		cnt++;
		to[i][2] = cnt;
		e[cnt][0] = x;
		e[cnt][1] = f[y];
		e[cnt][2] = w;
		f[y] = cnt;
	}
	for(int i = 1;i <= q;i++){
		scanf("%d%d%d%d",&x,&w,&s,&t);
		x ^= ans;w ^= ans;s ^= ans;t ^= ans;
		for(int i = 1;i <= n;i++){
			vis[i] = 0;
		}
		e[to[x][1]][2] = w;
		e[to[x][2]][2] = w;
		dfs(s,0);
		ans = 0;
		for(int i = 1;i <= n;i++){
			ans += vis[i];
		}
		printf("%d %d\n",ans,vis[t]);
	}
	return 0;
}
