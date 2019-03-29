#include<bits/stdc++.h>
#define N 105
#define ll long long
int n;
ll f[N],ans;
char s[N];
int main()
{
	scanf("%d",&n);
	scanf("%s",s+1);
	f[1]=1;
	for(int i=2;i<=n;i++)
	{
		f[i]=2*f[i-1]+1;
		if(f[i]>1e18) f[i]=-1;
	}
	for(int i=1;i<=n;i++) if(s[i]=='B')
	{
		ans+=1+f[i-1];
		if(f[i-1]==-1 || ans>1e18) return puts("-1"),0;
	}
	std::cout<<ans<<"\n";
}
/*
50
BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB
*/
