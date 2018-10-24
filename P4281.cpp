/*************************************************************************
	> File Name: P4281.cpp
	> Author: gpx
	> Mail: 1457495424@qq.com
	> Created Time: 2018年10月24日 星期三 17时02分04秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#define MAX_N 500000
#define MAX_K 20


// MAX_N 代表最大节点数
// MAX_K 代表最多向上跳 2^MAX_K 步
// 不用０节点

struct Edge {
    int v, n;
} g[MAX_N << 1];                                             // g[j].v代表第j条边的目的节点, g[j].n代表v的父亲节点先于第j条边插入的最后一条边

int head[MAX_N + 5] = {0}, cnt = 0;                          // head[i]代表从节点i出去的最后一条边的序号

inline void add(int a, int b) {
    g[++cnt].v = b;
    g[cnt].n = head[a];
    head[a] = cnt;
    return ;
}

int gas[MAX_N][MAX_K] = {0}, dep[MAX_N] = {0};               // gas[i][j]代表i往上走 2^j 步所能到达的节点编号; dep[i]代表节点i的深度

void dfs(int u, int father) {
    gas[u][0] = father;
    dep[u] = dep[father] + 1;
    for (int i = 1; i < MAX_K; i++) {
        gas[u][i] = gas[gas[u][i - 1]][i - 1];
    }
    for (int i = head[u]; i; i = g[i].n) {
        if (g[i].v == father) continue;                      // 因为这个树我们将每一条边虚拟成了来回两条边，所以可能形成环，当自环的时候跳过
        dfs(g[i].v, u);
    }
    return ;
}

int lca(int a, int b) {
    if (dep[b] < dep[a]) {                                   // 交换a,b两个节点的值, 使b节点是较深的那个节点
        a ^= b;
        b ^= a;
        a ^= b;
    }
    int l = dep[b] - dep[a];
    for (int i = 0; i < MAX_K; i++) {
        if ((l & (1 << i))) b = gas[b][i];                   // 倍增法, 利用位运算
    }
    // 执行完for语句后, a和b位于同一深度
    if (a == b) return a;
    for (int i = MAX_K - 1; i >= 0; i--) {
        if (gas[a][i] != gas[b][i]) a = gas[a][i], b = gas[b][i];
    }
    // 执行完for语句后, a和b位其最近公共父节点的下一层
    return gas[a][0];
}

int main() {
    int m, n, a, b, c;
    scanf("%d%d", &n, &m);
    for (int i = 1; i < n; i++) {                            // 边数比节点数少1
        scanf("%d%d", &a, &b);                               // a, b代表两个这条边的两个节点
        add(a, b);
        add(b, a);                                           // 执行两次add函数是因为我们将每条边虚拟成来回的两条边
    }
    dfs(1, 0);                                               // 不用0节点，假设1号节点的父亲的0号节点
    while (m--) {
        scanf("%d%d%d", &a, &b, &c);
        if (dep[a] > dep[b]) {
            a ^= b;
            b ^= a;
            a ^= b;
        }
        if (dep[a] > dep[c]) {
            a ^= c;
            c ^= a;
            a ^= c;
        }
        printf("%d %d\n", lca(b, c), dep[a] + dep[b] + dep[c] - dep[lca(a, b)] - dep[lca(a, c)] - dep[lca(b, c)]);
    }
    return 0;
}

