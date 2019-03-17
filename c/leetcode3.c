/*************************************************************************
	> File Name: leetcode3.c
	> Author: gpx
	> Mail: 1457495424@qq.com
	> Created Time: 2018年11月10日 星期六 19时11分39秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 方法一：滑动窗口的思想
int lengthOfLongestSubstring(char *s) {
    int pos[256], len = 0, ans = 0;                       // pos记录的是每个字符最后出现的位置, len是包含当前字符的最长子串长度
    memset(pos, -1, sizeof(pos));                         // pos初始全为-1
    for (int i = 0; s[i]; i++) {
        len += 1;
        if (i - pos[s[i]] < len) len = i - pos[s[i]];
        pos[s[i]] = i;
        if (len > ans) ans = len;
    }
    return ans;
}

// 方法二：前面一堆1, 后面一堆0, 找最后一个1
int check(char *s, int len) {                             // 判断字符串s中有没有长度为len的子串, len也代表滑动的窗口长度
    int nums[256] = {0}, cnt = 0;                         // cnt代表这个窗口中的最长子串长度
    for (int i = 0; s[i]; i++) {
        nums[s[i]] += 1;                                  // num[i]等于1代表长度为len的窗口首次出现这个字符, 最长子串长度应该加1
        cnt += (nums[s[i]] == 1);
        if (i >= len) {
            nums[s[i - len]]--;
            cnt -= (nums[s[i - len]] == 0);               // num[i]等于0代表这个字符被移除了长度为len的窗口，最长子串长度应该减1
        }
        if (cnt == len) return 1;
    }
    return 0;
}

int lengthOfLongestSubstring2(char *s) {
    int head = 0, tail = strlen(s), mid;
    while (head < tail) {
        mid = (head + tail + 1) >> 1;
        if (check(s, mid) == 1) head = mid;
        else tail = mid - 1;
    }
    return head;
}

int main() {
    char s[] = "abcabcbb";
    printf("%d\n", lengthOfLongestSubstring(s));
    printf("%d\n", lengthOfLongestSubstring2(s));
    return 0;
}
