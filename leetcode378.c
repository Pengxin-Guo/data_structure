/*************************************************************************
> File Name: leetcode378.c
> Author: gpx
> Mail: 1457495424@qq.com
> Created Time: 2018年11月11日 星期日 20时47分22秒
************************************************************************/

#include <stdio.h>
#include <stdlib.h>

int find(int **matrix, int matrixRowSize, int matrixColSize, int val, int *temp) {
    int ans = 0, k = matrixRowSize - 1;
    for (int i = 0; i < matrixColSize; i++) {
        while (k >= 0 && matrix[k][i] > val) k--;
        if (k < 0) return ans + 1;
        if (matrix[k][i] == val) {
            *temp = 1;
            k--;
        }
        ans = ans + k + 1;
    }
    return ans + 1;
}

int kthSmallest(int **matrix, int matrixRowSize, int matrixColSize, int k) {
    int head = matrix[0][0], tail = matrix[matrixRowSize - 1][matrixColSize - 1], mid;
    int temp = 0;
    while (head < tail) {
        temp = 0;
        mid = (head + tail + 1) >> 1;
        int tk = find(matrix, matrixRowSize, matrixColSize, mid, &temp);
        if (tk == k && temp == 1) return mid;
        if (tk == k && temp == 0) head = mid + 1;
        else if (tk < k) head = mid;
        else tail = mid - 1;
    }
    return head;
}

int main() {
    int **matrix = (int **)malloc(sizeof(int *) * 3);
    for (int i = 0; i < 3; i++) {
        matrix[i] = (int *)malloc(sizeof(int) * 3);
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
    int k = 8;
    printf("%d\n", kthSmallest(matrix, 3, 3, k));
    return 0;
}
