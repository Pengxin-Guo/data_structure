/*************************************************************************
	> File Name: LinkList.c
	> Author: gpx
	> Mail: 1457495424@qq.com
	> Created Time: 2018年10月11日 星期四 20时23分23秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct LinkNode {
    int data;
    struct LinkNode *next;
} LinkNode;

typedef struct LinkList {
    LinkNode head;
    int length;
} LinkList;

LinkList *init() {
    LinkList *p = (LinkList *)malloc(sizeof(LinkList));
    p->head.next = NULL;
    p->length = 0;
    return p;
}

LinkNode *getNewNode(int value) {
    LinkNode *p = (LinkNode *)malloc(sizeof(LinkNode));
    p->data = value;
    p->next = NULL;
    return p;
}

void insert(LinkList *l, int value, int ind) {
    if (ind < 0 || ind > l->length) return ;                 //加上这条语句，p就不会等于NULL
    LinkNode *p = &(l->head);
    while (ind--) {
        p = p->next;
        //if (p == NULL) return ;
    }
    LinkNode *new_node = getNewNode(value);
    new_node->next = p->next;
    p->next = new_node;
    l->length += 1;
    return ;
}

void erase(LinkList *l, int ind) {
    if (ind < 0 || ind >= l->length) return ;                //加上这条语句，p和p->next均不会等于NULL
    LinkNode *p = &(l->head);
    while (ind--) {
        p = p->next;
        //if (p == NULL) return ;
    }
    //if (p->next == NULL) return ;
    LinkNode *q = p->next;
    p->next = p->next->next;
    free(q);
    l->length -= 1;
    return ;
}

void clear(LinkList *l) {
    //if (l->head.next == NULL) return ;                     //这条语句应该被注释掉，不然无法释放l
    LinkNode *p = l->head.next, *q;
    while (p) {
        q = p;
        p = p->next;
        free(q);
    }
    free(l);
    return ;
}

void output(LinkList *l) {
    printf("[%d] ", l->length);
    LinkNode *p = l->head.next;
    while (p != NULL) {
        printf("%d->", p->data);
        p = p->next;
    }
    printf("NULL\n");
    return ;
}

int main() {
    srand(time(0));
    LinkList *l = init();
    #define MAX_OP 20 
    for (int i = 0; i < MAX_OP; i++) {
        int op = rand() % 4, value, ind;
        switch (op) {
            case 0:
            case 1:
            case 2: {
                ind = rand() % (l->length + 1);
                value = rand() % 100;
                printf("insert(%d, %d) to LinkList\n", value, ind);
                insert(l, value, ind);
                output(l);
            } break;
            case 3: {
                if (l->length == 0) break;
                ind = rand() % l->length;
                printf("erase(%d) from LinkList\n", ind);
                erase(l, ind);
                output(l);
            } break;
        }
    }
    clear(l);
    return 0;
}
