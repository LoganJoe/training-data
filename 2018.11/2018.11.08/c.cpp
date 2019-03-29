#include<bits/stdc++.h>
#define N 100005
int n,Q,A[N],B[N],sumA[N],sumB[N],lstA[N],nxtA[N],lstB[N],nxtB[N];
int valA(int x,int Delt)
{
	int sum=std::min(Delt>>1,std::min(lstA[x],nxtA[x]));
	return sum*10+Delt-2*sum;
}
int valB(int x,int Delt)
{
	int sum=std::min(Delt>>1,std::min(lstB[x],nxtB[x]));
	return sum*10+Delt-2*sum;
}
int solve(int x,int y,int ex,int ey)
{
	if(x<1 || x>n || y<1 || y>n) return 1e9;
	int res=abs(sumA[ex]-sumA[x])+abs(sumB[ey]-sumB[y]);
	if(abs(ex-x)>=abs(ey-y))
	{
		int Delt=abs(ex-x)-abs(ey-y);
		if(y<=ey && y+nxtB[y]<=ey || y>=ey && y-lstB[y]>=ey) res+=Delt;
		else res+=std::min(valB(y,Delt),valB(ey,Delt));
	}
	else
	{
		int Delt=abs(ey-y)-abs(ex-x);
		if(x<=ex && x+nxtA[x]<=ex || x>=ex && x-lstA[x]>=ex) res+=Delt;
		else res+=std::min(valA(x,Delt),valA(ex,Delt));
	}
	return res;
}
int main()
{
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);
	scanf("%d%d",&n,&Q);
	for(int i=2;i<=n;i++) scanf("%d",&A[i]),sumA[i]=sumA[i-1]+A[i];
	for(int i=2;i<=n;i++) scanf("%d",&B[i]),sumB[i]=sumB[i-1]+B[i];
	for(int i=1,pA=-1e8,pB=-1e8;i<=n;i++)
	{
		if(A[i]==1) pA=i;if(B[i]==1) pB=i;
		lstA[i]=i-pA,lstB[i]=i-pB;
	}
	for(int i=n,pA=1e8,pB=1e8;i>=1;i--)
	{
		nxtA[i]=pA-i-1,nxtB[i]=pB-i-1;
		if(A[i]==1) pA=i;if(B[i]==1) pB=i;
	}
//	for(int i=1;i<=n;i++) printf("%d ", lstA[i]);puts("");
//	for(int i=1;i<=n;i++) printf("%d ", nxtA[i]);puts("");
//	for(int i=1;i<=n;i++) printf("%d ", lstB[i]);puts("");
//	for(int i=1;i<=n;i++) printf("%d ", nxtB[i]);puts("");
	while(Q--)
	{
		int sx,sy,ex,ey;
		scanf("%d%d%d%d",&sx,&sy,&ex,&ey);
		if(sx>ex) std::swap(sx,ex),std::swap(sy,ey);
		int ans=1e9;
		if(abs((ex-sx)-(ey-sy))&1) 
		{
			ans=std::min(ans,solve(sx+1,sy,ex,ey)+A[sx+1]);
			ans=std::min(ans,solve(sx,sy+1,ex,ey)+B[sy+1]);
			ans=std::min(ans,solve(sx-1,sy,ex,ey)+A[sx]);
			ans=std::min(ans,solve(sx,sy-1,ex,ey)+B[sy]);
		}
		else ans=solve(sx,sy,ex,ey);
		printf("%d\n",ans);
	}
}
