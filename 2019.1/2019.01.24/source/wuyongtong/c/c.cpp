#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 1e5 + 10;
int c[N][2],v[N],n,T;
int main() {
	// freopen("c.in","r",stdin);
	for (cin>>T;T;T--) {
		memset(c,0,sizeof c);
		memset(v,0,sizeof v);
		cin>>n;
		for (int i = 1; i <= n; i++) {
			scanf("%d",&v[i]);
			if (v[i] == -1) {
				scanf("%d %d",&c[i][0],&c[i][1]);
			}
		}
		int od=0;
		for (int i = n-3; i; i-=2) {
			if (!od) v[i] = max(v[c[i][0]],v[c[i][1]]);
			else v[i] = min(v[c[i][0]],v[c[i][1]]);
			od=1-od;
		}
			if (!od) v[1] = max(v[c[1][0]],v[c[1][1]]);
			else v[1] = min(v[c[1][0]],v[c[1][1]]);
		printf("%d\n",v[1]);
	}
}
