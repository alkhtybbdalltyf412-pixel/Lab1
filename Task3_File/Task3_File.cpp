#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>

const int N = 1024;

bool isDigit(char c) { return c >= '0' && c <= '9'; }
bool isEven(char c) { return (c - '0') % 2 == 0; }

bool process(char* s) {
    int len = static_cast<int>(std::strlen(s));
    if (len == 0) return true;
    bool lastEven = isDigit(s[len - 1]) && isEven(s[len - 1]);

    int w = 0;
    for (int r = 0; r < len; ++r) {
        if (isDigit(s[r]) && !isEven(s[r])) continue;
        s[w++] = s[r];
    }
    s[w] = '\0';
    len = w;

    int cnt = 0;
    for (int i = 0; i < len; ++i)
        if (isDigit(s[i])) ++cnt;
    if (lastEven) --cnt;

    int newLen = len + 2 * cnt;
    if (newLen >= N) return false;

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

int main() {
    FILE* in = std::fopen("input.txt", "r");
    if (!in) {
        std::puts("Cannot open input.txt");
        return 1;
    }

    char s[N];
    if (!std::fgets(s, N, in)) s[0] = '\0';  // ملف فاضي
    std::fclose(in);

    // شيل محرف نهاية السطر إن وجد
    std::size_t len = std::strlen(s);
    if (len > 0 && s[len - 1] == '\n') s[len - 1] = '\0';

    if (!process(s)) {
        std::puts("Not enough space in array");
        return 1;
    }

    FILE* out = std::fopen("output.txt", "w");
    if (!out) {
        std::puts("Cannot open output.txt");
        return 1;
    }
    std::fputs(s, out);
    std::fputs("\n", out);
    std::fclose(out);

    std::puts("Done. Result written to output.txt");
    return 0;
}