#include<bits/stdc++.h>
#define N 800005
#define ll long long
int n,m,top,b[N],tot,st[N],cost[N],nxt[N],ans[N];
struct node
{
	int l,r,id;
	friend bool operator <(node t1,node t2){return t1.l<t2.l;}
}A[N];
void prep()
{
	for(int i=1,j=1;i<=tot;i++)
	{
		for(;j<top && A[j+1].l<=i;j++);
		nxt[i]=A[j].r;
	}
	for(int i=1;i<=tot;i++) cost[i]=1;
}
int Jump(int l,int r)
{
	if(l>=r) return 0;
	int res=Jump(nxt[l],r)+cost[l];
	if(nxt[nxt[l]]<=r) cost[l]+=cost[nxt[l]],nxt[l]=nxt[nxt[l]];
	return res;
}
int main()
{
	freopen("flag.in","r",stdin);
	freopen("flag.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		int l,r;scanf("%d%d",&l,&r);
		if(l>r) r+=m;
		A[++top]={l,r,i};
		b[++tot]=A[top].l,b[++tot]=A[top].r;
		A[++top]={l+m,std::min((ll)2e9,0ll+r+m),0};
		b[++tot]=A[top].l,b[++tot]=A[top].r;
	}
	
	std::sort(A+1,A+1+top);
	std::sort(b+1,b+1+tot);
	
	tot=std::unique(b+1,b+1+tot)-b-1;
	for(int i=1;i<=top;i++)
	{
		A[i].l=std::lower_bound(b+1,b+1+tot,A[i].l)-b;
		A[i].r=std::lower_bound(b+1,b+1+tot,A[i].r)-b;
		st[A[i].id]=A[i].l;
	}
	prep();
	for(int l=1,r=1;b[l]<=m && l<=tot;l++)
	{
		while(r<=tot && b[r]<b[l]+m) r++;
		ans[l]=Jump(l,r);
	}
	for(int i=1;i<=n;i++) printf("%d ",ans[st[i]]);
	puts("");
}
