#include<bits/stdc++.h>
#define N 5005
int d,n,m,deg[N][N],ans,QwQ;
class Graph
{
	int f[N],rnk[N];
	std::vector<int>s[N];
	int find(int x)
	{
		return f[x]==x?f[x]:f[x]=find(f[x]);
	}
public:
	void merge(int a,int b)
	{
		int fx=find(a),fy=find(b);
		if(fx==fy) return ;
		if(rnk[fx]<rnk[fy]) std::swap(fx,fy);
		f[fy]=fx,rnk[fx]+=rnk[fy];
		for(int i=0;i<s[fx].size();i++)
			for(int j=0;j<s[fy].size();j++)
			{
				//QwQ++;
				deg[s[fx][i]][s[fy][j]]++;
				deg[s[fy][j]][s[fx][i]]++;
				if(deg[s[fx][i]][s[fy][j]]==d) ans+=2;
			}
		for(int j=0;j<s[fy].size();j++) s[fx].push_back(s[fy][j]);
		s[fy].clear();
	}
	void init()
	{
		for(int i=1;i<=n;i++) f[i]=i,rnk[i]=1,s[i].push_back(i);
	}
}T[205];
int main()
{
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);
	scanf("%d%d%d",&d,&n,&m);ans=n;
	for(int i=1;i<=d;i++) T[i].init();
	while(m--)
	{
		int a,b,k;scanf("%d%d%d",&a,&b,&k);
		T[k].merge(a,b);
		printf("%d\n",ans);
	}
	//printf("%d\n",QwQ);
}
