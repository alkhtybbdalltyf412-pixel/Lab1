#include <iostream>

const int N = 1024;

bool isDigit(char c) { return c >= '0' && c <= '9'; }
bool isEven(char c) { return (c - '0') % 2 == 0; }

// المعالجة على نفس المصفوفة. n طول السلسلة، تُحدَّث. ترجع false إذا ما في مكان كافي
bool process(char s[], int& n) {
    if (n == 0) return true;
    bool lastEven = isDigit(s[n - 1]) && isEven(s[n - 1]);

    // 1) حذف الأرقام الفردية
    int w = 0;
    for (int r = 0; r < n; ++r) {
        if (isDigit(s[r]) && !isEven(s[r])) continue;
        s[w++] = s[r];
    }

    // 2) عدّ الأرقام الباقية (كلها زوجية) واستبعاد الأخير إذا كان آخر محرف
    int cnt = 0;
    for (int i = 0; i < w; ++i)
        if (isDigit(s[i])) ++cnt;
    if (lastEven) --cnt;

    int newLen = w + 2 * cnt;
    if (newLen > N) return false;

    // 3) التوسيع من النهاية للبداية
    int r = w - 1, p = newLen - 1;
    while (r >= 0) {
        if (isDigit(s[r]) && !(lastEven && r == w - 1)) {
            s[p--] = '+';
            s[p--] = '+';
        }
        s[p--] = s[r];
        --r;
    }
    n = newLen;
    return true;
}

int main() {
    char s[N];
    std::cout << "Enter string: ";
    std::cin.getline(s, N);
    int n = static_cast<int>(std::cin.gcount()) - 1;  // الطول بدون '\0'
    if (n < 0) n = 0;

    if (!process(s, n)) {
        std::cout << "Not enough space in array\n";
        return 1;
    }

    std::cout << "Result: ";
    for (int i = 0; i < n; ++i) std::cout << s[i];
    std::cout << '\n';
    return 0;
}