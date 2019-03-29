#include<bits/stdc++.h>
#define N 30
FILE *fin,*ftst,*fstd;
double f[N][N],s[N][N][N];
int res,n=28,p[N][N][N];
int main()
{
	fin=fopen("training.in","r");
	fstd=fopen("training.out","r");
	ftst=fopen("test.in","r");
	//fout=fopen("test.out","w");
	freopen("test.out","w",stdout);
	int M=30000;
	for(int T=1;T<=M;T++)
	{
		if(T%5000==0)  printf("%d\n",T);
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++) fscanf(fin,"%lf",&f[i][j]);
		fscanf(fstd,"%d",&res);
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++) s[res][i][j]+=f[i][j]; 
	}

	for(int num=0;num<=9;num++)
	{
		double avg=0;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++) avg+=s[num][i][j];
		avg/=28*28;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++) if(s[num][i][j]>=avg) p[num][i][j]=1;
	}
	M=10000;
	for(int T=1;T<=M;T++)
	{
		double avg=0;int tot=0;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++) fscanf(ftst,"%lf",&f[i][j]),avg+=f[i][j];
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++) if(f[i][j]>1e-3) tot++;
		avg/=tot; 
		int match=0,numb=0,minal=tot;
		for(int num=0;num<=9;num++)
		{
			int counter=0;
			for(int i=1;i<=n;i++) 
				for(int j=1;j<=n;j++) 
				{
					if(f[i][j]<avg) continue;
					if(p[num][i][j]) counter++;
				}
			if(counter>match) match=counter,numb=num;
			minal=std::min(minal,match);
		}
		if(T>=2600 && match-minal<=tot/16 && numb!=0)
		{
			std::cerr<<"&"<<T<<" "<<numb<<"\n";
			for(int i=1;i<=n;i++,std::cerr<<"\n")
				for(int j=1;j<=n;j++) std::cerr<<(f[i][j]>avg)?"#":" ";
			scanf("%d",&numb);
		}
		printf("%d\n",numb);
	}
 } 
 
