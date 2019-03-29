#include <bits/stdc++.h>
#define rep(i,l,r) for(int i=l;i<=r;i++)
#define per(i,r,l) for(int i=r;i>=l;i--)
#define mo 998244353
#define N 100005
int powmod(int x,int y){
	int z=1;
	while(y){
		if(y&1) z=1ll*z*x%mo;
		y>>=1;x=1ll*x*x%mo; 
	}
	return z;
}
int inv(int x){
	return powmod(x,mo-2);
}
int n,m,q,x,y,c,ans;
std::vector<int> e[N];
int t[N],dep[N];
int cn,l[N],s[N];
void dfs(int x,int d){
	dep[x]=d;
	rep(i,0,e[x].size()-1){
		int y=e[x][i];
		if(dep[y]){
			if(dep[y]>=dep[x]-1) continue;
			t[dep[x]-dep[y]]++;
			t[1]-=dep[x]-dep[y];
			continue;
		}
		dfs(y,d+1);
	}
}
int main(){
	freopen("inkmaster.in","r",stdin);
	freopen("inkmaster.out","w",stdout);
	
	scanf("%d%d%d",&n,&m,&q);
	rep(i,1,n) e[i].clear();
	rep(i,1,m){
		scanf("%d%d",&x,&y);
		e[x].push_back(y);
		e[y].push_back(x);
	}
	memset(t,0,sizeof(t));t[1]=n-1;
	memset(dep,0,sizeof(dep));
	dfs(1,1);
	cn=0;rep(i,1,n) if(t[i]) l[++cn]=i,s[cn]=t[i];
	l[0]=0;
	while(q--){  
		scanf("%d",&c);
		int ans=1,las=1,temp;
		int mul=1ll*inv(c)*(c-1)%mo;
		rep(i,1,cn){
			las=1ll*las*powmod(c-1,l[i]-l[i-1])%mo;
			temp=1ll*(las+(l[i]&1?1:-1))*mul%mo;
			ans=1ll*ans*powmod(temp,s[i])%mo;
		}
		ans=1ll*ans*c%mo;
		printf("%d\n",ans);
	}
	
	fclose(stdin);
	fclose(stdout);
	return 0;
}
