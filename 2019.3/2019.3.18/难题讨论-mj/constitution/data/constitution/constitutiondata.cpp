#include<algorithm>
#include<unistd.h>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<cctype>
#include<ctime>
#define rep(i,x,y) for(int i=x; i<=y; ++i)

using namespace std;

int main()
{
	freopen("constitution8.in","r",stdin);
	long long p,k,n;
	scanf("%lld%lld%lld",&p,&k,&n);
	fclose(stdin);
	freopen("constitution8.in","w",stdout);
	printf("%lld %lld %lld\n",p,k,n-1);
	return 0;
}
