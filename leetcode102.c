/*************************************************************************
	> File Name: leetcode102.c
	> Author: gpx
	> Mail: 1457495424@qq.com
	> Created Time: 2018年10月25日 星期四 19时21分31秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

//分析函数原型

int **__getResult(int x, int *size, int **cols) {
    int **ret;
    *size = 3;
    return ret;
}

int main() {
    int size, *cols;
    int **ret = __getResult(3, &size, &cols);

    return 0;
}

//* Definition for a binary tree node.
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *columnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

int getHeight(struct TreeNode *root) {
    if (root == NULL) return 0;
    int l = getHeight(root->left), r = getHeight(root->right);
    return (l > r ? l : r) + 1;
}

void getColumns(struct TreeNode *root, int *cols, int k) {
    if (root == NULL) return ;
    cols[k] += 1;
    getColumns(root->left, cols, k + 1);
    getColumns(root->right, cols, k + 1);
    return ;
}

void getResult(struct TreeNode *root, int **ret, int *cols, int k) {
    if (root == NULL) return ;
    ret[k][cols[k]++] = root->val;
    getResult(root->left, ret, cols, k + 1);
    getResult(root->right, ret, cols, k + 1);
    return ;
}

int** levelOrder(struct TreeNode* root, int** columnSizes, int* returnSize) {
    *returnSize = getHeight(root);                                         // returnSize代表行数, 树的深度即为行数
    *columnSizes = (int *)calloc(sizeof(int), *returnSize);                // columnSizes代表每一行有多少个元素, 树的每一层有几个节点代表这一行有几个元素
    getColumns(root, *columnSizes, 0);                                     // 首先树的根节点也就是数组的第0行开始遍历, 遍历整个树
    int **ret = (int **)malloc(sizeof(int *) * (*returnSize));             // 定义一个结果数组, 其行数为上面得到的树的深度
    for (int i = 0; i < *returnSize; i++) {
        ret[i] = (int *)malloc(sizeof(int) * (*columnSizes)[i]);           // 定义每一行有多少个元素,　根据上面得到的columnSizes定义
        (*columnSizes)[i] = 0;
    }
    getResult(root, ret, *columnSizes, 0);                                 // 得到ret数组的结果
    return ret;
}
