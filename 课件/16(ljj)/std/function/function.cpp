#include<bits/stdc++.h>
using namespace std;
#define LL long long

const int maxn=5000010;
LL n,Ans,a[maxn];
int m;

int main()
{
	freopen("function.in","r",stdin);
	freopen("function.out","w",stdout);
	int i;
	scanf("%lld%d",&n,&m);
	for (i=0;i<=m;i++) a[i]=1;
	for (i=m+1;;i++)
	{
		a[i]=a[i-1]+a[i-m];
		if (a[i]>n) break;
	}
	for (i--;i>=1;i--)
		if (n>=a[i]) n-=a[i],Ans+=a[i-1];
	printf("%lld\n",Ans);
}

