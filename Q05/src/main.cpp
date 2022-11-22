#include "solution.h"

int main() {
#ifdef _WIN32
    system("chcp 65001");
#endif
    solution();
#ifdef _WIN32
    system("pause");
#endif
    return 0;
}
