#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;

const int MAXV = 100010;
const int MAXE = 200010;

int head[MAXV], path[MAXV], ecnt;
int to[MAXE], nxt[MAXE], cost[MAXE];
int n;

void init_graph() {
    memset(head, -1, n * sizeof(int));
    ecnt = 0;
}

void add_edge(int u, int v, int c) {
    to[ecnt] = v; cost[ecnt] = c; nxt[ecnt] = head[u]; head[u] = ecnt++;
    to[ecnt] = u; cost[ecnt] = c; nxt[ecnt] = head[v]; head[v] = ecnt++;
}

void dfs(int u, int f, int val) {
    path[u] = val;
    for(int p = head[u]; ~p; p = nxt[p]) {
        int v = to[p];
        if(v == f) continue;
        dfs(v, u, val ^ cost[p]);
    }
}

struct Node {
    Node *go[2];
} StatePool[MAXV * 30], *rt;
int ncnt;

Node *new_node() {
    return StatePool + ncnt++;
}

void init_trie() {
    memset(StatePool, 0, ncnt * sizeof(Node));
    ncnt = 0;
    rt = new_node();
}

void insert(int val) {
    Node *p = rt;
    for(int k = 30; k >= 0; --k) {
        int i = (val >> k) & 1;
        if(!p->go[i]) p->go[i] = new_node();
        p = p->go[i];
    }
}

int get_max(int val) {
    Node *p = rt;
    int res = 0;
    for(int k = 30; k >= 0; --k) {
        int i = (val >> k) & 1;
        if(p->go[i ^ 1]) {
            res |= (1 << k);
            p = p->go[i ^ 1];
        } else p = p->go[i];
    }
    return res;
}

int main() {
    while(scanf("%d", &n) != EOF) {
        init_graph();
        for(int i = 1, a, b, c; i < n; ++i) {
            scanf("%d%d%d", &a, &b, &c);
            add_edge(a, b, c);
        }
        dfs(0, -1, 0);
        init_trie();
        int res = 0;
        for(int i = 0; i < n; ++i)
            insert(path[i]), res = max(res, get_max(path[i]));
        printf("%d\n", res);
    }
}
