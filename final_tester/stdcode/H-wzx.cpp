#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXV = 201;
const int MAXE = 40010;

int head[MAXV], to[MAXE], Next[MAXE], ecnt;
int link[MAXV];
bool vis[MAXE];

void init_edge(){
    ecnt = 0;
    memset(head, -1, sizeof(head));
    memset(link, 0, sizeof(link));
}
void add_edge(int u, int v){
    Next[ecnt] = head[u]; to[ecnt] = v; head[u] = ecnt++;
}

bool dfs(int u){
    for (int i = head[u]; i != -1; i = Next[i]){
        int v = to[i];
        if (vis[v]) continue; vis[v] = true;

        if (!link[v] || dfs(link[v])){
            link[v] = u;
            return true;
        }
    }
    return false;
}

int n, ans;
char c;

int main(){
    while (scanf("%d", &n)!= EOF){
        init_edge();
        for (int i = 1; i <= n; ++i){
            getchar();
            for (int j = 1; j <= n; ++j){
                c = getchar();
                if (c == 'U') add_edge(i, j);
            }
        }

        ans = 0;
        for (int i = 1; i <= n; ++i){
            memset(vis, false, sizeof(vis));
            if (dfs(i)) ++ans;
        }

        if (ans == n) puts("YES");
        else puts("NO");
    }
    return 0;
}
