/*************************************************************************
	> File Name: bruteforce.c
	> Author: gpx
	> Mail: 1457495424@qq.com
	> Created Time: 2019年01月01日 星期二 09时46分56秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

int BruteForce(char *str, char *pattern) {
    for (int i = 0; str[i]; i++) {
        int flag = 1;
        for (int j = 0; pattern[j]; j++) {
            if (str[i + j] == pattern[j]) continue;
            flag = 0;
            break;
        }
        if (flag) return i;
    }
    return -1;
}

int main() {
    char str[100], pattern[30];
    while (scanf("%s%s", str, pattern) != EOF) {
        printf("search %s in %s = %d\n", pattern, str, BruteForce(str, pattern));
    }
    return 0;
}
