#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;

const int MAXV = 310;
const int MAXE = MAXV * MAXV;
const int INF = 0x3f3f3f3f;

struct ZEK_FLOW {
    int head[MAXV << 1], dis[MAXV << 1];
    int next[MAXE], to[MAXE], cap[MAXE], cost[MAXE];
    int n, ecnt, st, ed;

    void init() {
        memset(head, -1, sizeof(head));
        ecnt = 0;
    }

    void add_edge(int u, int v, int c, int w) {
        to[ecnt] = v; cap[ecnt] = c; cost[ecnt] = w; next[ecnt] = head[u]; head[u] = ecnt++;
        to[ecnt] = u; cap[ecnt] = 0; cost[ecnt] = -w; next[ecnt] = head[v]; head[v] = ecnt++;
    }

    void SPFA() {
        for(int i = 1; i <= n; ++i) dis[i] = INF;
        priority_queue<pair<int, int> > que;
        dis[st] = 0; que.push(make_pair(0, st));
        while(!que.empty()) {
            int u = que.top().second, d = -que.top().first; que.pop();
            if(d != dis[u]) continue;
            for(int p = head[u]; ~p; p = next[p]) {
                int &v = to[p];
                if(cap[p] && dis[v] > d + cost[p]) {
                    dis[v] = d + cost[p];
                    que.push(make_pair(-dis[v], v));
                }
            }
        }
        int t = dis[ed];
        for(int i = 1; i <= n; ++i) dis[i] = t - dis[i];
    }

    int minCost, maxFlow;
    bool vis[MAXV << 1];

    int add_flow(int u, int aug) {
        if(u == ed) {
            maxFlow += aug;
            minCost += dis[st] * aug;
            return aug;
        }
        vis[u] = true;
        int now = aug;
        for(int p = head[u]; ~p; p = next[p]) {
            int &v = to[p];
            if(cap[p] && !vis[v] && dis[u] == dis[v] + cost[p]) {
                int t = add_flow(v, min(now, cap[p]));
                cap[p] -= t;
                cap[p ^ 1] += t;
                now -= t;
                if(!now) break;
            }
        }
        return aug - now;
    }

    bool modify_label() {
        int d = INF;
        for(int u = 1; u <= n; ++u) if(vis[u]) {
            for(int p = head[u]; ~p; p = next[p]) {
                int &v = to[p];
                if(cap[p] && !vis[v]) d = min(d, dis[v] + cost[p] - dis[u]);
            }
        }
        if(d == INF) return false;
        for(int i = 1; i <= n; ++i) if(vis[i]) dis[i] += d;
        return true;
    }

    int min_cost_flow(int ss, int tt, int nn) {
        st = ss, ed = tt, n = nn;
        minCost = maxFlow = 0;
        SPFA();
        while(true) {
            while(true) {
                for(int i = 1; i <= n; ++i) vis[i] = 0;
                if(!add_flow(st, INF)) break;
            }
            if(!modify_label()) break;
        }
        return minCost;
    }
} G;

int money[MAXV];
int n, m, T;

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &m);
        for(int i = 1; i <= n; ++i)
            scanf("%d", &money[i]);

        G.init();
        int ss = n + m + 1, tt = ss + 1, x;
        for(int i = 1; i <= n; ++i)
            G.add_edge(ss, i, 1, -money[i]);
        for(int j = 1; j <= m; ++j)
            G.add_edge(j + n, tt, 1, 0);
        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= m; ++j) {
                scanf("%d", &x);
                if(x == 1) G.add_edge(i, n + j, 1, 0);
            }
        printf("%d\n", -G.min_cost_flow(ss, tt, tt));
    }
}
