#include <stdio.h>

#define MAX_N 100005

int count = 0;

int a[MAX_N];
int tmp[MAX_N];

void merge(int l, int mid, int r) {
    int i = l, j = mid + 1; // [l, mid], [mid+1, r]
    int k = l;
    while (i <= mid && j <= r) {
        if (a[i] < a[j]) {
            tmp[k++] = a[i++];
        } else {
            tmp[k++] = a[j++];
        }
    }
    while (i <= mid) {
        tmp[k++] = a[i++];
    }
    while (j <= r) {
        tmp[k++] = a[j++];
    }

    k = l;
    while (k <= r) {
        a[k] = tmp[k];
        k++;
    }
}

void mergesort(int l, int r) {
    if (l >= r) return;
    int mid = (l + r) >> 1;
    mergesort(l, mid);
    mergesort(mid + 1, r);
    merge(l, mid, r);
}

int getint() {
    char ch = getchar();
    int ret = 0;
    while (ch != EOF && !(ch >= '0' && ch <= '9')) {
        ch = getchar();
    }
    if (ch == EOF) {return -1;}
    while (ch >= '0' && ch <= '9') {
        ret = (ret << 3) + (ret << 1) + (ch ^ '0');
        ch = getchar();
    }
    return ret;
}

int main() {
    int n = getint();
    // scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        a[i] = getint();
    }
    mergesort(0, n - 1);
    for (int i = 0; i < n; i++) {
        printf("%d%c", a[i], i == n-1 ? 10 : 32);
    }
    return 0;
}

