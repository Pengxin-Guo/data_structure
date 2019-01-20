/*************************************************************************
	> File Name: AC_cue.c
	> Author: gpx
	> Mail: 1457495424@qq.com
	> Created Time: 2019年01月20日 星期日 11时11分33秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BASE 26
#define BEGIN_LETTER 'a'

typedef struct Node {
    int flag;
    struct Node *next[BASE], *fail;
} Node;

typedef struct Queue {
    Node **data;
    int head, tail;
} Queue;

Queue *init_queue(int n) {
    Queue *q = (Queue *)calloc(sizeof(Queue), 1);
    q->data = (Node **)calloc(sizeof(Node *), n);
    q->head = q->tail = 0;
    return q;
}

int empty(Queue *q) {
    return q->head == q->tail;
}

void push(Queue *q, Node *node) {
    if (q == NULL) return ;
    q->data[q->tail++] = node;
    return ;
}

Node *front(Queue *q) {
    if (q == NULL) return NULL;
    return q->data[q->head];
}

void pop(Queue *q) {
    if (q == NULL) return ;
    if (empty(q)) return ;
    q->head++;
    return ;
}

void clear_queue(Queue *q) {
    if (q == NULL) return ;
    free(q->data);
    free(q);
    return ;
}

Node *getNewNode() {
    Node *p = (Node *)calloc(sizeof(Node), 1);
    return p;
}

int insert(Node *root, const char *str) {
    int cnt = 0;
    Node *p = root;
    for (int i = 0; str[i]; i++) {
        int ind = str[i] - BEGIN_LETTER;
        if (p->next[ind] == NULL) {
            p->next[ind] = getNewNode();
            cnt += 1;
        }
        p = p->next[ind];
    }
    p->flag = 1;
    return cnt;
}

void clear(Node *node) {
    if (node == NULL) return ;
    for (int i = 0; i < BASE; i++) {
        clear(node->next[i]);
    }
    free(node);
    return ;
}

void build_ac(Node *root, int n) {
    Queue *q = init_queue(n + 10);
    push(q, root);
    while (!empty(q)) {
        Node *now_node = front(q);
        pop(q);
        for (int i = 0; i < BASE; i++) {
            if (now_node->next[i] == NULL) {
                if (now_node != root) now_node->next[i] = now_node->fail->next[i];
                continue;
            }
            Node *p = now_node->fail ? now_node->fail->next[i] : root;
            if (p == NULL) p = root;
            now_node->next[i]->fail = p;
            push(q, now_node->next[i]);
        }
        /*
        // 下面几行代码为AC自动机的线索化, 改到97行实现了
        for (int i = 0; i < BASE && now_node != root; i++) {
            if (now_node->next[i]) continue;
            now_node->next[i] = now_node->fail->next[i];
        }
        */
    }
    clear_queue(q);
    return ;
}

int match(Node *root, const char *str) {
    int cnt = 0;
    Node *p = root, *q;
    while (str[0]) {
        p = p->next[str[0] - 'a'];
        q = p;
        while (q) cnt += q->flag, q = q->fail;
        if (p == NULL) p = root;
        str++;
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
        cnt += insert(root, str);
    }
    build_ac(root, cnt);
    scanf("%s", str);
    printf("match word cnt : %d\n", match(root, str));
    clear(root);
    return 0;
}

