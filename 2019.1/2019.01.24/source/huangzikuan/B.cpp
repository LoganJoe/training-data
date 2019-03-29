#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include <algorithm>
#include <stack>
#include <queue>
#include <map>
#include <iomanip>
#include <assert.h>

using namespace std;

typedef long long ll;
typedef long double db;

const int MAXN = 100005;

int n,q;
int last_ans;

namespace Subtask1
{
	struct Edge
	{
		int to;
		int mrk;
		int nxt;
	}edge[MAXN << 1];
	
	int id = 1;
	int first[MAXN];
	
	void addE(int u,int v,int c)
	{
		edge[++id] = (Edge){v,c,first[u]};
		first[u] = id;
	}
	
	pair<int,bool> dfs(int now,int fa,int T,bool mrk)
	{
		pair<int,bool> res = make_pair(1,now == T);
		for (int i = first[now];i;i = edge[i].nxt)
			if (edge[i].to != fa && (!mrk || edge[i].mrk != 3))
			{
				pair<int,bool> ret = dfs(edge[i].to,now,T,mrk | (edge[i].mrk != 1));
				res.first += ret.first;
				res.second |= ret.second;
			}
		return res;
	}
	
	void solve()
	{
		for (int u,v,c,i = 1;i < n;i++)
		{
			scanf("%d%d%d",&u,&v,&c);
			addE(u,v,c);
			addE(v,u,c);
		}
		for (int x,w,s,t,i = 1;i <= q;i++)
		{
			scanf("%d%d%d%d",&x,&w,&s,&t);
			x ^= last_ans;
			w ^= last_ans;
			s ^= last_ans;
			t ^= last_ans;
			edge[x << 1].mrk = edge[x << 1 | 1].mrk = w; 
			pair<int,bool> res = dfs(s,0,t,0);
			printf("%d %d\n",last_ans = res.first,res.second);
		}
	}
}

namespace Subtask2
{
	const int INF = (1 << 30) - 1;
	
	struct Node
	{
		int l[2];
		int r[2];
	}node[MAXN << 2],buf;
	
	int c[MAXN];
	
	Node merge(const Node &a,const Node &b)
	{
		Node res;
		res.l[0] = min(a.l[0],b.l[0]);
		res.l[1] = min(a.l[1],b.l[1]);
		res.r[0] = max(a.r[0],b.r[0]);
		res.r[1] = max(a.r[1],b.r[1]);
		return res;
	}
	
	void buildtree(int o,int l,int r)
	{
		if (l == r)
		{
			node[o].l[0] = node[o].l[1] = INF;
			node[o].r[0] = node[o].r[1] = -INF;
			if (c[l] == 2)
				node[o].l[0] = node[o].r[0] = l;
			if (c[l] == 3)
				node[o].l[1] = node[o].r[1] = l;
			return;
		}
		int mid = (l + r) >> 1;
		buildtree(o << 1,l,mid);
		buildtree(o << 1 | 1,mid + 1,r);
		node[o] = merge(node[o << 1],node[o << 1 | 1]);
	}
	
	void modify(int o,int l,int r,int p)
	{
		if (l == r)
		{
			node[o].l[0] = node[o].l[1] = INF;
			node[o].r[0] = node[o].r[1] = -INF;
			if (c[l] == 2)
				node[o].l[0] = node[o].r[0] = l;
			if (c[l] == 3)
				node[o].l[1] = node[o].r[1] = l;
			return;
		}
		int mid = (l + r) >> 1;
		if (mid >= p)
			modify(o << 1,l,mid,p);
		else
			modify(o << 1 | 1,mid + 1,r,p);
		node[o] = merge(node[o << 1],node[o << 1 | 1]);
	}
	
	Node query(int o,int l,int r,int x,int y)
	{
		if (x > y)
			return buf;
		if (l >= x && r <= y)
			return node[o];
		int mid = (l + r) >> 1;
		if (mid + 1 > y)
			return query(o << 1,l,mid,x,y);
		if (mid < x)
			return query(o << 1 | 1,mid + 1,r,x,y);
		return merge(query(o << 1,l,mid,x,y),query(o << 1 | 1,mid + 1,r,x,y));
	}
	
	void solve()
	{
		buf.l[0] = buf.l[1] = n;
		buf.r[0] = buf.r[1] = 0;
		for (int u,v,i = 1;i < n;i++)
			scanf("%d%d%d",&u,&v,&c[i]);
		c[0] = c[n] = 3;
		buildtree(1,0,n);
		for (int L,R,p,x,w,s,t,i = 1;i <= q;i++)
		{
			scanf("%d%d%d%d",&x,&w,&s,&t);
			x ^= last_ans;
			w ^= last_ans;
			s ^= last_ans;
			t ^= last_ans;
			c[x] = w;
			modify(1,0,n,x);
			Node l = query(1,0,n,0,s - 1),r = query(1,0,n,s,n);
			p = max(l.r[0],l.r[1]);
			L = query(1,0,n,0,p - 1).r[1] + 1;
			p = min(r.l[0],r.l[1]);
			R = query(1,0,n,p + 1,n).l[1];
			printf("%d %d\n",last_ans = R - L + 1,t >= L && t <= R);
		}
	}
}

int main()
{
	scanf("%d%d",&n,&q);
	if (n <= 1000 && q <= 1000)
		Subtask1::solve();
	else
		Subtask2::solve();
 	return 0;
}
