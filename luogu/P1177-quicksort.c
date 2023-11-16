#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000005
int data[MAXN];
int n, x;

inline static void swapv(int *p, int *q) {
    int tmp = *p;
    *p = *q;
    *q = tmp;
}

int partition(int *data, int left, int right, int *pend) {
    if (right - left > 1) {
        int mid = left + ((right - left) >> 1);
        if (data[left] > data[mid]) swapv(&data[left], &data[mid]);
        if (data[left] > data[right]) swapv(&data[left], &data[right]);
        if (data[mid] > data[right]) swapv(&data[mid], &data[right]);
        swapv(&data[mid], &data[left]);
    }
    int i = left, j = right + 1;
    int p = left + 1, q = right; // to optimize duplicate
    int pivot = data[left];
    
    while (i < j) {
        do {j--;} while (j > i && data[j] > pivot);
        do {i++;} while (i < j && data[i] < pivot);
        if (i < j) {
            swapv(&data[i], &data[j]);
            if (data[i] == pivot) {
                swapv(&data[i], &data[p]);
                p++;
            }
            if (data[j] == pivot) {
                swapv(&data[j], &data[q]);
                q--;
            }
        }
    }
    swapv(&data[j], &data[left]);
    // restore duplicate elements
    i = j - 1; j++;
    int k = (data[left] == pivot ? left : left + 1);
    for (; k < p && i >= p; k++, i--)
        swapv(&data[k], &data[i]);
    i -= (p - k - 1);
    if (i < left) i = left;
    if (i == left + 1 && data[left] == pivot) i = left;
    for (k = right; k > q && j <= q; k--, j++)
        swapv(&data[k], &data[j]);
    j += (k - q - 1);
    if (j > right) j = right;
    if (pend) *pend = j; // data[j] > pivot
    return i; // data[i] < pivot
}

// return the pivot of this row of quicksort
void quicksort(int *data, int left, int right) {
    if (left >= right) return ;
    int r;
    int k = partition(data, left, right, &r);
    // [k, r] == v
    quicksort(data, left, k - 1);
    quicksort(data, r + 1, right);
}

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &data[i]);
    }

    quicksort(data, 0, n - 1);

    for (int i = 0; i < n; i++) {
        printf("%d", data[i]);
        if (i < n - 1) putchar(32);
    }

    return 0;
}

/*
10
1 3 2 4 5 7 6 8 9 1
*/