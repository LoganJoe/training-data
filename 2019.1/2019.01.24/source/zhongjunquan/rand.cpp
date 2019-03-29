#include<cstring>
#include<cstdio>
#include<ctime>
#include<cstdlib>
using namespace std;
int main(){
	srand((int)time(0));rand();
	freopen("b.in","w",stdout);
	printf("%d %d")
	for(int i=1;i<=999;++i)printf("%d %d %d\n",i,i+1,rand()%3+1);
	
}
