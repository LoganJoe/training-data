#include<bits/stdc++.h>
#define N 1000005
int n, m, A[N], sg[N], mark[N<<2], tot, sum[N], ans;
struct node
{
	int l, r;
	friend bool operator <(node t1, node t2) { return t1.l < t2.l || t1.l==t2.l && t1.r<t2.r; }
}s[N<<1];
int main ()
{
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout); 
	scanf ("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf ("%d", &A[i]);
	for (int i = 1; i <= m; i++) tot++,scanf ("%d%d", &s[tot].l, &s[tot].r);
	for (int i = 1; i <= n; i++) s[++tot] = { i,i };
	std::sort (s + 1, s + 1 + tot);
	for (int i = n, j = tot; i; i--)
	{
		int last = j;
	//	mark[0]=1;
		while (s[j].l == i)
		{
			mark[sum[s[j].l + 1] ^ sum[s[j].r + 1]] = 1;
			j--;
		} 
		for (int k = 0; ; k++) if (!mark[k]) { sg[i] = k; break; }
		sum[i] = sum[i + 1] ^ sg[i];
		while (s[last].l == i)
		{
			mark[sum[s[last].l + 1] ^ sum[s[last].r + 1]] = 0;
			last--;
		}
	}
	for (int i = 1; i <= n; i++) if(A[i]) ans ^= sg[i];
	puts (ans == 0 ? "Second" : "First");
}
