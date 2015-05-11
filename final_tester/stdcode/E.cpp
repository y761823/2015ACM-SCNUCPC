#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <cassert>
using namespace std;
#define FOR(i, n) for(int i = 0; i < n; ++i)

const int MAXN = 50010;
const int MAXLEN = 1000010;
const int MAXS = 5;

struct Node {
    Node *go[MAXS];
    int val, cnt, weight;

    Node *ch[2], *fa;
    int size;
    int maxv, add;
} StatePool[MAXLEN], *rt, *nil, *trie;
int ncnt;

Node* pos[MAXN];
int value[MAXN];
char s[MAXLEN];
int n, m, T;

void modify_add(Node *x, int diff) {
    if(x != nil) {
        x->val += diff;
        x->maxv += diff;
        x->add += diff;
    }
}

void pushdown(Node *x) {
    if(x->add) {
        FOR(k, 2) modify_add(x->ch[k], x->add);
        x->add = 0;
    }
}

void update(Node *x) {
    x->size = x->ch[0]->size + x->ch[1]->size + 1;
    x->maxv = max(x->val, max(x->ch[0]->maxv, x->ch[1]->maxv));
}

Node* new_node(int size = 0) {
    Node* x = StatePool + ncnt++;
    x->fa = x->ch[0] = x->ch[1] = nil;
    x->size = size;
    return x;
}

Node* find_kth(Node *x, int k) {
    int size = x->ch[0]->size;
    if(size >= k) return find_kth(x->ch[0], k);
    if(size + 1 == k) return x;
    return find_kth(x->ch[1], k - size - 1);
}

void rotate(Node *x) {
    Node *y = x->fa;
    int t = (y->ch[1] == x);

    (y->fa->ch[y->fa->ch[1] == y] = x)->fa = y->fa;
    (y->ch[t] = x->ch[t ^ 1])->fa = y;
    (x->ch[t ^ 1] = y)->fa = x;
    update(y);
}

void push(Node *x) {
    if(x != nil) {
        push(x->fa);
        pushdown(x);
    }
}

void splay(Node *x, Node *top) {
    push(x);
    while(x->fa != top) {
        Node *f = x->fa, *ff = f->fa;
        if(ff != top) rotate((ff->ch[1] == f) == (f->ch[1] == x) ? f : x);
        rotate(x);
    }
    update(x);
    if(top == nil) rt = x;
}

void _insert(Node* &x, Node *f, int k, Node *p) {
    if(x == nil) {
        x = p;
        p->fa = f;
    } else {
        pushdown(x);
        int size = x->ch[0]->size;
        if(size >= k) _insert(x->ch[0], x, k, p);
        else _insert(x->ch[1], x, k - size - 1, p);
    }
    update(x);
}
void insert(Node* x, int k, Node *p) {
    _insert(x, nil, k, p);
    splay(p, nil);
}

int order(Node *x) {
    splay(x, nil);
    return x->ch[0]->size + 1;
}

void init() {
    memset(StatePool, 0, ncnt * sizeof(Node));
    ncnt = 0;
    nil = StatePool;
    nil = new_node();
    trie = rt = new_node(1);
    insert(rt, 0, new_node(1));
    insert(rt, 2, new_node(1));
}

void build(char s[], int id) {
    int len = strlen(s), z = 0;
    Node *p = trie;
    for(int& i = z; i < len; ++i) {
        int idx = s[i] - 'a';
        if(!p->go[idx]) break;
        p = p->go[idx];
        pos[id] = p;
    }
    p = trie;
    for(int i = 0, v = 0; i < len; ++i) {
        int idx = s[i] - 'a';
        p->cnt += len - z;
        v += p->weight;
        if(!p->go[idx]) {
            for(; i < len; ++i) {
                int idx = s[i] - 'a';
                Node *x = new_node(1);
                x->cnt = len - i; x->val = x->maxv = v;
                insert(rt, order(p), x);
                p->go[idx] = x;
                pos[id] = p = p->go[idx];
            }
            break;
        }
        p = p->go[idx];
    }
}

void maintain(int l, int c, int val) {
    splay(find_kth(rt, l - 1), nil);
    splay(find_kth(rt->ch[1], c + 1), rt);
    modify_add(rt->ch[1]->ch[0], val);
    update(rt->ch[1]); update(rt);
}

void modify_val(int val, int id) {
    assert(val >= 0);
    if(val < 0) val = 0;
    int diff = val - value[id];
    pos[id]->weight += diff;
    maintain(order(pos[id]), pos[id]->cnt, diff);
    value[id] = val;
}

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &m);
        init();
        for(int i = 1; i <= n; ++i) {
            scanf("%s", s);
            build(s, i);
        }
        for(int i = 1, x; i <= n; ++i) {
            value[i] = 0;
            scanf("%d", &x);
            modify_val(x, i);
        }
        char op[5];
        for(int i = 0, last_ans = 0, x, y; i < m; ++i) {
            scanf("%s", op);
            if(*op == 'Q') printf("%d\n", last_ans = rt->maxv);
            if(strcmp(op, "Cv") == 0) {
                scanf("%d%d", &x, &y);
                modify_val(y, x);
            }
            if(strcmp(op, "Cs") == 0) {
                scanf("%d%s", &x, s);
                int delt = last_ans % MAXS;
                for(int j = 0; s[j]; ++j) {
                    int t = s[j] - 'a' + delt;
                    if(t >= MAXS) t -= MAXS;
                    s[j] = 'a' + t;
                }
                int tmp = value[x];
                modify_val(0, x);
                build(s, x);
                modify_val(tmp, x);
            }
        }
    }
}
