#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>

#define Debug(...) fprintf(stderr, __VA_ARGS__)

const int MAXN = 1E5 + 7;
const int MAXM = 1E5 + 7;

int N, Q;

int input[MAXN][3];


struct node_edge
{
	int to;
	int w;
	struct node_edge *next;
};
struct node_edge pool[MAXM << 1], *mem = pool;
#define GetNewEdge() (mem++)
struct node_edge *pH[MAXN] = {NULL};
struct node_edge *edge[MAXM << 1][2] = {NULL};
inline void AddDirectedEdge(int u, int v, int w, int id)
{
	struct node_edge *e = GetNewEdge();
	e -> to = v;
	e -> w = w;
	e -> next = pH[u];
	pH[u] = e;
	if(edge[id][0] == NULL)
	{
		edge[id][0] = e;
	}
	else
	{
		edge[id][1] = e;
	}
	return;
}
/*
namespace CHAIN
{
	int array[MAXN];
	
	void Work()
	{
		int i;
		for(i = 1; i <= N; ++i)
		{
			array[i] = input[i][2];
		}
	}
}
*/

namespace PLAIN
{
	bool on_path[MAXN];
	int path_next_node[MAXN];
	int path_next_w[MAXN];
	int without_limit[MAXN];
	int limit[MAXN];
	bool reached[MAXN];
	
	
	bool FindPath(int now, int parent, int target)
	{
		on_path[now] = false;
		if(now == target)
		{
			on_path[now] = true;
			return true;
		}
		for(struct node_edge *p = pH[now]; p != NULL; p = p -> next)
		{
			if(p -> to != parent)
			{
				if(FindPath(p -> to, now, target))
				{
					on_path[now] = true;
					path_next_node[now] = p -> to;
					path_next_w[now] = p -> w;
					return true;
				}
				else
				{
					on_path[now] = false;
				}
			}
		}
		return on_path[now];
	}
	
	void Dfs(int now, int parent)
	{
		limit[now] = 0;
		without_limit[now] = 1;
		for(struct node_edge *p = pH[now]; p != NULL; p = p -> next)
		{
			if(p -> to != parent && !on_path[p -> to])
			{
				Dfs(p -> to, now);
				if(p -> w == 3)
				{
					limit[now] += without_limit[p -> to];
					without_limit[now] += 0;
				}
				else if(p -> w == 1)
				{
					without_limit[now] += without_limit[p -> to];
					limit[now] += limit[p -> to];
				}
				else
				{
					without_limit[now] += without_limit[p -> to];
					limit[now] += 0;
				}
			}
		}
		return;
	}
	
	int dfn[MAXN], dfn_clock = 0;
	int size[MAXN];
	int fa[MAXN];
	int fa_w[MAXN];
	void PreDfs(int now, int parent)
	{
		dfn[now] = ++dfn_clock;
		size[now] = 1;
		fa[now] = parent;
		for(struct node_edge *p = pH[now]; p != NULL; p = p -> next)
		{
			if(p -> to != parent)
			{
				fa_w[p -> to] = p -> w;
				PreDfs(p -> to, now);
				size[now] += size[p -> to];
			}
		}
		return;
	}
	
	inline bool InSubTree(int p, int root)
	{
		return dfn[p] >= dfn[root] && dfn[p] < dfn[root] + size[root];
	}
	
	
	void Work()
	{		
		int i, j;
		for(i = 1; i <= N - 1; ++i)
		{
			AddDirectedEdge(input[i][0], input[i][1], input[i][2], i);
			AddDirectedEdge(input[i][1], input[i][0], input[i][2], i);
		}
		
		PreDfs(1, 1);
		
		int x, w, s, t;
		int ans = 0;
		for(i = 1; i <= Q; ++i)
		{
			memset(on_path, false, sizeof(on_path));
			memset(without_limit, 0, sizeof(without_limit));
			memset(limit, 0, sizeof(limit));
			memset(reached, false, sizeof(reached));
			
			scanf("%d %d %d %d", &x, &w, &s, &t);
			x ^= ans;
			w ^= ans;
			s ^= ans;
			t ^= ans;
			
			edge[x][0] -> w = w;
			edge[x][1] -> w = w;
			
			FindPath(1, 1, s);
			
			/*
			for(j = 1; j <= N; ++j)
			{
			//  Debug("%d ", on_path[j] ? 1 : 0);
			}
			//Debug("\n");
			*/
			
			for(j = 1; j <= N; ++j)
			{
				if(on_path[j])
				{
					Dfs(j, j);
					//Debug("limit[%d] = %d, without_limit[%d] = %d\n", j, limit[j], j, without_limit[j]);
				}
			}
			
			int now = 1;
			int amount_no_limit = 0;
			int amount_limit = 0;
			while(now != s)
			{
				amount_no_limit += without_limit[now];
				amount_limit += limit[now];
				
				if(path_next_w[now] == 3)
				{
					amount_limit = amount_no_limit;
					amount_no_limit = 0;
				}
				else if(path_next_w[now] == 2)
				{
					amount_limit = 0;
				}
				
				//++amount_no_limit;
				
				now = path_next_node[now];
			}
			amount_no_limit += without_limit[s];
			amount_limit += limit[s];
			
			printf("%d ", amount_no_limit + amount_limit);
			ans = amount_no_limit + amount_limit;
			
			bool skip = false;
			bool limit = false;
			int pos = t;
			if(!InSubTree(pos, s))
			{
				while(!InSubTree(s, pos))
				{
					if(limit)
					{
						if(fa_w[pos] != 1)
						{
							printf("0\n");
							skip = true;
							break;
						}
					}
					else
					{
						if(fa_w[pos] == 3)
						{
							limit = true;
						}
					}
					pos = fa[pos];
				}
				if(skip)
				{
					continue;
				}
			}
			
			FindPath(pos, pos, s);
			while(pos != s)
			{
				if(limit)
				{
					if(path_next_w[pos] != 1)
					{
						printf("0\n");
						skip = true;
						break;
					}
				}
				else
				{
					if(path_next_w[pos] == 3)
					{
						limit = true;
					}
				}
				pos = path_next_node[pos];
			}
			if(skip)
			{
				continue;
			}
			
			printf("1\n");
			
		}
		
		return;
	}
}
					
					
int main()
{
	//freopen("B.in", "r", stdin);
	
	int i;
	bool chain = true;
	scanf("%d %d", &N, &Q);
	for(i = 1; i <= N - 1; ++i)
	{
		scanf("%d %d %d", &input[i][0], &input[i][1], &input[i][2]);
		if(input[i][0] != i || input[i][1] != i + 1)
		{
			chain = false;
		}
	}
	
	
	/*
	if(chain)
	{
		CHAIN::Work();
	}
	*/
	
	PLAIN::Work();
	
	return 0;
}