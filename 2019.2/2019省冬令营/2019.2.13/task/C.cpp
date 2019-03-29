#include<bits/stdc++.h>
#define N 1000005
#define ll long long
int n, A[N], p[N]; ll m;
std::priority_queue<int> q;
void solve (int L)
{
	for (int i = 1; i <= n; i++) p[A[i]] = i;
	for (int i = 1; i < L; i++)A[i] = i, q.push (p[i]);
	for (int i = L; i <= n; i++)
		if (q.top () < p[i]) A[p[i]] = i;
		else A[q.top ()] = i, q.pop (), q.push (p[i]);
}

int main ()
{
	freopen ("sort.in", "r", stdin);
	freopen ("sort.out", "w", stdout);
	scanf ("%d%lld", &n, &m);
	for (int i = 1; i <= n; i++) scanf ("%d", &A[i]);
	for (int i = 1; i <= n; i++)
	{
		if (m > n - i)
		{
			m -= n - i;
			continue;
		}
		if (i > 1)solve (i);
		for (int j = i + 1; j <= i + m; ++j)
			if (A[i] > A[j]) std::swap (A[i], A[j]);
		break;
	}
	for (int i = 1; i <= n; i++) printf ("%d ", A[i]);
	std::cout << "\n";
}
