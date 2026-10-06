#include "digit_processor.h"
#include <cstring>

namespace {
    bool isDigit(char c) { return c >= '0' && c <= '9'; }
    bool isEven(char c) { return (c - '0') % 2 == 0; }
}

bool process_digits(char* s, int capacity) {
    int len = static_cast<int>(std::strlen(s));
    if (len == 0) return true;
    bool lastEven = isDigit(s[len - 1]) && isEven(s[len - 1]);

    // 1) حذف الأرقام الفردية
    int w = 0;
    for (int r = 0; r < len; ++r) {
        if (isDigit(s[r]) && !isEven(s[r])) continue;
        s[w++] = s[r];
    }
    s[w] = '\0';
    len = w;

    // 2) عدّ الأرقام الباقية
    int cnt = 0;
    for (int i = 0; i < len; ++i)
        if (isDigit(s[i])) ++cnt;
    if (lastEven) --cnt;

    int newLen = len + 2 * cnt;
    if (newLen >= capacity) return false;

    // 3) التوسيع من النهاية للبداية
    s[newLen] = '\0';
    int r = len - 1, p = newLen - 1;
    while (r >= 0) {
        if (isDigit(s[r]) && !(lastEven && r == len - 1)) {
            s[p--] = '+';
            s[p--] = '+';
        }
        s[p--] = s[r];
        --r;
    }
    return true;
}