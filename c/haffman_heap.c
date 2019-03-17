/*************************************************************************
	> File Name: haffman_heap.c
	> Author: gpx
	> Mail: 1457495424@qq.com
	> Created Time: 2018年11月01日 星期四 11时05分44秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>

typedef struct Node {
    int key, freq;
    struct Node *lchild, *rchild;
} Node;

Node *getNewNode(int key, int freq) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->key = key;
    p->freq = freq;
    p->lchild = p->rchild = NULL;
    return p;
}

void clear(Node *root) {
    if (root == NULL) return ;
    clear(root->lchild);
    clear(root->rchild);
    free(root);
    return ;
}

int swap_node(Node **p, Node **q) {
    Node *temp = *p;
    *p = *q;
    *q = temp;
    return 1;
}

void heap_sort(Node **arr, int n) {
    Node **p = arr - 1;                                          // p[1]代表arr[0]
    // 线性建堆
    for (int i = n >> 1; i >= 1; i--) {
        int ind = i;
        while ((ind << 1) <= n) {
            int temp = ind;
            if (p[temp]->freq > p[ind << 1]->freq) temp = ind << 1;
            if ((ind << 1 | 1) <= n && p[temp]->freq > p[ind << 1 | 1]->freq) temp = ind << 1 | 1;
            if (temp == ind) break;
            swap_node(p + temp, p + ind);
            ind = temp;
        }
    }
    // n-1次出堆(将堆首元素放到堆尾)
    for (int i = n; i > 1; i--) {
        swap_node(p + i, p + 1);                                 // 将堆首元素放到堆尾
        int ind = 1;
        while ((ind << 1) <= i - 1) {                            // 调整堆元素(不包含堆尾元素)
            int temp = ind;                                      // 从堆顶向下调整
            if (p[temp]->freq > p[ind << 1]->freq) temp = ind << 1;
            if ((ind << 1 | 1) <= i - 1 && p[temp]->freq > p[ind << 1 | 1]->freq) temp = ind << 1 | 1;
            if (temp == ind) break;
            swap_node(p + temp, p + ind);
            ind = temp;
        }
    }
    return ;
}

Node *build_haffman(Node **arr, int n) {                         // 利用构建哈夫曼树
    for (int i = 0; i < n - 1; i++) {
        heap_sort(arr, n - i);
        Node *temp = getNewNode(0, arr[n - i - 1]->freq + arr[n - i - 2]->freq);
        temp->lchild = arr[n - i - 1];
        temp->rchild = arr[n - i - 2];
        arr[n - i - 2] = temp;
    }
    return arr[0];
}

void extract_code(Node *root, char (*code)[20], int k, char *buffer) {
    buffer[k] = 0;
    if (root->key) {
        strcpy(code[root->key], buffer);
        return ;
    }
    buffer[k] = '0';
    extract_code(root->lchild, code, k + 1, buffer);
    buffer[k] = '1';
    extract_code(root->rchild, code, k + 1, buffer);
    return ;
}

void output(Node *root) {
    if (root == NULL) {return;}
    printf("%d ", root->freq);
    output(root->lchild);
    output(root->rchild);
    return ;
}

int main() {
    int n;
    scanf("%d", &n);
    Node **arr = (Node **)malloc(sizeof(Node *) * n);
    Node *root  = NULL;
    for (int i = 0; i < n; i++) {
        char key[10];
        int freq;
        scanf("%s%d", key, &freq);
        arr[i] = getNewNode(key[0], freq);
    }
    root = build_haffman(arr, n);
    //output(root);
    //printf("\n");
    char code[256][20] = {0}, buffer[20];
    extract_code(root, code, 0, buffer);
    for (int i = 0; i < 256; i++) {
        if (code[i][0] == 0) continue;
        printf("%c : %s\n", i, code[i]);
    }
    return 0;
}
