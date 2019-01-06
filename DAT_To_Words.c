/*************************************************************************
	> File Name: DAT_To_Words.c
	> Author: gpx
	> Mail: 1457495424@qq.com
	> Created Time: 2019年01月06日 星期日 16时14分59秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct DATNode {
    int base, check;
    char ch;
}DATNode;

DATNode trie[200];

void dfs(int ind, int k, char *str) {
    if (trie[ind].check < 0) {
        printf("%s\n", str);
    }
    for (int i = 0; i < 26; i++) {
        int check = abs(trie[trie[ind].base + i].check);
        if (check == ind && trie[ind].base + i != 1) {
            str[k] = 'a' + i;
            str[k + 1] = 0;
            dfs(trie[ind].base + i, k + 1, str);
        }
    }
    return ;
}

int main() {
    int ind, base, check;
    while(scanf("%d%d%d", &ind, &base, &check) != EOF) {
        trie[ind].base = base;
        trie[ind].check = check;
    }
    char str[30];
    dfs(1, 0, str);
    return 0;
}
