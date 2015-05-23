#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <numeric>
using namespace std;
typedef long long LL;

int a[3010];
int n;

int main() {
    scanf("%d", &n);
    for(int i = 0; i < n; ++i) scanf("%d", &a[i]);
    sort(a, a + n);
    int last = -1, res = 0;
    for(int i = 0; i < n; ++i) {
        if(a[i] > last) last = a[i];
        else res += ++last - a[i];
    }
    printf("%d\n", res);
}
