#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;
const int N = 101000;
int n,Q;
int final[N],nex[N*2],to[N*2],tot,lastans,q[N];
void link(int x,int y){
	to[++tot] = y, nex[tot] = final[x], final[x] = tot;
}

int cnt,vis[N];
void dfs(int x,int fr,int o1) {
	cnt++;vis[x]=1;
	for (int i = final[x]; i; i=nex[i]) {
		int y = to[i]; if (y != fr) {
			if (!o1 && q[i>>1]==3) continue;
			dfs(y, x, o1 & (q[i>>1]==1));
		}
	}
}
int t[4*N][4];
void change(int x,int l,int r,int tg,int w) {
	if (l == r) {
		if (q[l]) t[x][q[l]]--;
		q[l] = w;
		t[x][q[l]]++;
		return;
	}
	if (tg <= (l+r>>1)) change(x<<1,l,l+r>>1,tg,w);
	else change(x<<1|1,(l+r>>1)+1,r,tg,w);
	for (int i = 1; i <= 3; i++) t[x][i] = t[x<<1][i] + t[x<<1|1][i];
}

void findle(int x,int l,int r,int br,int &rz) {
	if (r < br) return;
	if (!t[x][3]) return;
	if (l == r) {
		rz = l; return;
	}
	findle(x<<1,l,l+r>>1,br,rz);
	if (!rz)
		findle(x<<1|1,(l+r>>1)+1,r,br,rz);
}

void findre(int x,int l,int r,int br,int &rz) {
	if (l > br) return;
	if (!t[x][3]) return;
	if (l == r) {
		rz = l; return;
	}
	findre(x<<1|1,(l+r>>1)+1,r,br,rz);
	if (!rz)
		findre(x<<1,l,l+r>>1,br,rz);
}

bool full(int x,int l,int r,int tl,int tr) {
	if (r < tl || l > tr) return 1;
	if (tl <= l && r <= tr) {
		return t[x][2] == 0 && t[x][3] == 0;
	}
	return full(x<<1,l,l+r>>1,tl,tr) & full(x<<1|1,(l+r>>1)+1,r,tl,tr);
}
int main() {
	// freopen("b.in","r",stdin);
	// freopen("b2.out","w",stdout);
	cin>>n>>Q;
	tot=1;
	for (int i = 1; i < n; i++) {
		int u,v; scanf("%d %d",&u,&v);
		link(u,v), link(v,u);
		scanf("%d",&u); q[tot>>1] = u;
	}
	if (n > 1e4) {
		for (int i = 1; i < n; i++) {
			int ww = q[i]; q[i] = 0;
			change(1,1,n,i,ww);
		}
		for (int i = 1; i <= Q; i++) {
			int x,w,s,tt; scanf("%d %d %d %d",&x,&w,&s,&tt);
			x^=lastans,w^=lastans,s^=lastans,tt^=lastans;
			change(1,1,n,x,w);
			int l3=0,r3=0,lc=0,rc=0;
			findre(1,1,n,s-1,l3);
			if (l3 == 0) {
				lc = 1;
			} else {
				if (full(1,1,n,l3+1,s-1)) {
					int bo = 0;
					findre(1,1,n,l3-1,bo);
					if (bo == 0) lc = 1;
					else lc = bo + 1;
				} else lc = l3 + 1;
			}

			findle(1,1,n,s,r3);
			if (r3 == 0) {
				rc = n;
			} else {
				if (full(1,1,n,s,r3-1)) {
					int bo = 0;
					findle(1,1,n,r3+1,bo);
					if (bo == 0) rc = n;
					else rc = bo;
				} else rc = r3;
			}
			printf("%d %d\n",lastans=rc-lc+1,lc<=tt&&tt<=rc);
		}
		return 0;
	}
	for (int i = 1; i <= Q; i++) {
		int x,w,s,t; scanf("%d %d %d %d",&x,&w,&s,&t);
		x^=lastans,w^=lastans,s^=lastans,t^=lastans;
		q[x]=w;
		memset(vis,0,sizeof vis);
		cnt=0,dfs(s,0,1);
		printf("%d %d\n",lastans=cnt,vis[t]);
	}
}