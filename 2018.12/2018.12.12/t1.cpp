#include<bits/stdc++.h>
#define N 600005
#define mod 1000000007
int n, A[N], ans[N], sum[N], sum2[N], top, id, inv2 = (mod + 1) >> 1, Max, tp;
int mul (int x) { return x >= mod ? x - mod : x; }
struct Segment_Tree
{
#define lc t[x].ls
#define rc t[x].rs
#define mid ((l+r)>>1)
	struct tree { int ls, rs, sum, sum2, tag; } t[N * 30];
public:
	int root[N], cnt;
	void pushup (int x)
	{
		t[x].sum = mul (t[lc].sum + t[rc].sum);
		t[x].sum2 = mul (t[lc].sum2 + t[rc].sum2);
	}
	void update (int x, int v)
	{
		t[x].sum = 1ll * t[x].sum * v % mod;
		t[x].sum2 = 1ll * t[x].sum2 * v % mod * v % mod;
		t[x].tag = 1ll * t[x].tag * v % mod;
	}
	void pushdown (int x)
	{
		if (t[x].tag == 1) return;
		update (lc, t[x].tag);
		update (rc, t[x].tag);
		t[x].tag = 1;
	}
public:
	void insert (int &x, int l, int r, int p, int v)
	{
		if (!x) x = ++cnt; t[x].tag = 1;
		if (l == r) return (void)(t[x].sum += v, t[x].sum2 += v);
		pushdown (x);
		if (p <= mid) insert (lc, l, mid, p, v);
		else insert (rc, mid + 1, r, p, v);
		pushup (x);
	}
	void modify (int x, int l, int r, int ql, int qr,int v)
	{
		if (ql <= l && r <= qr) return update (x, v);
		pushdown (x);
		if (ql <= mid) modify (lc, l, mid, ql, qr, v);
		if (qr > mid) modify (rc, mid + 1, r, ql, qr, v);
		pushup (x);
	}
	void merge (int &x, int y, int l, int r)
	{
		pushdown (x), pushdown (y);
		if (!x && !y) return;
		if (!x && y)
		{
			x = y, tp = mul (tp + t[x].sum);
			return;
		}
		if (x && !y)
		{
			ans[id] = mul (ans[id] + 1ll * tp * t[x].sum % mod);
			return;
		}
		if (l == r)
		{
			ans[id] = mul (ans[id] + 1ll * tp * t[x].sum % mod);
			tp = mul (tp + t[y].sum);
			t[x].sum = mul (t[x].sum + t[y].sum), t[x].sum2 = 1ll * t[x].sum * t[x].sum % mod;
			return;
		}
		merge (t[x].ls, t[y].ls, l, mid);
		merge (t[x].rs, t[y].rs, mid + 1, r);
		pushup (x);
	}
	void getval (int x, int f) { sum[f] = t[x].sum; sum2[f] = t[x].sum2; }
}T;
int main ()
{
	freopen ("bubble.in", "r", stdin);
	freopen ("bubble.out", "w", stdout);
	scanf ("%d", &n);
	for (int i = 1; i <= n; i++) scanf ("%d", &A[i]), Max = std::max (Max, A[i]);
	for (int i = 1; i <= n; i++)
	{
		if (A[i] > 0)
		{
			top++, T.
				root[top] = 0; ans[top] = 0;
			T.insert (T.root[top], 1, Max, A[i], 1);
			sum[top] = sum2[top] = 1;
		}
		if (A[i] == 0)
		{
			ans[top - 1] = mul (ans[top - 1] + ans[top]);
			tp = 0, id = top - 1; T.merge (T.root[top - 1], T.root[top], 1, Max);
			top--, T.getval (T.root[top], top);
		}
		if (A[i] < 0)
		{
			A[i] = -A[i];
			ans[top] = mul (1ll * ans[top] * A[i] % mod + 1ll * inv2 * mul (1ll * sum[top] 
			* sum[top] % mod - sum2[top] + mod) % mod * A[i] % mod * (A[i] - 1) % mod * inv2 % mod);
			sum[top] = 1ll * sum[top] * A[i] % mod;
			sum2[top] = 1ll * sum2[top] * A[i] % mod * A[i] % mod;
			T.modify (T.root[top], 1, Max, 1, Max, A[i]);
		}
	}
	std::cout << ans[1] << "\n";
}
