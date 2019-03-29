#include<bits/stdc++.h>

#define N 300005
#define ll long long

int n, vis[N], stk[N], top;
ll res[N], tmp, f[3005][3005];
struct node
{
	int a; ll b;
	friend bool operator <(node t1, node t2) { return t1.a<t2.a; }
}A[N];
void update (int cnt)
{
	tmp = 0, top = 0;
	for (int i = 1; i <= n; i++) if (vis[i]) tmp += A[i].b, stk[++top] = A[i].b;
	std::sort (stk + 1, stk + 1 + top);
	for (int i = 1; i <= top; i++) tmp += 1ll * stk[i] * (i - 1);
	res[cnt] = std::max (res[cnt], tmp);
}
void dfs (int x, int cnt)
{
	if (x > n) { update (cnt); return; }
	vis[x] = 1, dfs (x + 1, cnt + 1);
	vis[x] = 0, dfs (x + 1, cnt);
}
void solve1 ()
{
	dfs (1, 0);
	for (int i = 1; i <= n; i++) printf ("%lld\n", res[i]);
}
void solve2 ()
{
	std::sort (A + 1, A + 1 + n);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= i; j++) f[i][j] = std::max (f[i - 1][j], f[i - 1][j - 1] + 1ll*A[i].a * (j - 1) + A[i].b);
	for (int i = 1; i <= n; i++) printf ("%lld\n", f[n][i]);
}
int main ()
{
	//freopen("value.in","r",stdin);
	//freopen("value.out","w",stdout);
	scanf ("%d", &n);
	for (int i = 1; i <= n; i++) scanf ("%d%lld", &A[i].a, &A[i].b);
	//if (n <= 20) solve1 ();
//	else 
	solve2 ();
}
