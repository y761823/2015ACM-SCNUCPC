#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <cassert>
using namespace std;
typedef long long LL;

const int MAXN = 50010;

struct Line {
    int y, x_st, x_ed, flag;
    Line() {}
    Line(int y, int x_st, int x_ed, int flag):
        y(max(0, y)), x_st(max(0, x_st)), x_ed(max(0, x_ed)), flag(flag) {}
    bool operator < (const Line &rhs) const {
        return y < rhs.y;
    }
};

Line a[MAXN * 2];
int tree[MAXN * 4], sum[MAXN * 4];

void update(int x, int l, int r, int a, int b, int val) {
    int ll = x << 1, rr = ll | 1, mid = (l + r) >> 1;
    if(a <= l && r <= b) {
        tree[x] += val;
        if(tree[x] > 0) sum[x] = r - l;
        else if(r - l == 1) sum[x] = 0;
        else sum[x] = sum[ll] + sum[rr];
    } else {
        if(a < mid) update(ll, l, mid, a, b, val);
        if(mid < b) update(rr, mid, r, a, b, val);
        if(tree[x] == 0) sum[x] = sum[ll] + sum[rr];
        else sum[x] = r - l;
    }
}

LL solve(int n, int size) {
    sort(a, a + n);
    LL ans = 0;
    for(int i = 0; i < n; ++i) {
        assert(a[i].x_ed > a[i].x_st);
        if(i > 0) ans += (a[i].y - a[i - 1].y) * LL(sum[1]);
        assert(a[i].x_ed <= size);
        update(1, 0, size, a[i].x_st, a[i].x_ed, a[i].flag);
    }
    return ans;
}

int x[MAXN], y[MAXN];
int n, m, w, h, k, T;

LL calc() {
    if(w > n || h > m) return 0;
    int cnt = 0;
    for(int i = 0; i < k; ++i) {
        a[cnt++] = Line(y[i] - h            , x[i] - w, min(n - w + 1, x[i]), 1);
        a[cnt++] = Line(min(m - h + 1, y[i]), x[i] - w, min(n - w + 1, x[i]), -1);
    }
    return max(0LL, LL(n - w + 1) * (m - h + 1) - solve(cnt, n - w + 1));
}

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d%d%d%d", &n, &m, &w, &h, &k);
        for(int i = 0; i < k; ++i)
            scanf("%d%d", &x[i], &y[i]);

        LL res = calc();
        if(w != h) swap(w, h), res += calc();
        cout<<res<<endl;
    }
}
