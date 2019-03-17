/*************************************************************************
	> File Name: KMP.cpp
	> Author: gpx
	> Mail: 1457495424@qq.com
	> Created Time: 2019年03月17日 星期日 10时49分48秒
 ************************************************************************/

#include <iostream>
#include <cstring>
using namespace std;

// 在字符串str中找字符串pattern第一次出现的位置
int KMP(char *str, char *pattern) {
    int *next = (int *)calloc(sizeof(int), strlen(pattern));
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
    while (cin >> str >> pattern) {
        cout << "search " << pattern << " in " << str << " = " << KMP(str, pattern) << endl;
    }
    return 0;
}
