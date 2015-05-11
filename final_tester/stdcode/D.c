#include <stdio.h>
#include <memory.h>
#include <string.h>

#define MAXN 100010

int index(char c) {
    return (int)c - (int)'a';
}

char str[MAXN];
int cnt[26], n, m, T;

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%s%d", str, &m);
        n = strlen(str);

        memset(cnt, 0, sizeof(cnt));
        for(int i = 0; i < n; ++i)
            cnt[index(str[i])]++;

        char q;
        int op, p;
        while(m--) {
            scanf("%d", &op);
            if(op == 1) {
                scanf("%d %c", &p, &q);
                cnt[index(str[p])]--;
                cnt[index(str[p] = q)]++;
            } else {
                scanf(" %c", &q);
                printf("%d\n", cnt[index(q)]);
            }
        }
    }
    return 0;
}
