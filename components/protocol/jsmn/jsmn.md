> [json](https://www.json.org/json-en.html)
>
> [jsmn information](http://zserge.com/jsmn.html)
>
> [jsmn github](https://github.com/zserge/jsmn)

`jsmn`（JSON Minimalist Parser）是一个轻量级的C语言库，用于解析JSON数据。它以一种简单、快速的方式解析JSON字符串，适合嵌入式系统等对资源要求苛刻的场景。`jsmn`的设计目标是提供一种无需动态内存分配且易于集成的小型JSON解析器。

### 主要特点

1. **轻量级**：`jsmn`仅包含一个C源文件和一个头文件，总大小非常小，适合嵌入式设备等资源有限的环境。
2. **无需动态内存分配**：`jsmn`不使用`malloc`或`free`，这使得它可以在不支持动态内存分配的环境中运行。
3. **基于令牌的解析**：`jsmn`不会将JSON解析为完整的树结构，而是将其解析为一组令牌（token）。这些令牌描述了JSON对象的结构，用户可以根据这些令牌来提取需要的值。
4. **只读模式**：`jsmn`只解析JSON数据，不修改输入数据，因此可以安全地解析常量或只读的JSON字符串。

### 基本概念

- **JSON令牌（Token）**：`jsmn`通过令牌来表示JSON数据结构。每个令牌都有一个类型（如对象、数组、字符串、原始类型）、起始位置、结束位置和大小。
- **令牌类型**：
  - `JSMN_PRIMITIVE`：表示基本类型（如数字、布尔值、`null`）。
  - `JSMN_STRING`：表示字符串。
  - `JSMN_OBJECT`：表示JSON对象。
  - `JSMN_ARRAY`：表示数组。
- **jsmn_parser**：`jsmn`的核心结构体，用于存储解析的状态。

### 使用步骤

1. **初始化解析器**：在解析JSON字符串之前，需要先初始化`jsmn_parser`结构体。

   ```
   c复制代码jsmn_parser parser;
   jsmn_init(&parser);
   ```

2. **解析JSON字符串**：调用`jsmn_parse`函数，传入JSON字符串、令牌数组及其大小。

   ```
   c复制代码jsmntok_t tokens[128];  // 假设最大有128个令牌
   int token_count = jsmn_parse(&parser, json_str, strlen(json_str), tokens, sizeof(tokens)/sizeof(tokens[0]));
   ```

3. **处理解析结果**：解析完成后，`tokens`数组中会存储所有解析出来的令牌，可以通过遍历令牌数组来访问JSON数据。

### 示例代码

下面是一个简单的例子，展示如何使用`jsmn`解析一个JSON字符串并提取其中的值。

```c
#include <stdio.h>
#include <string.h>
#include "jsmn.h"

int main() {
    const char *json_str = "{\"name\": \"John\", \"age\": 30, \"city\": \"New York\"}";

    jsmn_parser parser;
    jsmntok_t tokens[10];  // 假设最大有10个令牌

    jsmn_init(&parser);
    int token_count = jsmn_parse(&parser, json_str, strlen(json_str), tokens, sizeof(tokens)/sizeof(tokens[0]));

    if (token_count < 0) {
        printf("JSON解析失败: %d\n", token_count);
        return 1;
    }

    // 遍历解析出的令牌
    for (int i = 1; i < token_count; i++) {
        if (jsoneq(json_str, &tokens[i], "name") == 0) {
            printf("name: %.*s\n", tokens[i+1].end - tokens[i+1].start, json_str + tokens[i+1].start);
            i++;
        } else if (jsoneq(json_str, &tokens[i], "age") == 0) {
            printf("age: %.*s\n", tokens[i+1].end - tokens[i+1].start, json_str + tokens[i+1].start);
            i++;
        } else if (jsoneq(json_str, &tokens[i], "city") == 0) {
            printf("city: %.*s\n", tokens[i+1].end - tokens[i+1].start, json_str + tokens[i+1].start);
            i++;
        }
    }

    return 0;
}

// 比较令牌内容与字符串是否相等
int jsoneq(const char *json, jsmntok_t *tok, const char *s) {
    if (tok->type == JSMN_STRING && (int)strlen(s) == tok->end - tok->start &&
        strncmp(json + tok->start, s, tok->end - tok->start) == 0) {
        return 0;
    }
    return -1;
}
```

### 常见用法场景

1. **嵌入式系统**：由于`jsmn`轻量且无需动态内存分配，非常适合在内存和资源受限的嵌入式系统中使用。
2. **数据提取**：`jsmn`解析JSON数据的方式适合用来提取特定的键值对，而不需要构建完整的JSON树。
3. **数据验证**：`jsmn`可以快速验证一个JSON字符串的结构是否正确，适合用作简单的JSON格式验证工具。

### 总结

`jsmn` 是一个简洁、快速、易于使用的JSON解析库，尤其适合在嵌入式系统或其他资源受限的环境中使用。通过使用`jsmn`，你可以在C语言环境中高效地处理JSON数据