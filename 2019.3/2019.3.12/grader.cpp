#include "coin.h"
#include <iostream>
#include <assert.h>

using namespace std;

using u64 = unsigned long long;
using i64 = long long;

static struct random_t {
	u64 s0, s1;
	random_t(){
		s0 = 0x0123456789abcdef;
		s1 = 0xfedcba9876543210;
	}
	random_t(u64 s0, u64 s1):s0(s0), s1(s1){}
	u64 get(){
		std::swap(s0, s1);
		s1 ^= s1 << 23, s1 ^= (s1 >> 17) ^ s0 ^ (s0 >> 26);
		return s0 + s1;
	}
	int randint(int L, int R){
		return get() % (R - L + 1) + L;
	}
} rnd;

static int Test;
static string coin;
static int queries;

struct info{};

int ask(string guess){
	++queries;
	assert(guess.size() == 100);
	int ret = 0, x;
	for (x = 0; x < 100; ++x) {
		assert(guess[x] == '0' || guess[x] == '1');
		if (guess[x] == coin[x]) {
			++ret;
		}
	}
	if (ret == 100) {
		throw info();
	}
	x = rnd.randint(0, 99);
	if (guess[x] == coin[x]) {
		coin[x] ^= 1;
	}
//	for(int i=0;i<100;i++) printf("%c", coin[i]);puts("");
	return ret;
}

int main(){
	freopen ("coin.in","r",stdin);
//	freopen ("coin.out","w",stdout);
	cin >> rnd.s0 >> rnd.s1;
	double answer = 100;
	for (cin >> Test; Test; --Test) {
		double point = 0;
		cin >> coin;
		assert(coin.size() == 100);
		try {
			guess();
		} catch (info suc) {
			if (queries <= 200) point = 100;
			else if (queries <= 600) point = 120 - 0.15 * queries;
			else point = 36 - 0.01 * queries;
			if (point < 0) point = 0;
			queries = 0;
		}
		answer = min(answer, point);
		if (answer == 0) break;
	}
	if (Test) printf("Wrong Answer!\n");
	else printf("point = %.2lf\n", answer);
}
