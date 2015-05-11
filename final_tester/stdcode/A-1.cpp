#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;

const int MAXV = 310;
const int MAXE = MAXV * MAXV;
const int INF = 0x3f3f3f3f;

bool vis[MAXV];
int mat[MAXV][MAXV], link[MAXV], id[MAXV];
int money[MAXV];
int n, m, T;

bool dfs(int u) {
    if(vis[u]) return false;
    vis[u] = true;
    for(int v = 1; v <= m; ++v) if(mat[u][v]) {
        if(!link[v] || dfs(link[v])) {
            link[v] = u;
            return true;
        }
    }
    return false;
}

bool cmp(int a, int b) {
    return money[a] > money[b];
}

int hungry() {
    for(int i = 1; i <= n; ++i) id[i] = i;
    sort(id + 1, id + n + 1, cmp);

    memset(link + 1, 0, m * sizeof(int));
    int res = 0;
    for(int i = 1; i <= n; ++i) {
        memset(vis + 1, 0, n * sizeof(bool));
        if(dfs(id[i])) res += money[id[i]];
    }
    return res;
}

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &m);
        for(int i = 1; i <= n; ++i)
            scanf("%d", &money[i]);
        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= m; ++j)
                scanf("%d", &mat[i][j]);
        printf("%d\n", hungry());
    }
}
