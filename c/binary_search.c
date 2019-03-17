/*************************************************************************
	> File Name: binary_search.c
	> Author: gpx
	> Mail: 1457495424@qq.com
	> Created Time: 2018年11月06日 星期二 19时27分10秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define P(func) { \
    printf("%s = %d\n", #func, func); \
}

// 1 2 3 4 5 6
int binary_search1(int *num, int n, int x) {
    int head = 0, tail = n - 1;
    while (head <= tail) {
        int mid = (head + tail) >> 1;
        if (num[mid] == x) return mid;
        if (num[mid] > x) tail = mid - 1;
        else head = mid + 1;
    }
    return -1;
}

// 111110000
int binary_search2(int *num, int n) {
    int head = -1, tail = n - 1;
    while (head < tail) {
        int mid = (head + tail + 1) >> 1;
        if (num[mid] == 1) head = mid;
        else tail = mid - 1;
    }
    return head;
}

// 00001111111
int binary_search3(int *num, int n) {
    int head = 0, tail = n;
    while (head < tail) {
        int mid = (head + tail) >> 1;
        if (num[mid] == 1) tail = mid;
        else head = mid + 1;
    }
    return head == n ? -1 : head;
}

int main() {
    int arr1[] = {1, 3, 5, 7, 11, 13, 17, 23, 29};
    int arr2[] = {1, 1, 1, 0, 0, 0, 0, 0, 0, 0};
    int arr3[] = {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1};
    P(binary_search1(arr1,10, 11));
    P(binary_search2(arr2, 10));
    P(binary_search3(arr3, 10));
    return 0;
}
