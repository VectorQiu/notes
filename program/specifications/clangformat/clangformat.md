# ClangFormat

> https://clang.llvm.org/docs/ClangFormat.html
>
> https://clang.llvm.org/docs/ClangFormatStyleOptions.html

`clang-format` 是一个由 LLVM 项目开发的代码格式化工具，支持多种编程语言，包括 C、C++、Java、JavaScript、Objective-C、Protobuf 和 C#。它可以根据预定义的或自定义的代码风格规则自动格式化代码，从而保持代码的一致性和可读性。

## 1.安装 `clang-format`

### 1.1 在 Windows 上安装

1. **通过 LLVM 官方网站下载**：[下载链接](https://releases.llvm.org/)

2. **通过包管理工具安装**：Scoop

   ```c
   
   ```

### 1.2 在Linux上安装

**通过包管理工具安装**：

- 对于基于 Debian 的发行版（如 Ubuntu）：

  ```sh
  sudo apt-get install clang-format
  ```

- 对于基于 Red Hat 的发行版（如 Fedora）：

  ```sh
  sudo dnf install clang-format
  ```

**通过源码编译安装**：

- 下载 LLVM 源码并编译 `clang-format`（不推荐，较为复杂）。

## 2.使用 `clang-format`

### 基本用法

- 你可以通过命令行直接运行 `clang-format`，例如：

  ```sh
  clang-format -i <file>
  ```

  其中 `-i`参数表示直接修改文件。

### 配置文件 `.clang-format`

- `clang-format` 可以使用 `.clang-format` 配置文件定义格式规则。创建一个 `.clang-format`文件，并添加你想要的配置，例如：

  ```yaml
  BasedOnStyle: Google
  IndentWidth: 4
  ```

**要获得一个有效的 .clang 格式文件，其中包含某个预定义样式的所有配置选项，有一个简单的方法：**

```
clang-format -style=Google -dump-config > .clang-format
```

**禁用一段代码的格式化** 

Clang-format 也能理解在限定范围内切换格式化的特殊注释。从注释 // clang-format off 或 /* clang-format off */ 到注释 // clang-format on 或 /* clang-format on */ 之间的代码不会被格式化。注释本身将正常格式化（对齐）。此外，在 // clang-format off 或 // clang-format on 之后可能会出现冒号（:）和附加文本，以解释关闭或重新开启 clang-format 的原因。

```
int formatted_code;
// clang-format off
    void    unformatted_code  ;
// clang-format on
void formatted_code_again;
```

