#include<bits/stdc++.h>
#define N 1005
std::bitset<100000> s, base;
int n, a[N], mark[N], Max;
void solve (int x)
{
	for (int i = x + 1; i < n; i++) mark[a[i] - a[x]] = 1;
	base = s;
	for (int i = 1; i <= a[n - 1] - a[x]; i++) if (mark[i]) s |=(base << i);
	for (int i = 1; i <= n; i++) mark[i] = 0;
	return;
}
int main ()
{
	freopen("water.in","r",stdin);
	freopen("water.out","w",stdout);
	scanf ("%d",&n);
	for (int i = 1; i <= n; i++) scanf ("%d", &a[i]), Max = std::max (Max, a[i]);
	std::sort (a + 1, a + 1 + n); s[0] = 1;
	for (int i = 1; i <= n; i++) solve (i);
	for (int i = 0; i <= Max * n; i++) if (s[i]) printf ("%d ", i);
	return puts (""), 0;
}
