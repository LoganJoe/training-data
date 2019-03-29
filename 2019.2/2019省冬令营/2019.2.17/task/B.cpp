#include<bits/stdc++.h>
#define N 100005
int n, A[N], root[N], Xor[N], lst[N], f[N]; long long ans = 0;
int find (int x) { return f[x] == x ? f[x] : f[x] = find (f[x]); }
namespace solve1
{
	struct node
	{
		int l, r, v;
		friend bool operator <(node t1, node t2)
		{
			return t1.v < t2.v;
		}
	}s[N * 10];
	int cnt;
	void Main ()
	{
		for (int i = 1; i <= n; i++) Xor[i] = Xor[i - 1] ^ A[i];
		for (int i = 1; i <= n; i++)
			for (int j = i; j <= n; j++) s[++cnt] = { i - 1,j,Xor[j] ^ Xor[i - 1] };
		std::sort (s + 1, s + 1 + cnt);
		for (int i = 1; i <= n; i++) f[i] = i;
		for (int i = 1; i <= cnt; i++)
		{
			int fx = find (s[i].l), fy = find (s[i].r);
			if (fx == fy) continue;
			f[fx] = fy, ans += s[i].v;
		}
		std::cout << ans << "\n";
	}
}
namespace solve2
{
	struct Trie
	{
		struct node
		{
			int son[2], v;
			std::vector<int> right;
		}t[N * 32];
	public:
		int cnt;
		void insert (int x, int y, int v, int id)
		{
			t[x] = t[y];
			for (int i = 30; ~i; i--)
			{
				int k = v >> i & 1;
				t[x].son[k] = ++cnt;
				x = t[x].son[k], y = t[y].son[k];
				t[x] = t[y], t[x].v++;
			}
			t[x].right.push_back (id);
		}
		int ask (int x, int v, int numb)
		{
			int res = 0;
			for (int i = 30; ~i; i--)
			{
				int k = v >> i & 1;
				if (k) res += 1 << i;
				if (t[x].son[k] && t[t[x].son[k]].v >= numb) x = t[x].son[k];
				else if (t[x].son[k ^ 1]) numb -= t[t[x].son[k]].v, x = t[x].son[k ^ 1];
				else return -1;
			}
			for (auto id : t[x].right)
			{
				numb--;
				if (!numb) return id;
			}
		}
	}T;
	struct node
	{
		int l, r, v;
		friend bool operator <(node t1, node t2)
		{
			return t1.v > t2.v;
		}
	};
	std::priority_queue<node> q;
	void Main ()
	{
		T.insert (root[0] = ++T.cnt, 0, 0, 0);
		for (int i = 1; i <= n; i++)
		{
			Xor[i] = Xor[i - 1] ^ A[i];
			T.insert (root[i] = ++T.cnt, root[i - 1], Xor[i], i);
			int pos = T.ask (root[i - 1], Xor[i], 1);
			if (pos != -1) q.push ({ pos,i,Xor[i] ^ Xor[pos] });
			lst[i] = 1;
		}
		for (int i = 1; i <= n; i++) f[i] = i;
		int tot = 0;
		while (!q.empty ())
		{
			node u = q.top (); q.pop ();
			int fx = find (u.l), fy = find (u.r);
			if (fx != fy) f[fx] = fy, tot++, ans += u.v;
			if (tot == n) break;
			if (lst[u.r] == u.r) continue;
			int i = u.r;
			int pos = T.ask (root[i - 1], Xor[i], ++lst[i]);
			q.push ({ pos,i,Xor[i] ^ Xor[pos] });
		}
		std::cout << ans << "\n";
	}
}
namespace solve3
{
	void merge (int x, int y)
	{
		int fx = find (x), fy = find (y);
		if (fx == fy) return;
		f[fy] = fx;
	}
	struct Trie
	{
		struct node
		{
			int son[2], v;
		}t[N * 32];
	public:
		int cnt;
		void insert (int v)
		{
			int x = 0;
			for (int i = 30; ~i; i--)
			{
				int k = v >> i & 1;
				if (!t[x].son[k]) t[x].son[k] = ++cnt;
				x = t[x].son[k];
				t[x].v++;
			}
		}
		int ask (int v)
		{
			int x = 0, res = 0;
			for (int i = 30; ~i; i--)
			{
				int k = v >> i & 1;
				if (t[x].son[k] && t[t[x].son[k]].v) x = t[x].son[k];
				else x = t[x].son[k ^ 1], res ^= 1 << i;
			}
			return res;
		}
		int del (int v)
		{
			int x = 0;
			for (int i = 30; ~i; i--)
			{
				int k = v >> i & 1;
				x = t[x].son[k];
				t[x].v--;
			}
		}
	}T;
	bool check ()
	{
		int mark = 0;
		for (int i = 1; i <= n; i++) mark += f[i] == i;
		return mark == 1;
	}
	std::pair<int, int> p[N];
	int vis[N];
	void Main ()
	{
		for (int i = 1; i <= n; i++) A[i] = A[i - 1] ^ A[i]; A[++n] = 0;
		for (int i = 1; i <= n; i++) f[i] = i;
		std::sort (A + 1, A + 1 + n);
		n = std::unique (A + 1, A + 1 + n) - A - 1;
		for (int i = 1; i <= n; i++) T.insert (A[i]);
		while (!check ())
		{
			for (int i = 1; i <= n; i++) vis[i] = 0, p[i] = { find (i),i };
			std::sort (p + 1, p + 1 + n);
			int pre = p[1].first, lst = 1;
			for (int i = 1; i <= n; i++)
			{
				int x = p[i].second;
				if (!vis[pre] && p[i].first == pre) T.del (A[x]);
				if (p[i + 1].first != pre)
				{
					if (vis[find (x)])
					{
						for (int j = lst; j <= i; j++) T.insert (A[p[j].second]);
						lst = i + 1, pre = p[lst].first; continue;
					}
					vis[pre] = 1;
					int Min = 1e9, ori;
					for (int j = lst; j <= i; j++)
					{
						int val = T.ask (A[p[j].second]);
						if (val < Min) Min = val, ori = val ^ A[p[j].second];
					}
					ans += Min;
					for (int j = lst; j <= i; j++) T.insert (A[p[j].second]);
					int pos = std::lower_bound (A + 1, A + 1 + n, ori) - A;
					pos = find (pos), pre = find (x);
					if (pre > pos) std::swap (pre, pos);
					merge (pre, pos); pre = p[i + 1].first, lst = i + 1;
				}
			}
		}
		std::cout << ans << "\n";
	}
}
int main ()
{
	freopen("secret.in","r",stdin);
	freopen("secret.out","w",stdout);
	scanf ("%d", &n);
	for (int i = 1; i <= n; i++) scanf ("%d", &A[i]);
	if (n <= 1000) return solve1::Main (), 0;
//	else if (n <= 2000) return solve2::Main (), 0;
	else return solve3::Main (), 0;
}
/*
8 1 2 4 2 5 8 1 6
*/
