#include<cstdio>
#include<cctype>
using namespace std;
const int N=1e5+5;
int a[N],l[N],r[N];
inline int read()
{
    int X=0,w=0; char ch=0;
    while(!isdigit(ch)) w|=ch=='-',ch=getchar();
    while(isdigit(ch)) X=(X<<3)+(X<<1)+(ch^48),ch=getchar();
    return w?-X:X;
}
inline int max(int x,int y)
{
	return x>y?x:y;
}
inline int min(int x,int y)
{
	return x<y?x:y;
}
int main()
{
	//freopen("c.in","r",stdin);
	int T=read();
	while(T--)
	{
		int n=read();
		for(int i=1;i<=n;i++)
		{
			a[i]=read();
			if(a[i]==-1) l[i]=read(),r[i]=read();
		}
		if(n==1)
		{
			printf("%d\n",a[n]);
			continue;
		}
		int pd=0;
		for(int i=n-3;i>1;i-=2)
		{
			if(pd)
			{
				a[i]=min(a[l[i]],a[r[i]]);
			}else
				a[i]=max(a[l[i]],a[r[i]]);
			pd^=1;
		}
		if(pd)
		{
			a[1]=min(a[l[1]],a[r[1]]);
		}else
			a[1]=max(a[l[1]],a[r[1]]);
		printf("%d\n",a[1]);
	}
	return 0;
}
