/*************************************************************************
	> File Name: leetcode5_Manacher.c
	> Author: gpx
	> Mail: 1457495424@qq.com
	> Created Time: 2019年01月02日 星期三 19时53分32秒
 ************************************************************************/

// 马拉车算法, 代码易写, 算法不易懂a

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define min(a, b) ((a) < (b) ? (a) : (b))

char* longestPalindrome(char* s) {
    int len = strlen(s), str_len = 2 * len + 2;
    char *str = (char *)malloc(sizeof(char) * str_len);
    int *p = (int *)malloc(sizeof(int) * str_len);
    int mx = 0, id = 0, resLen = 0, resCenter = 0;
    str[0] = '$', str[1] = '#';
    for (int i = 0; i < len; i++) {
        str[2 * i + 2] = s[i];
        str[2 * i + 3] = '#';
    }
    for (int i = 1; i < str_len; i++) {
        p[i] = mx > i ? min(p[2 * id - i], mx - i) : 1;
        while (str[i + p[i]] == str[i - p[i]]) ++p[i];
        if (mx < i + p[i]) {
            mx = i + p[i];
            id = i;
        }
        if (resLen < p[i]) {
            resLen = p[i];
            resCenter = i;
        }
    }
    int temp = (resCenter - resLen) / 2;
    //printf("%d %d %d\n", resCenter, resLen, temp);
    s[temp + resLen - 1] = 0;
    return s + temp;
}

int main() {
    char str[1000];
    while (scanf("%s", str) != EOF) {
        printf("%s\n", longestPalindrome(str));  
    }
    return 0;
}
