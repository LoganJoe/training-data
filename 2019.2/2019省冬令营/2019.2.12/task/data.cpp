#include<bits/stdc++.h>
int n=300;
int main()
{
	freopen("diff.in","w",stdout);
	std::cout<<"300"<<"\n";
	srand(time(0));
	for(int k=1;k<=300;k++)
	{
		int len=rand()%300+1;
	for(int i=1;i<=len;i++) std::cout<<char(rand()%26+'a');puts("");}
	puts("1");
} 
