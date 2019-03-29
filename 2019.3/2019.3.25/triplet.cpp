#include <bits/stdc++.h>
#include "triplet.h"
#include "grader.cpp"
using namespace std;

const int N = 1e4 + 10;
const int mul = 233, Mod = 998244353;

int A[N], s[N], ans[N], tot;
struct node
{
	int a, b, c, t;
}B[N];
int guess (int n, int Taskid) {
	memset (A, 0, sizeof A);
	srand (233 + n + Taskid - 7);
	for (int i = 1; i <= n; i++) s[i] = i;
	std::random_shuffle (s + 1, s + 1 + n);
	int p1 = 1, p2 = 2, p3 = 3, t, mark = 1;
	B[++tot] = { p1,p2,p3, t = query (s[p1], s[p2], s[p3]) };
	for (int i = 4, tp, tp1, tp2; i <= n; i++)
	{

		B[++tot] = { p1,p2,i, tp = query (s[p1], s[p2], s[i]) };
		if (tp > t)
		{
			if (mark)
			{
				mark = 0;
				B[++tot] = { p2,p3,i,tp = query (s[p2], s[p3], s[i]) };
				if (tp < t) t = tp, p1 = i, std::swap (p1, p3);
				else
				{
					B[++tot] = { p1,p3,i,tp = query (s[p1], s[p3], s[i]) };
					if (tp < t) t = tp, p2 = i, std::swap (p2, p3);
				}
			}
		}
		else if (tp == t)
		{
			B[++tot] = { p2,p3,i, tp = query (s[p2], s[p3], s[i]) };
			if (tp < t) p1 = i, std::swap (p1, p3);
			else
			{
				B[++tot] = { p1,p3,i, tp = query (s[p1], s[p3], s[i]) };
				p2 = i, std::swap (p2, p3);
			}
			t = tp;
		}
		else
		{
			B[++tot] = { p2,p3,i, tp1 = query (s[p2], s[p3], s[i]) };
			B[++tot] = { p1,p3,i, tp2 = query (s[p1], s[p3], s[i]) };
			if (tp1 < tp && tp1 < tp2) t = tp1, p1 = i;
			else if (tp2 < tp && tp2 < tp1) t = tp2, p2 = i;
			else
			{
				t = tp, p3 = i;
				if (tp1 >= tp2 && tp1 > tp) std::swap (p2, p3);
				if (tp1 > tp2 && tp2 > tp) std::swap (p1, p2);
			}
		}
	}

	int ret = 0;
	for (int i = n; i; i--) ret = 1ll * (ret + A[i]) * mul % Mod;
	return ret;
}