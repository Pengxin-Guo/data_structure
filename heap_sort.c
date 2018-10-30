/*************************************************************************
	> File Name: heap_sort.c
	> Author: gpx
	> Mail: 1457495424@qq.com
	> Created Time: 2018年10月30日 星期二 20时27分40秒
 ************************************************************************/
// 堆排序算法实现升序排序，需要建大顶堆

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define swap(a, b) { \
    __typeof(a) __temp = a; a = b; b = __temp; \
}

void heap_sort(int *arr, int n) {
    int *p = arr - 1;                                            // p[1]代表arr[0]
    // 建大顶堆
    for (int i = 2; i <= n; i++) {                               // p[i]代表新插入元素
        int ind = i;
        while (ind > 1) {                                        // 调整堆，从堆尾向上调整
            if (p[ind] <= p[ind >> 1]) break;
            swap(p[ind], p[ind >> 1]);
            ind >>= 1;
        }
    }
    // n-1次出堆(将堆首元素放到堆尾)
    for (int i = n; i > 1; i--) {
        swap(p[i], p[1]);                                        // 将堆首元素放到堆尾
        int ind = 1;
        while ((ind << 1) <= i - 1) {                            // 调整堆元素(不包含堆尾元素)
            int temp = ind;                                      // 从堆顶向下调整
            if (p[temp] < p[ind << 1]) temp = ind << 1;
            if ((ind << 1 | 1) <= i - 1 && p[temp] < p[ind << 1 | 1]) temp = ind << 1 | 1;
            if (temp == ind) break;
            swap(p[temp], p[ind]);
            ind = temp;
        }
    }
    return ;
}

void output(int *num, int n) {
    printf("Arr = [");
    for (int i = 0; i < n; i++) {
        printf(" %d", num[i]);
        i == n - 1 || printf(",");
    }
    printf("]\n");
    return ;
}

int main() {
    srand(time(0));
    #define MAX_N 20
    int arr[MAX_N];
    for (int i = 0; i < MAX_N; i++) arr[i] = rand() % 100;
    output(arr, MAX_N);
    heap_sort(arr, MAX_N);
    output(arr, MAX_N);
    return 0;
}
