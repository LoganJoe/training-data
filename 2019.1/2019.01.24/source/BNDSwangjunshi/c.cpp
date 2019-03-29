#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>

#define Max(a, b) ((a > b) ? (a) : (b))
#define Min(a, b) ((a > b) ? (b) : (a))

const int MAXN = 1E5 + 7;

int T;

int N;

int son[MAXN][2];
int weight[MAXN];
bool sp[MAXN];
bool leaf[MAXN];

namespace special1
{
	void Work()
	{
		int type, i;
		scanf("%d", &N);
		for(i = 1; i <= N; ++i)
		{
			scanf("%d", &type);
			if(type == -1)
			{
				scanf("%d %d", &son[i][0], &son[i][1]);
			}
			else
			{
				weight[i] = type;
			}
		}
	
		int p = (N + 1) >> 1;
		bool D = true;
		while(p >= 1)
		{
			if(D)
			{
				weight[p] = Max(weight[son[p][0]], weight[son[p][1]]);
			}
			else
			{
				weight[p] = Min(weight[son[p][0]], weight[son[p][1]]);
			}
			D = !D;
			p >>= 1;
		}
		printf("%d\n", weight[1]);
		return;
	}
}


namespace plain
{
	int num_leaf;
	
	void Work()
	{
		memset(sp, false, sizeof(sp));
		int type, i;
		scanf("%d", &N);
		for(i = 1; i <= N; ++i)
		{
			scanf("%d", &type);
			if(type == -1)
			{
				scanf("%d %d", &son[i][0], &son[i][1]);
				leaf[i] = false;
			}
			else
			{
				++num_leaf;
				leaf[i] = true;
				weight[i] = type;
			}
		}
		for(i = 1; i <= N; ++i)
		{
			if(leaf[son[i][0]] && leaf[son[i][1]])
			{
				sp[i] = true;
			}
			else
			{
				sp[i] = false;
			}
		}
		
		Dfs(num_leaf, true);
		
		
	}
		
int main()
{
	//freopen("C.in", "r", stdin);
	
	scanf("%d", &T);
	while(T--)
	{
		special::Work();
	}
}
