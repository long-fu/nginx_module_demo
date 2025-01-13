#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <gmssl/sm4.h>
#include "base64.h"


long get_current_milliseconds() {
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    return (long)(ts.tv_sec) * 1000 + ts.tv_nsec / 1000000;
}

void replace_char(char* str, char old_char, char new_char) {
    while (*str != '\0') {  // 遍历整个字符串，直到遇到结尾符
        if (*str == old_char) {
            *str = new_char;  // 替换字符
        }
        str++;  // 移动到下一个字符
    }
}

