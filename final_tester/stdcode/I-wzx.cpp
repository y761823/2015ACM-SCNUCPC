#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 110000;

int a[MAXN], b[MAXN], t, n;
long long k;

int solve2(int val, int v){
    int l = 1, r = n + 1;
    while (l < r){
        int m = (l + r) >> 1;

        if (val * b[m] <= v) l = m + 1;
        else r = m;
    }
    return l;
}

long long calc(int v){
    long long num = 0;
    for (int i = 1; i <= n; ++i)
        num += n - solve2(a[i], v) + 1;
    return num;
}

int solve(){
    int l = 1, r = a[n] * b[n] + 1;
    while (l < r){
        int m = (l + r) >> 1;

        if (calc(m) >= k) l = m + 1;
        else r = m;
    }
    return l;
}

int main(){
    scanf("%d", &t);
    while (t--){
        scanf("%d%I64d", &n, &k);
        for (int i = 1; i <= n; ++i)
            scanf("%d", &a[i]);
        for (int i = 1; i <= n; ++i)
            scanf("%d", &b[i]);
        sort(a + 1, a + 1 + n);
        sort(b + 1, b + 1 + n);

        //k = n * n - k + 1;
        printf("%d\n", solve());
    }
    return 0;
}
