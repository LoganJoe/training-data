#include<bits/stdc++.h>
#define N 150005
#define P 19260817
#define ull unsigned long long
int n,m,cnt,len[N],A[20];
char s[N];
std::vector<ull> ha[N];
bool check(int k,int mid)
{
	for(int i=2;i<=k;i++) if(ha[A[i]][mid]!=ha[A[i-1]][mid]) return 0;
	return 1;
}
int main()
{
	freopen("biology.in","r",stdin);
	freopen("biology.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%s",s+1);len[i]=strlen(s+1);
		std::reverse(s+1,s+1+len[i]);
		ha[i].push_back(0);
		for(int j=1;j<=len[i];j++) ha[i].push_back(ha[i][j-1]*P+s[j]);
	}
	while(m--)
	{
		int op,k;scanf("%d",&op);
		if(op==1)
		{
			scanf("%s",s+1);len[++n]=strlen(s+1);
			std::reverse(s+1,s+1+len[n]);
			ha[n].push_back(0);
			for(int j=1;j<=len[n];j++) ha[n].push_back(ha[n][j-1]*P+s[j]);
		}
		else
		{
			scanf("%d",&k);int l=0,r=1e9;
			for(int i=1;i<=k;i++) 
				scanf("%d",&A[i]),r=std::min(r,(int)ha[A[i]].size()-1);
			while(l<r)
			{
				int mid=(l+r+1)>>1;
				if(check(k,mid)) l=mid;
				else r=mid-1;
			}
			printf("%d\n",l);
		}
	}
}
