/*************************************************************************
	> File Name: SUNDAY.c
	> Author: gpx
	> Mail: 1457495424@qq.com
	> Created Time: 2019年01月01日 星期二 10时28分29秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int Sunday(char *str, char *pattern) {
    #define BASE 128
    int ind[BASE] = {0};
    int len = strlen(pattern), max_len = strlen(str);
    for (int i = 0; i < BASE; i++) {
        ind[i] = len + 1;
    }
    for (int i = 0; i < len; i++) {
        ind[pattern[i]] = len - i;
    }
    for (int i = 0; i < max_len;) {
        int flag = 1;
        for (int j = 0; j < len; j++) {
            if (str[i + j] == pattern[j]) continue;
            i += ind[str[i + len]];
            flag = 0;
            break;
        }
        if (flag) return i;
    }
    return -1;
    #undef BASE
}

int main() {
    char str[100], pattern[30];
    while (scanf("%s%s", str, pattern) != EOF) {
        printf("search %s in %s = %d\n", pattern, str, Sunday(str, pattern));
    } 
    return 0;
}
