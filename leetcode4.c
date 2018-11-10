/*************************************************************************
	> File Name: leetcode4.c
	> Author: gpx
	> Mail: 1457495424@qq.com
	> Created Time: 2018年11月10日 星期六 20时35分36秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define min(a, b) ((a) < (b) ? (a) : (b))

// findk，在有序的num1,num2数组里面找出这两个数组的第k个位置的数
void findk(int *num1, int *num2, int *b1, int *b2, int e1, int e2, int k) {
    if (k <= 1) return ;
    // b1是数组num1的第一个位置, e1是数组num1的长度; b2是数组num2的第一个位置, e2是数组num2的长度
    if (*b1 == e1) {
        *b2 = *b2 + k - 1;
        return ;
    } else if (*b2 == e2) {
        *b1 = *b1 + k - 1;
        return ;
    }
    int a1, a2;
    a1 = min(k >> 1, e1 - *b1);
    a2 = min(k - (k >> 1), e2 - *b2);
    if (num1[a1 + *b1 - 1] > num2[a2 + *b2 - 1]) {
        *b2 += a2;
        k -= a2;
    } else {
        *b1 += a1;
        k -= a1;
    }
    findk(num1, num2, b1, b2, e1, e2, k);
}

int get_min_num(int *num1, int *num2, int *b1, int *b2, int e1, int e2) {
    int ret;
    if (*b1 == e1) {
        ret = num2[*b2];
        *b2 += 1;
    } else if (*b2 == e2) {
        ret = num1[*b1];
        *b1 += 1;
    } else {
        ret = min(num1[*b1], num2[*b2]);
        if (ret == num1[*b1]) *b1 += 1;
        else *b2 += 1;
    }
    return ret;
}

double findMedianSortedArrays(int *nums1, int nums1Size, int *nums2, int nums2Size) {
    int b1 = 0, b2 = 0, sum = 0;
    findk(nums1, nums2, &b1, &b2, nums1Size, nums2Size, (nums1Size + nums2Size + 1) >> 1);
    int i, j;
    for (i = (nums1Size + nums2Size) % 2, j = 0; i < 2; i++, j++) {
        sum += get_min_num(nums1, nums2, &b1, &b2, nums1Size, nums2Size);
    }
    return sum * 1.0 / j;
}

int main() {
    int nums1[] = {1, 2}, nums2[] = {3, 4};
    printf("%.1f\n", findMedianSortedArrays(nums1, 2, nums2, 2));
    return 0;
}
