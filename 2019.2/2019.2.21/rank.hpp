#include <stdio.h>
#include <stdlib.h>
#include <vector>
namespace test
{
int n,rk[1234],qry=0;
}
char ask(int a,int b)
{
	using namespace test; ++qry;
	if(!(0<=a&&a<n&&0<=b&&b<n&&a!=b))
	{
		puts("invalid query!");
		printf("%d %d\n",a,b);
		exit(-1);
	}
	char s=(rk[a]<rk[b])?'b':'g';
	if(rk[a]<1)
		return (s=='g')?'n':s;
	if(rk[a]==1) return 'n';
	if(rk[a]==2)
		return (rk[b]==3)?s:'n';
	if(rk[a]==3)
		return (s=='g')?'n':s;
	return (s=='b')?'n':s;
}
std::vector<int> work(int n);
int main()
{
	using namespace test;
	scanf("%d",&n);
	for(int i=0;i<n;++i) scanf("%d",rk+i);
	std::vector<int> v=work(n);
	if((int)v.size()!=n)
	{
		puts("wrong length");
		exit(-1);
	}
	for(int i=0;i<n;++i)
		if(v[i]!=rk[i])
		{
			puts("wrong answer");
			exit(-1);
		}
	printf("Good job! You used %d queries.\n",qry);
}
