#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int MAXN = 1010;
const int MAXQ = 1000010;

int pos[MAXQ], val[MAXQ], l, r;
int dp[MAXQ];
int a[MAXN];
int n, m, T;

void push_back(int p, int v) {
    if(v == -1) return ;
    while(l != r && val[r - 1] >= v) r--;
    pos[r] = p; val[r++] = v;
}

int solve() {
    l = r = 0;
    push_back(0, 0);

    int sum = 0;
    for(int i = 0; i < n; ++i) {
        for(int j = 1; j < a[i]; ++j) {
            int p = sum + j;
            while(l != r && p - pos[l] > m) l++;
            dp[p] = (l == r ? -1 : val[l] + a[i]);
        }
        for(int j = 1; j < a[i]; ++j) {
            push_back(sum + j, dp[sum + j]);
        }
        sum += a[i];
    }
    while(l != r && sum - pos[l] > m) l++;
    return l == r ? -1 : val[l];
}

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &m);
        for(int i = 0; i < n; ++i)
            scanf("%d", &a[i]);
        printf("%d\n", solve());
    }
}

