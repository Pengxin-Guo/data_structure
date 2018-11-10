/*************************************************************************
	> File Name: leetcode1.c
	> Author: gpx
	> Mail: 1457495424@qq.com
	> Created Time: 2018年11月10日 星期六 17时14分27秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 方法一
#define swaop(a, b) { \
    __typeof(a) _temp = a; a = b; b = _temp; \
}

void quick_sort(int *nums, int l ,int r) {
    if (r <= l) return ;
    int x = l, y = r, z = nums[l];
    while (x < y) {
        while (x < y && nums[y] >= z) --y;
        if (x < y) nums[x++] = nums[y];
        while (x < y && nums[x] <= z) ++x;
        if (x < y) nums[y--] = nums[x];
    }
    nums[x] = z;
    quick_sort(nums, l, x - 1);
    quick_sort(nums, x + 1, r);
    return ;
}

int *twoSum(int *nums, int numsSize, int target) {
    int *temp_num = (int *)malloc(sizeof(int) * numsSize);
    memcpy(temp_num, nums, sizeof(int) * numsSize);
    quick_sort(nums, 0, numsSize - 1);
    int p = 0, q = numsSize - 1;
    while (nums[p] + nums[q] != target) {
        if (nums[p] + nums[q] > target) q--;
        else p++;
    }
    int *ret = (int *)malloc(sizeof(int) * 2);
    int ans = 2;
    for (int i = 0; i < numsSize && ans; i++) {
        if (temp_num[i] == nums[p] || temp_num[i] == nums[q]) {
            ret[2 - ans] = i;
            ans--;
        }
    }
    free(temp_num);
    return ret;
}

// 方法二：利用哈希表
typedef struct Data {
    int val, ind;
} Data;

typedef struct HashTable {
    Data *data;
    int *flag;
    int size;
} HashTable;

HashTable *init(int n) {
    HashTable *h = (HashTable *)malloc(sizeof(HashTable));
    h->size = n << 1;
    h->data = (Data *)malloc(sizeof(Data) * h->size);
    h->flag = (int*)calloc(sizeof(int), h->size);
    return h;
}

int hashFunc(int val) {
    return val & 0x7fffffff;
}

int insert(HashTable *h, int val, int ind) {
    int hash = hashFunc(val);
    int pos = hash % h->size;
    int times = 1;
    while (h->flag[pos]) {
        pos += (times * times);
        pos %= h->size;
        times++;
    }
    h->data[pos].val = val;
    h->data[pos].ind = ind;
    h->flag[pos] = 1;
    return 1;
}

Data *search(HashTable *h, int val) {
    int hash = hashFunc(val);
    int pos = hash % h->size;
    int times = 1;
    while (h->flag[pos] && h->data[pos].val != val) {
        pos += (times * times);
        pos %= h->size;
        times++;
    }
    if (h->flag[pos] == 0) return NULL;
    return h->data + pos;
}

void clear(HashTable *h) {
    if (h == NULL) return ;
    free(h->data);
    free(h->flag);
    free(h);
    return ;
}

int *twoSum2(int *nums, int numsSize, int target) {
   HashTable *h = init(numsSize);
    int *ret = (int *)malloc(sizeof(int) * 2);
    for (int i = 0; i < numsSize; i++) {
        Data *result = search(h, target - nums[i]);
        if (result) {
            ret[0] = result->ind;
            ret[1] = i;
            break;
        } else {
            insert(h, nums[i], i);
        }
    }
    clear(h);
    return ret;
}

int main() {
    int nums[] = {2, 7, 11, 5};
    int *ret = twoSum(nums, 4, 9);
    int *ret2 = twoSum2(nums, 4, 9);
    printf("[%d, %d]\n", ret[0], ret[1]);
    printf("[%d, %d]\n", ret2[0], ret2[1]);
    return 0;
}
