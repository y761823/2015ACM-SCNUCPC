#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;

const int MAXN = 210;

char mat[MAXN][MAXN];
int link[MAXN];
bool vis[MAXN];
int n;

bool dfs(int u) {
    if(vis[u]) return false;
    vis[u] = true;
    for(int v = 1; v <= n; ++v) if(mat[u][v] == 'U') {
        if(!link[v] || dfs(link[v])) {
            link[v] = u;
            return true;
        }
    }
    return false;
}

bool solve() {
    memset(link + 1, 0, n * sizeof(int));
    int res = 0;
    for(int i = 1; i <= n; ++i) {
        memset(vis + 1, 0, n * sizeof(bool));
        res += dfs(i);
    }
    return res == n;
}

int main() {
    while(scanf("%d", &n) != EOF) {
        for(int i = 1; i <= n; ++i)
            scanf("%s", &mat[i][1]);
        puts(solve() ? "YES" : "NO");
    }
}
