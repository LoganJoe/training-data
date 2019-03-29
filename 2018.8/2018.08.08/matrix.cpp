#include<bits/stdc++.h>
#define N 305
int n, m, B[N], res[N];
std::bitset<N> s1[N], s2[N];
struct matrix
{
	int s[N][N];
	friend matrix operator *(matrix a, matrix b)
	{
		matrix c;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				s1[i][j] = a.s[i][j], s2[i][j] = b.s[j][i];
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++) c.s[i][j] = (s1[i] & s2[j]).count () & 1;
		return c;
	}
}A, E, mat;
matrix Pow (matrix x, int k)
{
	matrix res = E;
	while (k)
	{
		if (k & 1) res = res * x;
		x = x * x; k >>= 1;
	}
	return res;
}
char ch[N]; 
int main ()
{
	freopen("matrix.in","r",stdin);
	freopen("matrix.out","w",stdout);
	scanf ("%d", &n);
	for (int i = 1; i <= n; i++) E.s[i][i] = 1;
	for (int i = 1; i <= n; i++)
	{
		scanf("%s",ch+1);
		for (int j = 1; j <= n; j++) A.s[i][j]=ch[j]-'0';
	}
	scanf("%s",ch+1);
	for (int i = 1; i <= n; i++) B[i]=ch[i]-'0';
	scanf ("%d", &m);
	while (m--)
	{
		int a; scanf ("%d", &a);
		if (a == 0)
		{
			for (int i = 1; i <= n; i++) printf ("%d ", B[i]);
			puts ("");
			continue;
		}
		mat = A;
		mat = Pow (mat, a);
		for (int i = 1; i <= n; i++) res[i] = 0;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++) res[i] ^= B[j] & mat.s[i][j];
		for (int i = 1; i <= n; i++) printf ("%d", res[i]);
		puts ("");
	}
}
/*
3
110
011
111
101
10
0 2 3 14 1 1325 6 124124 151 12312

*/
