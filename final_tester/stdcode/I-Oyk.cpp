#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;

const int MAXN = 100010;

int a[MAXN], b[MAXN];
int T, n;
LL k;

bool check(int val) {
    LL cnt = 0;
    for(int i = 0, j = n - 1; i < n; ++i) {
        while(j >= 0 && a[i] * b[j] > val) --j;
        cnt += j + 1;
    }
    return cnt >= k;
}

int solve() {
    int l = a[0] * b[0], r = a[n - 1] * b[n - 1];
    while(l < r) {
        int mid = (l + r) >> 1;
        if(!check(mid)) l = mid + 1;
        else r = mid;
    }
    return l;
}

int main(){
    scanf("%d", &T);
    while (T--){
        scanf("%d%I64d", &n, &k);
        for(int i = 0; i < n; ++i) scanf("%d", &a[i]);
        for(int i = 0; i < n; ++i) scanf("%d", &b[i]);
        sort(a, a + n);
        sort(b, b + n);
        k = (LL)n * n - k + 1;
        printf("%d\n", solve());
    }
    return 0;
}
