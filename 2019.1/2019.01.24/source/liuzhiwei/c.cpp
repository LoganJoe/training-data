# include<cstdio>
# include<cstring>
# include<algorithm>
using namespace std;
const int N = 1e5 + 5;
int ch[N][2],v[N];
int n,T;
inline void dfs(int x,int opt)
{
	if (ch[x][0]) dfs(ch[x][0],opt ^ 1);
	if (ch[x][1]) dfs(ch[x][1],opt ^ 1);
	if (ch[x][0] && ch[x][1])
	{
		if (opt) v[x] = max(v[ch[x][0]],v[ch[x][1]]);
		else v[x] = min(v[ch[x][0]],v[ch[x][1]]);
	}
}
int main()
{
	scanf("%d",&T);
	while (T--)
	{
		scanf("%d",&n); memset(v,0,sizeof(v)),memset(ch,0,sizeof(ch));
		for (int i = 1 ; i <= n ; ++i)
		{
			scanf("%d",&v[i]);
			if (v[i] == -1) scanf("%d%d",&ch[i][0],&ch[i][1]);
		}
		dfs(1,n & 1);
		printf("%d\n",v[1]);
	}
	return 0;
}
