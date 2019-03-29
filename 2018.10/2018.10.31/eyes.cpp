#include<bits/stdc++.h>
#define N 1005
int Case,n,m,Q,st_being_hit=-1,cnt;
struct node
{
	int x,y;
}a,b,st,s[N];
int ans1,ans2;
char ch[10],op[10];
int main()
{
	freopen("eyes.in","r",stdin);
	freopen("eyes.out","w",stdout);
	scanf("%d",&Case);
	scanf("%d%d",&n,&m);
	scanf("%d%d",&a.x,&a.y);
	scanf("%d%d",&b.x,&b.y);st=b;
	if(a.x==b.x) st_being_hit=0,ans2++;
	scanf("%d",&Q);
	while(Q--)
	{
		scanf("%s",ch);
		if(ch[1]=='n')
		{
			cnt++,scanf("%d%d",&s[cnt].x,&s[cnt].y);
			for(int i=1;i<cnt;i++) 
				if(s[cnt].x==s[i].x && s[cnt].y==s[i].y) {cnt--;break;}
		}
		if(ch[1]=='e')
		{
			int x,y;scanf("%d%d",&x,&y);
			for(int i=1;i<=cnt;i++) 
				if(x==s[i].x && y==s[i].y) std::swap(s[i],s[cnt]),cnt--;
		}
		if(ch[1]=='A')
		{
			scanf("%s",op);
			for(int i=1;i<=cnt;i++)
			{
				if(op[0]=='U') s[i].y++;
				if(op[0]=='D') s[i].y--;
				if(op[0]=='L') s[i].x--;
				if(op[0]=='R') s[i].x++;
				if(s[i].x<1 || s[i].x>n || s[i].y<1 || s[i].y>m) std::swap(s[i],s[cnt]),cnt--;
			}
		}
		if(ch[1]=='B')
		{
			scanf("%s",op);
			if(op[0]=='U') b.y++;
			if(op[0]=='D') b.y--;
			if(op[0]=='L') b.x--;
			if(op[0]=='R') b.x++;
			if(b.x<1 || b.x>n || b.y<1 || b.y>m) b=st;
		}
		if(a.x==b.x && Q) ans2++;
		for(int i=1;i<=cnt;i++) if(s[i].x==b.x && s[i].y==b.y && Q) ans1++;
	}
	printf("%d\n%d\n",ans1,ans2);
}
