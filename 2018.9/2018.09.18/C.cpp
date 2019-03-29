#include<bits/stdc++.h>
#define N 1000005
#define ll long long
int n,m,A[N],B[N],mark[N],delt[N];
char s[N];
ll ans=1e18;
int main()
{
	freopen("C.in","r",stdin);
	freopen("C.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&A[i]);
	scanf("%d",&m);
	scanf("%s",s+1);
	for(int i=1;i<=m;i++) B[i]=(s[i]=='W')?1:-1;
	for(int i=1;i<=n;i++) 
	{
		int pos,cnt=0;
		for(pos=(i-1)%m+1;!mark[pos];pos=(pos-1+n)%m+1)
		{
			delt[i]+=B[pos];
			if(A[i]+delt[i]==0) 
			{
				ans=std::min(ans,1ll*cnt*n+i);
				for(int p=(i-1)%m+1;p!=pos;p=(p-1+n)%m+1) mark[p]=0;
				break;
			}
			mark[pos]=++cnt;
		}
		if(A[i]+delt[i]==0) continue;
		//len=cnt-mark[pos]+1 prelen=mark[pos]-1
		int bascal=0,p=pos;
		for(bascal+=B[pos],pos=(pos-1+n)%m+1;pos!=p;pos=(pos-1+n)%m+1) bascal+=B[pos];
		if(bascal>=0) continue;
		int res=A[i]+(delt[i]-bascal);
		bascal*=-1;
		ll times=1ll*(mark[pos]-1)*n+i+1ll*(res/bascal)*n*(cnt-mark[pos]+1);
		A[i]=res%bascal;
		if(!A[i]) ans=std::min(times,ans);
		delt[i]=0;
		for(pos=(i-1)%m+1;!mark[pos];pos=(pos-1+n)%m+1)
		{
			delt[i]+=B[pos];
			if(A[i]+delt[i]==0) 
			{
				ans=std::min(ans,1ll*cnt*n+times);
				break;
			}
		}
		for(pos=(i-1)%m+1;mark[pos];pos=(pos-1+n)%m+1) mark[pos]=0;
	}
	if(ans==1e18) puts("-1");
	else printf("%d\n",ans);
}
