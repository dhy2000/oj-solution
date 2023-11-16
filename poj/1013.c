#include <stdio.h>
#include <string.h>
#include <assert.h>

char k1[3][15], k2[3][15];
char v[3][15];

int verify(char coin, int sign) {
    int weight[12];
    for (int i = 0; i < 12; i++)
        weight[i] = 1;
    weight[(int)(coin - 'A')] += sign;
    for (int i = 0; i < 3; i++) {
         int w_left = 0, w_right = 0;
        for (int j = 0; k1[i][j]; j++) {
            w_left += weight[(int)(k1[i][j] - 'A')];
        }
        for (int j = 0; k2[i][j]; j++) {
            w_right += weight[(int)(k2[i][j] - 'A')];
        }
        // fprintf(stderr, "coin = %c, sign = %d: i = %d, w_left = %d, w_right = %d\n", coin, sign, i, w_left, w_right);
        if (w_left == w_right && strcmp(v[i], "even") == 0) continue;
        if (w_left > w_right && strcmp(v[i], "up") == 0) continue;
        if (w_left < w_right && strcmp(v[i], "down") == 0) continue;
        return 0;
    }
    return 1;
}

int main() {
    int n; scanf("%d", &n);
    while (n--) {
        for (int i = 0; i < 3; i++) {
            scanf("%s %s %s", k1[i], k2[i], v[i]);
        }
        int cnt = 0;
        for (int sign = -1; sign <= 1; sign += 2) {
            for (char uniq = 'A'; uniq <= 'L'; uniq++) {
                if (verify(uniq, sign)) {
                    cnt++;
                    printf("%c is the counterfeit coin and it is %s.\n", uniq, (sign < 0 ? "light" : "heavy"));
                }
            }
        }
        assert(cnt == 1);
    }

    return 0;
}