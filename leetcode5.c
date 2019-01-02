/*************************************************************************
	> File Name: leetcode5.c
	> Author: gpx
	> Mail: 1457495424@qq.com
	> Created Time: 2019年01月02日 星期三 10时39分38秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isPalindrome(char *str) {
    int len = strlen(str), flag = 1;
    for (int i = 0; i < len / 2 && flag; i++) {
        if (str[i] == str[len - i - 1]) continue;
        flag = 0;
    }
    if (flag) return 1;
    return 0;
}

char* longestPalindrome(char* s) {
    int ret = 0, len = 1, str_len =  strlen(s);
    char *str = (char *)malloc(sizeof(char) * str_len);
    for (int i = 0; i < str_len; i++) {
        memset(str, 0, sizeof(str));
        for (int j = i + 1; j <= str_len; j++) {
            //printf("%d\n", j - i);
            memset(str, 0, sizeof(str));
            strncpy(str, s + i, j - i);
            if (!isPalindrome(str)) {
                continue;
            }
            if (j - i > len) {
                len = j - i;
                ret = i;
            }
        }
    }
    s[ret + len] = 0;
    return s + ret;
}


int main() {
    char str[1000];
    while (scanf("%s", str) != EOF) {
        printf("%s\n", longestPalindrome(str));  
    }
    return 0;
}
