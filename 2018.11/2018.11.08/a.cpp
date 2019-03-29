#include<bits/stdc++.h>
int T,a,b,c,d,e,f;
int main()
{
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	for(scanf("%d",&T);T--;)
	{
		scanf("%d%d%d%d%d%d",&a,&b,&c,&d,&e,&f);
		if(!d) {puts("NO");continue;}
		if(!c) {puts("YES");continue;}
		if(!a && b) {puts("YES");continue;}
		if(!b) {puts("NO");continue;}
		if(!e && f) {puts("YES");continue;}
		if(!f) {puts("NO");continue;}
		if(1ll*b*d*f>1ll*c*e*a) {puts("YES");continue;}
		puts("NO");
	}
}
