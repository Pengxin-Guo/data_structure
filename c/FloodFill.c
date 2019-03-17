/*************************************************************************
	> File Name: FloodFill.c
	> Author: gpx
	> Mail: 1457495424@qq.com
	> Created Time: 2019年02月28日 星期四 09时25分49秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000

typedef struct Graph {
    int n;
    int *color;
    int **mat;
} Graph;

Graph *init(int n) {
    Graph *g = (Graph *)calloc(sizeof(Graph), 1);
    g->n = n;
    g->color = (int *)calloc(sizeof(int), g->n + 5);
    g->mat = (int **)calloc(sizeof(int *), g->n + 5);
    for (int i = 0; i < g->n; i++) {
        g->mat[i] = (int *)calloc(sizeof(int), g->n + 5);
    }
    return g;
}

void insert(Graph *g, int x, int y) {
    if (x < 0 || x >= g->n || y < 0 || y >= g->n) return ;
    g->mat[x][y] = 1;
    g->mat[y][x] = 1;
    return ;
}

void floodfill(Graph *g) {
    if (g == NULL) return ;
    int color_cnt = 0;
    int q[MAX_N + 5];
    for (int i = 0; i< g->n; i++) {
        if (g->color[i]) continue;
        color_cnt += 1;
        g->color[i] = color_cnt;
        int l = 0, r = 0;
        q[r++] = i;
        while (l < r) {
            int vertex = q[l++];
            for (int j = 0; j < g->n; j++) {
                if (g->color[j] || g->mat[vertex][j] == 0) continue;
                g->color[j] = color_cnt;
                q[r++] = j;
            }
        }
    }
    return ;
}

void output(Graph *g) {
    for (int i = 0; i < g->n; i++) {
        printf("num = %d, color = %d\n", i, g->color[i]);
    }
    return ;
}

void clear(Graph *g) {
    if (g == NULL) return ;
    free(g->color);
    for (int i = 0; i < g->n; i++) {
        free(g->mat[i]);
    }
    free(g->mat);
    free(g);
    return ;
}

int main() {
    int n, m, a, b;
    Graph *g = NULL;
    scanf("%d %d", &n, &m);
    g = init(n);
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &a, &b);
        insert(g, a, b);
    }
    floodfill(g);
    output(g);
    clear(g);
    return 0;
}
