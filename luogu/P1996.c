#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct LNode {
    int val;
    struct LNode *next;
}LNode, *llist;
LNode _Pool[100005], *pool_sp = _Pool;
#define NEWNODE(x) (pool_sp->val=(x), pool_sp++)
llist buildLoopList(int n) {
    llist head = NEWNODE(1);
    llist tail = head;
    for (int i = 2; i <= n; i++) {
        llist nxt = NEWNODE(i);
        tail->next = nxt;
        tail = nxt;
    }
    tail->next = head;
    return tail;
}
void rm(llist pre) {
    llist del = pre->next;
    pre->next = del->next;
    printf("%d ", del->val);
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    llist cur = buildLoopList(n);
    while (cur->next != cur) {
        for (int i = 1; i < m; i++) {
            cur = cur->next;
        }
        rm(cur);
    }
    printf("%d", cur->val);


    return 0;
}