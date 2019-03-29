#include<bits/stdc++.h>
#define N 3005

int n, a[N], b[N], f[N][N], val[N], mark[N], ans;
char s[N];
void check (int st, int ed, int delt)
{
	for (int i = st, tmp = 0; i <= ed; i += delt) mark[tmp ^= val[i]] = 1;
}
void solve (int st, int ed, int delt)
{
	if (a[st]) return;
	for (int i = st; i <= ed; i += delt) a[i] ^= 1;
	for (int i = 1; i <= n; i++) printf ("%c", a[i] ? 'S' : 'N');
	puts ("");exit (0);
}
bool force (int a[], int dep)
{
	int S[N];
	int ans = 0, flag = 1, A, B, C;
	for (int i = 1; i <= n; i++) if (!a[i]) flag = 0;
//	for (int i = 1; i <= n; i++) printf ("%d ", a[i]);
//	puts ("");
	if (flag) return 1;
	for (int i = 1; i <= n; i++) S[i] = a[i];
	for (int i = 1; i <= n; i++)
	{
		if (S[i]) continue;
		for (int j = 1; j + i <= n; j++)
		{
			for (int k = i; k <= n; k += j)
			{
				int res = 0;
				S[k] ^= 1, ans |= (res = force (S, dep + 1));
				if (res) A = i, B = j, C = k;
			}
			for (int k = i; k <= n; k += j) S[k] ^= 1;
		}
	}
	if (dep == 0)
	{
		if (ans)
		{
			for (int i = A; i <= C; i += B) S[i] ^= 1;
			for (int i = 1; i <= n; i++) printf ("%c", a[i] ? 'S' : 'N');
			puts ("");
		}
		else puts ("NIE");
	}
	if(dep==2)printf ("%d %d\n", dep, ans );
	return ans^1;
}
int main ()
{
	freopen("magica.in","r",stdin);
	freopen("magica.out","w",stdout);
	scanf ("%s", s + 1);
//	n = 300;
//	for (int i = 1; i <= 300; i++) a[i] = rand () % 2;
	n = strlen (s + 1);
	for (int i = 1; i <= n; i++) a[i] = s[i] == 'S';
//	if (n <= 10) return force (a, 0), 0;
	
	for (int i = n; i; i--)
	{
	//	if (a[i]) continue;
		for (int i = 1; i <= n; i++) mark[i] = 0;
		for (int j = 1; j + i <= n; j++)
			for (int k = i + j; k <= n; k += j)
				check (i, k, j);
	//	sg[0]=1;//empty
		for (int j = 1; j < N; j++) if (!mark[j]) { val[i] = j; break; }
	}
	for (int i = 1; i <= n; i++) if (!a[i]) ans ^= val[i];
	if (ans == 0) return puts ("NIE"), 0;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j + i <= n; j++)
			for (int k = i, tmp = 0; k <= n; k += j)
			{
				tmp ^= val[k];
				if ((tmp^ans) == 0) solve (i, k, j);
			}
	return puts ("NIE"), 0;
}

