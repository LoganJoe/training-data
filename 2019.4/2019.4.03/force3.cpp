#include<bits/stdc++.h> 
#define N 20
int n,m,k,la,a[N],ans;
bool vis[N];
void dfs(int dep,int Max)
{
	if(dep>k)
	{
		if(la) ans+=abs(a[m]-la);
		la=a[m];
		for(int i=1;i<=k;i++) std::cout<<a[i]<<" ";std::cout<<std::endl;
		return;
	}
	if(Max>n) return;
	for(int i=Max;i<=n;i++) a[dep]=i,dfs(dep+1,i+1);
}
int main()
{
	scanf("%d%d%d",&n,&k,&m);
	dfs(1,1);
	std::cout<<ans<<std::endl;
	return 0;
}

