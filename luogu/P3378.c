#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
/* ------ Declaration of Max Heap ------ */

int cmpint(int a, int b) {
    if (a == b) return 0;
    else return a < b ? 1 : -1;
} // if min-heap, return b - a;

#define MAX_HEAPSIZE 1000005
typedef struct Heap {
    // starts with index 1
    int siz;
    bool isdel;
    int elm[MAX_HEAPSIZE];
}Heap;
bool h_empty(Heap *heap) {
    return heap->siz == 0;
}
int h_size(Heap *heap) {
    return heap->siz;
}

void siftup(Heap *heap, int pos) {
    int tmp = heap->elm[pos];
    while (pos > 1) {
        int fa = pos >> 1;
        if (cmpint(tmp, heap->elm[fa]) > 0) heap->elm[pos] = heap->elm[fa];
        else break;
        pos = fa;
    }
    heap->elm[pos] = tmp;
}
void siftdown(Heap *heap, int pos) {
    int tmp = heap->elm[pos];
    while (pos < heap->siz) {
        int nxt = pos << 1;
        if (nxt > heap->siz) break;
        if (nxt + 1 <= heap->siz && cmpint(heap->elm[nxt], heap->elm[nxt + 1]) < 0) {
            nxt = nxt + 1;
        }
        if (cmpint(tmp, heap->elm[nxt]) > 0) break;
        heap->elm[pos] = heap->elm[nxt];
        pos = nxt;
    }
    heap->elm[pos] = tmp;
}

void h_push(Heap *heap, int x) {
    if (heap->isdel) {
        heap->elm[1] = x;
        siftdown(heap, 1);
        heap->isdel = false;
    }
    else {
        heap->elm[++heap->siz] = x;
        siftup(heap, heap->siz);
    }
}
void h_pop(Heap *heap) {
    if (heap->isdel) {
        heap->elm[1] = heap->elm[heap->siz--];
        siftdown(heap, 1);
    }
    else {
        heap->isdel = 1;
    }
}

int h_top(Heap *heap) {
    if (heap->isdel) {
        heap->elm[1] = heap->elm[heap->siz--];
        siftdown(heap, 1);
        heap->isdel = false;
    }
    return heap->elm[1];
}


Heap hp;

int main()
{
    int op, q, x;
    scanf("%d", &q);
    while (q--) {
        scanf("%d", &op);
        switch (op) {
            case 1: 
                scanf("%d", &x);
                h_push(&hp, x);
                break;
            case 2:
                printf("%d\n", h_top(&hp));
                break;
            case 3:
                h_pop(&hp);
                break;
        }
    }

    return 0;
}
/*
5
1 2
1 5
2
3
2
*/