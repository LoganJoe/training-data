#include<bits/stdc++.h>
#define P 2000000011
#define N 500005
#define ull unsigned long long
int n, A[N], delt[N], ans;
ull ha[N], po[N];
struct node
{
	ull v; int id;
	friend bool operator <(node t1, node t2) { return t1.v < t2.v || t1.v == t2.v && t1.id<t2.id; }
}s[N];
bool check (int mid)
{
	int cnt = 0;
	for (int i = 1; i + mid - 1 <= n; i++)
		s[++cnt] = { ha[i + mid - 1] - ha[i - 1] * po[mid] ,i };
	std::sort (s + 1, s + 1 + cnt);

	for (int i = 1, j = 1; i <= cnt; i = ++j)
	{
		while (j <= cnt && s[j].v == s[i].v) j++; j--;
		if (i == j) continue;
		if (s[j].id - s[i].id >= mid) return 1;
	}
	return 0;
}
int main ()
{
	freopen ("snowman.in", "r", stdin);
	freopen("snowman.ans","w",stdout);
	scanf ("%d", &n);
	for (int i = 1; i <= n; i++) scanf ("%d", &A[i]), delt[i] = A[i] - A[i - 1] + 1e9;
	po[0] = 1; for (int i = 1; i <= n; i++) po[i] = po[i - 1] * P;
	for (int i = 1; i <= n; i++) ha[i] = ha[i - 1] * P + delt[i];
	int l = 1, r = n;
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
		{
			int ha1=0,ha2=0;
			for(int k=1;k<=n;k++)
			{
				//if(ha[i+k-1]-ha[i-1]*po[k]==ha[j+k-1]-ha[j-1]*po[k])
				if(j+k-1>n) break;
				ha1=ha1*P+delt[i+k-1],ha2=ha2*P+delt[j+k-1];
				if(ha1==ha2) ans=std::max(ans,std::min(k,j-i));
			}
		}
	printf ("%d\n", ans);
}
