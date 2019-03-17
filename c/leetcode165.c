/*************************************************************************
	> File Name: leetcode165.c
	> Author: gpx
	> Mail: 1457495424@qq.com
	> Created Time: 2019年01月03日 星期四 11时57分13秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

int ston(char *str) {
    int ret = 0;
    while (str[0] && str[0] == '0') str++;
    while (str[0]) {
        ret = ret * 10 + str[0] - '0';
        str++;
    }
    return ret;
}

int func(char *str, int ret) {
    int num;
    while (str[0]) {
        char *temp = str;
        while (str[0] && str[0] != '.') str++;
        if (str[0] == 0) {
            num = ston(temp);
            if (num == 0) return 0;
            else return ret;
        }
        else {
            str[0] = 0;
            num = ston(temp);
            if (num == 0) {
                str++;
                continue;
            }
            else return ret;
        }
    }
    return 0;
}

int compareVersion(char* version1, char* version2) {
    int num1, num2;
    while (version1[0] && version2[0]) {
        num1 = 0, num2 = 0;
        char *temp1 = version1;
        while (version1[0] && version1[0] != '.') version1++;
        if (version1[0] == 0) {
            num1 = ston(temp1);
        }
        else {
            version1[0] = 0;
            num1 = ston(temp1);
            version1++;    
        }
        char *temp2 = version2;
        while (version2[0] && version2[0] != '.') version2++;
        if (version2[0] == 0) {
            num2 = ston(temp2);
        }
        else {
            version2[0] = 0;
            num2 = ston(temp2);
            version2++;    
        }
        if (num1 < num2) return -1;
        else if (num1 > num2) return 1;
    }
    if (version1[0] == 0 && version2[0] == 0) return 0;
    else if (version1[0] == 0) {
        return func(version2, -1);
    }
    else {
        return func(version1, 1);
    }
}

int main() {
    char str1[30], str2[30];
    while ((scanf("%s%s", str1, str2)) != EOF) {
        printf("%d\n", compareVersion(str1, str2));
    }
    return 0;
}
