/*************************************************************************
	> File Name: AC_DFS.c
	> Author: gpx
	> Mail: 1457495424@qq.com
	> Created Time: 2019年01月20日 星期日 09时44分23秒
 ************************************************************************/
 // 深度遍历建立trie树的失败指针

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BASE 26
#define BEGIN_LETTER 'a'

typedef struct Node {
    int flag;
    struct Node *next[BASE];
    struct Node *fail, *father;
} Node;

Node *getNewNode() {
    Node *p = (Node *)calloc(sizeof(Node), 1);
    return p;
}

void insert(Node *root, const char *str) {
    Node *p = root;
    for (int i = 0; str[i]; i++) {
        int ind = str[i] - BEGIN_LETTER;
        if (p->next[ind] == NULL) {
            p->next[ind] = getNewNode();
            p->next[ind]->father = p;
        }
        p = p->next[ind];
    }
    p->flag = 1;
    return ;
}

void clear(Node *node) {
    if (node == NULL) return ;
    for (int i = 0; i < BASE; i++) {
        clear(node->next[i]);
    }
    free(node);
    return ;
}

// 建立节点node的孩子的失败指针, 前提是node的失败指针已经建立了
void build_ac(Node *node) {
    if (node == NULL) return ;
    if (node->fail == NULL) build_ac(node->father);
    for (int i = 0; i < BASE; i++) {
        if (node->next[i] == NULL) continue;
        if (node->next[i]->fail) continue;
        Node *p = node->fail, *pre_p = node;
        while (p && p->next[i] == NULL) {
            if (p->fail == NULL) build_ac(p->father);
            pre_p = p;
            p = p->fail;
        }
        if (p == NULL) p = pre_p;
        else p = p->next[i];
        node->next[i]->fail = p;
        build_ac(node->next[i]);
    }
    return ;
}

int match(Node *root, const char *str) {
    int cnt = 0;
    Node *p = root;
    for (int i = 0; str[i]; i++) {
        int ind = str[i] - BEGIN_LETTER;
        while (p && p->next[ind] == NULL) p = p->fail;
        if (p == NULL) p = root;
        else p = p->next[ind];
        Node *q = p;
        while (q) {
            cnt += q->flag;
            q->flag = 0;
            q = q->fail;
        }
    }
    return cnt;
}

int main () {
    int n, cnt = 0;
    char str[1000];
    Node *root = getNewNode();
    scanf("%d", &n);
    while (n--) {
        scanf("%s", str);
        insert(root, str);
    }
    //printf("%p %p\n", root->fail, root->father);
    build_ac(root);
    scanf("%s", str);
    printf("match word cnt : %d\n", match(root, str));
    clear(root);
    return 0;
}
