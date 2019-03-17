/*************************************************************************
	> File Name: test_RBT.cpp
	> Author: gpx
	> Mail: 1457495424@qq.com
	> Created Time: 2019年02月22日 星期五 18时04分52秒
 ************************************************************************/
/*
* 注意包含你的头文件
* 注意主函数和输出函数中的结构体名称
* 解释：使用时把你的文件名包含进来就行．
* 如果没有出现错误会一直出现插入删除字段
* 如果有错误中间会有error字段或者停止
*/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "./RBT.c"

namespace lib{
    typedef struct RBNode {
        int key, color; // 0 red, 1 black, 2 double black
        struct RBNode *lchild, *rchild;
    } RBNode;

    RBNode *NIL;

    RBNode *getNewNode(int key) {
        RBNode *p = (RBNode *)malloc(sizeof(RBNode));
        p->key = key;
        p->color = 0;
        p->lchild = p->rchild = NIL;
        return p;
    }

    __attribute__((constructor)) void init_NIL() {
        NIL = getNewNode(-1);
        NIL->color = 1;
        NIL->lchild = NIL->rchild = NIL;
        return ;
    }

    int hasRedChild(RBNode *node) {
        return node->lchild->color == 0 || node->rchild->color == 0;
    }

    RBNode *left_rotate(RBNode *node) {
        RBNode *temp = node->rchild;
        node->rchild = temp->lchild;
        temp->lchild = node;
        return temp;
    }

    RBNode *right_rotate(RBNode *node) {
        RBNode *temp = node->lchild;
        node->lchild = temp->rchild;
        temp->rchild = node;
        return temp;
    }

    RBNode *insert_maintain(RBNode *root) {
        if (!hasRedChild(root)) return root;
        if (root->lchild->color == 0 && root->rchild->color == 0) {
            if (hasRedChild(root->lchild) || hasRedChild(root->rchild)) {
                root->color = 0;
                root->rchild->color = root->lchild->color = 1;
            }
            return root;
        }
        if (root->lchild->color == 0) {
            if (!hasRedChild(root->lchild)) return root;
            if (root->lchild->rchild->color == 0) {
                root->lchild = left_rotate(root->lchild);
            }
            root = right_rotate(root);
        } else {
            if (!hasRedChild(root->rchild)) return root;
            if (root->rchild->lchild->color == 0) {
                root->rchild = right_rotate(root->rchild);
            }
            root = left_rotate(root);
        }
        root->color = 0;
        root->lchild->color = root->rchild->color = 1;
        return root;
    }

RBNode *__insert(RBNode *root, int key) {
    if (root == NIL || root == NULL) return getNewNode(key);
    if (root->key == key) return root;
    if (root->key < key) root->rchild = __insert(root->rchild, key);
    else root->lchild = __insert(root->lchild, key);
    return insert_maintain(root);
}

RBNode *insert(RBNode *root, int key) {
    root = __insert(root, key);
    root->color = 1;
    return root;
}

RBNode *predecessor(RBNode *node) {
    RBNode *temp = node->lchild;
    while (temp->rchild != NIL) temp = temp->rchild;
    return temp;
}

RBNode *erase_maintain(RBNode *root) {
    if (root->lchild->color != 2 && root->rchild->color != 2) return root;
    if (root->lchild->color == 0 || root->rchild->color == 0) {
        root->color = 0;
        if (root->lchild->color == 0) {
            root->lchild->color = 1;
            root = right_rotate(root);
            root->rchild = erase_maintain(root->rchild);
        } else {
            root->rchild->color = 1;
            root = left_rotate(root);
            root->lchild = erase_maintain(root->lchild);
        }
        return root;
    }
    if (root->lchild->color == 2) {
        if (!hasRedChild(root->rchild)) {
            root->color += 1;
            root->lchild->color = 1;
            root->rchild->color = 0;
            return root;
        } else if (root->rchild->rchild->color != 0) {
            root->rchild = right_rotate(root->rchild);
            root->rchild->color = 1;
            root->rchild->rchild->color = 0;
        }
        root->lchild->color = 1;
        root = left_rotate(root);
        root->color = root->lchild->color;
        root->lchild->color = root->rchild->color = 1;
    } else {
        if (!hasRedChild(root->lchild)) {
            root->color += 1;
            root->rchild->color = 1;
            root->lchild->color = 0;
            return root;
        } else if (root->lchild->lchild->color != 0) {
            root->lchild = left_rotate(root->lchild);
            root->lchild->color = 1;
            root->lchild->lchild->color = 0;
        }
        root->rchild->color = 1;
        root = right_rotate(root);
        root->color = root->rchild->color;
        root->lchild->color = root->rchild->color = 1;
    }
    return root;
}

RBNode *__erase(RBNode *root, int key) {
    if (root == NULL || root == NIL) return NIL;
    if (root->key < key) root->rchild = __erase(root->rchild, key);
    else if (root->key > key) root->lchild = __erase(root->lchild, key);
    else {
        if (root->lchild == NIL && root->rchild == NIL) {
            NIL->color += root->color;
            free(root);
            return NIL;
        } else if (root->lchild == NIL || root->rchild == NIL) {
            RBNode *temp = root->lchild == NIL ? root->rchild : root->lchild;
            temp->color += root->color;
            free(root);
            return temp;
        } else {
            RBNode *temp = predecessor(root);
            root->key = temp->key;
            root->lchild = __erase(root->lchild, temp->key);
        }
    }
    return erase_maintain(root);
}

RBNode *erase(RBNode *root, int key) {
    root = __erase(root, key);
    root->color = 1;
    return root;
}

void clear(RBNode *root) {
    if (root == NIL || root == NULL) return ;
    clear(root->lchild);
    clear(root->rchild);
    free(root);
    return ;
}

void output(RBNode *root) {
    if (root == NIL) return ;
    printf("(%d | %d, %d, %d)\n", root->color, root->key, root->lchild->key, root->rchild->key);
    output(root->lchild);
    output(root->rchild);
    return ;
    }
}

void output2(RBTNode *node, lib::RBNode *node2 ){
    if (node == NIL && node2 == lib::NIL) return ;
    if (node == NIL || node2 == lib::NIL) {
        printf("\n\nnode %d node2 %d 1error\n\n", node->key, node2->key);
        while (1);
        return ;
    }
    printf("(%d %d l:%d %d r: %d %d %d %d)\n", node->key, node2->key, node->lchild->key, node2->lchild->key, node->rchild->key, node2->rchild->key, node->key == node2->key, node->color == node2->color);
    if (node->key != node2->key || node->color != node2->color) {
        printf("\n\n%d %d %d %d  2error\n\n",node->key,node2->key, node->color, node2->color);
        while (1);
    }
    output2(node->lchild, node2->lchild);
    output2(node->rchild, node2->rchild);
}

int main() {
    srand(time(0));
    int op, val;
    //你的节点名称
    RBTNode *root = NIL;
    lib::RBNode *root2 = lib::NIL;
    #define MAX_OP 20
    while (1){
        for (int i = 0; i < MAX_OP; i++) {
            op = rand() % 5, val = rand() % 10;
            switch (op) {
                case 0: {
                    printf("delete val %d from RBT\n", val);
                    root = erase(root, val);
                    root2 = lib::erase(root2, val);
                    break;}
                case 1:
                case 2:
                case 3:
                case 4:{
                    printf("insert val %d to RBT\n", val);
                    root = insert(root, val);
                    root2 = lib::insert(root2, val);
                    break;}
            }
            output2(root, root2);
        }
    }
    return 0;
}

