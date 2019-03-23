/*************************************************************************
	> File Name: Dijkstra.cpp
	> Author: gpx
	> Mail: 1457495424@qq.com
	> Created Time: 2019年03月23日 星期六 19时46分01秒
 ************************************************************************/

#include <iostream>
using namespace std;
#define MAX_N 100
const int INF = 0x3f3f3f;

struct Graph {
    int n;
    int *visited, *dist, **mat;
    Graph(int n) {
        this->n = n;
        visited = (int *)calloc(sizeof(int), n + 5);
        dist = (int *)calloc(sizeof(int), n + 5);
        mat = (int **)calloc(sizeof(int *), n + 5);
        for (int i = 0; i < n; i++) {
            dist[i] = INF;
            mat[i] = (int *)calloc(sizeof(int), n + 5);
            for (int j = 0; j < n; j++) {
                mat[i][j] = INF;
            }
        }
    }
    void insert(int x, int y, int w) {
        if (x < 0 || x > n || y < 0 || y > n) return ;
        mat[x][y] = w;
        mat[y][x] = w;
        return ;
    }
    void dijkstra(int v) {
        dist[v] = 0;
        for (int i = 0; i < n; i++) {
            int min_dist = INF, min_vertex;
            for (int j = 0; j < n; j++) {
                if (visited[j] || dist[j] > min_dist) continue;
                min_dist = dist[j];
                min_vertex = j;
            }
            visited[min_vertex] = 1;
            for (int j = 0; j < n; j++) {
                if (!visited[j] && min_dist + mat[min_vertex][j] < dist[j]) {
                    dist[j] = min_dist + mat[min_vertex][j];
                }
            }
        }
        return ;
    }
    ~Graph() {
        free(visited);
        free(dist);
        for (int i = 0; i < n; i++) {
            free(mat[i]);
        }
        free(mat);
    }
};

int main() {
    int n, m, a, b, c;
    cin >> n >> m;
    Graph g(n);
    for (int i = 0; i < m; i++) {
        cin >> a >> b >> c;
        g.insert(a, b, c);
    }
    cin >> m;
    g.dijkstra(m);
    for (int i = 0; i < n; i++) {
        cout << i << " " << g.dist[i] << endl;
    }
    return 0;
}
