#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;

long long n,k,ans,dp[1010][1010],sum[1010][1010];
const long long mod = 998244353;

void add(int p,int id,long long num){
	while(p <= n){
		sum[p][id] += num;
		sum[p][id] %= mod;
		p += p&-p;
	}
}

long long get(int p,int id){
	long long ret = 0;
	while(p){
		ret += sum[p][id];
		ret %= mod;
		p -= p&-p;
	}
	return ret;
}

int main(){
	cin >> n >> k;
	for(int i = 1;i <= n;i++){
		dp[i][i] = 1;
		add(i,i,1);
	}
	for(int K = 2;K < k;K++){
		for(int i = n;i >= 1;i--){
			add(i,n+1,-dp[i][n+1]);
			dp[i][n+1] = 0;
			for(int s = n-i+1;s <= n+1;s++){
				dp[i][n+1] += get(i-1,s);
				add(i,n+1,get(i-1,s));
			}
			for(int s = i;s <= n;s++){
				add(i,s,get(i-1,s-i)-dp[i][s]);
				dp[i][s] = get(i-1,s-i);
			}
		}
	}
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= n+1;j++){
			ans += 1ll*(j-i-1)*dp[i][j];
			ans %= mod;
		}
	}
	cout << ans;
	return 0;
}
