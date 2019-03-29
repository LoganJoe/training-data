#include "rank.hpp"

#include<bits/stdc++.h>
#define N 1005
int A[N], p[N], lstq;
int check (int n, int a, int b)
{
	if (a == lstq || b == lstq) return lstq;
	int cntA = 0, cntB = 0;
	for (int i = 0; i < n && !cntA; i++) if (i != a && i != b) cntA += ask (a, i) != 'n';
	for (int i = 0; i < n && !cntB; i++) if (i != a && i != b) cntB += ask (b, i) != 'n';
	if (cntA || cntB) return lstq = cntA ? b : a;
	int cntp = 0;
	for (int i = 0; i < n; i++) if (i != a && i != b) cntp += ask (a, i) == 'b';
	return lstq = (cntp == n - 3 ? a : b);
}
std::vector<int> work (int n)
{
	for (int i = 0; i < n; i++) A[i] = i;
	std::random_shuffle (A, A + n);
	p[1] = A[0];
	for (int i = 1; i < n; i++)
	{
		int l = 0, r = i;
		while (l < r)
		{
			int mid = l + r + 1 >> 1;
			char c = ask (p[mid], A[i]);
			if (c == 'g') r = mid - 1;
			else if (c == 'b') l = mid;
			else
			{
				c = ask (A[i], p[mid]);
				if (c == 'g') l = mid;
				else if (c == 'b')  r = mid - 1;
				else
				{
					if (A[i] == check (n, p[mid], A[i])) r = mid - 1;
					else l = mid;
				}
			}
		}
		for (int j = i + 1; j > l + 1; j--) p[j] = p[j - 1];
		p[l + 1] = A[i];
	}
	std::vector<int> v (n);
	//v.resize (n);
	for (int i = 1; i <= n; i++) if (p[i] == lstq) 
	{
		int x = i;
		for (int i = 1; i <= n; i++) v[p[i]] = i - x + 1;
		break;
	}
	return v;
}


