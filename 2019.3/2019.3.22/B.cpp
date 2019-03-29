#include "tree.h"
#include "grader.cpp"
#include <bits/stdc++.h>
#define N 1005
int deep[N], Maxdep, cnt[N];
bool S[N];
std::vector<int> A[N];
void solve(int n, int t) //ignore the Formal parameter 't'
{
	A[0].push_back(1);
	for (int i = 2; i <= n; i++)
	{
		for (int j = 2; j <= n; j++)
			S[j] = i != j;
		deep[i] = query(1, i, S) + 1;
		Maxdep = std::max(Maxdep, deep[i]);
		A[deep[i]].push_back(i);
	}
	for (int i = 1; i <= Maxdep; i++)
	{
		std::sort(A[i].begin(), A[i].end());
		if (A[i - 1].size() == 1)
		{
			for (int v : A[i])
				submit(A[i - 1][0], v);
			continue;
		}
		for (int v : A[i])
		{
			int l = 0, r = A[i - 1].size() - 1;
			for (int mid; l < r;)
			{
				mid = (l + r) >> 1;
				std::fill(S + 1, S + 1 + n, 0);
				for (int k = 0; k <= mid; k++)
					S[A[i - 1][k]] = 1;
				query(1, v, S) ? r = mid : l = mid + 1;
			}
			submit(A[i - 1][r], v);
		}
	}
}