/*************************************************************************
	> File Name: binary_search_tree.c
	> Author: gpx
	> Mail: 1457495424@qq.com
	> Created Time: 2019年01月20日 星期日 18时54分43秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    int key;
    struct Node *lchild, *rchild;
} Node;

Node *getNewNode(int key) {
    Node *p = (Node *)calloc(sizeof(Node), 1);
    p->key = key;
    return p;
}

Node *insert(Node *root, int key) {
    if (root == NULL) return getNewNode(key);
    if (root->key == key) return root;
    if (root->key > key) root->lchild = insert(root->lchild, key);
    else root->rchild = insert(root->rchild, key);
    return root;
}

Node *predecessor(Node *node) {
    Node *temp = node->lchild;
    while (temp->rchild) temp = temp->rchild;
    return temp;
}

Node *erase(Node *root, int key) {
    if (root == NULL) return root;
    if (root->key < key) {
        root->rchild = erase(root->rchild, key);
    } else if (root->key > key) {
        root->lchild = erase(root->lchild, key);
    } else {
        if (root->lchild == NULL && root->rchild == NULL) {
            free(root);
            return NULL;
        } else if (root->lchild == NULL || root->rchild == NULL) {
            Node *temp = (root->lchild ? root->lchild : root->rchild);
            free(root);
            return temp;
        } else {
            Node *temp = predecessor(root);
            root->key = temp->key;
            root->lchild = erase(root->lchild, temp->key);
        }
    }
    return root;
}

int search(Node *root, int key) {
    if (root == NULL) return 0;
    if (root->key == key) return 1;
    return (root->key > key ? search(root->lchild, key) : search(root->rchild, key));
}

void clear(Node *node) {
    if (node == NULL) return ;
    clear(node->lchild);
    clear(node->rchild);
    free(node);
    return ;
}

void output(Node *root) {
    if (root == NULL) return ;
    output(root->lchild);
    printf("%d ", root->key);
    output(root->rchild);
    return ;
}

int main() {
    srand(time(0));
    int op, val;
    #define MAX_OP 20
    #define MAX_N 15
    Node *root = NULL;
    for (int i = 0; i < MAX_OP; i++) {
        op = rand() % 6; // 0 search, 1 erase, 2 3 4 5 insert
        val = rand() % MAX_N;
        switch (op) {
            case 0: {
                printf("search %d = %d\n", val, search(root, val));
            } break;
            case 1: {
                printf("erase %d from BST\n", val);
                root = erase(root, val);
            } break;
            default: {
                printf("insert %d to BST\n", val);
                root = insert(root, val);
            } break;
        }
        output(root);
        printf("\n");
    }
    clear(root);
    return 0;
}
