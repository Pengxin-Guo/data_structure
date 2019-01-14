/*************************************************************************
	> File Name: leetcode5.c
	> Author: gpx
	> Mail: 1457495424@qq.com
	> Created Time: 2019年01月02日 星期三 10时39分38秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int expand(char *str, int i, int j, int len, int *temp) {
    while (i >= 0 && j < len && str[i] == str[j]) {
        i--;
        j++;
    }
    *temp = j - i - 1;
    return i + 1;
}

char* longestPalindrome(char* s) {
    int len = strlen(s), temp_len = 0, ret_len = 0, temp_ind = 0, ret_ind = 0;
    for (int i = 0; s[i]; i++) {
        temp_ind = expand(s, i, i, len, &temp_len);
        if (temp_len > ret_len) {
            ret_len = temp_len;
            ret_ind = temp_ind;
        } 
        temp_ind = expand(s, i, i + 1, len, &temp_len);
        if (temp_len > ret_len) {
            ret_len = temp_len;
            ret_ind = temp_ind;
        } 
    }
    s[ret_ind + ret_len] = 0;
    return s + ret_ind;
}

int main() {
    char str[1000];
    while (scanf("%s", str) != EOF) {
        printf("%s\n", longestPalindrome(str));  
    }
    return 0;
}
