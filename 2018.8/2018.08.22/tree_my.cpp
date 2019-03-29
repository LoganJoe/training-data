#include<bits/stdc++.h>
#define DEBUG 0
#define $ if(DEBUG)
#define dbg1(x) $ std::cerr << #x << "=" << x << " ";
#define dbg2(x) $ std::cerr << #x << "=" << x << "\n";
#define dbg3(x) $ for(auto v:x) std::cerr<<v<<" ";std::cerr<<"\n"
#define dbg4(x) $ std::cerr<<__FUNCTION__<<"() L"<<__LINE__<<":->: "#x"="<<(x)<<"\n"
const int N = 70005, M = 280, Sz = 280;
typedef long long ll;

int n, m, type, head[N], ecnt = 1, block[N];
int cnt[M][N], deep[N], in[N], out[N], pos[N], Log[N << 1], pre[N << 1][20], tim, idx;
ll ans, lastans;
char ch[10];
struct edge{int v, w, next;}e[N<<1];
void add (int u, int v, int w) { e[++ecnt] = { v,w,head[u] }; head[u] = ecnt; }
class Block_1
{
	ll t1[N], t2[M];
public:
	void add (int l, int r, ll v)
	{
		if (block[l] == block[r]) { for (int i = l; i <= r; i++) t1[i] += v; return; }
		for (int i = l; i <= block[l] * Sz; i++) t1[i] += v;
		for (int i = block[l] + 1; i < block[r]; i++) t2[i] += v;
		for (int i = (block[r] - 1)*Sz + 1; i <= r; i++) t1[i] += v;
	}
	ll ask (int x) { return t1[x] + t2[block[x]]; }
}A;
class Block_2
{
	ll t1[N], t2[M];
public:
	void add (int x, ll v) { if (x <= n) t1[x] += v, t2[block[x]] += v; }
	ll ask (int x)
	{
		ll res = 0;
		for (int i = 1; i < block[x]; i++) res += t2[i];
		for (int i = (block[x] - 1)*Sz + 1; i <= x; i++) res += t1[i];
		return res;
	}
}B[M];
void dfs (int u, int fa)
{
	deep[u] = deep[fa] + 1, cnt[block[u]][u]++;
	in[u] = ++tim; pre[pos[u] = ++idx][0] = u;
	for (int i = head[u]; i; i = e[i].next)
	{
		int v = e[i].v; if (v == fa) continue;
		dfs (v, u), pre[++idx][0] = u;
		for (int i = 1; i <= block[n]; i++) cnt[i][u] += cnt[i][v];
	}out[u] = tim;
}
int d_min(int x,int y){ return deep[x] < deep[y] ? x : y; }
void process ()
{
	for (int i = 2; i <= n << 1; i++) Log[i] = Log[i >> 1] + 1;
	for (int j = 1; j < 20; j++)
		for (int i = 1; i + (1 << j) - 1 <= idx; i++)
			pre[i][j] = d_min (pre[i][j - 1], pre[i + (1 << j - 1)][j - 1]);
	for (int i = 1; i <= block[n]; i++)
		for (int j = 1; j <= n; j++) cnt[i][j] += cnt[i - 1][j];
}
int lca (int x, int y)
{
	x = pos[x], y = pos[y];
	if (x > y) std::swap (x, y);
	int k = Log[y - x + 1];
	return d_min (pre[x][k], pre[y - (1 << k) + 1][k]);
}
void change (int x, int y, ll v)
{
	if (deep[x] < deep[y]) std::swap (x, y);
	A.add (in[x], out[x], v);
	for (int i = 1; i <= block[n]; i++)
	{
		ll amt = std::min (n, i*Sz) - 2 * cnt[i][x];
		$ printf("  %d\n",-amt);
		B[i].add (1, v*cnt[i][x]);
		B[i].add (in[x], amt * v);
		B[i].add (out[x]+1, -amt * v);
	}
}
ll ask (int x, int y)
{
	if (y == 0) return 0;
	ll res = B[block[y] - 1].ask (in[x]);
	$ printf("pr:%d %d %lld\n",block[y]-1,in[x],res);
	for (int i = (block[y] - 1)*Sz + 1; i <= y; i++)
		res += A.ask (in[x]) + A.ask (in[i]) - A.ask (in[lca (x, i)]) * 2;
	return res;
}
int main ()
{
	scanf ("%d%d%d", &n, &m, &type);
	for (int i = 1; i <= n; i++) block[i] = (i - 1) / Sz + 1;
	for (int i = 1; i < n; i++)
	{
		int u, v, w; scanf ("%d%d%d", &u, &v, &w);
		add (u, v, w), add (v, u, w);
	}
	dfs (1, 0); process ();
	for (int i = 2; i <= ecnt; i += 2) change (e[i].v, e[i ^ 1].v, e[i].w);
	while (m--)
	{ 
		int a, b, c;
		scanf ("%s %d%d", ch, &a, &b);
		if (type)a ^= lastans, b ^= lastans;
		if (ch[0] == 'm')
		{
			change (e[a << 1].v, e[(a << 1) ^ 1].v, b - e[a << 1].w);
			e[a << 1].w = e[(a << 1) ^ 1].w = b;
		}
		else
		{
			scanf ("%d", &c); if (type) c ^= lastans;
			printf ("%lld\n", lastans = ask (c, b) - ask (c, a - 1));
			lastans %= n;
		}
	}
}
