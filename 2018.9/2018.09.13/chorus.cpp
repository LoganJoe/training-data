#include<bits/stdc++.h>
#define N 100005
int n,A[N],Or,st[N][20],pos,ans=1e9;
int main()
{
	freopen("chorus.in","r",stdin);
	freopen("chorus.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&A[i]),Or|=A[i],st[i][0]=A[i];
	for(int j=1;j<20;j++)
		for(int i=1;i+(1<<j)-1<=n;i++)
			st[i][j]=st[i][j-1]|st[i+(1<<j-1)][j-1];
	for(int i=1;i<=n;i++)
	{
		int pos=i,s=0;
		for(int j=19;j;j--)
			if((s|st[pos][j])!=Or && pos+(1<<j)<=n) s|=st[pos][j],pos+=(1<<j);
		s|=st[pos][0],pos++;	
		if(s==Or) ans=std::min(ans,pos-i); 
	}
	printf("%d\n",ans);
}
	
