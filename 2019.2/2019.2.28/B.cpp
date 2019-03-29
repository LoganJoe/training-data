#include<bits/stdc++.h>
#define N 100005
int n, m, pos[N], mark[N], ans;
struct node
{
	int v, id;
	friend bool operator <(node t1, node t2) { return t1.v > t2.v || t1.v == t2.v && t1.id < t2.id; }
}A[N];
int main ()
{
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
	scanf ("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf ("%d", &A[i].v), A[i].id = i;
	std::sort (A + 1, A + 1 + n);
	for (int i = 1; i <= n; i++) pos[A[i].id] = i;
	while (m--)
	{
		int a; scanf ("%d", &a);
		for (int i = 1; i <= a; i++) mark[pos[i]] = 1;
		int Maxp = n + 1, x = 1; ans = 0;
		for (int i = 1, nowp = a + 1; i <= n; i++, nowp++)
		{
			if (i & 1)
				if (Maxp < x) ans += A[Maxp].v, Maxp = n + 1;
				else { for (; !mark[x]; x++); ans += A[x].v, x++; }
			else
				if (Maxp < x) ans -= A[Maxp].v, Maxp = n + 1;
				else { for (; !mark[x]; x++); ans -= A[x].v, x++; }
			if (nowp <= n)
				if (pos[nowp] < x) Maxp = pos[nowp];
				else Maxp = n + 1, mark[pos[nowp]] = 1;
		}
		for (int i = 1; i <= n; i++) mark[pos[i]] = 0;
		printf ("%d\n", ans);
	}

}
