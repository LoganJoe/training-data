#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
using namespace std;
const ll mod=1e9+7;
int read(){
	int x=0,flag=1;
	char ch=getchar();
	while(ch!='-'&&(ch<'0'||ch>'9')) ch=getchar();
	if(ch=='-') flag=-1,ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return x*flag;
}
int main(){
//	freopen("lighthouse.in","r",stdin);
//	freopen("lighthouse.out","w",stdout);
	printf("%lld\n",ans); 
	return 0;
}
