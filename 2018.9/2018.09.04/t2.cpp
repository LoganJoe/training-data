#include<bits/stdc++.h>
#define N 500005
#define ll long long
int n,k,A[N],B[N],med[N],mark[N],sqr,blo=1,intoset;
ll ans;
class Segment_Tree
{
#define lc x<<1
#define rc x<<1|1
#define mid ((l+r)>>1)
	struct tree
	{
		int v,tag;
	}t[N<<2];
	void pushup(int x){t[x].v=std::min(t[lc].v,t[rc].v);}
	void pushdown(int x)
	{
		if(!t[x].tag) return ;
		t[lc].v+=t[x].tag,t[rc].v+=t[x].tag;
		t[lc].tag+=t[x].tag,t[rc].tag+=t[x].tag;
		t[x].tag=0;
	}
public:
	void bulid(int x,int l,int r)
	{
		t[x].v=1e9;
		if(l==r) return (void)(t[x].v=med[l]);
		bulid(lc,l,mid),bulid(rc,mid+1,r);
		pushup(x);
	}
	void modify(int x,int l,int r,int ql,int qr,int v)
	{
		if(ql<=l && r<=qr) return (void)(t[x].v+=v,t[x].tag+=v);
		pushdown(x);
		if(ql<=mid) modify(lc,l,mid,ql,qr,v);
		if(qr>mid) modify(rc,mid+1,r,ql,qr,v);
		pushup(x);
	}
	int find(int x,int l,int r,int ql,int qr)
	{
		if(t[x].v>0) return 0;
		if(l==r && t[x].v==0) return l;
		pushdown(x); 
		int res=0;
		if(qr>mid) res=find(rc,mid+1,r,ql,qr);
		if(ql<=mid && !res) res=find(lc,l,mid,ql,qr);
		return res; 
	}
	int query(int x,int l,int r,int p)
	{
		if(l==r) return t[x].v;
		pushdown(x);
		if(p<=mid) return query(lc,l,mid,p);
		else return query(rc,mid+1,r,p);
	}
}T;

struct node
{
	int l,r,val;
	friend bool operator <(node t1,node t2)
	{
		return t1.val>t2.val;
	}
};
std::set<node> s;
std::set<node>::iterator it;
std::vector<int> a;
void reset()
{
	for(int i=1;i<=n;i++) med[i]=T.query(1,1,n,i);
	for(int i=1,pre=1;i<=n+1;i++)
		if(med[i]==0 && med[i-1]!=0 && i>1) s.insert((node){pre,i-1,a[i-2]-B[pre]}),pre=i;
		else if(med[i]==0) pre=i;
		
}
int main()
{
	freopen("bulb.in","r",stdin);
	freopen("bulb.out","w",stdout);
	scanf("%d%d",&n,&k);sqr=sqrt(n);
	for(int i=1;i<=n;i++) scanf("%d",&A[i]);
	for(int i=1;i<=n;i++) scanf("%d",&B[i]);
	std::sort(A+1,A+1+n);
	std::sort(B+1,B+1+n);
	for(int i=1;i<=n;i++) if(A[i]<B[i]) A[i]=B[i],k--;
	if(k<0) return puts("-1"),0;
	/*
	printf("%d\n",k);
	for(int i=1;i<=n;i++) printf("%d ",A[i]);
	puts("");
	*/
	for(int i=1,j=1;i<=n;i++)
	{
		while(A[j]<B[i]) j++;
		med[i]=i-j;
	}
	for(int i=1;i<=n;i++) if(med[i]==0) blo++;
	for(int i=1;i<=n;i++) a.push_back(A[i]);
	T.bulid(1,1,n);
	while(k--)
	{
		if(blo<sqr)
		{
			int pos=n,Max=0,l,r;
			blo=1;
			while(pos)
			{
				int p=T.find(1,1,n,1,pos);
				if(!p) break;
				if(pos-p==0) {pos=p-1;continue;}
				//p+1 --- pos
				int delt=a[pos-1]-B[p];
				if(delt>Max) Max=delt,l=p,r=pos;
				pos=p-1;
				blo++;
			} 
			a.insert(a.begin()+l-1,B[l]);
			a.erase(a.begin()+r);
			T.modify(1,1,n,l+1,r,-1);
		}
		else
		{
			
			if(intoset==0) reset(),intoset=1;
			it=s.begin();
			int l=(*it).l,r=(*it).r;
			a.insert(a.begin()+l-1,B[l]);
			a.erase(a.begin()+r);
			int pos[N],cnt=0;
			for(int i=l;i<=r;i++)
			{
				med[i]--;
				if(med[i]==0) pos[++cnt]=i;
			}
			s.erase(it);
			pos[0]=l,pos[cnt+1]=r+1;
			for(int i=1;i<=cnt+1;i++)
			if(pos[i-1]!=pos[i]) s.insert((node){pos[i-1],pos[i]-1,a[pos[i]-2]-B[pos[i-1]]});
			
		}
	}
	for(int i=0;i<a.size();i++) ans+=a[i];
	std::cout<<ans<<"\n";
	
}
