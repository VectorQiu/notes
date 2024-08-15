#include <stdio.h>
#include <string.h>

#include "jsmn.h"
static int jsoneq(const char *json, jsmntok_t *tok, const char *s);

int main() {
    const char *json_str =
        "{\"name\": \"John\", \"age\": 30, \"city\": \"New York\"}";

    jsmn_parser parser;
    jsmntok_t tokens[10];  // 假设最大有10个令牌

    jsmn_init(&parser);
    int token_count = jsmn_parse(
        &parser, json_str, strlen(json_str), tokens,
        sizeof(tokens) / sizeof(tokens[0])
    );

    if (token_count < 0) {
        printf("JSON解析失败: %d\n", token_count);
        return 1;
    }

    // 遍历解析出的令牌
    for (int i = 1; i < token_count; i++) {
        if (jsoneq(json_str, &tokens[i], "name") == 0) {
            printf(
                "name: %.*s\n", tokens[i + 1].end - tokens[i + 1].start,
                json_str + tokens[i + 1].start
            );
            i++;
        } else if (jsoneq(json_str, &tokens[i], "age") == 0) {
            printf(
                "age: %.*s\n", tokens[i + 1].end - tokens[i + 1].start,
                json_str + tokens[i + 1].start
            );
            i++;
        } else if (jsoneq(json_str, &tokens[i], "city") == 0) {
            printf(
                "city: %.*s\n", tokens[i + 1].end - tokens[i + 1].start,
                json_str + tokens[i + 1].start
            );
            i++;
        }
    }

    return 0;
}

// 比较令牌内容与字符串是否相等
static int jsoneq(const char *json, jsmntok_t *tok, const char *s) {
    if (tok->type == JSMN_STRING && (int)strlen(s) == tok->end - tok->start
        && strncmp(json + tok->start, s, tok->end - tok->start) == 0) {
        return 0;
    }
    return -1;
}