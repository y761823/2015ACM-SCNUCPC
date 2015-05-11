#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 110000;

int head[MAXN * 2], to[MAXN * 2], Next[MAXN * 2], val[MAXN * 2], cnt;
int dist[MAXN * 2], n, a[MAXN];

void init_edge(){
    memset(head, -1, sizeof(head));
    cnt = 0;
}
void add_edge(int u, int v, int w){
    Next[cnt] = head[u]; to[cnt] = v; val[cnt] = w; head[u] = cnt++;
    Next[cnt] = head[v]; to[cnt] = u; val[cnt] = w; head[v] = cnt++;
}

void dfs(int u, int fa){
    for (int i = head[u]; i != -1; i = Next[i]){
        int v = to[i];
        if (v == fa) continue;

        dist[v] = dist[u] ^ val[i];
        dfs(v, u);
    }
}

int ch[MAXN * 80][2], num[MAXN * 80], tcnt;
void init_trie(){
    tcnt = 0;
    memset(ch[0], 0, sizeof(ch[0]));
}
void Insert(int x){
    int u = 0;
    for (int i = 30; i >= 0; --i){
        int v = x & (1 << i);
        if (v) v = 1;

        if (!ch[u][v]){
            ch[u][v] = ++tcnt;
            memset(ch[tcnt], 0, sizeof(ch[tcnt]));
        }
        u = ch[u][v];
    }
    num[u] = x;
}
int Find(int x){
    int u = 0;
    for (int i = 30; i >= 0; --i){
        int v = x & (1 << i);
        if (v) v = 1;

        if (ch[u][1-v]) u = ch[u][1-v];
        else if (ch[u][v]) u = ch[u][v];
        else break;
    }
    return x ^ num[u];
}

void init(){
    init_edge();
    init_trie();
    memset(dist, 0, sizeof(dist));
}

int main(){
    while (scanf("%d", &n) != EOF){
        init();
        for (int i = 1; i < n; ++i){
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            add_edge(u, v, w);
        }
        dfs(0, -1);

        int ans = 0;
        for (int i = 0; i < n; ++i){
            ans = max(ans, Find(dist[i]));
            Insert(dist[i]);
        }
        printf("%d\n", ans);
    }
    return 0;
}
