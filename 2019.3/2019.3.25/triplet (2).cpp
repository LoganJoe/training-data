#include <bits/stdc++.h>
#include "triplet.h"
#include "grader.cpp"

using namespace std;

const int N = 1e4 + 10;
const int mul = 233, Mod = 998244353;

int A[N];

int guess (int n, int Taskid)
{
	memset (A, 0, sizeof A);
	int a, b, c;
	for (int i = 1; i <= n; i++) A[i] = 0;
	if (Taskid == 1)
	{
		A[1] = 1, A[2] = 2;
		for (int i = 3; i <= n; i++) A[i] = query (1, 2, i) - 1;
	}
	if (Taskid == 2)
	{
		a = 1, b = 2, c = 3;
	}
	int ret = 0;
	for (int i = n; i; i--) ret = 1ll * (ret + A[i]) * mul % Mod;
	return ret;
}
