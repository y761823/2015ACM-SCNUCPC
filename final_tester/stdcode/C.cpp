#include <bits/stdc++.h>
using namespace std;

const int MAXN = 50010;

int a[MAXN], fix[MAXN], rk[MAXN], tree[MAXN], ord[MAXN];
int T, n, k;

inline int lowbit(int x) {
    return x & -x;
}

void modify(int v, int val) {
    while(v <= n) {
        tree[v] += val;
        v += lowbit(v);
    }
}

int get_sum(int v) {
    int res = 0;
    while(v > 0) {
        res += tree[v];
        v -= lowbit(v);
    }
    return res;
}

bool check(int val) {
    for(int i = 1; i <= n; ++i)
        modify(i, 1);
    int cnt = 0;
    for(int i = 1; i <= n; ++i) {
        cnt += get_sum(upper_bound(ord + 1, ord + n + 1, val) - ord - 1);
        val += a[i];
        modify(rk[i], -1);
    }
    return k <= cnt;
}

int solve() {
    for(int i = 1; i <= n; ++i) ord[i] = i;
    sort(ord + 1, ord + n + 1, [&](int a, int b) {
        return fix[a] < fix[b];
    });
    for(int i = 1; i <= n; ++i) rk[ord[i]] = i;
    for(int i = 1; i <= n; ++i) ord[i] = fix[ord[i]];

    int l = *min_element(a + 1, a + n + 1);
    int r = *max_element(a + 1, a + n + 1);
    if(l < 0) l *= n;
    if(r > 0) r *= n;

    while(l < r) {
        int mid = l + (r - l) / 2;
        if(!check(mid)) l = mid + 1;
        else r = mid;
    }
    return l;
}

int bruce_force() {
    vector<int> sum;
    for(int i = 1; i <= n; ++i)
        for(int j = i; j <= n; ++j)
            sum.push_back(fix[j] - fix[i - 1]);
    sort(sum.begin(), sum.end());
    //for(auto x : sum) printf("%d ", x); puts("");
    return sum[k - 1];
}

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &k);
        for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);
        for(int i = 1; i <= n; ++i) fix[i] = fix[i - 1] + a[i];
        //printf("#debug %d\n", bruce_force());
        printf("%d\n", solve());
    }
}
