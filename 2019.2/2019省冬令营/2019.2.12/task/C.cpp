#include<bits/stdc++.h>
#define N 100005
#define ull unsigned long long
#define P 19990213
int n, S, T, cnt;
char str[N][305];
std::map<ull, int> mp;
class Maxflow
{
	struct edge
	{
		int v, cap, flow, next;
	}e[N<<2];
	int head[N], ecnt, dis[N], vis[N], cur[N];
	bool bfs ()
	{
		for (int i = 0; i <= cnt; i++) dis[i] = vis[i] = 0, cur[i] = head[i];
		std::queue<int>q; q.push (S); vis[S] = 1;
		while (!q.empty ())
		{
			int u = q.front (); q.pop ();
			for (int i = head[u]; i; i = e[i].next)
			{

				int v = e[i].v;
				if (!vis[v] && e[i].cap > e[i].flow)
				{
					dis[v] = dis[u] + 1;
					if (v == T) return 1;
					vis[v] = 1, q.push (v);
				}
			}
		}
		return 0;
	}
	int dfs (int u, int res)
	{
		if (u == T || res == 0) return res;
		int flow = 0, f;
		for (int i = cur[u]; i; i = e[i].next)
		{
			cur[u] = i;
			if (dis[e[i].v] == dis[u] + 1 && (f = dfs (e[i].v, std::min (e[i].cap - e[i].flow, res))) > 0)
			{
				e[i].flow += f; e[i ^ 1].flow -= f;
				flow += f; res -= f;
				if (res == 0) break;
			}
		}
		return flow;
	}
public:
	void pre () 
	{ 
		for (int i = 0; i <= cnt; i++) head[i] = 0;
		ecnt = 1; mp.clear ();
		S = 0, T = n + 1, cnt = n + 1;
		for (int i = 1; i <= n; i++) add (S, i, 1);
	}
	void add (int u, int v, int w)
	{
		e[++ecnt] = { v,w,0,head[u] }; head[u] = ecnt;
		e[++ecnt] = { u,0,0,head[v] }; head[v] = ecnt;
	}
	int Dinic ()
	{
		int sum = 0;
		while (bfs ()) sum += dfs (S, 1e9);
		return sum;
	}
	void print ()
	{
		for (int u = 1; u <= n; u++)
			for (int i = head[u]; i; i = e[i].next)
				if (e[i].v && e[i].cap == e[i].flow) puts (str[e[i].v]);
	}
}mf;
class STR
{
public:
	char s[305];
	int nxt[305][26], lst[26], id, rem, len;
	void build ()
	{
		len = strlen (s + 1);
		for (int i = 0; i < 26; i++) lst[i] = n + 1;
		for (int i = n; ~i; i--)
		{
			for (int j = 0; j < 26; ++j) nxt[i][j] = lst[j];
			lst[s[i] - 'a'] = i;
		//	std::cout << s[i] - 'a' << " " << i << "\n";
		}
	}
	char ch[N];
	void dfs (int u, int dep, int Max, ull ha, bool mark)
	{
		//std::cout << id << " " << u << " " << dep << " " << Max << " " << ha << " " << mark << "\n";
		if (dep && !mp[ha])
		{
			mp[ha] = ++cnt, mf.add (cnt, T, 1);
			if (mark)  strcpy (str[cnt], ch);
		}
		if (dep) rem--, mf.add (id, mp[ha], 1);
		if (dep == Max || rem <= 0) return;
		for (int j = 0; rem && j < 26; ++j) if (nxt[u][j] <= n)
		{
			ch[dep] = 'a' + j;
			dfs (nxt[u][j], dep + 1, Max, ha * P + j + 1, mark);
			ch[dep] = 0;
		}
	}
	void solve (int Max, int mark) { rem = n, dfs (0, 0, Max, 0, mark); }
}A[305];
void solve (int Max, int mark)
{
	mf.pre ();
	for (int i = 1; i <= n; i++) A[i].solve (Max, mark);
}
int main ()
{
	freopen ("diff.in", "r", stdin);
	freopen ("diff.out", "w", stdout);
	scanf ("%d", &n);
	for (int i = 1; i <= n; i++) 
		scanf ("%s", A[i].s + 1), A[i].id = i, A[i].build ();
	int l = 1, r = 301;
	for (int mid; l < r; mid = l + r >> 1, solve (mid, 0), mf.Dinic () == n ? r = mid : l = mid + 1);
	if (l > 300) return puts ("-1"), 0;
	printf ("%d\n", l);
	solve (l, 1), mf.Dinic (), mf.print ();
}
