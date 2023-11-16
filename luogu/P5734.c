#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char text[1005];
void concat(const char *str) {
    strcat(text, str);
    puts(text);
}
void cut(int a, int b) {
    char tmp[1005] = {};
    strncpy(tmp, text + a, b);
    strcpy(text, tmp);
    puts(text);
}
void insert(int a, const char *str) {
    char tmp[1005] = {};
    strncpy(tmp, text, a);
    strcat(tmp, str);
    strcat(tmp, text + a);
    strcpy(text, tmp);
    puts(text);
}
void query(const char *str) {
    char tmp[1005] = {};
    char *cur = strstr(text, str);
    if (cur == NULL) {
        puts("-1");
        return ;
    }
    printf("%d\n", cur - text);
}
int main()
{
    int op, a, b;
    char str[1005];
    int n;
    scanf("%d", &n);
    scanf("%s", text);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &op);
        switch (op) {
            case 1:
                scanf("%s", str);
                concat(str);
                break;
            case 2:
                scanf("%d %d", &a, &b);
                cut(a, b);
                break;
            case 3:
                scanf("%d %s", &a, str);
                insert(a, str);
                break;
            case 4:
                scanf("%s", str);
                query(str);
                break;
            default :;
        }
    }
    return 0;
}
/*
4
ILove
1 Luogu
2 5 5
3 3 guGugu
4 gu
*/