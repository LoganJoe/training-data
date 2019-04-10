#include<bits/stdc++.h>
#define N 200005
#define ll long long
int n, atk;
ll suma[N], sumr[N], ans, tot, res[N];
struct node
{
	int atk, rnd; ll v;
	friend bool operator <(node t1, node t2)
	{
		return 1ll * t1.atk * t1.rnd < 1ll * t2.atk * t2.rnd;
	}
}A[N];
struct point
{
	ll x, y;
	friend point operator +(point a, point b) { return { a.x + b.x, a.y + b.y }; }
	friend point operator -(point a, point b) { return { a.x - b.x, a.y - b.y }; }
} B[N], tp[N];
ll cross (point a, point b) { return a.x*b.y - b.x*a.y; }
ll calc (point a, int k) { return a.y - a.x * k; }
bool cmp1 (point t1, point t2) { return t1.x < t2.x; }
bool cmp2 (point t1, point t2) { return t1.x > t2.x; }
int sta[N], top;
void solve (int l, int r)
{
	if (l == r) return;
	int mid = l + r >> 1;
	int cnt = 0;
	for (int i = l; i <= mid; i++) B[++cnt] = { A[i].rnd, A[i].v };
	std::sort (B + 1, B + 1 + cnt, cmp1);
	sta[top = 1] = 1;
	for (int i = 2; i <= cnt; i++)
	{
		for (; top > 1 && cross (B[sta[top]] - B[sta[top - 1]], B[i] - B[sta[top - 1]]) >= 0; top--);
		sta[++top] = i;
	}
	cnt = 0;
	for (int i = mid + 1; i <= r; i++) tp[++cnt] = { A[i].atk,i };
	std::sort (tp + 1, tp + 1 + cnt, cmp2);
	for (int i = 1, j = 1; i <= cnt; i++)
	{
		for (; j < top && calc (B[sta[j + 1]], tp[i].x) >= calc (B[sta[j]], tp[i].x); j++);
		res[tp[i].y] = std::max (res[tp[i].y], calc (B[sta[j]], tp[i].x));
	}
	solve (l, mid), solve (mid + 1, r);
}
int main ()
{
	freopen ("fittest.in", "r", stdin);
	freopen ("fittest.out", "w", stdout);
	scanf ("%d%d", &n, &atk);
	for (int i = 1; i <= n; i++) 
		scanf ("%d%d", &A[i].atk, &A[i].rnd), A[i].rnd = (A[i].rnd + atk - 1) / atk;
	std::sort (A + 1, A + 1 + n);
	for (int i = 1; i <= n; i++) sumr[i] = sumr[i - 1] + A[i].rnd;
	for (int i = n; i >= 1; i--) suma[i] = suma[i + 1] + A[i].atk;
	for (int i = 1; i <= n; i++)
	{
		A[i].v = (sumr[i] - 1) * A[i].atk + suma[i + 1] * A[i].rnd;
		tot += (sumr[i] - 1) * A[i].atk;
	}
	ans = tot;
	if (n <= 10000)
	{
		for (int i = 1; i <= n; i++)
			for (int j = i + 1; j <= n; j++)
			{
				ll val = A[i].v + A[j].v - A[i].rnd * A[j].atk;
				ans = std::min (ans, tot - val);
			}
	}
	else
	{
		/*
		ll Max = 0;
		for (int i = 1; i <= n; i++)
		{
			ll val = A[i].v + Max;
			ans = std::min (ans, tot - val);
			Max = std::max (Max, A[i].v - A[i].atk);
		}
		*/

		solve (1, n);
		ll val = 0;
		for (int i = 1; i <= n; i++)
			val = std::max (val, A[i].v + res[i]);
		ans -= val;
	}
	std::cout << ans << "\n";
}	
/*
19994171116
*/
