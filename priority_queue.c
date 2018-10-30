/*************************************************************************
	> File Name: priority_queue.c
	> Author: gpx
	> Mail: 1457495424@qq.com
	> Created Time: 2018年10月30日 星期二 19时22分46秒
 ************************************************************************/
// 利用堆实现优先队列
// 本代码以大顶堆为例

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define swap(a, b) { \
    __typeof(a) t = a; \
    a = b; b = t; \
}

typedef struct priority_queue {
    int *data;
    int cnt, size;
} priority_queue;

int empty(priority_queue *q) {
    return q->cnt == 0;
}

int push(priority_queue *q, int value) {
    if (q->cnt == q->size) return 0;
    q->data[++q->cnt] = value;                               // 首先将该元素插在堆尾
    int ind = q->cnt;
    while (ind > 1) {                                        // 从堆尾开始向上调整堆
        if (q->data[ind] <= q->data[ind >> 1]) break;
        swap(q->data[ind], q->data[ind >> 1]);
        ind >>= 1;
    }
    return 1;
}

int pop(priority_queue *q) {
    if (empty(q)) return 0;
    q->data[1] = q->data[q->cnt--];                          // 将堆尾元素放置堆顶，相当于堆顶元素出堆
    int ind = 1;
    while ((ind << 1) <= q->cnt) {                           // 从堆顶开始向下调整堆
        int temp = ind;                                      // temp代表3个元素中最大的那个元素的位置
        if (q->data[temp] < q->data[ind << 1]) temp = ind << 1;
        if ((ind << 1 | 1) <= q->cnt && q->data[temp] < q->data[ind << 1 | 1]) temp = ind << 1 | 1;
        if (temp == ind) break;
        swap(q->data[ind], q->data[temp]);
        ind = temp;
    }
    return 1;
}

int top(priority_queue *q) {
    if (empty(q)) return 0;
    return q->data[1];
}

priority_queue *init(int n) {
    priority_queue *q = (priority_queue *)malloc(sizeof(priority_queue));
    q->data = (int *)malloc(sizeof(int) * (n + 1));          // 申请n+1个地址空间，不用0号位
    q->cnt = 0;
    q->size = n;
    return q;
}

void clear(priority_queue *q) {
    if (q == NULL) return ;
    free(q->data);
    free(q);
    return ;
}

void output(priority_queue *q) {
    printf("Queue = [");
    for (int i = 1; i <= q->cnt; i++) {
        printf(" %d", q->data[i]);
        i == q->cnt || printf(",");
    }
    printf("]\n");
    return ;
}

int main() {
    #define MAX_OP 20
    srand(time(0));
    priority_queue *q = init(MAX_OP);
    for (int i = 0; i < MAX_OP; i++) {
        int op = rand() % 4, value = rand() % 100;
        switch (op) {
            case 0:
            case 1:
            case 2:
                printf("push %d to priority_queue\n", value);
                push(q, value);
                break;
            case 3:
                printf("pop %d from priority_queue\n", top(q));
                pop(q);
                break;
        }
        output(q);
    }
    return 0;
}
