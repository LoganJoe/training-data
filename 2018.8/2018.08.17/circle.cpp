#include<bits/stdc++.h>
#define N 2005
#define ll long long
using namespace std;
int n, a[N], b[N]; ll sum[N], ans[N];
void solve (ll x)
{
	int t = 0;
	//for (int i = 1; i <= n; i++) t = std::max (t, ++mp[sum[i] % x]);
	for(int i=1;i<=n;i++) b[i]=sum[i]%x;
	std::sort(b+1,b+1+n);
	for(int i=1,pre=0;i<=n;i++)
		if(b[i]!=b[i+1] || i==n) t=std::max(t,i-pre),pre=i;
	ans[t] = std::max (ans[t], x);
}
int main ()
{
	//freopen("circle.in","r",stdin);
	//freopen("circle.out","w",stdout);
	scanf ("%d", &n);
	for (int i = 1; i <= n; i++) scanf ("%d", &a[i]), sum[i] = sum[i - 1] + a[i];
	int Sqrt = sqrt (sum[n]);
	for (int i = 1; i <= Sqrt; i++)
		if (sum[n] % i == 0) 
		{	solve (i);
			if (i*i != sum[n]) solve (sum[n] / i);
		}
	for (int i = n; i; i--) ans[i] = std::max (ans[i], ans[i + 1]);
	for (int i = 1; i <= n; i++) std::cout << ans[i] << "\n";
}
