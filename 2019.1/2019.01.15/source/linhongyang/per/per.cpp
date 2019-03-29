#include<bits/stdc++.h>
#define N 300005
int n,A[N],Max,cnt[40],sum[N];
namespace solve1
{
	int mark[1005][1005],vis[N],getp[N],b[N<<2],tot,deg[N];
	int sta[N],top,find;
	struct node
	{
		int a,b;
	};
	std::vector<node> s[N<<2];
	std::vector<int> e[N];
	void dfs(int x)
	{
		if(find) return;
		sta[++top]=x;vis[x]=1;
		if(top==n) return (void)(find=1);
		std::sort(e[x].begin(),e[x].end());
		for(int j=0;j<e[x].size();j++)
		{
			int v=e[x][j];
			if(vis[v]) continue;
			dfs(v);
			if(find) return;
 		}
 		top--,vis[x]=0;
	}
	void Main()
	{
		int Minv=1e9;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=i;j++) if(i^j)
				Minv=A[i]^A[j],b[++tot]=A[i]^A[j];
		std::sort(b+1,b+1+tot);
		tot=std::unique(b+1,b+1+tot)-b-1;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=i;j++) if(i^j)
			{
				mark[i][j]=mark[j][i]=std::lower_bound(b+1,b+1+tot,A[i]^A[j])-b;
				getp[mark[i][j]]++;
				s[mark[i][j]].push_back((node){i,j});
			}
		int tot0=n,tot1=0;
		for(int i=1;i<=tot;i++) 
		{
			for(int j=0;j<s[i].size();j++) 
			{
				e[s[i][j].a].push_back(s[i][j].b);
				e[s[i][j].b].push_back(s[i][j].a);
				int a=s[i][j].a,b=s[i][j].b;
				if(!deg[a]) tot0--;if(!deg[b]) tot0--;
				if(deg[a]==1) tot1--;if(deg[b]==1) tot1--;
				deg[a]++,deg[b]++;
				if(deg[a]==1) tot1++;if(deg[b]==1) tot1++;
			}
			if(tot0 || tot1>2) continue;
			int st;
			if(!tot1) st=1;
			for(int j=1;j<=n;j++) if(e[j].size()==1) {st=i;break;}
			find=0;top=0;dfs(st);
			if(find)break;
			
		}
		for(int i=1;i<=n;i++) printf("%d ",sta[i]);
		puts("");
	}
}
int main()
{
	freopen("per.in","r",stdin);
	freopen("per.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&A[i]);
	for(int i=1;i<=n;i++)
		for(int j=0;j<=30;j++) 
			if(A[i]>>j&1) cnt[j]++,sum[i]++;
	for(int j=0;j<=30;j++) if(cnt[j] && cnt[j]<n) Max=j;
	if(n<=1000) return solve1::Main(),0;
}
/*
*/
