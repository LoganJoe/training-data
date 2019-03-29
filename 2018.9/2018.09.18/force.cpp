#include<bits/stdc++.h>
#define ll long long
#define N 10005
int n,m;
ll A[N],s[N],lstd,d,b;
int main()
{
	freopen("A.in","r",stdin);
	freopen("A.ans","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&A[i]);
	while(m--)
	{
		scanf("%I64d%I64d",&d,&b);
		ll ans=0;
		for(int i=1;i<=n;i++) s[i]+=1ll*(d-lstd)*A[i];
		for(int i=1;i<=n;i++) if(s[i]>=b) ans+=s[i]-b,s[i]=b;
		lstd=d;
		printf("%I64d\n",ans);
	}
	
}
