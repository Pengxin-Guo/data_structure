/*************************************************************************
	> File Name: UnionSet.c
	> Author: gpx
	> Mail: 1457495424@qq.com
	> Created Time: 2019年01月20日 星期日 16时48分16秒
 ************************************************************************/
// quick_find

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct UnionSet {
    int *color;
    int size;
} UnionSet;

UnionSet *init(int n) {
    UnionSet *u = (UnionSet *)calloc(sizeof(UnionSet), 1);
    u->color = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        u->color[i] = i;
    }
    u->size = n;
    return u;
}

void clear(UnionSet *u) {
    if (u == NULL) return ;
    free(u->color);
    free(u);
    return ;
}

int find(UnionSet *u, int x) {
    return u->color[x];
}

int merge(UnionSet *u, int a, int b) {
    int color_a = find(u, a), coloc_b = find(u, b);
    if (color_a == coloc_b) return 0;
    for (int i  =0; i < u->size; i++) {
        if (u->color[i] == color_a) u->color[i] = coloc_b;
    }
    return 1;
}

void output(UnionSet *u) {
    for (int i = 0; i < u->size; i++) {
        printf("(%d, %d)\t", i, u->color[i]);
        if (i + 1 < u->size && i + 1 % 5 == 0) printf("\n");
    }
    printf("\n\n");
    return ;
}

int main() {
    srand(time(0));
    int op, a, b;
    #define MAX_OP 20
    #define MAX_N 10
    UnionSet *u = init(MAX_N);
    for(int i = 0; i < MAX_OP; i++) {
        op = rand() % 4;
        a = rand() % MAX_N;
        b = rand() % MAX_N;
        switch (op) {
            case 0: {
                printf("find %d <-> %d = %d\n", a, b, find(u, a) == find(u, b));
            } break;
            default: {
                printf("union %d <-> %d = %d\n", a, b, merge(u, a, b));
            } break;
        }
        output(u);
    }
    clear(u);
    return 0;
}
