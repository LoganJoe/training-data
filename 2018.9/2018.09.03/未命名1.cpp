#include<bits/stdc++.h>
FILE *fin,*ftst,*fstd;
int match;
int main ()
{
	fin=fopen("test 1-2600.out","r");
	fstd=fopen("test.out","r");
	for(int i=1;i<=2000;i++)
	{
		int a,b;
		fscanf(fin,"%d",&a);
		fscanf(fstd,"%d",&b);
		if(a==b) match++;
	}
	printf("%d\n",match);
	return 0;
}

