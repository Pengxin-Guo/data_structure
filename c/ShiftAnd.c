/*************************************************************************
	> File Name: ShiftAnd.c
	> Author: gpx
	> Mail: 1457495424@qq.com
	> Created Time: 2019年01月01日 星期二 11时20分26秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int ShiftAnd(char *str, char *pattern) {
    #define BASE 128
    int code[BASE] = {0}, len = strlen(pattern);
    for (int i = 0; i < len; i++) {
        code[pattern[i]] |= (1 << i);
    }
    int p = 0;
    for (int i = 0; str[i]; i++) {
        p = (p << 1 | 1) & code[str[i]];
        if (p & (1 << (len - 1))) return i - len + 1;
    }
    return -1;
    #undef BASE
}

int main() {
    char str[100], pattern[30];
    while (scanf("%s%s", str, pattern)) {
        printf("search %s in %s = %d\n", pattern, str, ShiftAnd(str, pattern));
    }
    return 0;
}
