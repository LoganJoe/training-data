#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;

int T,n,val[100010],son[100010][2],ans,deep[100010];
bool pass3,pass4;

void p4(){
	int p = 1;
	ans = max(val[n],val[n-1]);
	for(int i = n-2;i > 1;i--){
		if(i&1){
			if(p){
				ans = min(ans,val[i]);
			}else{
				ans = max(ans,val[i]);
			}
			p ^= 1;
		}
	}
	printf("%d\n",ans);
}

void dfs(int p,int dep){
	deep[p] = dep;
	dfs(son[p][0],dep+1);
	dfs(son[p][1],dep+1);
}

int main(){
	cin >> T;
	for(int t = 1;t <= T;t++){
		scanf("%d",&n);
		ans = 0;
		pass3 = 1;
		pass4 = 1;
		for(int i = 1;i <= n;i++){
			scanf("%d",&val[i]);
			if(val[i] == -1){
				scanf("%d%d",&son[i][0],&son[i][1]);
				if(i > 1 && (i&1)){
					pass4 = 0;
				}
			}
		}
		if(pass4){
			p4();
			continue;
		}
		dfs(1,1);
		for(int i = 1;i <= n;i++){
			if(val[i] != -1){
				if(!ans){
					ans = deep[i];
				}else if(ans != deep[i]){
					pass3 = 0;
					break;
				}
			}
		}
		if(pass3){
			p3();
			continue;
		}
	}
	return 0;
}
