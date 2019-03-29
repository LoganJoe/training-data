#include<bits/stdc++.h>
#define N 30
#define eps 1e-3
double s[N][N], avg, tot;
FILE *fin,*fout;
int ans,cnt;
char st;
int main ()
{
	fin=fopen("test.in","r");
	//fout=fopen("test.out","w");
	freopen("test.out","w",stdout);
	while (1)
	{
		std::cerr<<++cnt;
		avg=tot=0;
		for (int i = 1; i <= 28; i++)
			for (int j = 1; j <= 28; j++) fscanf(fin,"%lf",&s[i][j]);
			//std::cin >> s[i][j];
		if(cnt<=2580) continue;
		for (int i = 1; i <= 28; i++)
			for (int j = 1; j <= 28; j++) if (s[i][j]>eps) avg += s[i][j], tot++;
		avg /= tot;
		for (int i = 1; i <= 28; i++, std::cerr<<"\n")
			for(int j = 1; j <= 28; j++) 
			if (s[i][j] >= avg) std::cerr<<"#";
			else if(s[i][j]>eps) std::cerr<<".";
			else std::cerr<<" ";
		std::cerr<<"Please type the answer in the keyboard."<<std::endl;
		scanf("%d",&ans);
		printf("%d\n",ans);
		std::cerr<<"End Line\n";
	}
}
