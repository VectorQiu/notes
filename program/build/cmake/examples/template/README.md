# CMake Build Template Project

[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE) [![Build Status](https://img.shields.io/badge/build-passing-brightgreen.svg)](https://example.com/build-status)

这是一个使用 CMake 构建的 C 项目模板，包含源代码和单元测试结构，支持 Clang 编译器，并配置了代码格式管理。

## 目录

- [背景](#背景)
- [功能](#功能)
- [安装](#安装)
- [使用方法](#使用方法)
- [项目结构](#项目结构)
- [代码格式管理](#代码格式管理)
- [贡献](#贡献)
- [许可证](#许可证)

## 背景

该项目旨在提供一个 C 项目的基本模板，适合中小型项目的快速初始化。它包括代码模块、单元测试框架、代码格式化支持等，帮助开发者建立一致的开发环境和项目结构。

## 功能

- 使用 CMake 配置和构建
- `calculator` 和 `stack` 功能模块
- `clang-format` 代码格式管理
- 基于 Unity 框架的单元测试

## Windows

### MSVC编译器

#### 安装

- Microsoft C++ 生成工具: [visual-cpp-build-tools](https://visualstudio.microsoft.com/zh-hans/visual-cpp-build-tools/)
- [Python](https://www.python.org)
- [LLVM](https://llvm.org/)
  - [Clang](https://clang.llvm.org/)
  - [LLDB](https://lldb.llvm.org/)
  - [ClangFormat](https://clang.llvm.org/docs/ClangFormat.html)
- [CMake](https://cmake.org/)
- [Ninja](https://ninja-build.org/)

**验证安装**

```bash
# 1.Microsoft C++ 生成工具
# 在 Developer Command Prompt for VS 输入cl
C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools>cl
用于 x86 的 Microsoft (R) C/C++ 优化编译器 19.41.34123 版
版权所有(C) Microsoft Corporation。保留所有权利。

用法: cl [ 选项... ] 文件名... [ /link 链接选项... ]

# 2.Python
python --version
> Python 3.13.0

# 3.cmke
cmake --version
> cmake version 3.30.5

> CMake suite maintained and supported by Kitware (kitware.com/cmake).

# 4.ninja
ninja --version
> 1.12.1

# 5.clang-format
clang-format --version
> clang-format version 19.1.0
```

### Clang+LLDB

#### 安装

请确保已安装以下工具：

- [LLVM](https://llvm.org/)
  - [Clang](https://clang.llvm.org/)
  - [LLDB](https://lldb.llvm.org/)
  - [ClangFormat](https://clang.llvm.org/docs/ClangFormat.html)
- [CMake](https://cmake.org/)
- [Ninja](https://ninja-build.org/)

1. 克隆仓库：

    ```bash
    git clone https://github.com/yourusername/template.git
    cd template
    ```

2. 初始化并构建项目：

    ```bash
    mkdir build
    cd build
    cmake -G Ninja ..
    ninja
    ```

### GCC+GDB

https://sourceforge.net/projects/mingw-w64/

## 使用方法

### 运行项目

以下代码展示如何编写并运行一个简单的测试示例：

```bash
cd build
ninja test
```

### 代码格式化

该项目包含 `.clang-format` 和 `clang-format-config.json` 文件，可以使用 `clang-format` 工具统一代码风格。在 `.vscode` 目录中还设置了代码格式的自动化管理。

格式化命令：

```bash
python .\scripts\run-clang-format-from-config.py
```

## 代码格式管理

项目中配置了 `clang-format`，用于统一代码风格。你可以在 `.vscode` 的 `settings.json` 中配置自动格式化支持，或者手动运行格式化脚本 `scripts/run-clang-format-from-config.py`。

## 项目结构

```plaintext
TEMPLATE
│
├── .vscode                  # VSCode 配置，支持 clang-format
│
├── build                    # 构建生成目录
│
├── cmake                    # CMake 配置
│   └── clang.cmake          # Clang 编译器的 CMake 配置
│
├── scripts                  # 脚本目录
│   └── run-clang-format-from-config.py # 格式化脚本
│
├── src                      # 源代码目录
│   ├── calculator           # 计算模块
│   └── stack                # 栈模块
│
├── test                     # 单元测试目录
│   └── stack                # 栈模块测试
│
├── .clang-format            # Clang 格式化配置文件
├── .gitignore               # Git 忽略文件
├── CMakeLists.txt           # 顶层 CMake 配置文件
├── LICENSE                  # 许可证
└── README.md                # 项目说明文件
```



## 贡献

欢迎任何形式的贡献！如果你发现任何问题或希望增加新功能，请提交 Issue 或 Pull Request。

### 提交指南 

遵循 [约定式提交](https://www.conventionalcommits.org/zh-hans/) 规范。请确保你的提交信息符合以下格式：

<类型>(<范围>): <描述>

其中：
- `类型`：用于描述提交的类别，常见的类型包括：
  - `feat`：新功能
  - `fix`：修复问题
  - `docs`：仅文档更新
  - `style`：不影响代码含义的更改（例如格式化、缺少分号等）
  - `refactor`：既不修复错误也不添加功能的代码更改
  - `test`：添加缺失的测试或修改现有测试
  - `chore`：构建过程或辅助工具的变动
- `范围`：提交影响的模块或文件，可以省略。
- `描述`：简要说明修改内容。

#### 示例

- `feat(calculator): 添加乘法功能`
- `fix(stack): 修复栈溢出问题`
- `docs(readme): 更新安装说明`
- `chore(ci): 添加 GitHub Actions 配置`

### 提交步骤

1. Fork 此仓库
2. 创建分支 (`git checkout -b feat/your-feature`)
3. 按照约定式提交规范提交更改 (`git commit -m 'feat(scope): 添加新功能'`)
4. 推送到分支 (`git push origin feat/your-feature`)
5. 创建一个 Pull Request

## 许可证

此项目基于 `MIT `许可证。详细信息请查看 `LICENSE` 文件。