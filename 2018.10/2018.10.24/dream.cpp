#include<bits/stdc++.h>
#define N 100005
struct node
{
	int l, r, id;
	friend bool operator <(node t1, node t2) { return t1.r < t2.r; }
}A[N];
int n, m, B[N], ans;
std::set<int> s; std::set<int>::iterator it;
int main ()
{
	freopen("dream.in","r",stdin);
	freopen("dream.out","w",stdout);
	scanf ("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf ("%d%d", &A[i].l, &A[i].r);
	for (int i = 1; i <= m; i++) scanf ("%d", &B[i]);
	std::sort (A + 1, A + 1 + n);
	std::sort (B + 1, B + 1 + m);
	B[++m] = 1e9 + 7;
	for (int i = 1, j = 1; i <= m; i++)
	{
		s.insert (B[i]);
		for (; j <= n && A[j].r < B[i + 1]; j++)
		{
			it = s.lower_bound (A[j].l);
			if (it != s.end ()) ans++, s.erase (it);
		}
	}
	printf ("%d\n", ans);
}
/*
2 2
1 3
2 4
1 3
*/
