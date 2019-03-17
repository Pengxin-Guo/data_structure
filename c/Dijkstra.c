/*************************************************************************
	> File Name: Dijkstra.c
	> Author: gpx
	> Mail: 1457495424@qq.com
	> Created Time: 2019年03月01日 星期五 19时30分16秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000
const int INF = 0x3f3f3f;

typedef struct Graph {
    int n;
    int *visited, *dist, **mat;
} Graph;

Graph *init(int n) {
    Graph *g = (Graph *)malloc(sizeof(Graph));
    g->n = n;
    g->visited = (int *)calloc(sizeof(int), g->n + 5);
    g->dist = (int *)calloc(sizeof(int), g->n + 5);
    g->mat = (int **)calloc(sizeof(int *), g->n + 5);
    for (int i = 0; i < g->n; i++) {
        g->dist[i] = INF;
        g->mat[i] = (int *)calloc(sizeof(int), g->n + 5);
        for (int j = 0; j < g->n; j++) {
            g->mat[i][j] = INF;
        }
    }
    return g;
}

void insert(Graph *g, int x, int y, int weight) {
    if (g == NULL || x < 0 || x >= g->n || y < 0 || y >= g->n) return ;
    g->mat[x][y] = weight;
    g->mat[y][x] = weight;
    return ;
}

void dijkstra(Graph *g, int v) {
    if (g == NULL) return ;
    g->dist[v] = 0;
    for (int i = 0; i < g->n; i++) {
        int min_dist = INF, min_vertex;
        for (int j = 0; j < g->n; j++) {
            if (g->visited[j] || g->dist[j] >= min_dist) continue;
            min_dist = g->dist[j];
            min_vertex = j;
        }
        g->visited[min_vertex] = 1;
        for (int j = 0; j < g->n; j++) {
            if (g->visited[j] || min_dist + g->mat[min_vertex][j] >= g->dist[j]) continue;
            g->dist[j] = min_dist + g->mat[min_vertex][j];
        }
    }
    return ;
}

void clear(Graph *g) {
    if (g == NULL) return ;
    free(g->visited);
    free(g->dist);
    for (int i = 0; i < g->n; i++) {
        free(g->mat[i]);
    }
    free(g->mat);
    free(g);
    return ;
}

int main() {
    int n, m, a, b, c, v;
    scanf("%d %d", &n, &m);
    Graph *g = init(n);
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &a, &b, &c);
        insert(g, a, b, c);
    }
    scanf("%d", &v);
    dijkstra(g, v);
    for (int i = 0; i < n; i++) {
        printf("%d: %d\n", i, g->dist[i]);
    }
    clear(g);
    return 0;
}
