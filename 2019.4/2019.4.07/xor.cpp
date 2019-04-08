#include<bits/stdc++.h>
#define N 500005
#define ll long long
int n, K, cur[N];
ll A[N], Xor[N], ans;
class Trie
{
	struct node
	{
		int son[2], cnt;
	}t[N * 33];
public:
	int cnt;
	void insert (ll v)
	{
		int x = 1;
		for (int i = 31; ~i; i--)
		{
			int k = v >> i & 1;
			if (!t[x].son[k]) t[x].son[k] = ++cnt;
			x = t[x].son[k], t[x].cnt++;
		}
	}
	ll query (ll v, int kth)
	{
		int x = 1; ll res = 0;
		for (int i = 31; ~i; i--)
		{
			int k = (v >> i & 1) ? 0 : 1;
			if (t[t[x].son[k]].cnt >= kth) x = t[x].son[k], res |= 1ll << i;
			else kth -= t[t[x].son[k]].cnt, x = t[x].son[k ^ 1];
		}
		return res;
	}
}T;
std::priority_queue<std::pair<ll, int> > q;
int main ()
{
	freopen ("xor.in", "r", stdin);
	freopen ("xor.out", "w", stdout);
	scanf ("%d%d", &n, &K); T.cnt++, K <<= 1, T.insert (0);
	for (int i = 1; i <= n; i++) scanf ("%lld", &A[i]);
	for (int i = 1; i <= n; i++) Xor[i] = Xor[i - 1] ^ A[i], T.insert (Xor[i]);
	for (int i = 1; i <= n; i++) q.push ({ T.query (Xor[i], cur[i] = 1), i });
	while (K--)
	{
		std::pair<ll, int> u = q.top (); q.pop ();
		if (K & 1) ans += u.first;
		if (cur[u.second] <= n)
			q.push ({ T.query (Xor[u.second], ++cur[u.second]), u.second });
	}
	std::cout << ans << "\n";
}