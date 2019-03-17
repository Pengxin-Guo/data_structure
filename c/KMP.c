/*************************************************************************
	> File Name: KMP.c
	> Author: gpx
	> Mail: 1457495424@qq.com
	> Created Time: 2019年01月01日 星期二 09时55分57秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int KMP(char *str, char *pattern) {
    int *next = (int *)malloc(sizeof(char) * strlen(pattern));
    next[0] = -1;
    for (int i = 1; pattern[i]; i++) {
        int j = next[i - 1];
        while (j != -1 && pattern[i] != pattern[j + 1]) j = next[j];
        if (pattern[i] == pattern[j + 1]) next[i] = j + 1;
        else next[i] = -1;
    }
    int i = 0, j = -1;
    while (str[i]) {
        while (j != -1 && str[i] != pattern[j + 1]) j = next[j];
        if (str[i] == pattern[j + 1]) j += 1;
        i += 1;
        if (pattern[j + 1] == 0) return i - strlen(pattern);
    }
    return -1;
}

int main() {
    char str[100], pattern[30];
    while (scanf("%s%s", str, pattern)) {
        printf("search %s in %s = %d\n", pattern, str, KMP(str, pattern));
    }
    return 0;
}
