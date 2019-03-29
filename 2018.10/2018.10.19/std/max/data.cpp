#include <cstdio>
#include <cstdlib>
#include <ctime>

using namespace std;



int mx = 7000000;
int R() {
    return rand() % mx + 1;
}

int main() {
    freopen("max.in", "w", stdout);
    srand(time(0));
    
    int n = 10000000, m = 10000000;

    int gen = R();
    int cute1 = 20000527;
    int cute2 = 20000909;

    printf("%d %d\n", n, m);
    printf("%d %d %d", gen, cute1, cute2);

    
}