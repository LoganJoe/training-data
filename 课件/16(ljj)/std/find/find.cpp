#include"find.h"
#include<bits/stdc++.h>
using namespace std;

int a[250010],pos[1000],cnt[1000];

void partSolve(int m,int k)
{
	int i;
	for (i=1;i<=m;i++)
		a[i]=getNumber();
	sort(a+1,a+m+1);
	int p=0,mx=0;
	for (i=1;i<=m;i++)
	{
		while (a[i]-a[p]+1>k) p++;
		mx=max(mx,i-p+1);
	}
	if (mx<=m/2) return;
	for (p=0,i=1;i<=m;i++)
	{
		while (a[i]-a[p]+1>k) p++;
		if (i-p+1==mx)
		{
			for (int t=a[i]-k+1;t<=a[p];t++)
				pos[++pos[0]]=t;
		}
	}
}

int solve(int n,int k,int inputTimesLimit)
{
	k++;
	inputStart();
	partSolve(n>>2,k);
	partSolve(n>>2,k);
	partSolve(n>>2,k);
	partSolve(n-(n>>2)*3,k);
	inputStart();
	int i,j,x,Ans=0;
	for (i=1;i<=n;i++)
	{
		x=getNumber();
		for (j=1;j<=pos[0];j++)
			cnt[j]+=pos[j]<=x&&x<=pos[j]+k-1;
	}
	for (i=1;i<=pos[0];i++)
		Ans=max(Ans,cnt[i]);
	return Ans;
}

