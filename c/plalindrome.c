/*************************************************************************
	> File Name: plalindrome.c
	> Author: gpx
	> Mail: 1457495424@qq.com
	> Created Time: 2019年01月13日 星期日 15时29分13秒
 ************************************************************************/

// 找出一个字符串中所有的回文子串

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void expand(char *str, int i, int j, int n) {
    while (i >= 0 && j < n && str[i] == str[j]) {
        char c = str[j + 1];
        str[j + 1] = 0;
        printf ("%s\n", str + i);
        str[j + 1] = c;
        i--;
        j++;
    }
    return ;
}

int main () {
    char str[1000];
    scanf ("%s", str);
    int len = strlen(str);
    for (int i = 0; str[i]; i++) {
        expand(str, i, i, len);                    // 回文串长度是奇数
        expand (str, i, i + 1, len);               // 回文串长度是偶数
    }
    return 0;
}
