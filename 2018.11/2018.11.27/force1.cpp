#include<bits/stdc++.h>
#define N 500
int n,A[N], ans;
int main()
{
	freopen("a.in","r",stdin);
	freopen("a.ans","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&A[i]);
	for(int a=1;a<=n;a++)
		for(int b=a+1;b<=n;b++)
		{
			if(A[a]>=A[b]) continue;
			for(int c=1;c<=n;c++)
				for(int d=c+1;d<=n;d++)
				{
					if(c==a || c==b || d==a || d==b) continue;
					if(A[c]<=A[d]) continue;
					ans++;
				}
		 } 
	printf("%d\n",ans);
 } 
