> [Makefile教程- 廖雪峰的官方网站](https://liaoxuefeng.com/books/makefile/)
>
> [跟我一起写Makefile 1.0 文档](https://seisman.github.io/how-to-write-makefile/overview.html)

# 1 简介

Makefile 是一种用于自动化构建和管理软件项目的工具，通常用于编译程序、管理项目依赖关系、生成库文件、执行测试、清理构建环境等任务。它通过定义规则来描述文件之间的依赖关系和生成方法，从而实现自动化处理。

### Makefile 的基本要素

1. **目标（Target）**：
   - 目标是一个你希望生成的文件或执行的任务名称，比如可执行文件、库文件等。目标通常位于规则的开头。
2. **依赖（Dependencies）**：
   - 依赖是生成目标所需的文件或其他目标。如果依赖文件发生变化，Makefile 会知道目标需要重新生成。
3. **规则（Rules）**：
   - 规则定义了如何从依赖文件生成目标。规则由一系列命令组成，这些命令在目标需要更新时被执行。
4. **变量（Variables）**：
   - Makefile 中可以使用变量来简化和复用代码，比如指定编译器名称、编译选项等。

### 基本示例

```makefile
# 定义变量
CC = gcc
CFLAGS = -Wall -g

# 定义目标及其依赖
my_program: main.o utils.o
    $(CC) $(CFLAGS) -o my_program main.o utils.o

# 定义如何生成 .o 文件
main.o: main.c
    $(CC) $(CFLAGS) -c main.c

utils.o: utils.c
    $(CC) $(CFLAGS) -c utils.c

# 定义清理命令
clean:
    rm -f my_program *.o
```

### 主要功能

- **简化编译过程**：Makefile 可以自动识别哪些文件需要重新编译，减少不必要的编译步骤。
- **管理依赖关系**：当源文件或头文件发生变化时，Makefile 能够自动更新受影响的文件。
- **提高项目可维护性**：通过清晰的规则和变量定义，Makefile 可以使项目的构建过程更加可读和易于维护。
- **跨平台构建**：通过编写适当的 Makefile，项目可以在不同的操作系统或平台上轻松编译。

### 使用方法

- 在终端中运行 `make` 命令，Make 会根据 Makefile 中的规则自动处理构建过程。
- 可以通过指定不同的目标来执行不同的任务，例如 `make clean` 来清理构建生成的文件。

### 适用场景

Makefile 在 C/C++ 项目中应用广泛，但也可以用于任何需要自动化构建的项目，例如编译 LaTeX 文档、处理 Python 脚本等。

Makefile 是一种功能强大且灵活的工具，适用于各种编译和构建任务。

