/*************************************************************************
	> File Name: tree_father.c
	> Author: gpx
	> Mail: 1457495424@qq.com
	> Created Time: 2018年10月23日 星期二 19时39分20秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#define MAX_N 1000
#define MAX_K 20

//不用０节点

struct Edge {
    int v, n;
} g[MAX_N << 1];

int head[MAX_N + 5] = {0}, cnt = 0;

inline void add(int a, int b) {
    g[++cnt].v = b;
    g[cnt].n = head[a];
    head[a] = cnt;
    return ;
}

// gas[i][j]代表i往上走 2^j 步所能到达的节点编号
int gas[MAX_N][MAX_K] = {0}, dep[MAX_N] = {0};

void dfs(int u, int father) {
    gas[u][0] = father;
    dep[u] = dep[father] + 1;
    for (int i = 1; i < MAX_K; i++) {
        gas[u][i] = gas[gas[u][i - 1]][i - 1];
    }
    for (int i = head[u]; i; i = g[i].n) {
        if (g[i].v == father) continue;
        dfs(g[i].v, u);
    }
    return ;
}

int lca(int a, int b) {
    if (dep[b] < dep[a]) { // 交换a,b两个节点的值
        a ^= b;
        b ^= a;
        a ^= b;
    }
    int l = dep[b] - dep[a];
    for (int i = 0; i < MAX_K; i++) {
        if ((l & (1 << i))) b = gas[b][i]; //倍增法
    }
    if (a == b) return a;
    for (int i = MAX_K - 1; i >= 0; i--) {
        if (gas[a][i] != gas[b][i]) a = gas[a][i], b = gas[b][i];
    }
    return gas[a][0];
}

int main() {
    int n, a, b; //n代表节点数
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        scanf("%d%d", &a, &b);
        add(a, b);
        add(b, a);
    }
    dfs(1, 0);
    while (scanf("%d%d", &a, &b) != EOF) {
        printf("lca(%d, %d) = %d, a -> b = %d\n", a, b, lca(a, b), dep[a] + dep[b] - 2 * dep[lca(a, b)]);
    }
    return 0;
}
