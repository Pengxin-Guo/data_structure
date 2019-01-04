/*************************************************************************
	> File Name: ShiftAnd_2.cpp
	> Author: gpx
	> Mail: 1457495424@qq.com
	> Created Time: 2019年01月01日 星期二 11时20分26秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

class Pp{
private:
    int length;
    char *data;
public:
    Pp(int len) {
        length = len;
        data = (char *)malloc(sizeof(char) * length);
        for (int i = 0; i < len; i++) {
            data[i] = '0';
        }
    } 
    void shift() {
        for (int i = length - 1; i > 0; i--) {
            data[i] = data[i - 1];
        }
        data[0] = '1';
    }
    void and1(char *code) {
        for (int i = 0; i < length; i++) {
            if (data[i] == '1' && code[i] == '1') {
                data[i] = '1';
            } else {
                data[i] = '0';
            }
        }
    }
    bool valid() {
        if (data[length - 1] == '1') return true;
        return false;
    }
    char *getData() {
        return data;
    }
    void init() {
        for (int i = 0; i < length; i++) {
            data[i] = '0';
        }
    }
    ~Pp() {
        free(data);
    }
};

int ShiftAnd(char *str, char *pattern) {
    #define BASE 128
    char *code[BASE] = {0}, len = strlen(pattern);
    for (int i = 0; i < len; i++) {
        if (code[pattern[i]] == NULL) {
            code[pattern[i]] = (char *)malloc(sizeof(char) * len);
        }
        code[pattern[i]][i] = '1';
    }
    //printf("%s\n%s\n%s\n%s\n", code[97], code[99], code[100], code[101]);
    Pp p(len);
    for (int i = 0; str[i]; i++) {
        p.shift();
        if (code[str[i]] == NULL) {
            p.init();
            continue;
        }
        p.and1(code[str[i]]);
        if (p.valid()) return i - len + 1;
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
