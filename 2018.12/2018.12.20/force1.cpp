#include<bits/stdc++.h>
#define N 5005
int n,m,A[N],s[N];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&A[i]);
	for(scanf("%d",&m);m--;)
	{
		int l,r,k;scanf("%d%d%d",&l,&r,&k);
		int cnt=0;
		for(int i=l;i<=r;i++)s[++cnt]=A[i];
		std::sort(s+1,s+1+cnt);
		int sum=0,tot[2];tot[0]=tot[1]=0;
		for(int i=cnt;i && tot[0]+tot[1]<k;i--)
		{
			sum+=s[i];
			tot[s[i]&1]++;
		}
		if(cnt<k) 
		{
			puts("-1");
			continue;
		} 
		if(tot[0]%2==0 && tot[1]%2==0) 
		{
			std::cout<<sum<<"\n";
			continue;
		}
		else
		{
			int pre[2],nxt[2];
			int res=-1;
			pre[0]=pre[1]=nxt[0]=nxt[1]=-1;
			for(int i=1;i<=cnt-k;i++) pre[s[i]&1]=i;
			for(int i=cnt;i>cnt-k;i--) nxt[s[i]&1]=i;
			if(pre[0]>0 && nxt[1]>0) res=std::max(res,sum+pre[0]-nxt[1]);
			if(pre[1]>0 && nxt[0]>0) res=std::max(res,sum+pre[1]-nxt[0]);
			std::cout<<res<<"\n";
		}
	}
}
