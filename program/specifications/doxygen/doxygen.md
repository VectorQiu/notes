> [doxygen](https://www.doxygen.nl/index.html)
>
> [Do one thing and do it well](http://cedar-renjun.github.io/2014/03/21/learn-doxygen-in-10-minutes/index.html)
>
> [Microsoft HTML Help Downloads](https://learn.microsoft.com/en-us/previous-versions/windows/desktop/htmlhelp/microsoft-html-help-downloads)
>
> [Microsoft HTML Help Workshop](https://www.helpandmanual.com/downloads_mscomp.html)
>
> [Graphviz](https://graphviz.org)

在项目中使用Doxygen生成维护文档是一种非常有效的方法，它可以帮助团队成员更好地理解代码结构、功能模块和依赖关系。下面我将详细介绍如何使用Doxygen生成高质量的维护文档。

# Doxygen

## 目录

1. [安装与设置](#安装与设置)
2. [Doxygen配置文件的生成与编辑](#doxygen配置文件的生成与编辑)
3. [代码注释规范](#代码注释规范)
4. [文档生成](#文档生成)
5. [高级功能](#高级功能)
6. [自动化文档生成](#自动化文档生成)
7. [常见问题及解决方法](#常见问题及解决方法)
8. [总结](#总结)

------

## 安装与设置

### 安装Doxygen

Doxygen是一个跨平台的工具，支持Windows、macOS和Linux。你可以从Doxygen的官方网站下载并安装：https://www.doxygen.nl/download.html。

### 安装Graphviz（可选）

如果你想在文档中生成图表（如类图、调用图等），需要安装Graphviz。你可以从Graphviz官网下载并安装。安装后，确保`dot`命令可以在命令行中运行。

------

## Doxygen配置文件的生成与编辑

### 生成Doxygen配置文件

在项目的根目录下运行以下命令生成默认的`Doxyfile`配置文件：

```bash
doxygen -g Doxyfile
```

这将在当前目录下生成一个名为`Doxyfile`的配置文件。

### 编辑Doxyfile配置文件

打开`Doxyfile`，根据你的项目需求编辑以下关键参数：

```ini
# 项目名称
PROJECT_NAME           = "Your Project Name"

# 项目版本号
PROJECT_NUMBER         = 1.0.0

# 输入源文件的路径
INPUT                  = ./src

# 是否递归搜索子目录
RECURSIVE              = YES

# 输出目录
OUTPUT_DIRECTORY       = ./docs

# 生成HTML文档
GENERATE_HTML          = YES

# 生成LaTeX文档（用于生成PDF）
GENERATE_LATEX         = YES

# 是否生成类图、调用图等
HAVE_DOT               = YES

# DOT工具的路径（可选）
DOT_PATH               = /path/to/graphviz/bin

# 指定HTML输出目录
HTML_OUTPUT            = html

# 是否生成树形结构
GENERATE_TREEVIEW      = YES

# 代码注释风格，C/C++风格支持JavaDoc或Qt样式
JAVADOC_AUTOBRIEF      = YES
QT_AUTOBRIEF           = YES
```

这些配置将帮助你生成包含类结构图、函数调用关系图等信息的HTML或PDF文档。

------

## 代码注释规范

Doxygen依赖代码中的注释来生成文档。良好的注释不仅有助于自动生成文档，还能提升代码的可维护性。

### 注释风格

Doxygen支持多种注释风格，以下是常用的几种：

#### JavaDoc风格

```cpp
/**
 * @brief 计算两个整数的和。
 * 
 * @param[in] a 第一个整数
 * @param[in] b 第二个整数
 * @return int 返回两个整数的和
 */
int add(int a, int b);
```

```cpp
/**
 *  A test class. A more elaborate class description.
 */
class Javadoc_Test
{

  public:
    /** 
     * An enum.
     * More detailed enum description.
     */
    enum TEnum { 
          TVal1, /**< enum value TVal1. */  
          TVal2, /**< enum value TVal2. */  
          TVal3  /**< enum value TVal3. */  
         } 
       *enumPtr, /**< enum pointer. Details. */
       enumVar;  /**< enum variable. Details. */

      /**
       * A constructor.
       * A more elaborate description of the constructor.
       */
      Javadoc_Test();

      /**
       * A destructor.
       * A more elaborate description of the destructor.
       */
     ~Javadoc_Test();
    
      /**
       * a normal member taking two arguments and returning an integer value.
       * @param a an integer argument.
       * @param s a constant character pointer.
       * @see Javadoc_Test()
       * @see ~Javadoc_Test()
       * @see testMeToo()
       * @see publicVar()
       * @return The test results
       */
       int testMe(int a,const char *s);

      /**
       * A pure virtual member.
       * @see testMe()
       * @param c1 the first argument.
       * @param c2 the second argument.
       */
       virtual void testMeToo(char c1,char c2) = 0;

      /** 
       * a public variable.
       * Details.
       */
       int publicVar;

      /**
       * a function variable.
       * Details.
       */
       int (*handler)(int a,int b);
};
```

#### Qt风格

```cpp
/*!
 * \brief 计算两个整数的和。
 * 
 * \param[in] a 第一个整数
 * \param[in] b 第二个整数
 * \return 返回两个整数的和
 */
int add(int a, int b);
```

```cpp
//!  A test class. 
/*!
  A more elaborate class description.
*/
class QTstyle_Test
{
  public:
    
    //! An enum.
    /*! More detailed enum description. */
    enum TEnum { 
                 TVal1, /*!< Enum value TVal1. */  
                 TVal2, /*!< Enum value TVal2. */  
                 TVal3  /*!< Enum value TVal3. */  
               } 

         //! Enum pointer.
         /*! Details. */
         *enumPtr, 

         //! Enum variable.
         /*! Details. */
         enumVar;

    //! A constructor.
    /*!
      A more elaborate description of the constructor.
    */
    QTstyle_Test();

    //! A destructor.
    /*!
      A more elaborate description of the destructor.
    */
   ~QTstyle_Test();

    //! A normal member taking two arguments and returning an integer value.
    /*!
      \param a an integer argument.
      \param s a constant character pointer.
      \return The test results
      \sa QTstyle_Test(), ~QTstyle_Test(), testMeToo() and publicVar()
    */
    int testMe(int a,const char *s);

    //! A pure virtual member.
    /*!
      \sa testMe()
      \param c1 the first argument.
      \param c2 the second argument.
    */
    virtual void testMeToo(char c1,char c2) = 0;

    //! A public variable.
    /*!
      Details.
    */
    int publicVar;

    //! A function variable.
    /*!
      Details.
    */
    int (*handler)(int a,int b);
};
```

### 注释内容

在编写注释时，确保包含以下信息：

- **函数描述**：简要描述函数的作用。
- **参数说明**：详细说明每个参数的用途（使用`@param`或`\param`）。
- **返回值**：描述函数的返回值（使用`@return`或`\return`）。
- **异常或错误**：说明函数可能抛出的异常或错误条件。

### 文件和模块注释

除了函数和类的注释，还应为文件和模块添加注释，以便生成文档时能清晰展示项目的整体结构。

```cpp
/**
 * @file myfile.cpp
 * @brief 这个文件实现了XXX模块的功能。
 * 
 * 详细描述该文件的功能、用途、注意事项等。
 */
```

------

### 1. 常用的注释风格

Doxygen支持多种注释风格，以下是常用的几种：

#### 1.1 多行注释风格

```cpp
/**
 * 这是一个简单的函数，用于计算两个整数的和。
 * 
 * @param[in] a 第一个整数
 * @param[in] b 第二个整数
 * @return 返回两个整数的和
 */
int add(int a, int b);
```

#### 1.2 单行注释风格

```cpp
/// 这是一个简单的函数，用于计算两个整数的和。
int add(int a, int b);

int var; /*!< Detailed description after the member */
// Qt style detailed documentation block after a member
int var; /**< Detailed description after the member */
int var; //!< Detailed description after the member
int var; ///< Detailed description after the member
void foo(int v /**< [in] docs for input parameter v. */);

/*! A test class */
class Afterdoc_Test
{
  public:
    /** An enum type. 
     *  The documentation block cannot be put after the enum! 
     */
    enum EnumType
    {
     	int EVal1,     /**< enum value 1 */
      	int EVal2      /**< enum value 2 */
    };
    void member();   //!< a member function.

  protected:
    int value;       /*!< an integer value */
};
```

#### 1.3 特殊的`/*!` 风格

```cpp
/*!
 * 这是一个简单的函数，用于计算两个整数的和。
 * 
 * \param a 第一个整数
 * \param b 第二个整数
 * \return 返回两个整数的和
 */
int add(int a, int b);
```

### 2. 常用的JavaDoc `@` 标签

Doxygen支持多种`@`标签，用于描述函数、参数、返回值等。以下是一些常用的标签：

#### 2.1 基本标签

- **@brief**
  简要描述函数或类的作用。

  ```cpp
  /**
   * @brief 计算两个整数的和。
   */
  int add(int a, int b);
  ```

- **@param**
  描述函数的参数。可以使用`[in]`、`[out]`、`[in,out]`来标识参数的输入输出性质。

  ```cpp
  /**
   * @param[in] a 第一个整数
   * @param[in] b 第二个整数
   */
  int add(int a, int b);
  ```

- **@return**
  描述函数的返回值。

  ```cpp
  /**
   * @return 返回两个整数的和。
   */
  int add(int a, int b);
  ```

- **@retval**
  描述函数返回的不同值以及它们的含义。

  ```cpp
  /**
   * @retval 0 成功
   * @retval -1 失败
   */
  int init();
  ```

- **@file**
  描述文件的作用，可以放在文件的头部注释中。

  ```cpp
  /**
   * @file myfile.cpp
   * @brief 这个文件实现了XXX模块的功能。
   */
  ```

- **@author**
  记录作者信息。

  ```cpp
  /**
   * @author 张三
   */
  ```

- **@version**
  记录版本信息。

  ```cpp
  /**
   * @version 1.0
   */
  ```

- **@date**
  记录日期信息。

  ```cpp
  /**
   * @date 2024年8月23日
   */
  ```

#### 2.2 结构化标签

- **@code** / **@endcode**
  用于插入代码片段。

  ```cpp
  /**
   * @code
   * int result = add(1, 2);
   * @endcode
   */
  ```

- **@note**
  用于添加注释或特别说明。

  ```cpp
  /**
   * @note 此函数不处理负数。
   */
  ```

- **@warning**
  用于标记重要的警告信息。

  ```cpp
  /**
   * @warning 此函数为线程不安全。
   */
  ```

- **@todo**
  用于标记待办事项或未完成的功能。

  ```cpp
  /**
   * @todo 实现乘法功能。
   */
  ```

- **@bug**
  用于记录已知的bug。

  ```cpp
  /**
   * @bug 当a和b为负数时，结果不正确。
   */
  ```

- **@see**
  用于引用相关的函数或文档。

  ```cpp
  /**
   * @see subtract(int, int)
   */
  ```

- **@ingroup**
  将函数、类或文件分组。

  ```cpp
  /**
   * @ingroup MathFunctions
   */
  int add(int a, int b);
  ```

#### 2.3 类与结构体的标签

- **@class**
  用于注释类的定义。

  ```cpp
  /**
   * @class MyClass
   * @brief 这是一个示例类。
   */
  class MyClass {
      ...
  };
  ```

- **@struct**
  用于注释结构体的定义。

  ```cpp
  /**
   * @struct MyStruct
   * @brief 这是一个示例结构体。
   */
  struct MyStruct {
      int x;
      int y;
  };
  ```

- **@typedef**
  用于注释`typedef`类型定义。

  ```cpp
  /**
   * @typedef int MyInt
   * @brief MyInt是int类型的别名。
   */
  typedef int MyInt;
  ```

- **@enum**
  用于注释枚举类型。

  ```cpp
  /**
   * @enum Color
   * @brief 定义颜色的枚举。
   */
  enum Color {
      RED,
      GREEN,
      BLUE
  };
  ```

### 3.`@`标签

以下是JavaDoc风格的`@`标签在Doxygen中的详细说明，以表格形式列出：

| 标签          | 用途           | 说明                                                         |
| ------------- | -------------- | ------------------------------------------------------------ |
| `@brief`      | 简要描述       | 提供对函数、类、结构、文件等的简短描述。常用于生成文档中的摘要。 |
| `@param`      | 参数说明       | 描述函数的参数。通常使用`@param[in]`、`@param[out]`、`@param[in,out]`来标识参数的输入输出性质。 |
| `@return`     | 返回值说明     | 描述函数的返回值类型和含义。                                 |
| `@retval`     | 返回值详细说明 | 详细描述特定返回值的含义，通常用于函数可能返回多种不同值的情况。 |
| `@author`     | 作者信息       | 用于记录代码的作者姓名。                                     |
| `@version`    | 版本信息       | 用于记录代码或文档的版本号。                                 |
| `@date`       | 日期           | 用于记录代码的创建或最后修改日期。                           |
| `@since`      | 自从版本       | 指出自从哪个版本引入了该函数、类或模块。                     |
| `@deprecated` | 弃用说明       | 标记代码的某些部分已弃用，并建议使用其他方法。               |
| `@see`        | 相关项引用     | 提供相关函数、类或模块的引用，用于跳转到相关内容。           |
| `@code`       | 代码片段       | 用于插入代码示例，必须配合`@endcode`使用。                   |
| `@endcode`    | 结束代码片段   | 用于结束代码片段的标记，与`@code`配合使用。                  |
| `@note`       | 注释           | 提供额外的注释或说明。                                       |
| `@warning`    | 警告           | 提供需要注意的重要警告信息。                                 |
| `@todo`       | 待办事项       | 标记未来需要完成的任务或功能。                               |
| `@bug`        | 已知问题       | 记录代码中已知的bug或问题。                                  |
| `@pre`        | 前置条件       | 描述函数执行前必须满足的条件。                               |
| `@post`       | 后置条件       | 描述函数执行后的结果或必须满足的条件。                       |
| `@par`        | 分段说明       | 创建一个新的段落，用于详细描述。                             |
| `@ingroup`    | 分组           | 将函数、类、文件等分组，生成模块化的文档结构。               |
| `@class`      | 类注释         | 用于注释类的定义，通常包括类的简要说明。                     |
| `@struct`     | 结构体注释     | 用于注释结构体的定义，通常包括结构体的简要说明。             |
| `@typedef`    | 类型定义       | 注释`typedef`定义的类型，描述其用途和类型别名。              |
| `@enum`       | 枚举类型注释   | 用于注释枚举类型，描述枚举值的含义。                         |
| `@var`        | 变量注释       | 用于注释全局变量或类成员变量。                               |
| `@property`   | 属性注释       | 描述类或结构体中的属性，用于生成属性文档。                   |
| `@namespace`  | 命名空间注释   | 描述命名空间的用途和内容。                                   |
| `@fn`         | 函数注释       | 提供函数的详细注释说明。                                     |
| `@def`        | 宏定义注释     | 用于注释预处理器中的宏定义。                                 |
| `@headerfile` | 头文件注释     | 指定函数或类所属的头文件，便于生成头文件引用。               |
| `@example`    | 示例代码       | 提供一个独立的代码示例，通常用于展示某个功能的用法。         |
| `@todo`       | 待办事项       | 列出需要完成的任务或功能。                                   |
| `@attention`  | 注意事项       | 类似`@warning`，用于提醒注意。                               |
| `@exception`  | 异常说明       | 描述函数可能抛出的异常类型及其含义。                         |
| `@throws`     | 异常抛出说明   | 类似`@exception`，描述函数可能抛出的异常类型。               |
| `@remark`     | 备注           | 提供额外的备注或补充说明。                                   |
| `@internal`   | 内部说明       | 标记仅供内部使用的注释，不会在公开文档中显示。               |
| `@page`       | 页面注释       | 创建独立的文档页面，适合描述大的模块或独立的主题。           |
| `@section`    | 文档节         | 在独立页面或组页面中创建一个新节。                           |
| `@subsection` | 文档子节       | 创建文档的小节，通常配合`@section`使用。                     |
| `@mainpage`   | 主页           | 用于描述项目的主页，通常用于项目的整体介绍。                 |
| `@anchor`     | 锚点           | 创建一个可以跳转的锚点，便于在文档中快速导航。               |
| `@subpage`    | 子页面         | 用于创建和链接到子页面。                                     |
| `@xrefitem`   | 交叉引用项     | 用于在文档中创建交叉引用项。                                 |
| `@todo`       | 任务列表       | 列出尚未完成的任务或功能。                                   |

### 4.Doxygen Groups 功能

#### 1. **创建和定义分组**

在 Doxygen 中，你可以通过以下方式定义分组：

1. **在代码注释中使用 `@defgroup` 标签** 来定义一个新的分组。
2. **在代码中使用 `@ingroup` 标签** 将函数、类或变量加入到某个已定义的分组中。

#### 示例代码

```cpp
/**
 * @defgroup MathFunctions 数学函数
 * @{
 */

/**
 * @brief 计算两个整数的和。
 * @param[in] a 第一个整数
 * @param[in] b 第二个整数
 * @return 返回两个整数的和。
 */
int add(int a, int b);

/**
 * @brief 计算两个整数的差。
 * @param[in] a 第一个整数
 * @param[in] b 第二个整数
 * @return 返回两个整数的差。
 */
int subtract(int a, int b);

/** @} */ // 结束 MathFunctions 分组
```

在上述代码中，`@defgroup` 用于定义一个名为 `MathFunctions` 的分组。`@{` 和 `@}` 用于包裹属于该分组的所有函数或变量。这样，`add` 和 `subtract` 函数就被归入了 `MathFunctions` 分组。

#### 2. **将代码元素加入分组**

你可以将其他代码元素（如类、变量）加入到分组中：

```cpp
/**
 * @class Calculator
 * @ingroup MathFunctions
 * @brief 提供数学运算功能。
 */
class Calculator {
public:
    /**
     * @brief 计算两个整数的和。
     * @param[in] a 第一个整数
     * @param[in] b 第二个整数
     * @return 返回两个整数的和。
     */
    int add(int a, int b);
    
    // 更多成员函数和变量
};
```

在这里，`Calculator` 类被加入到 `MathFunctions` 分组中，使得它与之前定义的函数一起被组织到同一个分组下。

#### 3. **生成文档**

配置好 `Doxyfile` 后，运行 Doxygen 生成文档。Doxygen 会根据分组信息生成文档，并在文档中显示不同分组的内容。通常，在生成的文档中，你会看到每个分组的标题和相关的函数、类等信息。

### 高级用法

#### 1. **子分组**

你可以创建子分组来更细致地组织文档：

```cpp
/**
 * @defgroup MathFunctions 数学函数
 * @{
 */

/**
 * @defgroup BasicOperations 基本运算
 * @{
 */

/**
 * @brief 计算两个整数的和。
 * @param[in] a 第一个整数
 * @param[in] b 第二个整数
 * @return 返回两个整数的和。
 */
int add(int a, int b);

/** @} */ // 结束 BasicOperations 子分组

/** @} */ // 结束 MathFunctions 分组
```

在这个例子中，`BasicOperations` 是 `MathFunctions` 的子分组。

#### 2. **文档中的分组链接**

在 Doxygen 的文档中，分组会被列在相关的页面上，用户可以点击分组名称查看该分组下的所有代码元素。这有助于用户快速找到相关的功能或模块。

#### 3. **跨文件的分组**

分组不仅限于一个文件，你可以在多个文件中使用相同的分组名称：

```cpp
// 文件1.cpp
/**
 * @defgroup MathFunctions 数学函数
 * @{
 */

/** @} */

// 文件2.cpp
/**
 * @ingroup MathFunctions
 * @brief 计算两个整数的和。
 */
int add(int a, int b);
```

在这种情况下，Doxygen 会将所有文件中属于 `MathFunctions` 分组的内容聚合在一起。

`@addtogroup` 是 Doxygen 中用于将代码元素添加到已存在分组的标签。这与 `@ingroup` 的作用相似，但 `@addtogroup` 更常用于在分组的定义和内容之间创建关联，使得不同文件中的代码元素能够被纳入到相同的分组中。

### 使用 `@addtogroup` 标签

#### 1. **定义分组**

首先，你需要在某个文件中定义一个分组。可以使用 `@defgroup` 标签来完成：

```cpp
/**
 * @defgroup MathFunctions 数学函数
 * @{
 */

/**
 * @brief 计算两个整数的和。
 * @param[in] a 第一个整数
 * @param[in] b 第二个整数
 * @return 返回两个整数的和。
 */
int add(int a, int b);

/** @} */ // 结束 MathFunctions 分组
```

#### 2. **将代码元素添加到分组**

在其他文件中，你可以使用 `@addtogroup` 标签将相关的函数、类或变量添加到已存在的分组中：

```cpp
/**
 * @addtogroup MathFunctions
 * @{
 */

/**
 * @brief 计算两个整数的差。
 * @param[in] a 第一个整数
 * @param[in] b 第二个整数
 * @return 返回两个整数的差。
 */
int subtract(int a, int b);

/** @} */ // 结束 MathFunctions 分组
```

在上述示例中，`@addtogroup MathFunctions` 标签将 `subtract` 函数添加到已经定义的 `MathFunctions` 分组中。

### 使用场景

#### 1. **跨文件分组**

当一个分组的定义和其内容分布在多个文件中时，`@addtogroup` 标签可以帮助你将所有相关内容汇集到一个分组中。例如，分组的定义可以放在一个头文件中，而实现可以放在不同的源文件中：

```cpp
// MathFunctions.h
/**
 * @defgroup MathFunctions 数学函数
 * @{
 */

/**
 * @brief 计算两个整数的和。
 * @param[in] a 第一个整数
 * @param[in] b 第二个整数
 * @return 返回两个整数的和。
 */
int add(int a, int b);

/** @} */ // 结束 MathFunctions 分组
cpp复制代码// MathFunctions.cpp
/**
 * @addtogroup MathFunctions
 * @{
 */

/**
 * @brief 计算两个整数的差。
 * @param[in] a 第一个整数
 * @param[in] b 第二个整数
 * @return 返回两个整数的差。
 */
int subtract(int a, int b);

/** @} */ // 结束 MathFunctions 分组
```

#### 2. **添加到现有分组**

`@addtogroup` 标签允许你在需要时将额外的代码元素添加到已经存在的分组中，而不必重新定义整个分组。这对于大型项目尤其有用，可以保持文档结构的一致性。

### 注意事项

- **分组的定义**：分组的定义通常使用 `@defgroup` 标签，并在定义之后使用 `@{` 和 `@}` 包裹分组的内容。`@addtogroup` 标签则用来在定义后的其他地方将内容添加到该分组。
- **文档生成**：当你使用 `@addtogroup` 标签时，Doxygen 会将添加的内容与定义的分组汇总在一起，确保文档中分组的完整性和一致性。
- **分组名称**：`@addtogroup` 标签使用的分组名称必须与 `@defgroup` 标签中定义的名称一致，以确保正确的分组关联。

## 文档生成

### 生成HTML文档

配置好`Doxyfile`后，运行以下命令生成HTML文档：

```cpp
doxygen Doxyfile
```

生成的HTML文档会保存在`docs/html`目录中，你可以通过浏览器打开`index.html`文件来查看文档。

### 生成PDF文档

Doxygen可以通过LaTeX生成PDF文档。首先确保你的系统已安装LaTeX发行版，然后执行以下步骤：

1. 运行Doxygen生成LaTeX文件：

   ```bash
   doxygen Doxyfile
   ```

2. 切换到生成的LaTeX文件目录：

   ```bash
   cd docs/latex
   ```

3. 使用`make`命令生成PDF：

   ```bash
   make
   ```

生成的PDF文件将保存在当前目录下。

------

## 高级功能

### 生成图表

如果已安装Graphviz，可以在文档中生成类图、调用图等。确保`Doxyfile`中已启用Graphviz相关选项，并通过设置`HAVE_DOT = YES`来生成图表。

### 使用分组和模块

Doxygen允许你将代码分组，从而生成更具结构性的文档。例如，可以为项目的不同功能模块创建分组：

```cpp
/**
 * @defgroup MathFunctions 数学函数
 * @{
 */

/**
 * @brief 计算两个整数的和。
 */
int add(int a, int b);

/**
 * @brief 计算两个整数的差。
 */
int subtract(int a, int b);

/** @} */
```

```cpp
/** @defgroup group1 The First Group
 *  This is the first group
 *  @{
 */

/** @brief class C1 in group 1 */
class C1 {};

/** @brief class C2 in group 1 */
class C2 {};

/** function in group 1 */
void func() {}

/** @} */ // end of group1

 
/**
 *  @defgroup group2 The Second Group
 *  This is the second group
 */

/** @defgroup group3 The Third Group
 *  This is the third group
 */

/** @defgroup group4 The Fourth Group
 *  @ingroup group3
 *  Group 4 is a subgroup of group 3
 */

/**
 *  @ingroup group2
 *  @brief class C3 in group 2
 */
class C3 {};

/** @ingroup group2
 *  @brief class C4 in group 2
 */
class C4 {};

/** @ingroup group3
 *  @brief class C5 in @link group3 the third group@endlink.
 */
class C5 {};

/** @ingroup group1 group2 group3 group4
 *  namespace N1 is in four groups
 *  @sa @link group1 The first group@endlink, group2, group3, group4 
 *
 *  Also see @ref mypage2
 */
namespace N1 {};

/** @file
 *  @ingroup group3
 *  @brief this file in group 3
 */

/** @defgroup group5 The Fifth Group
 *  This is the fifth group
 *  @{
 */

/** @page mypage1 This is a section in group 5
 *  Text of the first section
 */

/** @page mypage2 This is another section in group 5
 *  Text of the second section
 */

/** @} */ // end of group5

 

/** @addtogroup group1
 *  
 *  More documentation for the first group.
 *  @{
 */
 

/** another function in group 1 */
void func2() {}

/** yet another function in group 1 */
void func3() {}

/** @} */ // end of group1
```



这样，生成的文档会显示不同模块的功能，使文档更加清晰。

### 处理多语言项目

如果你的项目包含多个编程语言（如C++和Python），可以配置Doxygen同时生成多语言的文档。确保`Doxyfile`中的`FILE_PATTERNS`设置了相应的文件扩展名，如：

```ini
FILE_PATTERNS = *.cpp *.h *.py
```

------

## 自动化文档生成

为了确保文档与代码保持同步，建议将Doxygen文档生成集成到项目的CI/CD流水线中。以下是一些示例：

### 使用Makefile

你可以在项目中添加一个Makefile来简化文档生成：

```Makefile
docs:
    doxygen Doxyfile
```

### CI/CD流水线集成

在CI/CD工具（如Jenkins、GitLab CI、GitHub Actions）中，可以配置脚本在每次提交或定期生成文档并将其部署到服务器或发布存储库中。

## 在项目中使用 Doxygen

在项目中使用 Doxygen 生成优质的文档时，需要注意以下几个方面，以确保文档清晰、结构合理、易于维护和阅读：

### 1. **项目结构和规划**

- **定义文档结构**：在项目开始时，规划好文档的整体结构，包括分组、模块和层次结构。这有助于在文档中形成一致的组织方式。
- **文件和目录**：保持文件和目录结构的清晰，与文档分组和模块划分保持一致。例如，将相关的头文件和源文件放在同一目录中，并在文档中定义相应的分组。

### 2. **注释风格和一致性**

- **统一的注释风格**：确保所有注释遵循一致的风格和格式。可以使用 Doxygen 支持的 Javadoc 风格或其他一致的注释风格。
- **详细而简明**：为函数、类、变量等提供详细的描述，同时保持简洁。使用 `@brief` 提供简要说明，使用详细描述进一步解释复杂部分。
- **示例和用法**：在文档中包含代码示例（使用 `@code` 和 `@endcode`），以帮助用户理解如何使用函数或类。示例应当清晰、准确，并涵盖常见的用法。

### 3. **分组和模块化**

- **使用 `@defgroup` 和 `@addtogroup`**：合理使用 `@defgroup` 和 `@addtogroup` 标签来组织和分组相关的代码元素。这样可以使文档更加结构化，便于用户查找相关内容。
- **子分组**：对于较大的模块，可以创建子分组（使用 `@defgroup` 和 `@addtogroup`）以进一步细化文档。

### 4. **详细的注释**

- **函数和类注释**：为每个函数、类、结构体等提供详细的文档，包括功能、参数、返回值、异常等。使用 `@param`、`@return`、`@exception` 等标签描述参数和返回值。
- **参数和返回值**：详细描述每个参数和返回值的含义和作用。使用 `@param[in]`、`@param[out]`、`@param[in,out]` 标签来标识参数的输入输出性质。
- **文档中的链接和引用**：使用 `@see` 和 `@ref` 标签创建内部和外部链接，帮助用户快速导航到相关的文档部分或代码元素。

### 5. **自动化和脚本**

- **Doxygen 配置**：配置 Doxyfile 以满足项目的需求，包括输入目录、输出目录、生成的文档格式（HTML、LaTeX、PDF 等）。确保配置文件与项目结构相匹配。
- **脚本化文档生成**：可以编写脚本自动生成文档并将其集成到构建过程中。这样可以确保文档在每次构建时保持最新。

### 6. **文档维护**

- **定期更新**：随着代码的修改和功能的增加，定期更新文档以保持其准确性和完整性。确保新添加的功能和模块被正确记录。
- **审查和反馈**：定期审查文档，获取团队成员的反馈，修正可能的错误或不清晰的地方。确保文档易于理解且没有遗漏重要信息。

### 7. **高级功能**

- **自定义模板**：使用 Doxygen 的自定义模板功能来调整文档的外观和风格，使其符合项目的需求和公司标准。
- **图表和关系图**：利用 Graphviz（通过 Doxygen 的 `HAVE_DOT` 配置选项）生成类图、调用图和依赖图，帮助更好地展示代码结构和模块间的关系。
- **多语言支持**：如果项目支持多种语言，可以使用 Doxygen 的多语言功能（`\language` 标签）提供不同语言版本的文档。

### 8. **示例**

以下是一个简单的示例，展示如何在项目中应用上述原则：

```cpp
/**
 * @file Calculator.h
 * @brief 提供计算器功能的类。
 */

/**
 * @defgroup MathFunctions 数学函数
 * @{
 */

/**
 * @class Calculator
 * @ingroup MathFunctions
 * @brief 提供基本的数学运算功能。
 *
 * 这个类包含了几个基础的数学运算函数，例如加法和减法。
 */
class Calculator {
public:
    /**
     * @brief 计算两个整数的和。
     * @param[in] a 第一个整数。
     * @param[in] b 第二个整数。
     * @return 返回两个整数的和。
     * @see subtract() 用于减法运算。
     */
    int add(int a, int b);

    /**
     * @brief 计算两个整数的差。
     * @param[in] a 第一个整数。
     * @param[in] b 第二个整数。
     * @return 返回两个整数的差。
     * @exception std::invalid_argument 如果 b 大于 a。
     */
    int subtract(int a, int b);
};

/** @} */ // 结束 MathFunctions 分组
```

------

## 常见问题及解决方法

### 1. 图表无法生成

**解决方法**：确保已正确安装Graphviz，并且`dot`命令可用。检查`Doxyfile`中的`HAVE_DOT`和`DOT_PATH`设置是否正确。

### 2. 文档中的链接错误或失效

**解决方法**：检查代码中的注释是否正确，特别是类和函数的引用格式。确保在Doxygen中启用了相关的链接选项。

### 3. 中文乱码问题

**解决方法**：在`Doxyfile`中设置正确的字符编码：

```ini
INPUT_ENCODING = UTF-8
```

并确保源文件也使用UTF-8编码保存。

### 4. LaTeX生成PDF失败

**解决方法**：确保系统安装了完整的LaTeX发行版，并检查生成过程中是否有缺失的包或依赖。可以尝试安装所需的LaTeX包后重新编译。



# HTML Help Workshop

HTML Help Workshop 是微软提供的一款工具，用于创建编译HTML帮助（CHM）文件，这种文件常用于Windows应用程序的文档。通过这个工具，你可以将一组HTML文件、图片和其他资源编译成一个CHM文件，用户可以使用微软HTML帮助查看器查看这些文件。

在使用**Doxygen**生成文档时，你可以结合**HTML Help Workshop**将文档编译成CHM格式，方便在Windows平台下进行离线阅读和分发。下面将详细介绍如何在Doxygen中使用HTML Help Workshop生成CHM帮助文件。

## 目录

1. [准备工作](#2.准备工作)
2. [配置Doxygen生成HTML文件](#配置doxygen生成html文件)
3. [配置Doxygen生成CHM相关文件](#配置doxygen生成chm相关文件)
4. [使用HTML Help Workshop编译CHM文件](#使用html-help-workshop编译chm文件)
5. [完整步骤总结](#完整步骤总结)
6. [常见问题及解决方法](#常见问题及解决方法)
7. [参考资料](#参考资料)

------

## 准备工作

在开始之前，你需要确保以下工具已经安装在你的系统中：

1. **Doxygen**：用于从源代码中生成文档。
2. **HTML Help Workshop (hhw)**：用于将HTML文件编译成CHM文件。

### 下载链接

- **Doxygen**：https://www.doxygen.nl/download.html
- **HTML Help Workshop**：https://docs.microsoft.com/en-us/previous-versions/windows/desktop/htmlhelp/microsoft-html-help-downloads

安装完成后，确保它们的可执行文件路径已添加到系统的环境变量中，方便在命令行中直接调用。

------

## 配置Doxygen生成HTML文件

首先，你需要配置Doxygen以生成HTML格式的文档，这是生成CHM文件的基础。

### 生成Doxygen配置文件

使用以下命令生成默认的Doxygen配置文件：

```bash
doxygen -g Doxyfile
```

这将在当前目录下生成一个名为`Doxyfile`的配置文件。

### 配置关键参数

打开`Doxyfile`，根据需要修改以下参数：

```ini
# 项目名称
PROJECT_NAME           = "Your Project Name"

# 输入源文件的路径
INPUT                  = path/to/your/source/code

# 是否递归搜索子目录
RECURSIVE              = YES

# 输出目录
OUTPUT_DIRECTORY       = docs

# 生成HTML文档
GENERATE_HTML          = YES

# 指定HTML输出目录
HTML_OUTPUT            = html

# 是否生成索引页
GENERATE_INDEX         = YES

# 是否生成树形结构
GENERATE_TREEVIEW      = YES
```

确保以上参数设置正确，以便Doxygen能够正确地生成HTML文档。

------

## 配置Doxygen生成CHM相关文件

为了生成CHM文件，Doxygen需要生成一些特定的配置文件，例如`.hhp`、`.hhc`和`.hhk`文件。

### 启用CHM文件生成

在`Doxyfile`中，找到并设置以下参数：

```ini
# 启用CHM文件生成
GENERATE_HTMLHELP      = YES

# 指定CHM文件名
CHM_FILE               = YourProject.chm

# 指定CHM文件标题
CHM_INDEX_ENCODING     = UTF-8

# 生成的CHM文件标题
HTML_HELP_TITLE        = "Your Project Documentation"

# 生成CHM文件的目录
GENERATE_CHI           = NO

# 路径及文件名前缀
BINARY_TOC             = NO
TOC_EXPAND             = NO
```

### 添加自定义LOGO（可选）

如果你希望在文档中添加自定义的LOGO，可以设置以下参数：

```ini
# 指定LOGO图片路径
PROJECT_LOGO           = path/to/your/logo.png

# LOGO的宽度和高度
LOGO_WIDTH             = 100
LOGO_HEIGHT            = 100
```

### 设置文件编码

确保文档的字符编码正确，防止出现乱码：

```ini
# 输入文件的编码
INPUT_ENCODING         = UTF-8

# 输出文件的编码
OUTPUT_ENCODING        = UTF-8
```

------

## 使用HTML Help Workshop编译CHM文件

完成上述配置后，Doxygen会在生成HTML文档的同时生成`.hhp`、`.hhc`和`.hhk`文件，这些文件是HTML Help Workshop编译CHM文件所需的配置文件。

### 运行Doxygen生成文件

在命令行中运行：

```bash
doxygen Doxyfile
```

这将根据配置生成HTML文档和相关的HTML Help配置文件。

### 使用HTML Help Workshop编译

#### 方法一：使用图形界面

1. **打开HTML Help Workshop**：
   - 运行`HTML Help Workshop`应用程序。
2. **打开项目文件**：
   - 在菜单中选择`File -> Open`，然后选择Doxygen生成的`.hhp`文件。该文件通常位于`docs/html/`目录下。
3. **编译项目**：
   - 在菜单中选择`Compile -> Compile`，或者直接按`F9`键。
   - 设置输出文件路径和名称，然后点击`Compile`开始编译。
4. **查看结果**：
   - 编译完成后，点击`View`按钮查看生成的CHM文件。

#### 方法二：使用命令行

你也可以使用命令行工具`hhc.exe`直接编译：

```bash
cd path/to/docs/html/
hhc.exe YourProject.hhp
```

运行上述命令后，会在当前目录下生成`YourProject.chm`文件。

------

## 完整步骤总结

1. **安装Doxygen和HTML Help Workshop**。
2. 配置Doxygen：
   - 生成并编辑`Doxyfile`配置文件。
   - 设置`GENERATE_HTMLHELP`等参数。
3. 运行Doxygen：
   - 执行`doxygen Doxyfile`命令，生成HTML文档和CHM配置文件。
4. 编译CHM文件：
   - 使用`HTML Help Workshop`打开并编译`.hhp`文件。
   - 或者使用命令行`hhc.exe`直接编译。
5. 测试CHM文件：
   - 打开生成的`YourProject.chm`文件，检查文档结构、内容和链接是否正常。
6. 发布和分发：
   - 将生成的CHM文件分发给用户，提供离线文档支持。

------

## 常见问题及解决方法

### 1. 编译时出现警告或错误

**解决方法**：

- 检查`.hhp`、`.hhc`和`.hhk`文件的路径是否正确。
- 确保所有引用的HTML文件和资源文件都存在且路径正确。
- 检查文件名中是否有特殊字符，尽量使用英文和数字命名。

### 2. 生成的CHM文件内容乱码

**解决方法**：

- 确保`Doxyfile`中的`INPUT_ENCODING`和`OUTPUT_ENCODING`设置为`UTF-8`。
- 在HTML Help Workshop中，设置项目的字符集为`Unicode (UTF-8)`。

### 3. 搜索功能无法正常工作

**解决方法**：

- 确保在Doxygen配置中启用了索引和搜索功能：

  ```ini
  SEARCHENGINE          = YES
  ```

- 重新编译CHM文件，检查搜索功能是否恢复正常。

### 4. 图片无法显示

**解决方法**：

- 确认所有图片文件都位于正确的路径下，并在HTML中引用正确。
- 检查图片的格式是否被支持，常用的PNG、JPG格式一般没有问题。

------

## 参考资料

- **Doxygen官方文档**：https://www.doxygen.nl/manual/index.html
- **HTML Help Workshop官方指南**：https://docs.microsoft.com/en-us/previous-versions/windows/desktop/htmlhelp/html-help-workshop-user-interface
- 使用Doxygen生成CHM文件的教程：
  - https://stackoverflow.com/questions/4208643/doxygen-generate-chm-help-file
  - https://www.codeproject.com/Articles/4886/Using-Doxygen-For-Generating-CHM-Files

# Graphviz

在Doxygen中使用**Graphviz**可以自动生成项目的类图、调用图、协作图等图表，帮助更好地理解代码结构和调用关系。以下是如何在Doxygen中配置和使用Graphviz的详细步骤。

## 目录

1. [安装Graphviz](#安装graphviz)
2. [配置Doxygen以支持Graphviz](#配置doxygen以支持graphviz)
3. [生成图表](#生成图表)
4. [常见问题及解决方法](#常见问题及解决方法)
5. [参考资料](#参考资料)

------

## 安装Graphviz

### Windows

1. 访问Graphviz官网：https://graphviz.org/download/
2. 下载适用于Windows的安装程序。
3. 安装Graphviz，并确保将安装路径添加到系统的环境变量中。

### macOS

在macOS上，你可以使用`brew`来安装Graphviz：

```bash
brew install graphviz
```

### Linux

在大多数Linux发行版上，可以使用包管理器安装Graphviz，例如：

```bash
sudo apt-get install graphviz
```

或者对于基于Red Hat的系统：

```bash
sudo yum install graphviz
```

安装完成后，确保`dot`命令可以在命令行中运行。

------

## 配置Doxygen以支持Graphviz

### 生成Doxygen配置文件

如果还没有Doxygen配置文件，先生成一个：

```bash
doxygen -g Doxyfile
```

这会在当前目录下生成`Doxyfile`配置文件。

### 修改Doxygen配置

打开`Doxyfile`，根据需要调整以下配置选项以启用Graphviz支持：

```ini
# 启用调用图的生成
CALL_GRAPH            = YES

# 启用类图的生成
CLASS_DIAGRAMS        = YES

# 启用协作图的生成
COLLABORATION_GRAPH   = YES

# 启用类继承图的生成
INHERITANCE_GRAPH     = YES

# 启用包依赖图的生成
UML_LOOK              = YES

# 启用DOT工具的使用
HAVE_DOT              = YES

# DOT工具的路径（可选，如果已添加到环境变量中可留空）
DOT_PATH              = /path/to/graphviz/bin

# 设置DOT的输出格式（可选）
DOT_IMAGE_FORMAT      = png

# 如果需要生成更大、更复杂的图，可以调整此参数
DOT_GRAPH_MAX_NODES   = 50

# 是否使用HTML imagemaps来支持点击放大图片
INTERACTIVE_SVG       = YES
```

确保`HAVE_DOT`设置为`YES`，并且`DOT_PATH`指向Graphviz的`bin`目录。如果Graphviz的路径已经添加到环境变量中，`DOT_PATH`可以留空。

------

## 生成图表

配置完成后，运行Doxygen以生成文档和图表：

```bash
doxygen Doxyfile
```

Doxygen会根据代码自动生成各种图表，这些图表会嵌入到生成的HTML文档中。生成的图表包括：

- **类图**（Class Diagrams）：展示类的继承关系。
- **调用图**（Call Graphs）：展示函数之间的调用关系。
- **协作图**（Collaboration Diagrams）：展示类之间的协作关系。
- **包依赖图**（Package Dependency Graphs）：展示包或命名空间之间的依赖关系。

生成的图表会以配置的格式（例如PNG、SVG）输出，并包含在HTML文档中。

------

## 常见问题及解决方法

### 1. 图表未生成或显示为空白

**解决方法**：

- 检查Graphviz是否正确安装，并且`dot`命令可以在命令行中运行。
- 确保Doxygen配置文件中的`HAVE_DOT`设置为`YES`。
- 检查`DOT_PATH`是否正确指向Graphviz的安装路径。

### 2. 图表过于复杂，难以阅读

**解决方法**：

- 调整`DOT_GRAPH_MAX_NODES`参数以限制图中节点的数量。
- 将`DOT_CLEANUP`设置为`NO`以保留中间的`.dot`文件，并使用Graphviz的`dot`工具手动调试图表。

### 3. 生成的图表无法点击放大

**解决方法**：

- 确保`INTERACTIVE_SVG`设置为`YES`，以便生成支持点击放大的图表。
- 使用SVG格式作为图表的输出格式：

```ini
DOT_IMAGE_FORMAT      = svg
```

### 4. 文档生成时出现Graphviz相关的错误信息

**解决方法**：

- 检查Graphviz的版本，确保使用最新的稳定版本。
- 验证Graphviz的安装路径是否正确配置，特别是在多平台开发时。

------

## 参考资料

- **Doxygen官方文档**：https://www.doxygen.nl/manual/config.html
- **Graphviz官网**：https://graphviz.org/
- **Doxygen与Graphviz集成指南**：https://www.doxygen.nl/manual/diagrams.html



# 附录

## Doxygen 配置

### 1.Project

```ini
#---------------------------------------------------------------------------
# Project related configuration options
#---------------------------------------------------------------------------

# This tag specifies the encoding used for all characters in the configuration
# file that follow. The default is UTF-8 which is also the encoding used for all
# text before the first occurrence of this tag. Doxygen uses libiconv (or the
# iconv built into libc) for the transcoding. See
# https://www.gnu.org/software/libiconv/ for the list of possible encodings.
# The default value is: UTF-8.

# 此标签指定了后面的配置文件中所有字符使用的编码。
# 默认编码为 UTF-8，这也是该标签第一次出现之前所有文本使用的编码。
# Doxygen 使用 libiconv（或 libc 内置的iconv）进行编码转换。
# 默认值为UTF-8：UTF-8。
DOXYFILE_ENCODING      = UTF-8

# The PROJECT_NAME tag is a single word (or a sequence of words surrounded by
# double-quotes, unless you are using Doxywizard) that should identify the
# project for which the documentation is generated. This name is used in the
# title of most generated pages and in a few other places.
# The default value is: My Project.

# PROJECT_NAME标记是一个单词（或一系列用双引号括起来的单词，除非您使用的是Doxywizard），
# 它应该标识生成文档的项目。此名称用于大多数生成页面的标题和其他一些地方。
PROJECT_NAME           = "My Project"

# The PROJECT_NUMBER tag can be used to enter a project or revision number. This
# could be handy for archiving the generated documentation or if some version
# control system is used.

# PROJECT_NUMBER 标签可用于输入项目或修订版编号。
# 如果要对生成的文档进行归档，或使用某种版本控制系统，这将非常方便。
PROJECT_NUMBER         = 0.0.1

# Using the PROJECT_BRIEF tag one can provide an optional one line description
# for a project that appears at the top of each page and should give viewer a
# quick idea about the purpose of the project. Keep the description short.

# 使用PROJECT_BRIEF标签，可以提供可选的单行描述
# 对于出现在每页顶部的项目，应该给观众一个快速了解项目的目的。
# 保持描述简短。
PROJECT_BRIEF          = 简短描述

# With the PROJECT_LOGO tag one can specify a logo or an icon that is included
# in the documentation. The maximum height of the logo should not exceed 55
# pixels and the maximum width should not exceed 200 pixels. Doxygen will copy
# the logo to the output directory.

PROJECT_LOGO           =

# With the PROJECT_ICON tag one can specify an icon that is included in the tabs
# when the HTML document is shown. Doxygen will copy the logo to the output
# directory.

PROJECT_ICON           =

# The OUTPUT_DIRECTORY tag is used to specify the (relative or absolute) path
# into which the generated documentation will be written. If a relative path is
# entered, it will be relative to the location where Doxygen was started. If
# left blank the current directory will be used.

OUTPUT_DIRECTORY       = .\doc\doxygen

# If the CREATE_SUBDIRS tag is set to YES then Doxygen will create up to 4096
# sub-directories (in 2 levels) under the output directory of each output format
# and will distribute the generated files over these directories. Enabling this
# option can be useful when feeding Doxygen a huge amount of source files, where
# putting all generated files in the same directory would otherwise causes
# performance problems for the file system. Adapt CREATE_SUBDIRS_LEVEL to
# control the number of sub-directories.
# The default value is: NO.

CREATE_SUBDIRS         = YES

# Controls the number of sub-directories that will be created when
# CREATE_SUBDIRS tag is set to YES. Level 0 represents 16 directories, and every
# level increment doubles the number of directories, resulting in 4096
# directories at level 8 which is the default and also the maximum value. The
# sub-directories are organized in 2 levels, the first level always has a fixed
# number of 16 directories.
# Minimum value: 0, maximum value: 8, default value: 8.
# This tag requires that the tag CREATE_SUBDIRS is set to YES.

CREATE_SUBDIRS_LEVEL   = 8

# If the ALLOW_UNICODE_NAMES tag is set to YES, Doxygen will allow non-ASCII
# characters to appear in the names of generated files. If set to NO, non-ASCII
# characters will be escaped, for example _xE3_x81_x84 will be used for Unicode
# U+3044.
# The default value is: NO.

ALLOW_UNICODE_NAMES    = YES

# The OUTPUT_LANGUAGE tag is used to specify the language in which all
# documentation generated by Doxygen is written. Doxygen will use this
# information to generate all constant output in the proper language.
# Possible values are: Afrikaans, Arabic, Armenian, Brazilian, Bulgarian,
# Catalan, Chinese, Chinese-Traditional, Croatian, Czech, Danish, Dutch, English
# (United States), Esperanto, Farsi (Persian), Finnish, French, German, Greek,
# Hindi, Hungarian, Indonesian, Italian, Japanese, Japanese-en (Japanese with
# English messages), Korean, Korean-en (Korean with English messages), Latvian,
# Lithuanian, Macedonian, Norwegian, Persian (Farsi), Polish, Portuguese,
# Romanian, Russian, Serbian, Serbian-Cyrillic, Slovak, Slovene, Spanish,
# Swedish, Turkish, Ukrainian and Vietnamese.
# The default value is: English.

OUTPUT_LANGUAGE        = Chinese

# If the BRIEF_MEMBER_DESC tag is set to YES, Doxygen will include brief member
# descriptions after the members that are listed in the file and class
# documentation (similar to Javadoc). Set to NO to disable this.
# The default value is: YES.

# 如果BRIEF_MEMBER_DESC标记设置为YES
# Doxygen将在文件和类文档中列出的成员之后包含简短的成员描述（类似于Javadoc）。
# 设置为“否”可禁用此功能。
BRIEF_MEMBER_DESC      = YES

# If the REPEAT_BRIEF tag is set to YES, Doxygen will prepend the brief
# description of a member or function before the detailed description
#
# Note: If both HIDE_UNDOC_MEMBERS and BRIEF_MEMBER_DESC are set to NO, the
# brief descriptions will be completely suppressed.
# The default value is: YES.

# 如果REPEAT_BRIEF标记设置为YES，Doxygen将在详细描述之前添加成员或函数的简要描述
# 注意：如果HIDE_UNDOC_MEMBERS和BRIEF_MEMBER_DESC都设置为“否”，则简要描述将被完全抑制。
REPEAT_BRIEF           = YES

# This tag implements a quasi-intelligent brief description abbreviator that is
# used to form the text in various listings. Each string in this list, if found
# as the leading text of the brief description, will be stripped from the text
# and the result, after processing the whole list, is used as the annotated
# text. Otherwise, the brief description is used as-is. If left blank, the
# following values are used ($name is automatically replaced with the name of
# the entity):The $name class, The $name widget, The $name file, is, provides,
# specifies, contains, represents, a, an and the.

# 此标签实现了一个准智能的简短描述缩写器，用于在各种列表中形成文本。
# 如果发现此列表中的每个字符串是简要描述的前导文本，则将从文本中删除，处理整个列表后的结果将用作注释文本。
# 否则，将按原样使用简要描述。
# 如果留空，则使用以下值（$name会自动替换为实体的名称）：
# $name类、$name小部件、$name文件是、提供、指定、包含、表示、a、an和。
ABBREVIATE_BRIEF       = "The $name class" \
                         "The $name widget" \
                         "The $name file" \
                         is \
                         provides \
                         specifies \
                         contains \
                         represents \
                         a \
                         an \
                         the

# If the ALWAYS_DETAILED_SEC and REPEAT_BRIEF tags are both set to YES then
# Doxygen will generate a detailed section even if there is only a brief
# description.
# The default value is: NO.

# 如果ALWAYS_DETAILED_SEC和REPEAT_BRIEF标签都设置为“YES”，
# 即使只有简短的描述，Doxygen也会生成一个详细的部分
ALWAYS_DETAILED_SEC    = NO

# If the INLINE_INHERITED_MEMB tag is set to YES, Doxygen will show all
# inherited members of a class in the documentation of that class as if those
# members were ordinary class members. Constructors, destructors and assignment
# operators of the base classes will not be shown.
# The default value is: NO.

# 如果INLINE_INHERITED_MEMB标记设置为YES，
# Doxygen将在该类的文档中显示该类的所有继承成员，就像这些成员是普通类成员一样。
# 基类的构造函数、析构函数和赋值运算符将不会显示。
INLINE_INHERITED_MEMB  = YES

# If the FULL_PATH_NAMES tag is set to YES, Doxygen will prepend the full path
# before files name in the file list and in the header files. If set to NO the
# shortest path that makes the file name unique will be used
# The default value is: YES.

# 如果FULL_PATH_NAMES标记设置为YES，
# Doxygen将在文件列表和头文件中的文件名之前添加完整路径。
# 如果设置为“否”，将使用使文件名唯一的最短路径
FULL_PATH_NAMES        = YES

# The STRIP_FROM_PATH tag can be used to strip a user-defined part of the path.
# Stripping is only done if one of the specified strings matches the left-hand
# part of the path. The tag can be used to show relative paths in the file list.
# If left blank the directory from which Doxygen is run is used as the path to
# strip.
#
# Note that you can specify absolute paths here, but also relative paths, which
# will be relative from the directory where Doxygen is started.
# This tag requires that the tag FULL_PATH_NAMES is set to YES.

# STRIP_FROM_PATH标签可用于剥离路径中用户定义的部分。
# 只有当指定的字符串之一与路径的左侧部分匹配时，才会进行剥离。
# 标记可用于显示文件列表中的相对路径。
# 如果留空，则运行Doxygen的目录将用作剥离路径。

# 注意，您可以在此处指定绝对路径，也可以指定相对路径，这些路径将与Doxygen启动的目录相对。
# 此标记要求将标记FULL_PATH_NAMES设置为YES。
STRIP_FROM_PATH        =

# The STRIP_FROM_INC_PATH tag can be used to strip a user-defined part of the
# path mentioned in the documentation of a class, which tells the reader which
# header file to include in order to use a class. If left blank only the name of
# the header file containing the class definition is used. Otherwise one should
# specify the list of include paths that are normally passed to the compiler
# using the -I flag.

# STRIP_FROM_INC_PATH标记可用于剥离类的文档中提到的路径的用户定义部分，
# 这会“告诉”读取器要包含哪个头文件才能使用类。
# 如果留空，则只使用包含类定义的头文件的名称。
# 否则，应该使用-I标志指定通常传递给编译器的包含路径列表。
STRIP_FROM_INC_PATH    =

# If the SHORT_NAMES tag is set to YES, Doxygen will generate much shorter (but
# less readable) file names. This can be useful is your file systems doesn't
# support long names like on DOS, Mac, or CD-ROM.
# The default value is: NO.

# 如果SHORT_NAMES标记设置为YES，Doxygen将生成更短（但可读性更低）的文件名。
# 这可能很有用，因为您的文件系统不支持DOS、Mac或CD-ROM上的长名称。
SHORT_NAMES            = NO

# If the JAVADOC_AUTOBRIEF tag is set to YES then Doxygen will interpret the
# first line (until the first dot) of a Javadoc-style comment as the brief
# description. If set to NO, the Javadoc-style will behave just like regular Qt-
# style comments (thus requiring an explicit @brief command for a brief
# description.)
# The default value is: NO.

# 如果JAVADOC_AUTOBRIEF标记设置为YES，
# Doxygen将把JAVADOC样式注释的第一行（直到第一个点）解释为简要描述。
# 如果设置为“否”，Javadoc样式的行为将与常规Qt样式的注释一样
#（因此需要一个显式的@brief命令来进行简要描述。）
JAVADOC_AUTOBRIEF      = YES

# If the JAVADOC_BANNER tag is set to YES then Doxygen will interpret a line
# such as
# /***************
# as being the beginning of a Javadoc-style comment "banner". If set to NO, the
# Javadoc-style will behave just like regular comments and it will not be
# interpreted by Doxygen.
# The default value is: NO.

# 如果JAVADOC_BANNER标签设置为YES，Doxygen将解释如下行
# /***************
# 作为Javadoc风格注释“横幅”的开始。
# 如果设置为“否”，Javadoc样式的行为将与常规注释一样，Doxygen不会对其进行解释。
JAVADOC_BANNER         = NO

# If the QT_AUTOBRIEF tag is set to YES then Doxygen will interpret the first
# line (until the first dot) of a Qt-style comment as the brief description. If
# set to NO, the Qt-style will behave just like regular Qt-style comments (thus
# requiring an explicit \brief command for a brief description.)
# The default value is: NO.

# 如果QT_AUTOBRIEF标记设置为YES，Doxygen将QT样式注释的第一行（直到第一个点）解释为简要描述。
# 如果设置为“否”，Qt样式的行为将与常规Qt样式注释一样（因此需要一个显式的\brief命令来进行简要描述。）
QT_AUTOBRIEF           = NO

# The MULTILINE_CPP_IS_BRIEF tag can be set to YES to make Doxygen treat a
# multi-line C++ special comment block (i.e. a block of //! or /// comments) as
# a brief description. This used to be the default behavior. The new default is
# to treat a multi-line C++ comment block as a detailed description. Set this
# tag to YES if you prefer the old behavior instead.
#
# Note that setting this tag to YES also means that rational rose comments are
# not recognized any more.
# The default value is: NO.

# MULTILINE_CPP_IS_BRIEF标签可以设置为YES，
# 使Doxygen将多行C++特殊注释块（即//！或///注释块）视为简要描述。
# 这曾经是默认行为。新的默认设置是将多行C++注释块视为详细描述。
# 如果您更喜欢旧的行为，请将此标记设置为“是”。
#
# 注意，将此标签设置为“是”也意味着不再识别rationalrose评论。
MULTILINE_CPP_IS_BRIEF = NO

# By default Python docstrings are displayed as preformatted text and Doxygen's
# special commands cannot be used. By setting PYTHON_DOCSTRING to NO the
# Doxygen's special commands can be used and the contents of the docstring
# documentation blocks is shown as Doxygen documentation.
# The default value is: YES.

# 默认情况下，Python文档字符串显示为预格式化文本，不能使用Doxygen的特殊命令。
# 通过将PYTHON_DOCSTRING设置为NO，可以使用Doxygen的特殊命令，
# 并且DOCSTRING文档块的内容显示为Doxygen文档。
PYTHON_DOCSTRING       = YES

# If the INHERIT_DOCS tag is set to YES then an undocumented member inherits the
# documentation from any documented member that it re-implements.
# The default value is: YES.

# 如果INHERIT_DOCS标记设置为“是”，则未记录的成员将从其重新实现的任何记录的成员继承文档。
INHERIT_DOCS           = YES

# If the SEPARATE_MEMBER_PAGES tag is set to YES then Doxygen will produce a new
# page for each member. If set to NO, the documentation of a member will be part
# of the file/class/namespace that contains it.
# The default value is: NO.

# 如果SEPRATE_MEMBER_PAGES标记设置为YES，
# 则Doxygen将为每个成员生成一个新页面。
# 如果设置为“否”，则成员的文档将是包含它的文件/类/命名空间的一部分
SEPARATE_MEMBER_PAGES  = NO

# The TAB_SIZE tag can be used to set the number of spaces in a tab. Doxygen
# uses this value to replace tabs by spaces in code fragments.
# Minimum value: 1, maximum value: 16, default value: 4.

TAB_SIZE               = 4

# This tag can be used to specify a number of aliases that act as commands in
# the documentation. An alias has the form:
# name=value
# For example adding
# "sideeffect=@par Side Effects:^^"
# will allow you to put the command \sideeffect (or @sideeffect) in the
# documentation, which will result in a user-defined paragraph with heading
# "Side Effects:". Note that you cannot put \n's in the value part of an alias
# to insert newlines (in the resulting output). You can put ^^ in the value part
# of an alias to insert a newline as if a physical newline was in the original
# file. When you need a literal { or } or , in the value part of an alias you
# have to escape them by means of a backslash (\), this can lead to conflicts
# with the commands \{ and \} for these it is advised to use the version @{ and
# @} or use a double escape (\\{ and \\})

# 此标记可用于指定在文档中充当命令的多个别名。
# 别名的格式为：name=value
# 例如，添加
# "sideeffect=@par Side Effects:^^"
# 将允许您将命令\sideeffect（或@sideeffect）放入文档中，这将导致用户定义的段落标题为"Side Effects:"。
# 注意，您不能在别名的值部分插入换行符（在结果输出中）。
# 您可以将^^放在别名的值部分，以插入换行符，就像原始文件中有物理换行符一样。
# 当你需要一个文字{或}，或者在别名的值部分必须用反斜杠（\）转义它们时，
# 这可能会导致与这些命令的命令\{和\}冲突。
# 建议使用版本@{和@}或使用双转义符（\\{和\\}）
ALIASES                =

# Set the OPTIMIZE_OUTPUT_FOR_C tag to YES if your project consists of C sources
# only. Doxygen will then generate output that is more tailored for C. For
# instance, some of the names that are used will be different. The list of all
# members will be omitted, etc.
# The default value is: NO.

# 如果您的项目仅由C源代码组成，请将OPTIMIZE_OUTPUT_FOR-C标记设置为YES。
# Doxygen将生成更适合C的输出。
# 例如，使用的一些名称将有所不同。所有成员的名单将被省略，等等。
OPTIMIZE_OUTPUT_FOR_C  = NO

# Set the OPTIMIZE_OUTPUT_JAVA tag to YES if your project consists of Java or
# Python sources only. Doxygen will then generate output that is more tailored
# for that language. For instance, namespaces will be presented as packages,
# qualified scopes will look different, etc.
# The default value is: NO.

# 如果您的项目仅包含JAVA或Python源代码，请将OPTIMIZE_OUTPUT_JAVA标记设置为YES。
# Doxygen将生成更适合该语言的输出。
# 例如，名称空间将以包的形式呈现，限定的作用域将看起来不同，等等。
OPTIMIZE_OUTPUT_JAVA   = NO

# Set the OPTIMIZE_FOR_FORTRAN tag to YES if your project consists of Fortran
# sources. Doxygen will then generate output that is tailored for Fortran.
# The default value is: NO.

# 如果您的项目包含FORTRAN源代码，请将OPTIMIZE_FOR_FORTRAN标记设置为“是”。
# Doxygen将生成为Fortran量身定制的输出。
OPTIMIZE_FOR_FORTRAN   = NO

# Set the OPTIMIZE_OUTPUT_VHDL tag to YES if your project consists of VHDL
# sources. Doxygen will then generate output that is tailored for VHDL.
# The default value is: NO.

# 如果您的项目包含VHDL源代码，请将OPTIMIZE_OUTPUT_VHDL标记设置为“是”。
# Doxygen将生成为VHDL定制的输出。
OPTIMIZE_OUTPUT_VHDL   = NO

# Set the OPTIMIZE_OUTPUT_SLICE tag to YES if your project consists of Slice
# sources only. Doxygen will then generate output that is more tailored for that
# language. For instance, namespaces will be presented as modules, types will be
# separated into more groups, etc.
# The default value is: NO.

# 如果您的项目仅由SLICE源组成，请将OPTIMIZE_OUTPUT_SLICE标记设置为YES。
# Doxygen将生成更适合该语言的输出。
# 例如，名称空间将以模块的形式呈现，类型将被分成更多的组等。
OPTIMIZE_OUTPUT_SLICE  = NO

# Doxygen selects the parser to use depending on the extension of the files it
# parses. With this tag you can assign which parser to use for a given
# extension. Doxygen has a built-in mapping, but you can override or extend it
# using this tag. The format is ext=language, where ext is a file extension, and
# language is one of the parsers supported by Doxygen: IDL, Java, JavaScript,
# Csharp (C#), C, C++, Lex, D, PHP, md (Markdown), Objective-C, Python, Slice,
# VHDL, Fortran (fixed format Fortran: FortranFixed, free formatted Fortran:
# FortranFree, unknown formatted Fortran: Fortran. In the later case the parser
# tries to guess whether the code is fixed or free formatted code, this is the
# default for Fortran type files). For instance to make Doxygen treat .inc files
# as Fortran files (default is PHP), and .f files as C (default is Fortran),
# use: inc=Fortran f=C.
#
# Note: For files without extension you can use no_extension as a placeholder.
#
# Note that for custom extensions you also need to set FILE_PATTERNS otherwise
# the files are not read by Doxygen. When specifying no_extension you should add
# * to the FILE_PATTERNS.
#
# Note see also the list of default file extension mappings.

# Doxygen根据它解析的文件的扩展名选择要使用的解析器。
# 使用此标记，您可以为给定的扩展指定使用哪个解析器。
# Doxygen有一个内置的映射，但您可以使用此标记覆盖或扩展它。
# 格式为ext=language，其中ext是文件扩展名，language是Doxygen支持的解析器之一：IDL、Java、JavaScript、Csharp（C#）、C、C++、Lex、D、PHP、md（Markdown）、Objective-C、Python、Slice、VHDL、Fortran（固定格式Fortran:FortranFixed、自由格式Fortran:FortranFree、未知格式Fortran:Bortran。在后一种情况下，解析器试图猜测代码是固定格式还是自由格式的代码，这是Fortran类型文件的默认值）。
# 例如，要使Doxygen将.inc文件视为Fortran文件（默认为PHP），将.f文件视为C（默认为Fortran），请使用：inc=Fortran f=C。
#
# 注意：对于没有扩展名的文件，您可以使用no.extension作为占位符。
#
# 注意，对于自定义扩展名，您还需要设置FILE_PATTERNS，否则Doxygen无法读取文件。
# 当指定no_textension时，您应该在FILE_PATTERNS中添加*。
# 注意，另请参阅默认文件扩展名映射列表。
EXTENSION_MAPPING      =

# If the MARKDOWN_SUPPORT tag is enabled then Doxygen pre-processes all comments
# according to the Markdown format, which allows for more readable
# documentation. See https://daringfireball.net/projects/markdown/ for details.
# The output of markdown processing is further processed by Doxygen, so you can
# mix Doxygen, HTML, and XML commands with Markdown formatting. Disable only in
# case of backward compatibilities issues.
# The default value is: YES.

# 如果启用了MARKDOWN_SUPPORT标签，Doxygen将根据MARKDOWN格式预处理所有注释，从而使文档更具可读性。
# 请参阅https://daringfireball.net/projects/markdown/了解详情。
# markdown处理的输出由Doxygen进一步处理，因此您可以将Doxygen、HTML和XML命令与markdown格式混合使用。
# 仅在出现向后兼容性问题时禁用。
MARKDOWN_SUPPORT       = YES

# When the TOC_INCLUDE_HEADINGS tag is set to a non-zero value, all headings up
# to that level are automatically included in the table of contents, even if
# they do not have an id attribute.
# Note: This feature currently applies only to Markdown headings.
# Minimum value: 0, maximum value: 99, default value: 6.
# This tag requires that the tag MARKDOWN_SUPPORT is set to YES.

# 当TOC_ININCLUDE_HEADINGS标记设置为非零值时，该级别之前的所有标题都会自动包含在目录中，
# 即使它们没有id属性。
# 注意：此功能目前仅适用于Markdown标题。最小值：0，最大值：99，默认值：6。
# 此标记要求标记MARKDOWN_SUPPORT设置为“是”。
TOC_INCLUDE_HEADINGS   = 6

# The MARKDOWN_ID_STYLE tag can be used to specify the algorithm used to
# generate identifiers for the Markdown headings. Note: Every identifier is
# unique.
# Possible values are: DOXYGEN use a fixed 'autotoc_md' string followed by a
# sequence number starting at 0 and GITHUB use the lower case version of title
# with any whitespace replaced by '-' and punctuation characters removed.
# The default value is: DOXYGEN.
# This tag requires that the tag MARKDOWN_SUPPORT is set to YES.

# MARKDOWN_ID-STYLE标签可用于指定用于为MARKDOWN标题生成标识符的算法。
# 注意：每个标识符都是唯一的。可能的值有：DOXYGEN使用固定的“autotoc_md”字符串，
# 后跟从0开始的序列号，GITHUB使用小写版本的标题，任何空格都替换为“-”，标点符号被删除。
# 默认值为：DOXYGEN。
# 此标记要求标记MARKDOWN_SUPPORT设置为“是”。
MARKDOWN_ID_STYLE      = DOXYGEN

# When enabled Doxygen tries to link words that correspond to documented
# classes, or namespaces to their corresponding documentation. Such a link can
# be prevented in individual cases by putting a % sign in front of the word or
# globally by setting AUTOLINK_SUPPORT to NO.
# The default value is: YES.

# 启用后，Doxygen会尝试将与记录的类或名称空间对应的单词链接到其相应的文档。
# 在个别情况下，可以通过在单词前面加上%符号来防止这种链接，
# 或者在全局范围内将AUTOLINK_SUPPORT设置为NO来防止这种连接。
AUTOLINK_SUPPORT       = YES

# If you use STL classes (i.e. std::string, std::vector, etc.) but do not want
# to include (a tag file for) the STL sources as input, then you should set this
# tag to YES in order to let Doxygen match functions declarations and
# definitions whose arguments contain STL classes (e.g. func(std::string);
# versus func(std::string) {}). This also makes the inheritance and
# collaboration diagrams that involve STL classes more complete and accurate.
# The default value is: NO.

# 如果你使用STL类（即std:：string、std:：vector等），
# 但不想将STL源代码作为输入（的标签文件），那么你应该将此标签设置为YES，
# 以便Doxygen匹配其参数包含STL类的函数声明和定义（例如func（std:：string）；
# 与func（std:：string）{}相比）。这也使得涉及STL类的继承和协作图更加完整和准确。
BUILTIN_STL_SUPPORT    = NO

# If you use Microsoft's C++/CLI language, you should set this option to YES to
# enable parsing support.
# The default value is: NO.

# 如果您使用Microsoft的C++/CLI语言，则应将此选项设置为“是”以启用解析支持。
CPP_CLI_SUPPORT        = NO

# Set the SIP_SUPPORT tag to YES if your project consists of sip (see:
# https://www.riverbankcomputing.com/software) sources only. Doxygen will parse
# them like normal C++ but will assume all classes use public instead of private
# inheritance when no explicit protection keyword is present.
# The default value is: NO.

# 如果您的项目包含SIP，请将SIP_SUPPORT标签设置为YES
#（请参阅：https://www.riverbankcomputing.com/software)只有来源。
# Doxygen将像普通C++一样解析它们，但在没有显式保护关键字的情况下，
# 将假设所有类都使用公共继承而不是私有继承。
SIP_SUPPORT            = NO

# For Microsoft's IDL there are propget and propput attributes to indicate
# getter and setter methods for a property. Setting this option to YES will make
# Doxygen to replace the get and set methods by a property in the documentation.
# This will only work if the methods are indeed getting or setting a simple
# type. If this is not the case, or you want to show the methods anyway, you
# should set this option to NO.
# The default value is: YES.

# 对于Microsoft的IDL，有propget和propput属性来指示属性的getter和setter方法。
# 将此选项设置为“是”将使Doxygen用文档中的属性替换get和set方法。
# 只有当方法确实获取或设置了一个简单的类型时，这才有效。
# 如果不是这样，或者您仍然想显示方法，则应将此选项设置为“否”。
IDL_PROPERTY_SUPPORT   = YES

# If member grouping is used in the documentation and the DISTRIBUTE_GROUP_DOC
# tag is set to YES then Doxygen will reuse the documentation of the first
# member in the group (if any) for the other members of the group. By default
# all members of a group must be documented explicitly.
# The default value is: NO.

# 如果文档中使用了成员分组，并且DISTRIBUTE_GROUP_DOC标记设置为“是”，
# 则Doxygen将为组中的其他成员重用组中第一个成员的文档（如果有的话）。
# 默认情况下，必须明确记录组的所有成员。
DISTRIBUTE_GROUP_DOC   = NO

# If one adds a struct or class to a group and this option is enabled, then also
# any nested class or struct is added to the same group. By default this option
# is disabled and one has to add nested compounds explicitly via \ingroup.
# The default value is: NO.

# 如果将结构或类添加到组中并且启用了此选项，则任何嵌套的类或结构也会添加到同一组中。
# 默认情况下，此选项被禁用，必须通过\ingroup显式添加嵌套化合物。
GROUP_NESTED_COMPOUNDS = NO

# Set the SUBGROUPING tag to YES to allow class member groups of the same type
# (for instance a group of public functions) to be put as a subgroup of that
# type (e.g. under the Public Functions section). Set it to NO to prevent
# subgrouping. Alternatively, this can be done per class using the
# \nosubgrouping command.
# The default value is: YES.

# 将SUBGROUPING标记设置为YES，以允许将相同类型的类成员组（例如一组公共函数）作为该类型的子组放置（例如在公共函数部分下）。
# 将其设置为“否”以防止分组。或者，可以使用\nsubgrouping命令按类完成此操作。
SUBGROUPING            = YES

# When the INLINE_GROUPED_CLASSES tag is set to YES, classes, structs and unions
# are shown inside the group in which they are included (e.g. using \ingroup)
# instead of on a separate page (for HTML and Man pages) or section (for LaTeX
# and RTF).
#
# Note that this feature does not work in combination with
# SEPARATE_MEMBER_PAGES.
# The default value is: NO.

# 当INLINE_GROUPED_CLASS标记设置为YES时，类、结构和联合将显示在包含它们的组内
#（例如使用\ingroup），而不是显示在单独的页面（对于HTML和手册页）或部分（对于LaTeX和RTF）上。
#
# 注意，此功能不能与SEPRATE_MEMBER_PAGES结合使用。
INLINE_GROUPED_CLASSES = NO

# When the INLINE_SIMPLE_STRUCTS tag is set to YES, structs, classes, and unions
# with only public data fields or simple typedef fields will be shown inline in
# the documentation of the scope in which they are defined (i.e. file,
# namespace, or group documentation), provided this scope is documented. If set
# to NO, structs, classes, and unions are shown on a separate page (for HTML and
# Man pages) or section (for LaTeX and RTF).
# The default value is: NO.

# 当INLINE_SIMPLE_STRUCTS标记设置为YES时，
# 只有公共数据字段或简单typedef字段的结构、类和单位将在定义它们的范围的文档中内联显示
# （即文件、命名空间或组文档），前提是该范围有文档记录。
# 如果设置为“否”，结构、类和联合将显示在单独的页面（对于HTML和手册页）或部分（对于LaTeX和RTF）上。
INLINE_SIMPLE_STRUCTS  = NO

# When TYPEDEF_HIDES_STRUCT tag is enabled, a typedef of a struct, union, or
# enum is documented as struct, union, or enum with the name of the typedef. So
# typedef struct TypeS {} TypeT, will appear in the documentation as a struct
# with name TypeT. When disabled the typedef will appear as a member of a file,
# namespace, or class. And the struct will be named TypeS. This can typically be
# useful for C code in case the coding convention dictates that all compound
# types are typedef'ed and only the typedef is referenced, never the tag name.
# The default value is: NO.

# 当TYPEDEF_HIDES_STRUCT标记被启用时，
# 结构、联合或枚举的TYPEDEF被记录为具有TYPEDEF名称的结构、联合或者枚举。
# 因此，typedef结构体TypeS{}TypeT将在文档中显示为名为TypeT的结构体。
# 禁用时，typedef将显示为文件、命名空间或类的成员。该结构体将被命名为TypeS。
# 如果编码约定规定所有复合类型都是typedef的，并且只引用typedef，而不引用标签名，那么这通常对C代码很有用。
TYPEDEF_HIDES_STRUCT   = NO

# The size of the symbol lookup cache can be set using LOOKUP_CACHE_SIZE. This
# cache is used to resolve symbols given their name and scope. Since this can be
# an expensive process and often the same symbol appears multiple times in the
# code, Doxygen keeps a cache of pre-resolved symbols. If the cache is too small
# Doxygen will become slower. If the cache is too large, memory is wasted. The
# cache size is given by this formula: 2^(16+LOOKUP_CACHE_SIZE). The valid range
# is 0..9, the default is 0, corresponding to a cache size of 2^16=65536
# symbols. At the end of a run Doxygen will report the cache usage and suggest
# the optimal cache size from a speed point of view.
# Minimum value: 0, maximum value: 9, default value: 0.

LOOKUP_CACHE_SIZE      = 0

# The NUM_PROC_THREADS specifies the number of threads Doxygen is allowed to use
# during processing. When set to 0 Doxygen will based this on the number of
# cores available in the system. You can set it explicitly to a value larger
# than 0 to get more control over the balance between CPU load and processing
# speed. At this moment only the input processing can be done using multiple
# threads. Since this is still an experimental feature the default is set to 1,
# which effectively disables parallel processing. Please report any issues you
# encounter. Generating dot graphs in parallel is controlled by the
# DOT_NUM_THREADS setting.
# Minimum value: 0, maximum value: 32, default value: 1.

# 可以使用lookup_cache_size设置符号查找缓存的大小。
# 此缓存用于解析给定名称和范围的符号。
# 由于这可能是一个昂贵的过程，而且同一个符号在代码中经常出现多次，Doxygen会保留一个预解析符号的缓存。
# 如果缓存太小，Doxygen将变慢。
# 如果缓存太大，内存就会浪费。缓存大小由以下公式给出：2^（16+LOOKUP_cache_size）。
# 有效范围为0..9，默认值为0，对应于2^16=65536个符号的缓存大小。
# 在运行结束时，Doxygen将报告缓存使用情况，并从速度的角度建议最佳缓存大小。
# 最小值：0，最大值：9，默认值：0。
NUM_PROC_THREADS       = 1

# If the TIMESTAMP tag is set different from NO then each generated page will
# contain the date or date and time when the page was generated. Setting this to
# NO can help when comparing the output of multiple runs.
# Possible values are: YES, NO, DATETIME and DATE.
# The default value is: NO.

# 如果TIMESTAMP标签设置为不同于“否”，
# 则每个生成的页面将包含页面生成的日期或日期和时间。
# 将此设置为“否”有助于比较多次运行的输出。
# 可能的值有：是、否、日期时间和日期。
TIMESTAMP              = NO
```

### 2.Build

```ini
#---------------------------------------------------------------------------
# Build related configuration options
#---------------------------------------------------------------------------

# If the EXTRACT_ALL tag is set to YES, Doxygen will assume all entities in
# documentation are documented, even if no documentation was available. Private
# class members and static file members will be hidden unless the
# EXTRACT_PRIVATE respectively EXTRACT_STATIC tags are set to YES.
# Note: This will also disable the warnings about undocumented members that are
# normally produced when WARNINGS is set to YES.
# The default value is: NO.

# 如果EXTRACT_ALL标签设置为YES，
# Doxygen将假设文档中的所有实体都有文档记录，即使没有可用的文档。
# 除非分别将EXTRACT_Private和EXTRACT_static标记设置为YES，
# 否则私有类成员和静态文件成员将被隐藏。
# 注意：这也将禁用当“警告”设置为“是”时通常会产生的关于未记录成员的警告。
EXTRACT_ALL            = NO

# If the EXTRACT_PRIVATE tag is set to YES, all private members of a class will
# be included in the documentation.
# The default value is: NO.

# 如果EXTRACT_PRIVATE标记设置为YES，则类的所有私有成员都将包含在文档中。
EXTRACT_PRIVATE        = NO

# If the EXTRACT_PRIV_VIRTUAL tag is set to YES, documented private virtual
# methods of a class will be included in the documentation.
# The default value is: NO.

# 如果EXTRACT_PRIV_VIRTUAL标记设置为YES，则文档中将包含类的已记录私有虚拟方法。
EXTRACT_PRIV_VIRTUAL   = NO

# If the EXTRACT_PACKAGE tag is set to YES, all members with package or internal
# scope will be included in the documentation.
# The default value is: NO.

# 如果EXTRACT_PACKAGE标记设置为YES，则所有具有包或内部作用域的成员都将包含在文档中。
EXTRACT_PACKAGE        = NO

# If the EXTRACT_STATIC tag is set to YES, all static members of a file will be
# included in the documentation.
# The default value is: NO.

# 如果EXTRACT_STATIC标记设置为YES，则文件的所有静态成员都将包含在文档中。
EXTRACT_STATIC         = NO

# If the EXTRACT_LOCAL_CLASSES tag is set to YES, classes (and structs) defined
# locally in source files will be included in the documentation. If set to NO,
# only classes defined in header files are included. Does not have any effect
# for Java sources.
# The default value is: YES.

# 如果EXTRACT_LOCAL_CLASSES标记设置为YES，则源文件中本地定义的类（和结构）将包含在文档中。
# 如果设置为“否”，则只包括头文件中定义的类。对Java源代码没有任何影响。
EXTRACT_LOCAL_CLASSES  = YES

# This flag is only useful for Objective-C code. If set to YES, local methods,
# which are defined in the implementation section but not in the interface are
# included in the documentation. If set to NO, only methods in the interface are
# included.
# The default value is: NO.

# 此标志仅对Objective-C代码有用。
# 如果设置为“是”，则文档中会包含在实现部分中定义但未在接口中定义的本地方法。
# 如果设置为“否”，则只包括接口中的方法。
EXTRACT_LOCAL_METHODS  = NO

# If this flag is set to YES, the members of anonymous namespaces will be
# extracted and appear in the documentation as a namespace called
# 'anonymous_namespace{file}', where file will be replaced with the base name of
# the file that contains the anonymous namespace. By default anonymous namespace
# are hidden.
# The default value is: NO.

# 如果此标志设置为“是”，则匿名命名空间的成员将被提取，
# 并在文档中显示为名为“anonymous_namespace{file}”的命名空间，
# 其中文件将被替换为包含匿名命名空间的文件的基名。
# 默认情况下，匿名命名空间是隐藏的。
EXTRACT_ANON_NSPACES   = NO

# If this flag is set to YES, the name of an unnamed parameter in a declaration
# will be determined by the corresponding definition. By default unnamed
# parameters remain unnamed in the output.
# The default value is: YES.

# 如果此标志设置为“是”，则声明中未命名参数的名称将由相应的定义确定。
# 默认情况下，未命名的参数在输出中保持未命名状态。
RESOLVE_UNNAMED_PARAMS = YES

# If the HIDE_UNDOC_MEMBERS tag is set to YES, Doxygen will hide all
# undocumented members inside documented classes or files. If set to NO these
# members will be included in the various overviews, but no documentation
# section is generated. This option has no effect if EXTRACT_ALL is enabled.
# The default value is: NO.

# 如果HIDE_UNDOC_MEMBERS标记设置为YES，
# Doxygen将隐藏有文档的类或文件中的所有无文档成员。
# 如果设置为“否”，这些成员将包含在各种概述中，但不会生成文档部分。
# 如果启用了EXTRACT_ALL，则此选项无效。
HIDE_UNDOC_MEMBERS     = NO

# If the HIDE_UNDOC_CLASSES tag is set to YES, Doxygen will hide all
# undocumented classes that are normally visible in the class hierarchy. If set
# to NO, these classes will be included in the various overviews. This option
# will also hide undocumented C++ concepts if enabled. This option has no effect
# if EXTRACT_ALL is enabled.
# The default value is: NO.

# 如果HIDE_UNDOC_CLASSES标记设置为YES，
# Doxygen将隐藏类层次结构中通常可见的所有未记录的类。
# 如果设置为“否”，这些类将包含在各种概述中。
# 如果启用此选项，还将隐藏未记录的C++概念。
# 如果启用了EXTRACT_ALL，则此选项无效。
HIDE_UNDOC_CLASSES     = NO

# If the HIDE_FRIEND_COMPOUNDS tag is set to YES, Doxygen will hide all friend
# declarations. If set to NO, these declarations will be included in the
# documentation.
# The default value is: NO.

# 如果HIDE_FRIEND_COMPOUNDS标记设置为YES，
# Doxygen将隐藏所有好友声明。
# 如果设置为“否”，这些声明将包含在文档中。
HIDE_FRIEND_COMPOUNDS  = NO

# If the HIDE_IN_BODY_DOCS tag is set to YES, Doxygen will hide any
# documentation blocks found inside the body of a function. If set to NO, these
# blocks will be appended to the function's detailed documentation block.
# The default value is: NO.

# 如果HIDE_IN_BODY_DOCS标记设置为YES，
# Doxygen将隐藏函数体内发现的任何文档块。
# 如果设置为“否”，这些块将附加到函数的详细文档块中。
HIDE_IN_BODY_DOCS      = NO

# The INTERNAL_DOCS tag determines if documentation that is typed after a
# \internal command is included. If the tag is set to NO then the documentation
# will be excluded. Set it to YES to include the internal documentation.
# The default value is: NO.

# INTERNAL_DOCS标记确定是否包含在\INTERNAL命令后键入的文档。
# 如果标签设置为“否”，则文档将被排除在外。将其设置为“是”以包括内部文档。
INTERNAL_DOCS          = NO

# With the correct setting of option CASE_SENSE_NAMES Doxygen will better be
# able to match the capabilities of the underlying filesystem. In case the
# filesystem is case sensitive (i.e. it supports files in the same directory
# whose names only differ in casing), the option must be set to YES to properly
# deal with such files in case they appear in the input. For filesystems that
# are not case sensitive the option should be set to NO to properly deal with
# output files written for symbols that only differ in casing, such as for two
# classes, one named CLASS and the other named Class, and to also support
# references to files without having to specify the exact matching casing. On
# Windows (including Cygwin) and macOS, users should typically set this option
# to NO, whereas on Linux or other Unix flavors it should typically be set to
# YES.
# Possible values are: SYSTEM, NO and YES.
# The default value is: SYSTEM.

# 通过正确设置选项CASE_SENSE_NAMES，Doxygen将能够更好地匹配底层文件系统的功能。
# 如果文件系统区分大小写（即它支持同一目录中名称仅大小写不同的文件），
# 则必须将选项设置为“是”，以便在输入中出现此类文件时正确处理。
# 对于不区分大小写的文件系统，应将该选项设置为“否”，以正确处理为仅大小写不同的符号编写的输出文件，
# 例如两个类，一个名为CLASS，另一个命名为Class，并且还支持对文件的引用，而无需指定精确匹配的大小写。
# 在Windows（包括Cygwin）和macOS上，用户通常应将此选项设置为“否”，
# 而在Linux或其他Unix版本上，通常应将其设置为“是”。
CASE_SENSE_NAMES       = SYSTEM

# If the HIDE_SCOPE_NAMES tag is set to NO then Doxygen will show members with
# their full class and namespace scopes in the documentation. If set to YES, the
# scope will be hidden.
# The default value is: NO.

# 如果HIDE_SCOPE_NAMES标记设置为NO，
# 则Doxygen将在文档中显示成员及其完整的类和命名空间范围。
# 如果设置为“是”，则范围将被隐藏。
HIDE_SCOPE_NAMES       = NO

# If the HIDE_COMPOUND_REFERENCE tag is set to NO (default) then Doxygen will
# append additional text to a page's title, such as Class Reference. If set to
# YES the compound reference will be hidden.
# The default value is: NO.

# 如果HIDE_COMPOUND_REFERENCE标记设置为NO（默认值），
# 则Doxygen将在页面标题后附加其他文本，例如Class REFERENCE。
# 如果设置为“是”，则复合引用将被隐藏。
HIDE_COMPOUND_REFERENCE= NO

# If the SHOW_HEADERFILE tag is set to YES then the documentation for a class
# will show which file needs to be included to use the class.
# The default value is: YES.

# 如果SHOW_HEADERFILE标记设置为YES，则类的文档将显示需要包含哪个文件才能使用该类。
SHOW_HEADERFILE        = YES

# If the SHOW_INCLUDE_FILES tag is set to YES then Doxygen will put a list of
# the files that are included by a file in the documentation of that file.
# The default value is: YES.

# 如果SHOW_INCLUDE_FILES标记设置为YES，则Doxygen将在该文件的文档中列出文件所包含的文件列表。
SHOW_INCLUDE_FILES     = YES

# If the SHOW_GROUPED_MEMB_INC tag is set to YES then Doxygen will add for each
# grouped member an include statement to the documentation, telling the reader
# which file to include in order to use the member.
# The default value is: NO.

# 如果SHOW_GROUPED_MEMB_INC标记设置为YES，
# 则Doxygen将为每个分组的成员在文档中添加一个include语句，告诉读者要包含哪个文件才能使用该成员。
SHOW_GROUPED_MEMB_INC  = NO

# If the FORCE_LOCAL_INCLUDES tag is set to YES then Doxygen will list include
# files with double quotes in the documentation rather than with sharp brackets.
# The default value is: NO.

# 如果FORCE_LOCAL_INCLUDES标记设置为YES，则Doxygen将在文档中列出包含双引号而不是尖括号的文件。
FORCE_LOCAL_INCLUDES   = NO

# If the INLINE_INFO tag is set to YES then a tag [inline] is inserted in the
# documentation for inline members.
# The default value is: YES.

# 如果INLINE_INFO标记设置为YES，则会在文档中为内联成员插入标记[INLINE]。
INLINE_INFO            = YES

# If the SORT_MEMBER_DOCS tag is set to YES then Doxygen will sort the
# (detailed) documentation of file and class members alphabetically by member
# name. If set to NO, the members will appear in declaration order.
# The default value is: YES.

# 如果SORT_MEMBER_DOCS标记设置为“是”，
# 则Doxygen将按成员名称的字母顺序对文件和类成员的（详细）文档进行排序。
# 如果设置为“否”，则成员将按声明顺序出现。
SORT_MEMBER_DOCS       = YES

# If the SORT_BRIEF_DOCS tag is set to YES then Doxygen will sort the brief
# descriptions of file, namespace and class members alphabetically by member
# name. If set to NO, the members will appear in declaration order. Note that
# this will also influence the order of the classes in the class list.
# The default value is: NO.

# 如果SORT_BRIEF_DOCS标记设置为YES，
# 则Doxygen将按成员名称的字母顺序对文件、命名空间和类成员的简要描述进行排序。
# 如果设置为“否”，则成员将按声明顺序出现。请注意，这也会影响类列表中类的顺序。
SORT_BRIEF_DOCS        = NO

# If the SORT_MEMBERS_CTORS_1ST tag is set to YES then Doxygen will sort the
# (brief and detailed) documentation of class members so that constructors and
# destructors are listed first. If set to NO the constructors will appear in the
# respective orders defined by SORT_BRIEF_DOCS and SORT_MEMBER_DOCS.
# Note: If SORT_BRIEF_DOCS is set to NO this option is ignored for sorting brief
# member documentation.
# Note: If SORT_MEMBER_DOCS is set to NO this option is ignored for sorting
# detailed member documentation.
# The default value is: NO.

# 如果SORT_MEMBERS_CTORS_1ST标记设置为YES，
# 则Doxygen将对类成员的（简短而详细的）文档进行排序，以便构造函数和析构函数首先列出。
# 如果设置为“否”，构造函数将以SORT_BRIEF_DOCS和SORT_MEMBER_DOCS定义的相应顺序出现。
# 注意：如果SORT_BRIEF_DOCS设置为“否”，则在排序简短成员文档时会忽略此选项。
SORT_MEMBERS_CTORS_1ST = NO

# If the SORT_GROUP_NAMES tag is set to YES then Doxygen will sort the hierarchy
# of group names into alphabetical order. If set to NO the group names will
# appear in their defined order.
# The default value is: NO.

# 如果SORT_GROUP_NAMES标记设置为YES，
# 则Doxygen将按字母顺序对组名的层次结构进行排序。
# 如果设置为“否”，组名将按其定义的顺序显示。
SORT_GROUP_NAMES       = NO

# If the SORT_BY_SCOPE_NAME tag is set to YES, the class list will be sorted by
# fully-qualified names, including namespaces. If set to NO, the class list will
# be sorted only by class name, not including the namespace part.
# Note: This option is not very useful if HIDE_SCOPE_NAMES is set to YES.
# Note: This option applies only to the class list, not to the alphabetical
# list.
# The default value is: NO.

# 如果SORT_BY_SCOPE_NAME标记设置为YES，
# 则类列表将按完全限定名（包括命名空间）排序。
# 如果设置为“否”，则类列表将仅按类名排序，不包括命名空间部分。
# 注意：如果HIDE_SCOPE_NAMES设置为“是”，则此选项不是很有用。
# 注意：此选项仅适用于类列表，不适用于按字母顺序排列的列表。
SORT_BY_SCOPE_NAME     = NO

# If the STRICT_PROTO_MATCHING option is enabled and Doxygen fails to do proper
# type resolution of all parameters of a function it will reject a match between
# the prototype and the implementation of a member function even if there is
# only one candidate or it is obvious which candidate to choose by doing a
# simple string match. By disabling STRICT_PROTO_MATCHING Doxygen will still
# accept a match between prototype and implementation in such cases.
# The default value is: NO.

# 如果启用了STRIC_PROTO_MATCHING选项，
# 并且Doxygen未能对函数的所有参数进行正确的类型解析，
# 则它将拒绝原型和成员函数实现之间的匹配，即使只有一个候选者，
# 或者通过简单的字符串匹配可以明显选择哪个候选者。
# 通过禁用STRIC_PROTO_MATCHING，Doxygen在这种情况下仍将接受原型和实现之间的匹配。
STRICT_PROTO_MATCHING  = NO

# The GENERATE_TODOLIST tag can be used to enable (YES) or disable (NO) the todo
# list. This list is created by putting \todo commands in the documentation.
# The default value is: YES.

# GENERATE_TOOLIST标记可用于启用（是）或禁用（否）待办事项列表。
# 此列表是通过在文档中放置\todo命令创建的。
GENERATE_TODOLIST      = YES

# The GENERATE_TESTLIST tag can be used to enable (YES) or disable (NO) the test
# list. This list is created by putting \test commands in the documentation.
# The default value is: YES.

# GENERATE_TESTLIST标签可用于启用（是）或禁用（否）测试列表。
# 此列表是通过在文档中放置\test命令创建的。
GENERATE_TESTLIST      = YES

# The GENERATE_BUGLIST tag can be used to enable (YES) or disable (NO) the bug
# list. This list is created by putting \bug commands in the documentation.
# The default value is: YES.

# GENERATE_BUGLIST标签可用于启用（是）或禁用（否）错误列表。此列表是通过在文档中添加\bug命令创建的。
GENERATE_BUGLIST       = YES

# The GENERATE_DEPRECATEDLIST tag can be used to enable (YES) or disable (NO)
# the deprecated list. This list is created by putting \deprecated commands in
# the documentation.
# The default value is: YES.

# GENERATE_DEPRECATEDLIST标签可用于启用（是）或禁用（否）已弃用列表。
# 此列表是通过在文档中添加\弃用命令创建的。
GENERATE_DEPRECATEDLIST= YES

# The ENABLED_SECTIONS tag can be used to enable conditional documentation
# sections, marked by \if <section_label> ... \endif and \cond <section_label>
# ... \endcond blocks.

# ENABLED_SECTIONS标签可用于启用条件文档部分，
# 标记为\if<section_label>。。。\endif 和\cord<section_label>。。。\endcond blocks。
ENABLED_SECTIONS       =

# The MAX_INITIALIZER_LINES tag determines the maximum number of lines that the
# initial value of a variable or macro / define can have for it to appear in the
# documentation. If the initializer consists of more lines than specified here
# it will be hidden. Use a value of 0 to hide initializers completely. The
# appearance of the value of individual variables and macros / defines can be
# controlled using \showinitializer or \hideinitializer command in the
# documentation regardless of this setting.
# Minimum value: 0, maximum value: 10000, default value: 30.

# MAX_INTIALIZER_LINES标记确定变量或宏/定义的初始值在文档中显示的最大行数。
# 如果初始化器包含的行数超过此处指定的行数，则它将被隐藏。
# 使用值0完全隐藏初始化器。无论此设置如何，
# 都可以使用文档中的\showinitializer或\hideinitializer命令来控制单个变量和宏/定义的值的外观。
# 最小值：0，最大值：10000，默认值：30。
MAX_INITIALIZER_LINES  = 30

# Set the SHOW_USED_FILES tag to NO to disable the list of files generated at
# the bottom of the documentation of classes and structs. If set to YES, the
# list will mention the files that were used to generate the documentation.
# The default value is: YES.

# 将SHOW_USED_FILES标记设置为NO，以禁用在类和结构文档底部生成的文件列表。
# 如果设置为“是”，则列表将提及用于生成文档的文件。
SHOW_USED_FILES        = YES

# Set the SHOW_FILES tag to NO to disable the generation of the Files page. This
# will remove the Files entry from the Quick Index and from the Folder Tree View
# (if specified).
# The default value is: YES.

# 将SHOW_FILES标签设置为“否”以禁用“文件”页面的生成。
# 这将从快速索引和文件夹树视图（如果指定）中删除“文件”条目。
SHOW_FILES             = YES

# Set the SHOW_NAMESPACES tag to NO to disable the generation of the Namespaces
# page. This will remove the Namespaces entry from the Quick Index and from the
# Folder Tree View (if specified).
# The default value is: YES.

# 将SHOW_NAMESPACES标记设置为“否”以禁用“命名空间”页面的生成。
# 这将从快速索引和文件夹树视图（如果指定）中删除命名空间条目。
SHOW_NAMESPACES        = YES

# The FILE_VERSION_FILTER tag can be used to specify a program or script that
# Doxygen should invoke to get the current version for each file (typically from
# the version control system). Doxygen will invoke the program by executing (via
# popen()) the command command input-file, where command is the value of the
# FILE_VERSION_FILTER tag, and input-file is the name of an input file provided
# by Doxygen. Whatever the program writes to standard output is used as the file
# version. For an example see the documentation.

# FILE_VERSION_FILTER标记可用于指定Doxygen应调用的程序或脚本，
# 以获取每个文件的当前版本（通常来自版本控制系统）。
# Doxygen将通过执行（通过popen（））命令命令输入文件来调用程序，
# 其中command是file_VERSION_FILTER标记的值，输入文件是Doxygen提供的输入文件的名称。
# 程序写入标准输出的任何内容都用作文件版本。有关示例，请参阅文档。
FILE_VERSION_FILTER    =

# The LAYOUT_FILE tag can be used to specify a layout file which will be parsed
# by Doxygen. The layout file controls the global structure of the generated
# output files in an output format independent way. To create the layout file
# that represents Doxygen's defaults, run Doxygen with the -l option. You can
# optionally specify a file name after the option, if omitted DoxygenLayout.xml
# will be used as the name of the layout file. See also section "Changing the
# layout of pages" for information.
#
# Note that if you run Doxygen from a directory containing a file called
# DoxygenLayout.xml, Doxygen will parse it automatically even if the LAYOUT_FILE
# tag is left empty.

# LAYOUT_FILE标签可用于指定Doxygen将解析的布局文件。
# 布局文件以独立于输出格式的方式控制生成的输出文件的全局结构。
# 要创建表示Doxygen默认值的布局文件，请使用-l选项运行Doxygen。
# 您可以选择在选项后指定文件名，如果省略，DoxygenLayout.xml将用作布局文件的名称。
# 另请参阅“更改页面布局”一节以获取信息。
LAYOUT_FILE            =

# The CITE_BIB_FILES tag can be used to specify one or more bib files containing
# the reference definitions. This must be a list of .bib files. The .bib
# extension is automatically appended if omitted. This requires the bibtex tool
# to be installed. See also https://en.wikipedia.org/wiki/BibTeX for more info.
# For LaTeX the style of the bibliography can be controlled using
# LATEX_BIB_STYLE. To use this feature you need bibtex and perl available in the
# search path. See also \cite for info how to create references.

# CITE_BIB_FILES标记可用于指定一个或多个包含引用定义的BIB文件。
# 这一定是一个.bib文件列表。如果省略，.bib扩展名将自动附加。
# 这需要安装bibtex工具。另请参见https://en.wikipedia.org/wiki/BibTeX了解更多信息。
# 对于LaTeX，可以使用LaTeX_BIB_style控制参考书目的样式。
# 要使用此功能，您需要在搜索路径中提供bibtex和perl。有关如何创建引用的信息，请参阅\cite。

CITE_BIB_FILES         =

# The EXTERNAL_TOOL_PATH tag can be used to extend the search path (PATH
# environment variable) so that external tools such as latex and gs can be
# found.
# Note: Directories specified with EXTERNAL_TOOL_PATH are added in front of the
# path already specified by the PATH variable, and are added in the order
# specified.
# Note: This option is particularly useful for macOS version 14 (Sonoma) and
# higher, when running Doxygen from Doxywizard, because in this case any user-
# defined changes to the PATH are ignored. A typical example on macOS is to set
# EXTERNAL_TOOL_PATH = /Library/TeX/texbin /usr/local/bin
# together with the standard path, the full search path used by doxygen when
# launching external tools will then become
# PATH=/Library/TeX/texbin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin

# EXTERNAL_TOOL_PATH标记可用于扩展搜索路径（PATH环境变量），以便可以找到外部工具，如latex和gs。
# 注意：使用EXTERNAL_TOOL_PATH指定的目录将添加到PATH变量已指定的路径之前，并按照指定的顺序添加。
# 注意：当从Doxywizard运行Doxygen时，此选项对于macOS版本14（Sonoma）和更高版本特别有用，因为在这种情况下，对PATH的任何用户定义的更改都会被忽略。
# macOS上的一个典型示例是将EXTERNAL_TOOL_PATH=/Library/TeX/texbin/usr/local/bin与标准路径一起设置，doxygen在启动外部工具时使用的完整搜索路径将变为PATH=/Library/TiX/texbin:/usr/local/bin:/usr/bin:/bin:usr/sbin:/sbin
EXTERNAL_TOOL_PATH     =
```

### 3.Input

```ini
#---------------------------------------------------------------------------
# Configuration options related to the input files
#---------------------------------------------------------------------------

# The INPUT tag is used to specify the files and/or directories that contain
# documented source files. You may enter file names like myfile.cpp or
# directories like /usr/src/myproject. Separate the files or directories with
# spaces. See also FILE_PATTERNS and EXTENSION_MAPPING
# Note: If this tag is empty the current directory is searched.

# INPUT标签用于指定包含已记录源文件的文件和/或目录。
# 您可以输入文件名，如myfile.cpp，或目录，如/usr/src/myproject。
# 用空格分隔文件或目录。另请参见FILE_PATTERNS和EXTENSION_MAPPING
# 注意：如果此标记为空，则搜索当前目录。
INPUT                  =

# This tag can be used to specify the character encoding of the source files
# that Doxygen parses. Internally Doxygen uses the UTF-8 encoding. Doxygen uses
# libiconv (or the iconv built into libc) for the transcoding. See the libiconv
# documentation (see:
# https://www.gnu.org/software/libiconv/) for the list of possible encodings.
# See also: INPUT_FILE_ENCODING
# The default value is: UTF-8.

# 此标记可用于指定Doxygen解析的源文件的字符编码。
# Doxygen内部使用UTF-8编码。Doxygen使用libiconv（或libc内置的iconv）进行转码。
# 请参阅libiconv文档（请参阅：https://www.gnu.org/software/libiconv/)查看可能的编码列表。
INPUT_ENCODING         = UTF-8

# This tag can be used to specify the character encoding of the source files
# that Doxygen parses The INPUT_FILE_ENCODING tag can be used to specify
# character encoding on a per file pattern basis. Doxygen will compare the file
# name with each pattern and apply the encoding instead of the default
# INPUT_ENCODING) if there is a match. The character encodings are a list of the
# form: pattern=encoding (like *.php=ISO-8859-1).
# See also: INPUT_ENCODING for further information on supported encodings.

# 此标记可用于指定Doxygen解析的源文件的字符编码。
# INPUT_FILE_encoding标记可用于在每个文件模式的基础上指定字符编码。
# Doxygen会将文件名与每个模式进行比较，如果匹配，则应用编码而不是默认的INPUT_encoding）。
# 字符编码是以下形式的列表：pattern=encoding（如*.php=ISO-8859-1）。
INPUT_FILE_ENCODING    =

# If the value of the INPUT tag contains directories, you can use the
# FILE_PATTERNS tag to specify one or more wildcard patterns (like *.cpp and
# *.h) to filter out the source-files in the directories.
#
# Note that for custom extensions or not directly supported extensions you also
# need to set EXTENSION_MAPPING for the extension otherwise the files are not
# read by Doxygen.
#
# Note the list of default checked file patterns might differ from the list of
# default file extension mappings.
#
# If left blank the following patterns are tested:*.c, *.cc, *.cxx, *.cxxm,
# *.cpp, *.cppm, *.ccm, *.c++, *.c++m, *.java, *.ii, *.ixx, *.ipp, *.i++, *.inl,
# *.idl, *.ddl, *.odl, *.h, *.hh, *.hxx, *.hpp, *.h++, *.ixx, *.l, *.cs, *.d,
# *.php, *.php4, *.php5, *.phtml, *.inc, *.m, *.markdown, *.md, *.mm, *.dox (to
# be provided as Doxygen C comment), *.py, *.pyw, *.f90, *.f95, *.f03, *.f08,
# *.f18, *.f, *.for, *.vhd, *.vhdl, *.ucf, *.qsf and *.ice.

# 如果INPUT标记的值包含目录，则可以使用FILE_PATTERNS标记指定一个或多个通配符模式（如*.cpp和*.h）来过滤目录中的源文件。
# 注意，对于自定义扩展名或不直接支持的扩展名，您还需要为扩展名设置EXTENSION_MAPPING，否则Doxygen将无法读取文件
FILE_PATTERNS          = *.c \
                         *.cc \
                         *.cxx \
                         *.cxxm \
                         *.cpp \
                         *.cppm \
                         *.ccm \
                         *.c++ \
                         *.c++m \
                         *.java \
                         *.ii \
                         *.ixx \
                         *.ipp \
                         *.i++ \
                         *.inl \
                         *.idl \
                         *.ddl \
                         *.odl \
                         *.h \
                         *.hh \
                         *.hxx \
                         *.hpp \
                         *.h++ \
                         *.ixx \
                         *.l \
                         *.cs \
                         *.d \
                         *.php \
                         *.php4 \
                         *.php5 \
                         *.phtml \
                         *.inc \
                         *.m \
                         *.markdown \
                         *.md \
                         *.mm \
                         *.dox \
                         *.py \
                         *.pyw \
                         *.f90 \
                         *.f95 \
                         *.f03 \
                         *.f08 \
                         *.f18 \
                         *.f \
                         *.for \
                         *.vhd \
                         *.vhdl \
                         *.ucf \
                         *.qsf \
                         *.ice

# The RECURSIVE tag can be used to specify whether or not subdirectories should
# be searched for input files as well.
# The default value is: NO.

# RECURSIVE标签可用于指定是否也应在子目录中搜索输入文件。
RECURSIVE              = NO

# The EXCLUDE tag can be used to specify files and/or directories that should be
# excluded from the INPUT source files. This way you can easily exclude a
# subdirectory from a directory tree whose root is specified with the INPUT tag.
#
# Note that relative paths are relative to the directory from which Doxygen is
# run.

# EXCLUDE标记可用于指定应从INPUT源文件中排除的文件和/或目录。
# 这样，您可以轻松地从目录树中排除根目录由INPUT标记指定的子目录。
# 注意，相对路径是相对于运行Doxygen的目录的。
EXCLUDE                =

# The EXCLUDE_SYMLINKS tag can be used to select whether or not files or
# directories that are symbolic links (a Unix file system feature) are excluded
# from the input.
# The default value is: NO.

# EXCLUDE_SYMLINKS标记可用于选择是否从输入中排除符号链接（Unix文件系统功能）的文件或目录。
EXCLUDE_SYMLINKS       = NO

# If the value of the INPUT tag contains directories, you can use the
# EXCLUDE_PATTERNS tag to specify one or more wildcard patterns to exclude
# certain files from those directories.
#
# Note that the wildcards are matched against the file with absolute path, so to
# exclude all test directories for example use the pattern */test/*

# 如果INPUT标记的值包含目录，则可以使用EXCLUDE_PATTERNS标记指定一个或多个通配符模式，以从这些目录中排除某些文件。
#注意，通配符与具有绝对路径的文件匹配，因此要排除所有测试目录，例如使用模式*/test/*
EXCLUDE_PATTERNS       =

# The EXCLUDE_SYMBOLS tag can be used to specify one or more symbol names
# (namespaces, classes, functions, etc.) that should be excluded from the
# output. The symbol name can be a fully qualified name, a word, or if the
# wildcard * is used, a substring. Examples: ANamespace, AClass,
# ANamespace::AClass, ANamespace::*Test

# EXCLUDE_SYMBOLS标记可用于指定应从输出中排除的一个或多个符号名称（命名空间、类、函数等）。
# 符号名称可以是完全限定名、单词，或者如果使用通配符*，则可以是子字符串。
# 示例：ANamespace、AClass、ANamespace:：AClass、ANamespace:
EXCLUDE_SYMBOLS        =

# The EXAMPLE_PATH tag can be used to specify one or more files or directories
# that contain example code fragments that are included (see the \include
# command).

# EXAMPLE_PATH标记可用于指定包含示例代码片段的一个或多个文件或目录（请参阅\include命令）。
EXAMPLE_PATH           =

# If the value of the EXAMPLE_PATH tag contains directories, you can use the
# EXAMPLE_PATTERNS tag to specify one or more wildcard pattern (like *.cpp and
# *.h) to filter out the source-files in the directories. If left blank all
# files are included.

# 如果EXAMPLE_PATH标记的值包含目录，
# 则可以使用EXAMPLE_PATHRNS标记指定一个或多个通配符模式（如*.cpp和*.h）来筛选目录中的源文件。
# 如果留空，则包括所有文件。
EXAMPLE_PATTERNS       = *

# If the EXAMPLE_RECURSIVE tag is set to YES then subdirectories will be
# searched for input files to be used with the \include or \dontinclude commands
# irrespective of the value of the RECURSIVE tag.
# The default value is: NO.

# 如果EXAMPLE_RECURSIVE标记设置为YES，
# 则将在子目录中搜索与\include或\dontinclude命令一起使用的输入文件，而不管RECURSIVE标签的值如何。
EXAMPLE_RECURSIVE      = NO

# The IMAGE_PATH tag can be used to specify one or more files or directories
# that contain images that are to be included in the documentation (see the
# \image command).

# #IMAGE_PATH标记可用于指定一个或多个文件或目录，其中包含要包含在文档中的图像（请参阅\IMAGE命令）。
IMAGE_PATH             =

# The INPUT_FILTER tag can be used to specify a program that Doxygen should
# invoke to filter for each input file. Doxygen will invoke the filter program
# by executing (via popen()) the command:
#
# <filter> <input-file>
#
# where <filter> is the value of the INPUT_FILTER tag, and <input-file> is the
# name of an input file. Doxygen will then use the output that the filter
# program writes to standard output. If FILTER_PATTERNS is specified, this tag
# will be ignored.
#
# Note that the filter must not add or remove lines; it is applied before the
# code is scanned, but not when the output code is generated. If lines are added
# or removed, the anchors will not be placed correctly.
#
# Note that Doxygen will use the data processed and written to standard output
# for further processing, therefore nothing else, like debug statements or used
# commands (so in case of a Windows batch file always use @echo OFF), should be
# written to standard output.
#
# Note that for custom extensions or not directly supported extensions you also
# need to set EXTENSION_MAPPING for the extension otherwise the files are not
# properly processed by Doxygen.

# INPUT_FILTER标记可用于指定Doxygen应调用的程序，以对每个输入文件进行筛选。Doxygen将通过执行（通过popen（））命令来调用过滤器程序：
# 
# <filter> <input-file>
# 
# 其中<filter>是INPUT_filter标记的值，<inputfile>是输入文件的名称。Doxygen将使用过滤器程序写入标准输出的输出。如果指定了FILTER_PATTERNS，则将忽略此标记。
#
# 注意，过滤器不得添加或删除线条；它在扫描代码之前应用，但在生成输出代码时不应用。如果添加或删除线条，锚将无法正确放置。
#
# 注意，Doxygen将使用已处理并写入标准输出的数据进行进一步处理，
# 因此，其他任何内容，如调试语句或使用的命令（因此，在Windows批处理文件的情况下，始终使用@echo OFF），都不应写入标准输出。
#
# 注意，对于自定义扩展名或不直接支持的扩展名，您还需要为扩展名设置EXTENSION_MAPPING，否则Doxygen无法正确处理文件。
INPUT_FILTER           =

# The FILTER_PATTERNS tag can be used to specify filters on a per file pattern
# basis. Doxygen will compare the file name with each pattern and apply the
# filter if there is a match. The filters are a list of the form: pattern=filter
# (like *.cpp=my_cpp_filter). See INPUT_FILTER for further information on how
# filters are used. If the FILTER_PATTERNS tag is empty or if none of the
# patterns match the file name, INPUT_FILTER is applied.
#
# Note that for custom extensions or not directly supported extensions you also
# need to set EXTENSION_MAPPING for the extension otherwise the files are not
# properly processed by Doxygen.

# FILTER_PATTERNS标记可用于在每个文件模式的基础上指定过滤器。
# Doxygen会将文件名与每个模式进行比较，如果匹配，则应用过滤器。
# 过滤器是一个格式为：pattern=filter（如*.cpp=my_cpp_filter）的列表。
# 有关如何使用过滤器的更多信息，请参阅INPUT_FILTER。
# 如果FILTER_PATTERNS标记为空，或者没有一个模式与文件名匹配，则应用INPUT_FILTER。
#
# 注意，对于自定义扩展名或不直接支持的扩展名，您还需要为扩展名设置EXTENSION_MAPPING，否则Doxygen无法正确处理文件。
FILTER_PATTERNS        =

# If the FILTER_SOURCE_FILES tag is set to YES, the input filter (if set using
# INPUT_FILTER) will also be used to filter the input files that are used for
# producing the source files to browse (i.e. when SOURCE_BROWSER is set to YES).
# The default value is: NO.

# 如果FILTER_SOURCE_FILES标记设置为YES，则输入过滤器（如果使用input_FILTER设置）也将用于过滤用于生成要浏览的源文件的输入文件（即当SOURCE_BROWSER设置为YES时）。
FILTER_SOURCE_FILES    = NO

# The FILTER_SOURCE_PATTERNS tag can be used to specify source filters per file
# pattern. A pattern will override the setting for FILTER_PATTERN (if any) and
# it is also possible to disable source filtering for a specific pattern using
# *.ext= (so without naming a filter).
# This tag requires that the tag FILTER_SOURCE_FILES is set to YES.

# FILTER_SOURCE_PATTERNS标记可用于为每个文件模式指定源过滤器。
# 模式将覆盖FILTER_PATTRN的设置（如果有的话），
# 也可以使用*.ext=禁用特定模式的源过滤（因此无需命名过滤器）。
# 此标记要求将标记FILTER_SOURCE_FILES设置为YES。
FILTER_SOURCE_PATTERNS =

# If the USE_MDFILE_AS_MAINPAGE tag refers to the name of a markdown file that
# is part of the input, its contents will be placed on the main page
# (index.html). This can be useful if you have a project on for instance GitHub
# and want to reuse the introduction page also for the Doxygen output.

# 如果USE_MDFILE_AS_MAINPAGE标记引用了作为输入一部分的markdown文件的名称，则其内容将放置在主页（index.html）上。
# 如果你在GitHub上有一个项目，并且想将介绍页面也用于Doxygen输出，这可能会很有用。

USE_MDFILE_AS_MAINPAGE =

# The Fortran standard specifies that for fixed formatted Fortran code all
# characters from position 72 are to be considered as comment. A common
# extension is to allow longer lines before the automatic comment starts. The
# setting FORTRAN_COMMENT_AFTER will also make it possible that longer lines can
# be processed before the automatic comment starts.
# Minimum value: 7, maximum value: 10000, default value: 72.

# Fortran标准规定，对于固定格式的Fortran代码，从位置72开始的所有字符都应被视为注释。# # 一个常见的扩展是在自动注释开始之前允许更长的行。
# 设置FORTRAN_COMMENT_AFTER还可以在自动注释开始之前处理较长的行。
# 最小值：7，最大值：10000，默认值：72。
FORTRAN_COMMENT_AFTER  = 72
```

### 4.Source browsing 源代码浏览

```ini
#---------------------------------------------------------------------------
# Configuration options related to source browsing
#---------------------------------------------------------------------------

# If the SOURCE_BROWSER tag is set to YES then a list of source files will be
# generated. Documented entities will be cross-referenced with these sources.
#
# Note: To get rid of all source code in the generated output, make sure that
# also VERBATIM_HEADERS is set to NO.
# The default value is: NO.

# 如果将 SOURCE_BROWSER 标记设置为 YES，则会生成源文件列表。
# 记录的实体将与这些源交叉引用。
# 注意：要删除生成的输出中的所有源代码，请确保 VERBATIM_HEADERS 也设置为 NO
SOURCE_BROWSER         = NO

# Setting the INLINE_SOURCES tag to YES will include the body of functions,
# multi-line macros, enums or list initialized variables directly into the
# documentation.
# The default value is: NO.

# 将INLINE_SOURCES标记设置为YES，
# 会将函数主体、多行宏、枚举或列表初始化变量直接包含在文档中。
INLINE_SOURCES         = NO

# Setting the STRIP_CODE_COMMENTS tag to YES will instruct Doxygen to hide any
# special comment blocks from generated source code fragments. Normal C, C++ and
# Fortran comments will always remain visible.
# The default value is: YES.

# 将STRIP_CODE_COMMENTS标记设置为YES
# 将指示 Doxygen 隐藏生成的源代码片段中的任何特殊注释块。
# 普通的 C、C++ 和 Fortran 注释将始终保持可见。
STRIP_CODE_COMMENTS    = YES

# If the REFERENCED_BY_RELATION tag is set to YES then for each documented
# entity all documented functions referencing it will be listed.
# The default value is: NO.

# 如果 REFERENCED_BY_RELATION 标记设置为 YES，
# 则对于每个记录的实体，将列出引用它的所有记录的函数。
REFERENCED_BY_RELATION = NO

# If the REFERENCES_RELATION tag is set to YES then for each documented function
# all documented entities called/used by that function will be listed.
# The default value is: NO.

# 如果 REFERENCES_RELATION 标记设置为 YES，
# 则对于每个记录的函数，将列出该函数调用/使用的所有记录的实体。
REFERENCES_RELATION    = NO

# If the REFERENCES_LINK_SOURCE tag is set to YES and SOURCE_BROWSER tag is set
# to YES then the hyperlinks from functions in REFERENCES_RELATION and
# REFERENCED_BY_RELATION lists will link to the source code. Otherwise they will
# link to the documentation.
# The default value is: YES.

# 如果 REFERENCES_LINK_SOURCE 标记设置为 YES，
# 且 SOURCE_BROWSER 标记设置为 YES，
# 则 REFERENCES_RELATION 和 REFERENCED_BY_RELATION 列表中的函数的超链接将链接到源代码。
# 否则，它们将链接到文档。
REFERENCES_LINK_SOURCE = YES

# If SOURCE_TOOLTIPS is enabled (the default) then hovering a hyperlink in the
# source code will show a tooltip with additional information such as prototype,
# brief description and links to the definition and documentation. Since this
# will make the HTML file larger and loading of large files a bit slower, you
# can opt to disable this feature.
# The default value is: YES.
# This tag requires that the tag SOURCE_BROWSER is set to YES.

# 如果启用了 SOURCE_TOOLTIPS（默认），
# 则将鼠标悬停在源代码中的超链接上将显示一个工具提示，其中包含其他信息，
# 例如原型、简要说明以及指向定义和文档的链接。
# 由于这会使 HTML 文件变大，并且大文件的加载速度会变慢，因此您可以选择禁用此功能。
SOURCE_TOOLTIPS        = YES

# If the USE_HTAGS tag is set to YES then the references to source code will
# point to the HTML generated by the htags(1) tool instead of Doxygen built-in
# source browser. The htags tool is part of GNU's global source tagging system
# (see https://www.gnu.org/software/global/global.html). You will need version
# 4.8.6 or higher.
#
# To use it do the following:
# - Install the latest version of global
# - Enable SOURCE_BROWSER and USE_HTAGS in the configuration file
# - Make sure the INPUT points to the root of the source tree
# - Run doxygen as normal
#
# Doxygen will invoke htags (and that will in turn invoke gtags), so these
# tools must be available from the command line (i.e. in the search path).
#
# The result: instead of the source browser generated by Doxygen, the links to
# source code will now point to the output of htags.
# The default value is: NO.
# This tag requires that the tag SOURCE_BROWSER is set to YES.

# 如果将 USE_HTAGS 标记设置为 YES，则对源代码的引用将指向 htags(1) 工具生成的 HTML，而不是 Doxygen 内置源浏览器。
# htags 工具是 GNU 全局源标记系统的一部分（请参阅 https://www.gnu.org/software/global/global.html）。您需要 4.8.6 或更高版本。
# 要使用它，请执行以下操作：
# - 安装最新版本的全局
# - 在配置文件中启用 SOURCE_BROWSER 和 USE_HTAGS
# - 确保 INPUT 指向源树的根
# - 正常运行 doxygen
#
# Doxygen 将调用 htags（进而调用 gtags），因此这些工具必须可从命令行（即在搜索路径中）获得。
#
# 结果：源代码链接现在将指向 htags 的输出，而不是由 Doxygen 生成的源浏览器。
USE_HTAGS              = NO

# If the VERBATIM_HEADERS tag is set the YES then Doxygen will generate a
# verbatim copy of the header file for each class for which an include is
# specified. Set to NO to disable this.
# See also: Section \class.
# The default value is: YES.

# 如果将 VERBATIM_HEADERS 标记设置为 YES，
# 则 Doxygen 将为每个指定了包含的类生成一个
VERBATIM_HEADERS       = YES

# If the CLANG_ASSISTED_PARSING tag is set to YES then Doxygen will use the
# clang parser (see:
# http://clang.llvm.org/) for more accurate parsing at the cost of reduced
# performance. This can be particularly helpful with template rich C++ code for
# which Doxygen's built-in parser lacks the necessary type information.
# Note: The availability of this option depends on whether or not Doxygen was
# generated with the -Duse_libclang=ON option for CMake.
# The default value is: NO.

# 如果将 CLANG_ASSISTED_PARSING 标记设置为 YES，
# 则 Doxygen 将使用 clang 解析器（请参阅：http://clang.llvm.org/）进行更准确的解析，但代价是性能降低。
# 这对于模板丰富的 C++ 代码尤其有用，因为 Doxygen 的内置解析器缺少必要的类型信息。
# 注意：此选项的可用性取决于 Doxygen 是否是使用 CMake 的 -Duse_libclang=ON 选项生成的。
CLANG_ASSISTED_PARSING = NO

# If the CLANG_ASSISTED_PARSING tag is set to YES and the CLANG_ADD_INC_PATHS
# tag is set to YES then Doxygen will add the directory of each input to the
# include path.
# The default value is: YES.
# This tag requires that the tag CLANG_ASSISTED_PARSING is set to YES.

# 如果将 CLANG_ASSISTED_PARSING 标记设置为 YES，
# 并将 CLANG_ADD_INC_PATHS 标记设置为 YES，则 Doxygen 会将每个输入的目录添加到包含路径。
CLANG_ADD_INC_PATHS    = YES

# If clang assisted parsing is enabled you can provide the compiler with command
# line options that you would normally use when invoking the compiler. Note that
# the include paths will already be set by Doxygen for the files and directories
# specified with INPUT and INCLUDE_PATH.
# This tag requires that the tag CLANG_ASSISTED_PARSING is set to YES.

# 如果启用了 clang 辅助解析，您可以为编译器提供命令行选项，这些选项通常在调用编译器时使用。请注意，Doxygen 已为 INPUT 和 INCLUDE_PATH 指定的文件和目录设置包含路径。
CLANG_OPTIONS          =

# If clang assisted parsing is enabled you can provide the clang parser with the
# path to the directory containing a file called compile_commands.json. This
# file is the compilation database (see:
# http://clang.llvm.org/docs/HowToSetupToolingForLLVM.html) containing the
# options used when the source files were built. This is equivalent to
# specifying the -p option to a clang tool, such as clang-check. These options
# will then be passed to the parser. Any options specified with CLANG_OPTIONS
# will be added as well.
# Note: The availability of this option depends on whether or not Doxygen was
# generated with the -Duse_libclang=ON option for CMake.

# 如果启用了 clang 辅助解析，您可以向 clang 解析器提供包含名为 compile_commands.json 的文件的目录路径。
# 此文件是编译数据库（请参阅：http://clang.llvm.org/docs/HowToSetupToolingForLLVM.html），其中包含构建源文件时使用的选项。
# 这相当于为 clang 工具（例如 clang-check）指定 -p 选项。然后，这些选项将传递给解析器。任何使用 CLANG_OPTIONS 指定的选项也将被添加。
CLANG_DATABASE_PATH    =
```

### 5.alphabetical class index 按字母顺序排列的类索引

```sh
#---------------------------------------------------------------------------
# Configuration options related to the alphabetical class index
#---------------------------------------------------------------------------

# If the ALPHABETICAL_INDEX tag is set to YES, an alphabetical index of all
# compounds will be generated. Enable this if the project contains a lot of
# classes, structs, unions or interfaces.
# The default value is: YES.

# 如果将 ALPHABETICAL_INDEX 标记设置为 YES，则会生成所有化合物的字母索引。
# 如果项目包含大量类、结构、联合或接口，请启用此功能。
ALPHABETICAL_INDEX     = YES

# The IGNORE_PREFIX tag can be used to specify a prefix (or a list of prefixes)
# that should be ignored while generating the index headers. The IGNORE_PREFIX
# tag works for classes, function and member names. The entity will be placed in
# the alphabetical list under the first letter of the entity name that remains
# after removing the prefix.
# This tag requires that the tag ALPHABETICAL_INDEX is set to YES.

# IGNORE_PREFIX 标记可用于指定在生成索引头时应忽略的前缀（或前缀列表）。
# IGNORE_PREFIX 标记适用于类、函数和成员名称。
# 实体将放置在删除前缀后剩余的实体名称首字母下的字母列表中。
# 此标记要求将标记 ALPHABETICAL_INDEX 设置为 YES。
IGNORE_PREFIX          =
```

### 6.HTML output

```ini
#---------------------------------------------------------------------------
# Configuration options related to the HTML output
#---------------------------------------------------------------------------

# If the GENERATE_HTML tag is set to YES, Doxygen will generate HTML output
# The default value is: YES.

# 如果 GENERATE_HTML 标记设置为 YES，Doxygen 将生成 HTML 输出
GENERATE_HTML          = YES

# The HTML_OUTPUT tag is used to specify where the HTML docs will be put. If a
# relative path is entered the value of OUTPUT_DIRECTORY will be put in front of
# it.
# The default directory is: html.
# This tag requires that the tag GENERATE_HTML is set to YES.

# HTML_OUTPUT 标记用于指定 HTML 文档的放置位置。
# 如果输入的是相对路径，则 OUTPUT_DIRECTORY 的值将放在其前面。
# 默认目录为：html。
# 此标记要求将标记 GENERATE_HTML 设置为 YES。
HTML_OUTPUT            = html

# The HTML_FILE_EXTENSION tag can be used to specify the file extension for each
# generated HTML page (for example: .htm, .php, .asp).
# The default value is: .html.
# This tag requires that the tag GENERATE_HTML is set to YES.

# HTML_FILE_EXTENSION 标记可用于指定每个生成的 HTML 页面的文件扩展名（例如：.htm、.php、.asp）。
# 默认值为：.html。
# 此标记要求将标记 GENERATE_HTML 设置为 YES。
HTML_FILE_EXTENSION    = .html

# The HTML_HEADER tag can be used to specify a user-defined HTML header file for
# each generated HTML page. If the tag is left blank Doxygen will generate a
# standard header.
#
# To get valid HTML the header file that includes any scripts and style sheets
# that Doxygen needs, which is dependent on the configuration options used (e.g.
# the setting GENERATE_TREEVIEW). It is highly recommended to start with a
# default header using
# doxygen -w html new_header.html new_footer.html new_stylesheet.css
# YourConfigFile
# and then modify the file new_header.html. See also section "Doxygen usage"
# for information on how to generate the default header that Doxygen normally
# uses.
# Note: The header is subject to change so you typically have to regenerate the
# default header when upgrading to a newer version of Doxygen. For a description
# of the possible markers and block names see the documentation.
# This tag requires that the tag GENERATE_HTML is set to YES.

# HTML_HEADER 标记可用于为每个生成的 HTML 页面指定用户定义的 HTML 标头文件。如果标记留空，Doxygen 将生成标准标头。
# 要获取有效的 HTML，标头文件包含 Doxygen 所需的任何脚本和样式表，这取决于所使用的配置选项（例如设置 GENERATE_TREEVIEW）。强烈建议使用 doxygen -w html new_header.html new_footer.html new_stylesheet.css YourConfigFile 从默认标头开始，然后修改文件 new_header.html。另请参阅“Doxygen 使用”部分，了解如何生成 Doxygen 通常使用的默认标头。
# 注意：标头可能会发生变化，因此升级到较新版本的 Doxygen 时通常必须重新生成默认标头。有关可能的标记和块名称的描述，请参阅文档。
# 此标记要求将标记 GENERATE_HTML 设置为 YES。
HTML_HEADER            =

# The HTML_FOOTER tag can be used to specify a user-defined HTML footer for each
# generated HTML page. If the tag is left blank Doxygen will generate a standard
# footer. See HTML_HEADER for more information on how to generate a default
# footer and what special commands can be used inside the footer. See also
# section "Doxygen usage" for information on how to generate the default footer
# that Doxygen normally uses.
# This tag requires that the tag GENERATE_HTML is set to YES.

# HTML_FOOTER 标记可用于为每个生成的 HTML 页面指定用户定义的 HTML 页脚。如果该标记留空，Doxygen 将生成标准页脚。有关如何生成默认页脚以及可以在页脚内使用哪些特殊命令的更多信息，请参阅 HTML_HEADER。有关如何生成 Doxygen 通常使用的默认页脚的信息，另请参阅“Doxygen 使用”部分。
HTML_FOOTER            =

# The HTML_STYLESHEET tag can be used to specify a user-defined cascading style
# sheet that is used by each HTML page. It can be used to fine-tune the look of
# the HTML output. If left blank Doxygen will generate a default style sheet.
# See also section "Doxygen usage" for information on how to generate the style
# sheet that Doxygen normally uses.
# Note: It is recommended to use HTML_EXTRA_STYLESHEET instead of this tag, as
# it is more robust and this tag (HTML_STYLESHEET) will in the future become
# obsolete.
# This tag requires that the tag GENERATE_HTML is set to YES.

# HTML_STYLESHEET 标记可用于指定每个 HTML 页面使用的用户定义级联样式表。它可用于微调 HTML 输出的外观。如果留空，Doxygen 将生成默认样式表。
# 另请参阅“Doxygen 使用”部分，了解如何生成 Doxygen 通常使用的样式表。
# 注意：建议使用 HTML_EXTRA_STYLESHEET 代替此标记，因为它更强大，并且此标记 (HTML_STYLESHEET) 将来会过时。
# 此标记要求将标记 GENERATE_HTML 设置为 YES。
HTML_STYLESHEET        =

# The HTML_EXTRA_STYLESHEET tag can be used to specify additional user-defined
# cascading style sheets that are included after the standard style sheets
# created by Doxygen. Using this option one can overrule certain style aspects.
# This is preferred over using HTML_STYLESHEET since it does not replace the
# standard style sheet and is therefore more robust against future updates.
# Doxygen will copy the style sheet files to the output directory.
# Note: The order of the extra style sheet files is of importance (e.g. the last
# style sheet in the list overrules the setting of the previous ones in the
# list).
# Note: Since the styling of scrollbars can currently not be overruled in
# Webkit/Chromium, the styling will be left out of the default doxygen.css if
# one or more extra stylesheets have been specified. So if scrollbar
# customization is desired it has to be added explicitly. For an example see the
# documentation.
# This tag requires that the tag GENERATE_HTML is set to YES.

# HTML_EXTRA_STYLESHEET 标记可用于指定附加的用户定义级联样式表，这些样式表包含在由 Doxygen 创建的标准样式表之后。使用此选项可以否决某些样式方面。这比使用 HTML_STYLESHEET 更可取，因为它不会替换标准样式表，因此对未来更新更具鲁棒性。Doxygen 会将样式表文件复制到输出目录。
# 注意：附加样式表文件的顺序很重要（例如，列表中的最后一个样式表会否决列表中前一个样式表的设置）。
# 注意：由于目前无法在 Webkit/Chromium 中否决滚动条的样式，因此如果指定了一个或多个附加样式表，样式将排除在默认 doxygen.css 之外。因此，如果需要自定义滚动条，则必须明确添加。有关示例，请参阅文档。
HTML_EXTRA_STYLESHEET  =

# The HTML_EXTRA_FILES tag can be used to specify one or more extra images or
# other source files which should be copied to the HTML output directory. Note
# that these files will be copied to the base HTML output directory. Use the
# $relpath^ marker in the HTML_HEADER and/or HTML_FOOTER files to load these
# files. In the HTML_STYLESHEET file, use the file name only. Also note that the
# files will be copied as-is; there are no commands or markers available.
# This tag requires that the tag GENERATE_HTML is set to YES.

# HTML_EXTRA_FILES 标记可用于指定应复制到 HTML 输出目录的一个或多个额外图像或其他源文件。请注意，这些文件将被复制到基本 HTML 输出目录。使用 HTML_HEADER 和/或 HTML_FOOTER 文件中的 $relpath^ 标记来加载这些文件。在 HTML_STYLESHEET 文件中，仅使用文件名。另请注意，文件将按原样复制；没有可用的命令或标记。
HTML_EXTRA_FILES       =

# The HTML_COLORSTYLE tag can be used to specify if the generated HTML output
# should be rendered with a dark or light theme.
# Possible values are: LIGHT always generates light mode output, DARK always
# generates dark mode output, AUTO_LIGHT automatically sets the mode according
# to the user preference, uses light mode if no preference is set (the default),
# AUTO_DARK automatically sets the mode according to the user preference, uses
# dark mode if no preference is set and TOGGLE allows a user to switch between
# light and dark mode via a button.
# The default value is: AUTO_LIGHT.
# This tag requires that the tag GENERATE_HTML is set to YES.

# HTML_COLORSTYLE 标签可用于指定生成的 HTML 输出是否应使用深色或浅色主题呈现。可能的值包括：LIGHT 始终生成浅色模式输出，DARK 始终生成深色模式输出，AUTO_LIGHT 根据用户偏好自动设置模式，如果未设置偏好则使用浅色模式（默认），AUTO_DARK 根据用户偏好自动设置模式，如果未设置偏好则使用深色模式，TOGGLE 允许用户通过按钮在浅色和深色模式之间切换。
HTML_COLORSTYLE        = AUTO_LIGHT

# The HTML_COLORSTYLE_HUE tag controls the color of the HTML output. Doxygen
# will adjust the colors in the style sheet and background images according to
# this color. Hue is specified as an angle on a color-wheel, see
# https://en.wikipedia.org/wiki/Hue for more information. For instance the value
# 0 represents red, 60 is yellow, 120 is green, 180 is cyan, 240 is blue, 300
# purple, and 360 is red again.
# Minimum value: 0, maximum value: 359, default value: 220.
# This tag requires that the tag GENERATE_HTML is set to YES.

# HTML_COLORSTYLE_HUE 标签控制 HTML 输出的颜色。Doxygen 将根据此颜色调整样式表和背景图像中的颜色。色调指定为色轮上的一个角度，有关更多信息，请参阅 https://en.wikipedia.org/wiki/Hue。例如，值 0 代表红色，60 代表黄色，120 代表绿色，180 代表青色，240 代表蓝色，300 代表紫色，360 代表红色。
# 最小值：0，最大值：359，默认值：220。
# 此标签要求将标签 GENERATE_HTML 设置为 YES。
HTML_COLORSTYLE_HUE    = 220

# The HTML_COLORSTYLE_SAT tag controls the purity (or saturation) of the colors
# in the HTML output. For a value of 0 the output will use gray-scales only. A
# value of 255 will produce the most vivid colors.
# Minimum value: 0, maximum value: 255, default value: 100.
# This tag requires that the tag GENERATE_HTML is set to YES.

# HTML_COLORSTYLE_SAT 标签控制 HTML 输出中颜色的纯度（或饱和度）。值为 0 时，输出将仅使用灰度。值为 255 时将产生最鲜艳的颜色。
# 最小值：0，最大值：255，默认值：100。
# 此标签要求将标签 GENERATE_HTML 设置为 YES。
HTML_COLORSTYLE_SAT    = 100

# The HTML_COLORSTYLE_GAMMA tag controls the gamma correction applied to the
# luminance component of the colors in the HTML output. Values below 100
# gradually make the output lighter, whereas values above 100 make the output
# darker. The value divided by 100 is the actual gamma applied, so 80 represents
# a gamma of 0.8, The value 220 represents a gamma of 2.2, and 100 does not
# change the gamma.
# Minimum value: 40, maximum value: 240, default value: 80.
# This tag requires that the tag GENERATE_HTML is set to YES.

# HTML_COLORSTYLE_GAMMA 标签控制对 HTML 输出中颜色亮度分量应用的伽马校正。低于 100 的值逐渐使输出变亮，而高于 100 的值使输出变暗。该值除以 100 是实际应用的伽马，因此 80 表示伽马为 0.8，值 220 表示伽马为 2.2，而 100 不会改变伽马。
# 最小值：40，最大值：240，默认值：80。
# 此标签要求将标签 GENERATE_HTML 设置为 YES。
HTML_COLORSTYLE_GAMMA  = 80

# If the HTML_DYNAMIC_MENUS tag is set to YES then the generated HTML
# documentation will contain a main index with vertical navigation menus that
# are dynamically created via JavaScript. If disabled, the navigation index will
# consists of multiple levels of tabs that are statically embedded in every HTML
# page. Disable this option to support browsers that do not have JavaScript,
# like the Qt help browser.
# The default value is: YES.
# This tag requires that the tag GENERATE_HTML is set to YES.

# 如果 HTML_DYNAMIC_MENUS 标记设置为 YES，则生成的 HTML 文档将包含一个主索引，其中包含通过 JavaScript 动态创建的垂直导航菜单。如果禁用，导航索引将由静态嵌入每个 HTML 页面的多个级别的选项卡组成。禁用此选项以支持没有 JavaScript 的浏览器，例如 Qt 帮助浏览器。
# 默认值为：YES。
# 此标记要求将标记 GENERATE_HTML 设置为 YES。
HTML_DYNAMIC_MENUS     = YES

# If the HTML_DYNAMIC_SECTIONS tag is set to YES then the generated HTML
# documentation will contain sections that can be hidden and shown after the
# page has loaded.
# The default value is: NO.
# This tag requires that the tag GENERATE_HTML is set to YES.

# 如果 HTML_DYNAMIC_SECTIONS 标签设置为 YES，则生成的 HTML 文档将包含可在页面加载后隐藏和显示的部分。
# 默认值为：NO。
# 此标签要求将标签 GENERATE_HTML 设置为 YES。
HTML_DYNAMIC_SECTIONS  = NO

# If the HTML_CODE_FOLDING tag is set to YES then classes and functions can be
# dynamically folded and expanded in the generated HTML source code.
# The default value is: YES.
# This tag requires that the tag GENERATE_HTML is set to YES.

# 如果将 HTML_CODE_FOLDING 标签设置为 YES，则可以在生成的 HTML 源代码中动态折叠和展开类和函数。
# 默认值为：YES。
# 此标签要求将标签 GENERATE_HTML 设置为 YES。
HTML_CODE_FOLDING      = YES

# If the HTML_COPY_CLIPBOARD tag is set to YES then Doxygen will show an icon in
# the top right corner of code and text fragments that allows the user to copy
# its content to the clipboard. Note this only works if supported by the browser
# and the web page is served via a secure context (see:
# https://www.w3.org/TR/secure-contexts/), i.e. using the https: or file:
# protocol.
# The default value is: YES.
# This tag requires that the tag GENERATE_HTML is set to YES.

# 如果 HTML_COPY_CLIPBOARD 标记设置为 YES，则 Doxygen 将在代码和文本片段的右上角显示一个图标，允许用户将其内容复制到剪贴板。请注意，这仅在浏览器支持且网页通过安全上下文提供时才有效（请参阅：https://www.w3.org/TR/secure-contexts/），即使用 https: 或 file: 协议。
# 默认值为：YES。
# 此标记要求将 GENERATE_HTML 标记设置为 YES。
HTML_COPY_CLIPBOARD    = YES

# Doxygen stores a couple of settings persistently in the browser (via e.g.
# cookies). By default these settings apply to all HTML pages generated by
# Doxygen across all projects. The HTML_PROJECT_COOKIE tag can be used to store
# the settings under a project specific key, such that the user preferences will
# be stored separately.
# This tag requires that the tag GENERATE_HTML is set to YES.

# Doxygen 在浏览器中持久存储一些设置（例如通过 cookie）。默认情况下，这些设置适用于 Doxygen 在所有项目中生成的所有 HTML 页面。HTML_PROJECT_COOKIE 标记可用于将设置存储在项目特定键下，这样用户首选项将被单独存储。
# 此标记要求将标记 GENERATE_HTML 设置为 YES。
HTML_PROJECT_COOKIE    =

# With HTML_INDEX_NUM_ENTRIES one can control the preferred number of entries
# shown in the various tree structured indices initially; the user can expand
# and collapse entries dynamically later on. Doxygen will expand the tree to
# such a level that at most the specified number of entries are visible (unless
# a fully collapsed tree already exceeds this amount). So setting the number of
# entries 1 will produce a full collapsed tree by default. 0 is a special value
# representing an infinite number of entries and will result in a full expanded
# tree by default.
# Minimum value: 0, maximum value: 9999, default value: 100.
# This tag requires that the tag GENERATE_HTML is set to YES.

# 使用 HTML_INDEX_NUM_ENTRIES，可以控制最初在各种树结构索引中显示的首选条目数；用户可以稍后动态展开和折叠条目。Doxygen 将树展开到这样的级别，即最多可以看到指定数量的条目（除非完全折叠的树已经超过此数量）。因此，默认情况下，将条目数设置为 1 将产生一个完全折叠的树。0 是一个特殊值，代表无限数量的条目，默认情况下将产生一个完全展开的树。
# 最小值：0，最大值：9999，默认值：100。
# 此标记要求将标记 GENERATE_HTML 设置为 YES。
HTML_INDEX_NUM_ENTRIES = 100

# If the GENERATE_DOCSET tag is set to YES, additional index files will be
# generated that can be used as input for Apple's Xcode 3 integrated development
# environment (see:
# https://developer.apple.com/xcode/), introduced with OSX 10.5 (Leopard). To
# create a documentation set, Doxygen will generate a Makefile in the HTML
# output directory. Running make will produce the docset in that directory and
# running make install will install the docset in
# ~/Library/Developer/Shared/Documentation/DocSets so that Xcode will find it at
# startup. See https://developer.apple.com/library/archive/featuredarticles/Doxy
# genXcode/_index.html for more information.
# The default value is: NO.
# This tag requires that the tag GENERATE_HTML is set to YES.

# 如果将 GENERATE_DOCSET 标记设置为 YES，则会生成其他索引文件，这些文件可用作 Apple 的 Xcode 3 集成开发环境的输入（请参阅：https://developer.apple.com/xcode/），该环境随 OSX 10.5（Leopard）一起引入。要创建文档集，Doxygen 将在 HTML 输出目录中生成 Makefile。运行 make 将在该目录中生成文档集，运行 make install 将在 ~/Library/Developer/Shared/Documentation/DocSets 中安装文档集，以便 Xcode 在启动时找到它。有关更多信息，请参阅 https://developer.apple.com/library/archive/featuredarticles/Doxy genXcode/_index.html。
# 默认值为：NO。
# 此标记要求将标记 GENERATE_HTML 设置为 YES。
GENERATE_DOCSET        = NO

# This tag determines the name of the docset feed. A documentation feed provides
# an umbrella under which multiple documentation sets from a single provider
# (such as a company or product suite) can be grouped.
# The default value is: Doxygen generated docs.
# This tag requires that the tag GENERATE_DOCSET is set to YES.

# 此标签确定文档集提要的名称。文档提要提供了一个保护伞，可以将来自单个提供商（例如公司或产品套件）的多个文档集分组到该保护伞下。
# 默认值为：Doxygen 生成的文档。
# 此标签要求将标签 GENERATE_DOCSET 设置为 YES。
DOCSET_FEEDNAME        = "Doxygen generated docs"

# This tag determines the URL of the docset feed. A documentation feed provides
# an umbrella under which multiple documentation sets from a single provider
# (such as a company or product suite) can be grouped.
# This tag requires that the tag GENERATE_DOCSET is set to YES.

# 此标签确定文档集提要的 URL。文档提要提供了一个保护伞，可以将来自单个提供商（例如公司或产品套件）的多个文档集分组到该保护伞下。
# 此标签要求将标签 GENERATE_DOCSET 设置为 YES。
DOCSET_FEEDURL         =

# This tag specifies a string that should uniquely identify the documentation
# set bundle. This should be a reverse domain-name style string, e.g.
# com.mycompany.MyDocSet. Doxygen will append .docset to the name.
# The default value is: org.doxygen.Project.
# This tag requires that the tag GENERATE_DOCSET is set to YES.

# 此标记指定一个字符串，该字符串应唯一地标识文档集包。这应该是反向域名样式的字符串，例如 com.mycompany.MyDocSet。Doxygen 将在名称后附加 .docset。
# 默认值为：org.doxygen.Project。
# 此标记要求将标记 GENERATE_DOCSET 设置为 YES。
DOCSET_BUNDLE_ID       = org.doxygen.Project

# The DOCSET_PUBLISHER_ID tag specifies a string that should uniquely identify
# the documentation publisher. This should be a reverse domain-name style
# string, e.g. com.mycompany.MyDocSet.documentation.
# The default value is: org.doxygen.Publisher.
# This tag requires that the tag GENERATE_DOCSET is set to YES.

# DOCSET_PUBLISHER_ID 标记指定一个字符串，该字符串应唯一地标识文档发布者。这应该是反向域名样式的字符串，例如 com.mycompany.MyDocSet.documentation。
# 默认值为：org.doxygen.Publisher。
# 此标记要求将标记 GENERATE_DOCSET 设置为 YES。
DOCSET_PUBLISHER_ID    = org.doxygen.Publisher

# The DOCSET_PUBLISHER_NAME tag identifies the documentation publisher.
# The default value is: Publisher.
# This tag requires that the tag GENERATE_DOCSET is set to YES.

# DOCSET_PUBLISHER_NAME 标签标识文档发布者。
# 默认值为：Publisher。
# 此标签要求将 GENERATE_DOCSET 标签设置为 YES。
DOCSET_PUBLISHER_NAME  = Publisher

# If the GENERATE_HTMLHELP tag is set to YES then Doxygen generates three
# additional HTML index files: index.hhp, index.hhc, and index.hhk. The
# index.hhp is a project file that can be read by Microsoft's HTML Help Workshop
# on Windows. In the beginning of 2021 Microsoft took the original page, with
# a.o. the download links, offline the HTML help workshop was already many years
# in maintenance mode). You can download the HTML help workshop from the web
# archives at Installation executable (see:
# http://web.archive.org/web/20160201063255/http://download.microsoft.com/downlo
# ad/0/A/9/0A939EF6-E31C-430F-A3DF-DFAE7960D564/htmlhelp.exe).
#
# The HTML Help Workshop contains a compiler that can convert all HTML output
# generated by Doxygen into a single compiled HTML file (.chm). Compiled HTML
# files are now used as the Windows 98 help format, and will replace the old
# Windows help format (.hlp) on all Windows platforms in the future. Compressed
# HTML files also contain an index, a table of contents, and you can search for
# words in the documentation. The HTML workshop also contains a viewer for
# compressed HTML files.
# The default value is: NO.
# This tag requires that the tag GENERATE_HTML is set to YES.

# 如果 GENERATE_HTMLHELP 标记设置为 YES，则 Doxygen 会生成三个额外的 HTML 索引文件：index.hhp、index.hhc 和 index.hhk。index.hhp 是一个项目文件，可以由 Windows 上的 Microsoft HTML Help Workshop 读取。2021 年初，Microsoft 将原始页面（包括下载链接）下线，HTML 帮助研讨会已处于维护模式多年。您可以从安装可执行文件的 Web 档案中下载 HTML 帮助研讨会（请参阅：http://web.archive.org/web/20160201063255/http://download.microsoft.com/downlo ad/0/A/9/0A939EF6-E31C-430F-A3DF-DFAE7960D564/htmlhelp.exe）。HTML Help Workshop 包含一个编译器，可以将 Doxygen 生成的所有 HTML 输出转换为单个编译的 HTML 文件 (.chm)。编译后的 HTML 文件现在用作 Windows 98 帮助格式，将来将在所有 Windows 平台上取代旧的 Windows 帮助格式 (.hlp)。压缩的 HTML 文件还包含索引、目录，并且您可以在文档中搜索单词。HTML 工作室还包含压缩 HTML 文件的查看器。
# 默认值为：NO。
# 此标记要求将标记 GENERATE_HTML 设置为 YES。
GENERATE_HTMLHELP      = NO

# The CHM_FILE tag can be used to specify the file name of the resulting .chm
# file. You can add a path in front of the file if the result should not be
# written to the html output directory.
# This tag requires that the tag GENERATE_HTMLHELP is set to YES.

# CHM_FILE 标签可用于指定生成的 .chm 文件的文件名。如果结果不应写入 html 输出目录，您可以在文件前面添加路径。
# 此标签要求将标签 GENERATE_HTMLHELP 设置为 YES。
CHM_FILE               =

# The HHC_LOCATION tag can be used to specify the location (absolute path
# including file name) of the HTML help compiler (hhc.exe). If non-empty,
# Doxygen will try to run the HTML help compiler on the generated index.hhp.
# The file has to be specified with full path.
# This tag requires that the tag GENERATE_HTMLHELP is set to YES.

# HHC_LOCATION 标签可用于指定 HTML 帮助编译器 (hhc.exe) 的位置（包括文件名的绝对路径）。如果不为空，Doxygen 将尝试在生成的 index.hhp 上运行 HTML 帮助编译器。
# 必须指定文件的完整路径。
# 此标签要求将标签 GENERATE_HTMLHELP 设置为 YES。
HHC_LOCATION           =

# The GENERATE_CHI flag controls if a separate .chi index file is generated
# (YES) or that it should be included in the main .chm file (NO).
# The default value is: NO.
# This tag requires that the tag GENERATE_HTMLHELP is set to YES.

# GENERATE_CHI 标志控制是否生成单独的 .chi 索引文件（YES）或是否应将其包含在主 .chm 文件中（NO）。
# 默认值为：NO。
# 此标记要求将标记 GENERATE_HTMLHELP 设置为 YES。
GENERATE_CHI           = NO

# The CHM_INDEX_ENCODING is used to encode HtmlHelp index (hhk), content (hhc)
# and project file content.
# This tag requires that the tag GENERATE_HTMLHELP is set to YES.

# CHM_INDEX_ENCODING 用于对 HtmlHelp 索引 (hhk)、内容 (hhc) 和项目文件内容进行编码。
# 此标签要求将标签 GENERATE_HTMLHELP 设置为 YES。
CHM_INDEX_ENCODING     = 

# The BINARY_TOC flag controls whether a binary table of contents is generated
# (YES) or a normal table of contents (NO) in the .chm file. Furthermore it
# enables the Previous and Next buttons.
# The default value is: NO.
# This tag requires that the tag GENERATE_HTMLHELP is set to YES.

# BINARY_TOC 标志控制在 .chm 文件中是否生成二进制目录（YES）或普通目录（NO）。此外，它启用上一个和下一个按钮。
# 默认值为：NO。
# 此标记要求将标记 GENERATE_HTMLHELP 设置为 YES。
BINARY_TOC             = NO

# The TOC_EXPAND flag can be set to YES to add extra items for group members to
# the table of contents of the HTML help documentation and to the tree view.
# The default value is: NO.
# This tag requires that the tag GENERATE_HTMLHELP is set to YES.

# TOC_EXPAND 标志可以设置为 YES，以便将组成员的额外项目添加到 HTML 帮助文档的目录和树视图中。
# 在 Doxygen 中，TOC_EXPAND 配置选项用于控制生成的 HTML 文档中的目录（Table of Contents，简称 TOC）是否默认展开。这个选项影响 HTML 输出文档的用户导航体验，尤其是在文档包含多个层次的内容时。
# 默认值为：NO。
# 此标记要求将标记 GENERATE_HTMLHELP 设置为 YES。
TOC_EXPAND             = NO

# The SITEMAP_URL tag is used to specify the full URL of the place where the
# generated documentation will be placed on the server by the user during the
# deployment of the documentation. The generated sitemap is called sitemap.xml
# and placed on the directory specified by HTML_OUTPUT. In case no SITEMAP_URL
# is specified no sitemap is generated. For information about the sitemap
# protocol see https://www.sitemaps.org
# This tag requires that the tag GENERATE_HTML is set to YES.

# SITEMAP_URL 标签用于指定用户在部署文档期间将生成的文档放置在服务器上的位置的完整 URL。生成的站点地图称为 sitemap.xml，并放置在 HTML_OUTPUT 指定的目录中。如果没有指定 SITEMAP_URL，则不会生成站点地图。有关站点地图协议的信息，请参阅 https://www.sitemaps.org
# 此标签要求将 GENERATE_HTML 设置为 YES。
SITEMAP_URL            =

# If the GENERATE_QHP tag is set to YES and both QHP_NAMESPACE and
# QHP_VIRTUAL_FOLDER are set, an additional index file will be generated that
# can be used as input for Qt's qhelpgenerator to generate a Qt Compressed Help
# (.qch) of the generated HTML documentation.
# The default value is: NO.
# This tag requires that the tag GENERATE_HTML is set to YES.

# 如果将 GENERATE_QHP 标记设置为 YES，并且同时设置了 QHP_NAMESPACE 和 QHP_VIRTUAL_FOLDER，则会生成一个附加索引文件，该文件可用作 Qt 的 qhelpgenerator 的输入，以生成生成的 HTML 文档的 Qt 压缩帮助 (.qch)。
# 默认值为：NO。
# 此标记要求将 GENERATE_HTML 标记设置为 YES。
GENERATE_QHP           = NO

# If the QHG_LOCATION tag is specified, the QCH_FILE tag can be used to specify
# the file name of the resulting .qch file. The path specified is relative to
# the HTML output folder.
# This tag requires that the tag GENERATE_QHP is set to YES.

# 如果指定了 QHG_LOCATION 标签，则可以使用 QCH_FILE 标签指定生成的 .qch 文件的文件名。指定的路径相对于 HTML 输出文件夹。
# 此标签要求将标签 GENERATE_QHP 设置为 YES。
QCH_FILE               =

# The QHP_NAMESPACE tag specifies the namespace to use when generating Qt Help
# Project output. For more information please see Qt Help Project / Namespace
# (see:
# https://doc.qt.io/archives/qt-4.8/qthelpproject.html#namespace).
# The default value is: org.doxygen.Project.
# This tag requires that the tag GENERATE_QHP is set to YES.

# QHP_NAMESPACE 标签指定生成 Qt Help Project 输出时要使用的命名空间。有关更多信息，请参阅 Qt Help Project / Namespace（参见：https://doc.qt.io/archives/qt-4.8/qthelpproject.html#namespace）。
# 默认值为：org.doxygen.Project。
# 此标签要求将标签 GENERATE_QHP 设置为 YES。
QHP_NAMESPACE          = org.doxygen.Project

# The QHP_VIRTUAL_FOLDER tag specifies the namespace to use when generating Qt
# Help Project output. For more information please see Qt Help Project / Virtual
# Folders (see:
# https://doc.qt.io/archives/qt-4.8/qthelpproject.html#virtual-folders).
# The default value is: doc.
# This tag requires that the tag GENERATE_QHP is set to YES.

# QHP_VIRTUAL_FOLDER 标签指定生成 Qt Help Project 输出时要使用的命名空间。有关更多信息，请参阅 Qt Help Project / Virtual Folders（参见：https://doc.qt.io/archives/qt-4.8/qthelpproject.html#virtual-folders）。
# 默认值为：doc。
# 此标签要求将标签 GENERATE_QHP 设置为 YES。
QHP_VIRTUAL_FOLDER     = doc

# If the QHP_CUST_FILTER_NAME tag is set, it specifies the name of a custom
# filter to add. For more information please see Qt Help Project / Custom
# Filters (see:
# https://doc.qt.io/archives/qt-4.8/qthelpproject.html#custom-filters).
# This tag requires that the tag GENERATE_QHP is set to YES.

# 如果设置了 QHP_CUST_FILTER_NAME 标签，则指定要添加的自定义过滤器的名称。有关更多信息，请参阅 Qt 帮助项目/自定义过滤器（参见：https://doc.qt.io/archives/qt-4.8/qthelpproject.html#custom-filters）。
# 此标签要求将标签 GENERATE_QHP 设置为 YES。
QHP_CUST_FILTER_NAME   =

# The QHP_CUST_FILTER_ATTRS tag specifies the list of the attributes of the
# custom filter to add. For more information please see Qt Help Project / Custom
# Filters (see:
# https://doc.qt.io/archives/qt-4.8/qthelpproject.html#custom-filters).
# This tag requires that the tag GENERATE_QHP is set to YES.

# QHP_CUST_FILTER_ATTRS 标签指定要添加的自定义过滤器的属性列表。有关更多信息，请参阅 Qt 帮助项目/自定义过滤器（参见：https://doc.qt.io/archives/qt-4.8/qthelpproject.html#custom-filters）。
# 此标签要求将标签 GENERATE_QHP 设置为 YES。
QHP_CUST_FILTER_ATTRS  =

# The QHP_SECT_FILTER_ATTRS tag specifies the list of the attributes this
# project's filter section matches. Qt Help Project / Filter Attributes (see:
# https://doc.qt.io/archives/qt-4.8/qthelpproject.html#filter-attributes).
# This tag requires that the tag GENERATE_QHP is set to YES.

# QHP_SECT_FILTER_ATTRS 标签指定此项目的过滤器部分匹配的属性列表。Qt 帮助项目/过滤器属性（参见：https://doc.qt.io/archives/qt-4.8/qthelpproject.html#filter-attributes）。
# 此标签要求将标签 GENERATE_QHP 设置为 YES。
QHP_SECT_FILTER_ATTRS  =

# The QHG_LOCATION tag can be used to specify the location (absolute path
# including file name) of Qt's qhelpgenerator. If non-empty Doxygen will try to
# run qhelpgenerator on the generated .qhp file.
# This tag requires that the tag GENERATE_QHP is set to YES.

# QHG_LOCATION 标签可用于指定 Qt 的 qhelpgenerator 的位置（包括文件名的绝对路径）。如果非空，Doxygen 将尝试在生成的 .qhp 文件上运行 qhelpgenerator。
# 此标签要求将标签 GENERATE_QHP 设置为 YES。
QHG_LOCATION           =

# If the GENERATE_ECLIPSEHELP tag is set to YES, additional index files will be
# generated, together with the HTML files, they form an Eclipse help plugin. To
# install this plugin and make it available under the help contents menu in
# Eclipse, the contents of the directory containing the HTML and XML files needs
# to be copied into the plugins directory of eclipse. The name of the directory
# within the plugins directory should be the same as the ECLIPSE_DOC_ID value.
# After copying Eclipse needs to be restarted before the help appears.
# The default value is: NO.
# This tag requires that the tag GENERATE_HTML is set to YES.

# 如果将 GENERATE_ECLIPSEHELP 标记设置为 YES，则会生成附加索引文件，它们与 HTML 文件一起构成 Eclipse 帮助插件。要安装此插件并使其在 Eclipse 中的帮助内容菜单下可用，需要将包含 HTML 和 XML 文件的目录的内容复制到 eclipse 的插件目录中。插件目录中的目录名称应与 ECLIPSE_DOC_ID 值相同。复制后，需要重新启动 Eclipse 才能显示帮助。
# 默认值为：NO。
# 此标记要求将 GENERATE_HTML 标记设置为 YES。
GENERATE_ECLIPSEHELP   = NO

# A unique identifier for the Eclipse help plugin. When installing the plugin
# the directory name containing the HTML and XML files should also have this
# name. Each documentation set should have its own identifier.
# The default value is: org.doxygen.Project.
# This tag requires that the tag GENERATE_ECLIPSEHELP is set to YES.

# Eclipse 帮助插件的唯一标识符。安装插件时，包含 HTML 和 XML 文件的目录名称也应具有此名称。每个文档集都应有自己的标识符。
# 默认值为：org.doxygen.Project。
# 此标记要求将标记 GENERATE_ECLIPSEHELP 设置为 YES。
ECLIPSE_DOC_ID         = org.doxygen.Project

# If you want full control over the layout of the generated HTML pages it might
# be necessary to disable the index and replace it with your own. The
# DISABLE_INDEX tag can be used to turn on/off the condensed index (tabs) at top
# of each HTML page. A value of NO enables the index and the value YES disables
# it. Since the tabs in the index contain the same information as the navigation
# tree, you can set this option to YES if you also set GENERATE_TREEVIEW to YES.
# The default value is: NO.
# This tag requires that the tag GENERATE_HTML is set to YES.

# 如果您想要完全控制生成的 HTML 页面的布局，可能需要禁用索引并将其替换为您自己的索引。DISABLE_INDEX 标记可用于打开/关闭每个 HTML 页面顶部的压缩索引（选项卡）。值为 NO 启用索引，值为 YES 禁用索引。由于索引中的选项卡包含与导航树相同的信息，因此如果您还将 GENERATE_TREEVIEW 设置为 YES，则可以将此选项设置为 YES。
# 默认值为：NO。
# 此标记要求将标记 GENERATE_HTML 设置为 YES。
DISABLE_INDEX          = NO

# The GENERATE_TREEVIEW tag is used to specify whether a tree-like index
# structure should be generated to display hierarchical information. If the tag
# value is set to YES, a side panel will be generated containing a tree-like
# index structure (just like the one that is generated for HTML Help). For this
# to work a browser that supports JavaScript, DHTML, CSS and frames is required
# (i.e. any modern browser). Windows users are probably better off using the
# HTML help feature. Via custom style sheets (see HTML_EXTRA_STYLESHEET) one can
# further fine tune the look of the index (see "Fine-tuning the output"). As an
# example, the default style sheet generated by Doxygen has an example that
# shows how to put an image at the root of the tree instead of the PROJECT_NAME.
# Since the tree basically has the same information as the tab index, you could
# consider setting DISABLE_INDEX to YES when enabling this option.
# The default value is: NO.
# This tag requires that the tag GENERATE_HTML is set to YES.

# GENERATE_TREEVIEW 标记用于指定是否应生成树状索引结构以显示层次结构信息。如果将标记值设置为 YES，则会生成一个包含树状索引结构的侧面板（就像为 HTML 帮助生成的侧面板一样）。要实现此功能，需要使用支持 JavaScript、DHTML、CSS 和框架的浏览器（即任何现代浏览器）。Windows 用户最好使用 HTML 帮助功能。通过自定义样式表（请参阅 HTML_EXTRA_STYLESHEET），可以进一步微调索引的外观（请参阅“微调输出”）。例如，Doxygen 生成的默认样式表有一个示例，展示了如何将图像放在树的根部而不是 PROJECT_NAME。由于树基本上具有与选项卡索引相同的信息，因此在启用此选项时，您可以考虑将 DISABLE_INDEX 设置为 YES。
# 默认值为：NO。
# 此标签要求将标签 GENERATE_HTML 设置为 YES。
GENERATE_TREEVIEW      = NO

# When both GENERATE_TREEVIEW and DISABLE_INDEX are set to YES, then the
# FULL_SIDEBAR option determines if the side bar is limited to only the treeview
# area (value NO) or if it should extend to the full height of the window (value
# YES). Setting this to YES gives a layout similar to
# https://docs.readthedocs.io with more room for contents, but less room for the
# project logo, title, and description. If either GENERATE_TREEVIEW or
# DISABLE_INDEX is set to NO, this option has no effect.
# The default value is: NO.
# This tag requires that the tag GENERATE_HTML is set to YES.

# 当 GENERATE_TREEVIEW 和 DISABLE_INDEX 都设置为 YES 时，FULL_SIDEBAR 选项将确定侧边栏是否仅限于树形视图区域（值 NO）或者是否应扩展到窗口的整个高度（值 YES）。将其设置为 YES 可提供类似于 https://docs.readthedocs.io 的布局，内容空间更大，但项目徽标、标题和说明的空间更小。如果 GENERATE_TREEVIEW 或 DISABLE_INDEX 设置为 NO，则此选项无效。
# 默认值为：NO。
# 此标记要求将标记 GENERATE_HTML 设置为 YES。
FULL_SIDEBAR           = NO

# The ENUM_VALUES_PER_LINE tag can be used to set the number of enum values that
# Doxygen will group on one line in the generated HTML documentation.
#
# Note that a value of 0 will completely suppress the enum values from appearing
# in the overview section.
# Minimum value: 0, maximum value: 20, default value: 4.
# This tag requires that the tag GENERATE_HTML is set to YES.

# ENUM_VALUES_PER_LINE 标签可用于设置 Doxygen 在生成的 HTML 文档中一行上分组的枚举值的数量。
#
# 请注意，值为 0 将完全禁止枚举值出现在概述部分中。
# 最小值：0，最大值：20，默认值：4。
# 此标签要求将标签 GENERATE_HTML 设置为 YES。
ENUM_VALUES_PER_LINE   = 4

# When the SHOW_ENUM_VALUES tag is set doxygen will show the specified
# enumeration values besides the enumeration mnemonics.
# The default value is: NO.

# 当设置了SHOW_ENUM_VALUES标签时，doxygen将在枚举助记符旁边显示指定的枚举值。
# 默认值为：NO。
SHOW_ENUM_VALUES       = NO

# If the treeview is enabled (see GENERATE_TREEVIEW) then this tag can be used
# to set the initial width (in pixels) of the frame in which the tree is shown.
# Minimum value: 0, maximum value: 1500, default value: 250.
# This tag requires that the tag GENERATE_HTML is set to YES.

# 如果启用了树形视图（参见 GENERATE_TREEVIEW），则此标记可用于设置显示树的框架的初始宽度（以像素为单位）。
# 最小值：0，最大值：1500，默认值：250。
# 此标记要求将标记 GENERATE_HTML 设置为 YES。
TREEVIEW_WIDTH         = 250

# If the EXT_LINKS_IN_WINDOW option is set to YES, Doxygen will open links to
# external symbols imported via tag files in a separate window.
# The default value is: NO.
# This tag requires that the tag GENERATE_HTML is set to YES.

# 如果 EXT_LINKS_IN_WINDOW 选项设置为 YES，Doxygen 将在单独的窗口中打开通过标记文件导入的外部符号的链接。
# 默认值为：NO。
# 此标记要求将标记 GENERATE_HTML 设置为 YES。
EXT_LINKS_IN_WINDOW    = NO

# If the OBFUSCATE_EMAILS tag is set to YES, Doxygen will obfuscate email
# addresses.
# The default value is: YES.
# This tag requires that the tag GENERATE_HTML is set to YES.

# 如果 OBFUSCATE_EMAILS 标签设置为 YES，Doxygen 将混淆电子邮件地址。
# 默认值为：YES。
# 此标签要求将 GENERATE_HTML 标签设置为 YES。
OBFUSCATE_EMAILS       = YES

# If the HTML_FORMULA_FORMAT option is set to svg, Doxygen will use the pdf2svg
# tool (see https://github.com/dawbarton/pdf2svg) or inkscape (see
# https://inkscape.org) to generate formulas as SVG images instead of PNGs for
# the HTML output. These images will generally look nicer at scaled resolutions.
# Possible values are: png (the default) and svg (looks nicer but requires the
# pdf2svg or inkscape tool).
# The default value is: png.
# This tag requires that the tag GENERATE_HTML is set to YES.

# 如果 HTML_FORMULA_FORMAT 选项设置为 svg，Doxygen 将使用 pdf2svg 工具（请参阅 https://github.com/dawbarton/pdf2svg）或 inkscape（请参阅 https://inkscape.org）将公式生成为 SVG 图像，而不是 PNG，用于 HTML 输出。这些图像在缩放分辨率下通常看起来更美观。可能的值是：png（默认值）和 svg（看起来更美观，但需要 pdf2svg 或 inkscape 工具）。
# 默认值为：png。
# 此标记要求将标记 GENERATE_HTML 设置为 YES。
HTML_FORMULA_FORMAT    = png

# Use this tag to change the font size of LaTeX formulas included as images in
# the HTML documentation. When you change the font size after a successful
# Doxygen run you need to manually remove any form_*.png images from the HTML
# output directory to force them to be regenerated.
# Minimum value: 8, maximum value: 50, default value: 10.
# This tag requires that the tag GENERATE_HTML is set to YES.

# 使用此标签更改 HTML 文档中作为图像包含的 LaTeX 公式的字体大小。在成功运行 Doxygen 后更改字体大小时，您需要手动从 HTML 输出目录中删除任何 form_*.png 图像以强制重新生成它们。
# 最小值：8，最大值：50，默认值：10。
# 此标签要求将标签 GENERATE_HTML 设置为 YES。
FORMULA_FONTSIZE       = 10

# The FORMULA_MACROFILE can contain LaTeX \newcommand and \renewcommand commands
# to create new LaTeX commands to be used in formulas as building blocks. See
# the section "Including formulas" for details.

# FORMULA_MACROFILE 可以包含 LaTeX \newcommand 和 \renewcommand 命令，以创建新的 LaTeX 命令，作为公式中的构建块使用。有关详细信息，请参阅“包含公式”部分。
FORMULA_MACROFILE      =

# Enable the USE_MATHJAX option to render LaTeX formulas using MathJax (see
# https://www.mathjax.org) which uses client side JavaScript for the rendering
# instead of using pre-rendered bitmaps. Use this if you do not have LaTeX
# installed or if you want to formulas look prettier in the HTML output. When
# enabled you may also need to install MathJax separately and configure the path
# to it using the MATHJAX_RELPATH option.
# The default value is: NO.
# This tag requires that the tag GENERATE_HTML is set to YES.

# 启用 USE_MATHJAX 选项以使用 MathJax 呈现 LaTeX 公式（请参阅 https://www.mathjax.org），它使用客户端 JavaScript 进行呈现，而不是使用预渲染的位图。如果您未安装 LaTeX，或者希望公式在 HTML 输出中看起来更漂亮，请使用此选项。启用后，您可能还需要单独安装 MathJax 并使用 MATHJAX_RELPATH 选项配置其路径。
# 默认值为：NO。
# 此标记要求将标记 GENERATE_HTML 设置为 YES。
USE_MATHJAX            = NO

# With MATHJAX_VERSION it is possible to specify the MathJax version to be used.
# Note that the different versions of MathJax have different requirements with
# regards to the different settings, so it is possible that also other MathJax
# settings have to be changed when switching between the different MathJax
# versions.
# Possible values are: MathJax_2 and MathJax_3.
# The default value is: MathJax_2.
# This tag requires that the tag USE_MATHJAX is set to YES.

# 使用 MATHJAX_VERSION 可以指定要使用的 MathJax 版本。请注意，不同版本的 MathJax 对不同设置有不同的要求，因此在不同的 MathJax 版本之间切换时，可能还需要更改其他 MathJax 设置。
# 可能的值是：MathJax_2 和 MathJax_3。
# 默认值为：MathJax_2。
# 此标签要求将标签 USE_MATHJAX 设置为 YES。
MATHJAX_VERSION        = MathJax_2

# When MathJax is enabled you can set the default output format to be used for
# the MathJax output. For more details about the output format see MathJax
# version 2 (see:
# http://docs.mathjax.org/en/v2.7-latest/output.html) and MathJax version 3
# (see:
# http://docs.mathjax.org/en/latest/web/components/output.html).
# Possible values are: HTML-CSS (which is slower, but has the best
# compatibility. This is the name for Mathjax version 2, for MathJax version 3
# this will be translated into chtml), NativeMML (i.e. MathML. Only supported
# for MathJax 2. For MathJax version 3 chtml will be used instead.), chtml (This
# is the name for Mathjax version 3, for MathJax version 2 this will be
# translated into HTML-CSS) and SVG.
# The default value is: HTML-CSS.
# This tag requires that the tag USE_MATHJAX is set to YES.

# 启用 MathJax 后，您可以设置 MathJax 输出的默认输出格式。有关输出格式的更多详细信息，请参阅 MathJax 版本 2（请参阅：
# http://docs.mathjax.org/en/v2.7-latest/output.html）和 MathJax 版本 3（请参阅：http://docs.mathjax.org/en/latest/web/components/output.html）。可能的值包括：HTML-CSS（速度较慢，但​​兼容性最佳。这是 Mathjax 版本 2 的名称，对于 MathJax 版本 3，它将被翻译成 chtml）、NativeMML（即 MathML。仅支持 MathJax 2。对于 MathJax 版本 3，将改用 chtml。）、chtml（这是 Mathjax 版本 3 的名称，对于 MathJax 版本 2，它将被翻译成 HTML-CSS）和 SVG。
# 默认值为：HTML-CSS。
# 此标签要求将标签USE_MATHJAX设置为YES。
MATHJAX_FORMAT         = HTML-CSS

# When MathJax is enabled you need to specify the location relative to the HTML
# output directory using the MATHJAX_RELPATH option. The destination directory
# should contain the MathJax.js script. For instance, if the mathjax directory
# is located at the same level as the HTML output directory, then
# MATHJAX_RELPATH should be ../mathjax. The default value points to the MathJax
# Content Delivery Network so you can quickly see the result without installing
# MathJax. However, it is strongly recommended to install a local copy of
# MathJax from https://www.mathjax.org before deployment. The default value is:
# - in case of MathJax version 2: https://cdn.jsdelivr.net/npm/mathjax@2
# - in case of MathJax version 3: https://cdn.jsdelivr.net/npm/mathjax@3
# This tag requires that the tag USE_MATHJAX is set to YES.

# 启用 MathJax 后，您需要使用 MATHJAX_RELPATH 选项指定相对于 HTML 输出目录的位置。目标目录应包含 MathJax.js 脚本。例如，如果 mathjax 目录与 HTML 输出目录位于同一级别，则 MATHJAX_RELPATH 应为 ../mathjax。默认值指向 MathJax 内容交付网络，因此您无需安装 MathJax 即可快速查看结果。但是，强烈建议在部署之前从 https://www.mathjax.org 安装 MathJax 的本地副本。默认值为：
# - 对于 MathJax 版本 2：https://cdn.jsdelivr.net/npm/mathjax@2
# - 对于 MathJax 版本 3：https://cdn.jsdelivr.net/npm/mathjax@3
# 此标记要求将标记 USE_MATHJAX 设置为 YES。
MATHJAX_RELPATH        =

# The MATHJAX_EXTENSIONS tag can be used to specify one or more MathJax
# extension names that should be enabled during MathJax rendering. For example
# for MathJax version 2 (see
# https://docs.mathjax.org/en/v2.7-latest/tex.html#tex-and-latex-extensions):
# MATHJAX_EXTENSIONS = TeX/AMSmath TeX/AMSsymbols
# For example for MathJax version 3 (see
# http://docs.mathjax.org/en/latest/input/tex/extensions/index.html):
# MATHJAX_EXTENSIONS = ams
# This tag requires that the tag USE_MATHJAX is set to YES.

# The MATHJAX_EXTENSIONS tag can be used to specify one or more MathJax
# extension names that should be enabled during MathJax rendering. For example
# for MathJax version 2 (see
# https://docs.mathjax.org/en/v2.7-latest/tex.html#tex-and-latex-extensions):
# MATHJAX_EXTENSIONS = TeX/AMSmath TeX/AMSsymbols
# For example for MathJax version 3 (see
# http://docs.mathjax.org/en/latest/input/tex/extensions/index.html):
# MATHJAX_EXTENSIONS = ams
# This tag requires that the tag USE_MATHJAX is set to YES.

# MATHJAX_EXTENSIONS 标签可用于指定在 MathJax 渲染期间应启用的一个或多个 MathJax 扩展名。例如，对于 MathJax 版本 2（请参阅 https://docs.mathjax.org/en/v2.7-latest/tex.html#tex-and-latex-extensions）：MATHJAX_EXTENSIONS = TeX/AMSmath TeX/AMSsymbols 例如，对于 MathJax 版本 3（请参阅 http://docs.mathjax.org/en/latest/input/tex/extensions/index.html）：MATHJAX_EXTENSIONS = ams 此标签要求将标签 USE_MATHJAX 设置为 YES。

# MATHJAX_EXTENSIONS 标签可用于指定在 MathJax 渲染期间应启用的一个或多个 MathJax 扩展名。例如，对于 MathJax 版本 2（请参阅 https://docs.mathjax.org/en/v2.7-latest/tex.html#tex-and-latex-extensions）：MATHJAX_EXTENSIONS = TeX/AMSmath TeX/AMSsymbols 例如，对于 MathJax 版本 3（请参阅 http://docs.mathjax.org/en/latest/input/tex/extensions/index.html）：MATHJAX_EXTENSIONS = ams 此标签要求将标签 USE_MATHJAX 设置为 YES。
MATHJAX_EXTENSIONS     =

# The MATHJAX_CODEFILE tag can be used to specify a file with JavaScript pieces
# of code that will be used on startup of the MathJax code. See the MathJax site
# (see:
# http://docs.mathjax.org/en/v2.7-latest/output.html) for more details. For an
# example see the documentation.
# This tag requires that the tag USE_MATHJAX is set to YES.

# MATHJAX_CODEFILE 标签可用于指定一个文件，其中包含将在启动 MathJax 代码时使用的 JavaScript 代码片段。有关更多详细信息，请参阅 MathJax 网站（参见：http://docs.mathjax.org/en/v2.7-latest/output.html）。有关示例，请参阅文档。
# 此标签要求将标签 USE_MATHJAX 设置为 YES。
MATHJAX_CODEFILE       =

# When the SEARCHENGINE tag is enabled Doxygen will generate a search box for
# the HTML output. The underlying search engine uses JavaScript and DHTML and
# should work on any modern browser. Note that when using HTML help
# (GENERATE_HTMLHELP), Qt help (GENERATE_QHP), or docsets (GENERATE_DOCSET)
# there is already a search function so this one should typically be disabled.
# For large projects the JavaScript based search engine can be slow, then
# enabling SERVER_BASED_SEARCH may provide a better solution. It is possible to
# search using the keyboard; to jump to the search box use <access key> + S
# (what the <access key> is depends on the OS and browser, but it is typically
# <CTRL>, <ALT>/<option>, or both). Inside the search box use the <cursor down
# key> to jump into the search results window, the results can be navigated
# using the <cursor keys>. Press <Enter> to select an item or <escape> to cancel
# the search. The filter options can be selected when the cursor is inside the
# search box by pressing <Shift>+<cursor down>. Also here use the <cursor keys>
# to select a filter and <Enter> or <escape> to activate or cancel the filter
# option.
# The default value is: YES.
# This tag requires that the tag GENERATE_HTML is set to YES.

# 启用 SEARCHENGINE 标记后，Doxygen 将为 HTML 输出生成一个搜索框。底层搜索引擎使用 JavaScript 和 DHTML，可在任何现代浏览器上运行。请注意，使用 HTML 帮助 (GENERATE_HTMLHELP)、Qt 帮助 (GENERATE_QHP) 或文档集 (GENERATE_DOCSET) 时，已经有一个搜索功能，因此通常应禁用此功能。对于大型项目，基于 JavaScript 的搜索引擎可能会很慢，然后启用 SERVER_BASED_SEARCH 可能会提供更好的解决方案。可以使用键盘进行搜索；要跳转到搜索框，请使用 <access key> + S（<access key> 是什么取决于操作系统和浏览器，但通常是 <CTRL>、<ALT>/<option> 或两者）。在搜索框内，使用 <cursor down key> 跳转到搜索结果窗口，可以使用 <cursor keys> 浏览结果。按 <Enter> 选择一个项目或按 <escape> 取消搜索。当光标位于搜索框内时，可以通过按 <Shift>+<光标向下> 来选择过滤选项。同样，在这里使用 <光标键> 选择过滤器，然后按 <Enter> 或 <escape> 激活或取消过滤选项。
# 默认值为：YES。
# 此标签要求将标签 GENERATE_HTML 设置为 YES。
SEARCHENGINE           = YES

# When the SERVER_BASED_SEARCH tag is enabled the search engine will be
# implemented using a web server instead of a web client using JavaScript. There
# are two flavors of web server based searching depending on the EXTERNAL_SEARCH
# setting. When disabled, Doxygen will generate a PHP script for searching and
# an index file used by the script. When EXTERNAL_SEARCH is enabled the indexing
# and searching needs to be provided by external tools. See the section
# "External Indexing and Searching" for details.
# The default value is: NO.
# This tag requires that the tag SEARCHENGINE is set to YES.

# 启用 SERVER_BASED_SEARCH 标记后，搜索引擎将使用 Web 服务器而不是使用 JavaScript 的 Web 客户端来实现。根据 EXTERNAL_SEARCH 设置，有两种基于 Web 服务器的搜索方式。禁用时，Doxygen 将生成用于搜索的 PHP 脚本和该脚本使用的索引文件。启用 EXTERNAL_SEARCH 后，索引和搜索需要由外部工具提供。有关详细信息，请参阅“外部索引和搜索”部分。
# 默认值为：NO。
# 此标记要求将标记 SEARCHENGINE 设置为 YES。
SERVER_BASED_SEARCH    = NO

# When EXTERNAL_SEARCH tag is enabled Doxygen will no longer generate the PHP
# script for searching. Instead the search results are written to an XML file
# which needs to be processed by an external indexer. Doxygen will invoke an
# external search engine pointed to by the SEARCHENGINE_URL option to obtain the
# search results.
#
# Doxygen ships with an example indexer (doxyindexer) and search engine
# (doxysearch.cgi) which are based on the open source search engine library
# Xapian (see:
# https://xapian.org/).
#
# See the section "External Indexing and Searching" for details.
# The default value is: NO.
# This tag requires that the tag SEARCHENGINE is set to YES.

# 当 EXTERNAL_SEARCH 标记启用时，Doxygen 将不再生成用于搜索的 PHP 脚本。相反，搜索结果将写入需要由外部索引器处理的 XML 文件。Doxygen 将调用 SEARCHENGINE_URL 选项指向的外部搜索引擎来获取搜索结果。
#
# Doxygen 附带一个示例索引器 (doxyindexer) 和搜索引擎 (doxysearch.cgi)，它们基于开源搜索引擎库 Xapian（请参阅：https://xapian.org/）。
# 有关详细信息，请参阅“外部索引和搜索”部分。
# 默认值为：NO。
# 此标记要求将标记 SEARCHENGINE 设置为 YES。
EXTERNAL_SEARCH        = NO

# The SEARCHENGINE_URL should point to a search engine hosted by a web server
# which will return the search results when EXTERNAL_SEARCH is enabled.
#
# Doxygen ships with an example indexer (doxyindexer) and search engine
# (doxysearch.cgi) which are based on the open source search engine library
# Xapian (see:
# https://xapian.org/). See the section "External Indexing and Searching" for
# details.
# This tag requires that the tag SEARCHENGINE is set to YES.

# SEARCHENGINE_URL 应指向由 Web 服务器托管的搜索引擎，当启用 EXTERNAL_SEARCH 时，该搜索引擎将返回搜索结果。
#
# Doxygen 附带一个示例索引器 (doxyindexer) 和搜索引擎 (doxysearch.cgi)，它们基于开源搜索引擎库 Xapian（请参阅：https://xapian.org/）。有关详细信息，请参阅“外部索引和搜索”部分。
# 此标记要求将标记 SEARCHENGINE 设置为 YES。
SEARCHENGINE_URL       =

# When SERVER_BASED_SEARCH and EXTERNAL_SEARCH are both enabled the unindexed
# search data is written to a file for indexing by an external tool. With the
# SEARCHDATA_FILE tag the name of this file can be specified.
# The default file is: searchdata.xml.
# This tag requires that the tag SEARCHENGINE is set to YES.

# 当 SERVER_BASED_SEARCH 和 EXTERNAL_SEARCH 都启用时，未编入索引的搜索数据将写入文件，以供外部工具编入索引。使用 SEARCHDATA_FILE 标记可以指定此文件的名称。
# 默认文件为：searchdata.xml。
# 此标记要求将标记 SEARCHENGINE 设置为 YES。
SEARCHDATA_FILE        = searchdata.xml

# When SERVER_BASED_SEARCH and EXTERNAL_SEARCH are both enabled the
# EXTERNAL_SEARCH_ID tag can be used as an identifier for the project. This is
# useful in combination with EXTRA_SEARCH_MAPPINGS to search through multiple
# projects and redirect the results back to the right project.
# This tag requires that the tag SEARCHENGINE is set to YES.

# 当 SERVER_BASED_SEARCH 和 EXTERNAL_SEARCH 都启用时，EXTERNAL_SEARCH_ID 标记可用作项目的标识符。这与 EXTRA_SEARCH_MAPPINGS 结合使用非常有用，可以搜索多个项目并将结果重定向回正确的项目。
# 此标记要求将标记 SEARCHENGINE 设置为 YES。
EXTERNAL_SEARCH_ID     =

# The EXTRA_SEARCH_MAPPINGS tag can be used to enable searching through Doxygen
# projects other than the one defined by this configuration file, but that are
# all added to the same external search index. Each project needs to have a
# unique id set via EXTERNAL_SEARCH_ID. The search mapping then maps the id of
# to a relative location where the documentation can be found. The format is:
# EXTRA_SEARCH_MAPPINGS = tagname1=loc1 tagname2=loc2 ...
# This tag requires that the tag SEARCHENGINE is set to YES.

# EXTRA_SEARCH_MAPPINGS 标记可用于搜索除此配置文件定义的项目之外的 Doxygen 项目，但这些项目都添加到同一个外部搜索索引中。每个项目都需要通过 EXTERNAL_SEARCH_ID 设置一个唯一的 ID。然后，搜索映射将 ID 映射到可以找到文档的相对位置。格式为：EXTRA_SEARCH_MAPPINGS = tagname1=loc1 tagname2=lo​​c2 ...
# 此标记要求将标记 SEARCHENGINE 设置为 YES。
EXTRA_SEARCH_MAPPINGS  =
```

### 7.preprocessor 预处理

```sh
#---------------------------------------------------------------------------
# Configuration options related to the preprocessor
#---------------------------------------------------------------------------

# If the ENABLE_PREPROCESSING tag is set to YES, Doxygen will evaluate all
# C-preprocessor directives found in the sources and include files.
# The default value is: YES.

# 如果 ENABLE_PREPROCESSING 标记设置为 YES，Doxygen 将评估在源文件和包含文件中找到的所有 C 预处理器指令。
# 默认值为：YES。
ENABLE_PREPROCESSING   = YES

# If the MACRO_EXPANSION tag is set to YES, Doxygen will expand all macro names
# in the source code. If set to NO, only conditional compilation will be
# performed. Macro expansion can be done in a controlled way by setting
# EXPAND_ONLY_PREDEF to YES.
# The default value is: NO.
# This tag requires that the tag ENABLE_PREPROCESSING is set to YES.

# 如果 MACRO_EXPANSION 标记设置为 YES，Doxygen 将扩展源代码中的所有宏名称。如果设置为 NO，则仅执行条件编译。通过将 EXPAND_ONLY_PREDEF 设置为 YES，可以以受控方式进行宏扩展。
# 默认值为：NO。
# 此标记要求将标记 ENABLE_PREPROCESSING 设置为 YES。
MACRO_EXPANSION        = NO

# If the EXPAND_ONLY_PREDEF and MACRO_EXPANSION tags are both set to YES then
# the macro expansion is limited to the macros specified with the PREDEFINED and
# EXPAND_AS_DEFINED tags.
# The default value is: NO.
# This tag requires that the tag ENABLE_PREPROCESSING is set to YES.

# 如果 EXPAND_ONLY_PREDEF 和 MACRO_EXPANSION 标签都设置为 YES，则宏扩展仅限于使用 PREDEFINED 和 EXPAND_AS_DEFINED 标签指定的宏。
# 默认值为：NO。
# 此标签要求将标签 ENABLE_PREPROCESSING 设置为 YES。
EXPAND_ONLY_PREDEF     = NO

# If the SEARCH_INCLUDES tag is set to YES, the include files in the
# INCLUDE_PATH will be searched if a #include is found.
# The default value is: YES.
# This tag requires that the tag ENABLE_PREPROCESSING is set to YES.

# 如果 SEARCH_INCLUDES 标记设置为 YES，则在找到 #include 时将搜索 INCLUDE_PATH 中的包含文件。
# 默认值为：YES。
# 此标记要求将标记 ENABLE_PREPROCESSING 设置为 YES。
SEARCH_INCLUDES        = YES

# The INCLUDE_PATH tag can be used to specify one or more directories that
# contain include files that are not input files but should be processed by the
# preprocessor. Note that the INCLUDE_PATH is not recursive, so the setting of
# RECURSIVE has no effect here.
# This tag requires that the tag SEARCH_INCLUDES is set to YES.

# INCLUDE_PATH 标记可用于指定一个或多个包含文件的目录，这些文件不是输入文件，但应由预处理器处理。请注意，INCLUDE_PATH 不是递归的，因此 RECURSIVE 的设置在这里不起作用。
# 此标记要求将 SEARCH_INCLUDES 标记设置为 YES。
INCLUDE_PATH           =

# You can use the INCLUDE_FILE_PATTERNS tag to specify one or more wildcard
# patterns (like *.h and *.hpp) to filter out the header-files in the
# directories. If left blank, the patterns specified with FILE_PATTERNS will be
# used.
# This tag requires that the tag ENABLE_PREPROCESSING is set to YES.

# 您可以使用 INCLUDE_FILE_PATTERNS 标记指定一个或多个通配符模式（如 *.h 和 *.hpp）来过滤目录中的头文件。如果留空，则将使用 FILE_PATTERNS 指定的模式。
# 此标记要求将标记 ENABLE_PREPROCESSING 设置为 YES。
INCLUDE_FILE_PATTERNS  =

# The PREDEFINED tag can be used to specify one or more macro names that are
# defined before the preprocessor is started (similar to the -D option of e.g.
# gcc). The argument of the tag is a list of macros of the form: name or
# name=definition (no spaces). If the definition and the "=" are omitted, "=1"
# is assumed. To prevent a macro definition from being undefined via #undef or
# recursively expanded use the := operator instead of the = operator.
# This tag requires that the tag ENABLE_PREPROCESSING is set to YES.

# PREDEFINED 标记可用于指定在启动预处理器之前定义的一个或多个宏名称（类似于 gcc 的 -D 选项）。该标记的参数是宏的列表，格式为：name 或 name=definition（无空格）。如果省略定义和“=”，则假定为“=1”。为防止宏定义通过 #undef 未定义或递归扩展，请使用 := 运算符而不是 = 运算符。
# 此标记要求将标记 ENABLE_PREPROCESSING 设置为 YES
PREDEFINED             =

# If the MACRO_EXPANSION and EXPAND_ONLY_PREDEF tags are set to YES then this
# tag can be used to specify a list of macro names that should be expanded. The
# macro definition that is found in the sources will be used. Use the PREDEFINED
# tag if you want to use a different macro definition that overrules the
# definition found in the source code.
# This tag requires that the tag ENABLE_PREPROCESSING is set to YES.

# 如果 MACRO_EXPANSION 和 EXPAND_ONLY_PREDEF 标记设置为 YES，则此标记可用于指定应扩展的宏名称列表。将使用在源代码中找到的宏定义。如果要使用不同的宏定义来覆盖在源代码中找到的定义，请使用 PREDEFINED 标记。
# 此标记要求将标记 ENABLE_PREPROCESSING 设置为 YES。
EXPAND_AS_DEFINED      =

# If the SKIP_FUNCTION_MACROS tag is set to YES then Doxygen's preprocessor will
# remove all references to function-like macros that are alone on a line, have
# an all uppercase name, and do not end with a semicolon. Such function macros
# are typically used for boiler-plate code, and will confuse the parser if not
# removed.
# The default value is: YES.
# This tag requires that the tag ENABLE_PREPROCESSING is set to YES.

# 如果将 SKIP_FUNCTION_MACROS 标记设置为 YES，则 Doxygen 的预处理器将删除所有对单独一行、名称全大写且不以分号结尾的函数类宏的引用。此类函数宏通常用于样板代码，如果不删除，会使解析器感到困惑。
# 默认值为：YES。
# 此标记要求将标记 ENABLE_PREPROCESSING 设置为 YES。
SKIP_FUNCTION_MACROS   = YES
```

### 8.external references 外部引用

```ini

#---------------------------------------------------------------------------
# Configuration options related to external references
#---------------------------------------------------------------------------

# The TAGFILES tag can be used to specify one or more tag files. For each tag
# file the location of the external documentation should be added. The format of
# a tag file without this location is as follows:
# TAGFILES = file1 file2 ...
# Adding location for the tag files is done as follows:
# TAGFILES = file1=loc1 "file2 = loc2" ...
# where loc1 and loc2 can be relative or absolute paths or URLs. See the
# section "Linking to external documentation" for more information about the use
# of tag files.
# Note: Each tag file must have a unique name (where the name does NOT include
# the path). If a tag file is not located in the directory in which Doxygen is
# run, you must also specify the path to the tagfile here.

# TAGFILES 标签可用于指定一个或多个标签文件。对于每个标签文件，应添加外部文档的位置。没有此位置的标签文件的格式如下：
# TAGFILES = file1 file2 ...
# 添加标签文件的位置如下：
# TAGFILES = file1=loc1 "file2 = loc2" ...
# 其中 loc1 和 loc2 可以是相对或绝对路径或 URL。有关标签文件使用的更多信息，请参阅“链接到外部文档”部分。
# 注意：每个标签文件必须具有唯一的名称（名称不包括路径）。如果标签文件不在运行 Doxygen 的目录中，您还必须在此处指定标签文件的路径。
TAGFILES               =

# When a file name is specified after GENERATE_TAGFILE, Doxygen will create a
# tag file that is based on the input files it reads. See section "Linking to
# external documentation" for more information about the usage of tag files.

# 当在 GENERATE_TAGFILE 之后指定文件名时，Doxygen 将根据其读取的输入文件创建一个标记文件。有关标记文件用法的更多信息，请参阅“链接到外部文档”部分。
GENERATE_TAGFILE       =

# If the ALLEXTERNALS tag is set to YES, all external classes and namespaces
# will be listed in the class and namespace index. If set to NO, only the
# inherited external classes will be listed.
# The default value is: NO.

# 如果将ALLEXTERNALS标签设置为YES，则类和命名空间索引中会列出所有外部类和命名空间。如果设置为NO，则只列出继承的外部类。
# 默认值为：NO。
ALLEXTERNALS           = NO

# If the EXTERNAL_GROUPS tag is set to YES, all external groups will be listed
# in the topic index. If set to NO, only the current project's groups will be
# listed.
# The default value is: YES.

# 如果 EXTERNAL_GROUPS 标签设置为 YES，则所有外部群组都会列在主题索引中。如果设置为 NO，则只列出当前项目的群组。
# 默认值为：YES。
EXTERNAL_GROUPS        = YES

# If the EXTERNAL_PAGES tag is set to YES, all external pages will be listed in
# the related pages index. If set to NO, only the current project's pages will
# be listed.
# The default value is: YES.

# 如果 EXTERNAL_PAGES 标签设置为 YES，则所有外部页面都会列在相关页面索引中。如果设置为 NO，则只列出当前项目的页面。
# 默认值为：YES。
EXTERNAL_PAGES         = YES
```

### 9.diagram generator tools 图表生成器工具

```ini
#---------------------------------------------------------------------------
# Configuration options related to diagram generator tools
#---------------------------------------------------------------------------

# If set to YES the inheritance and collaboration graphs will hide inheritance
# and usage relations if the target is undocumented or is not a class.
# The default value is: YES.

# 如果设置为 YES，则如果目标未记录或不是类，继承和协作图将隐藏继承和使用关系。
# 默认值为：YES。
HIDE_UNDOC_RELATIONS   = YES

# If you set the HAVE_DOT tag to YES then Doxygen will assume the dot tool is
# available from the path. This tool is part of Graphviz (see:
# https://www.graphviz.org/), a graph visualization toolkit from AT&T and Lucent
# Bell Labs. The other options in this section have no effect if this option is
# set to NO
# The default value is: NO.

# 如果将 HAVE_DOT 标记设置为 YES，则 Doxygen 将假定点工具可从路径中使用。此工具是 Graphviz 的一部分（请参阅：https://www.graphviz.org/），这是 AT&T 和 Lucent Bell Labs 的图形可视化工具包。如果将此选项设置为 NO，则本节中的其他选项无效
# 默认值为：NO。
HAVE_DOT               = NO

# The DOT_NUM_THREADS specifies the number of dot invocations Doxygen is allowed
# to run in parallel. When set to 0 Doxygen will base this on the number of
# processors available in the system. You can set it explicitly to a value
# larger than 0 to get control over the balance between CPU load and processing
# speed.
# Minimum value: 0, maximum value: 32, default value: 0.
# This tag requires that the tag HAVE_DOT is set to YES.

# DOT_NUM_THREADS 指定允许 Doxygen 并行运行的点调用数。设置为 0 时，Doxygen 将根据系统中可用的处理器数量来确定此数量。您可以将其明确设置为大于 0 的值，以控制 CPU 负载和处理速度之间的平衡。
# 最小值：0，最大值：32，默认值：0。
# 此标记要求将标记 HAVE_DOT 设置为 YES。
DOT_NUM_THREADS        = 0

# DOT_COMMON_ATTR is common attributes for nodes, edges and labels of
# subgraphs. When you want a differently looking font in the dot files that
# Doxygen generates you can specify fontname, fontcolor and fontsize attributes.
# For details please see <a href=https://graphviz.org/doc/info/attrs.html>Node,
# Edge and Graph Attributes specification</a> You need to make sure dot is able
# to find the font, which can be done by putting it in a standard location or by
# setting the DOTFONTPATH environment variable or by setting DOT_FONTPATH to the
# directory containing the font. Default graphviz fontsize is 14.
# The default value is: fontname=Helvetica,fontsize=10.
# This tag requires that the tag HAVE_DOT is set to YES.

# DOT_COMMON_ATTR 是节点、边和子图标签的通用属性。如果您希望 Doxygen 生成的点文件中的字体看起来不同，可以指定 fontname、fontcolor 和 fontsize 属性。有关详细信息，请参阅<a href=https://graphviz.org/doc/info/attrs.html>节点、边和图形属性规范</a>。您需要确保点能够找到字体，这可以通过将其放在标准位置或设置 DOTFONTPATH 环境变量或将 DOT_FONTPATH 设置为包含字体的目录来完成。默认的 graphviz 字体大小为 14。
# 默认值为：fontname=Helvetica,fontsize=10。
# 此标签要求将标签 HAVE_DOT 设置为 YES。
DOT_COMMON_ATTR        = "fontname=Helvetica,fontsize=10"

# DOT_EDGE_ATTR is concatenated with DOT_COMMON_ATTR. For elegant style you can
# add 'arrowhead=open, arrowtail=open, arrowsize=0.5'. <a
# href=https://graphviz.org/doc/info/arrows.html>Complete documentation about
# arrows shapes.</a>
# The default value is: labelfontname=Helvetica,labelfontsize=10.
# This tag requires that the tag HAVE_DOT is set to YES.

# DOT_EDGE_ATTR 与 DOT_COMMON_ATTR 连接。为了获得优雅的风格，您可以添加“arrowhead=open、arrowtail=open、arrowsize=0.5”。<a href=https://graphviz.org/doc/info/arrows.html>有关箭头形状的完整文档。</a>
# 默认值为：labelfontname=Helvetica、labelfontsize=10。
# 此标签要求将标签 HAVE_DOT 设置为 YES。
DOT_EDGE_ATTR          = "labelfontname=Helvetica,labelfontsize=10"

# DOT_NODE_ATTR is concatenated with DOT_COMMON_ATTR. For view without boxes
# around nodes set 'shape=plain' or 'shape=plaintext' <a
# href=https://www.graphviz.org/doc/info/shapes.html>Shapes specification</a>
# The default value is: shape=box,height=0.2,width=0.4.
# This tag requires that the tag HAVE_DOT is set to YES.

# DOT_NODE_ATTR 与 DOT_COMMON_ATTR 连接。对于没有节点周围框的视图，请设置“shape=plain”或“shape=plaintext”<a href=https://www.graphviz.org/doc/info/shapes.html>形状规范</a>
# 默认值为：shape=box,height=0.2,width=0.4。
# 此标签要求将标签 HAVE_DOT 设置为 YES。
DOT_NODE_ATTR          = "shape=box,height=0.2,width=0.4"

# You can set the path where dot can find font specified with fontname in
# DOT_COMMON_ATTR and others dot attributes.
# This tag requires that the tag HAVE_DOT is set to YES.

# 您可以在 # DOT_COMMON_ATTR 和其他点属性中设置点可以找到用字体名称指定的字体的路径。
# 此标签要求将标签 HAVE_DOT 设置为 YES。
DOT_FONTPATH           =

# If the CLASS_GRAPH tag is set to YES or GRAPH or BUILTIN then Doxygen will
# generate a graph for each documented class showing the direct and indirect
# inheritance relations. In case the CLASS_GRAPH tag is set to YES or GRAPH and
# HAVE_DOT is enabled as well, then dot will be used to draw the graph. In case
# the CLASS_GRAPH tag is set to YES and HAVE_DOT is disabled or if the
# CLASS_GRAPH tag is set to BUILTIN, then the built-in generator will be used.
# If the CLASS_GRAPH tag is set to TEXT the direct and indirect inheritance
# relations will be shown as texts / links. Explicit enabling an inheritance
# graph or choosing a different representation for an inheritance graph of a
# specific class, can be accomplished by means of the command \inheritancegraph.
# Disabling an inheritance graph can be accomplished by means of the command
# \hideinheritancegraph.
# Possible values are: NO, YES, TEXT, GRAPH and BUILTIN.
# The default value is: YES.

# 如果将 CLASS_GRAPH 标记设置为 YES 或 GRAPH 或 BUILTIN，则 Doxygen 将为每个记录的类生成一个图形，显示直接和间接继承关系。如果将 CLASS_GRAPH 标记设置为 YES 或 GRAPH，并且同时启用了 HAVE_DOT，则将使用点来绘制图形。如果将 CLASS_GRAPH 标记设置为 YES，并且禁用了 HAVE_DOT，或者将 CLASS_GRAPH 标记设置为 BUILTIN，则将使用内置生成器。
# 如果将 CLASS_GRAPH 标记设置为 TEXT，则直接和间接继承关系将显示为文本/链接。可以通过命令 \inheritancegraph 明确启用继承图或为特定类的继承图选择不同的表示形式。
# 可以通过命令
# \hideinheritancegraph 禁用继承图。
# 可能的值有：NO、YES、TEXT、GRAPH 和 BUILTIN。
# 默认值为：YES。
CLASS_GRAPH            = YES

# If the COLLABORATION_GRAPH tag is set to YES then Doxygen will generate a
# graph for each documented class showing the direct and indirect implementation
# dependencies (inheritance, containment, and class references variables) of the
# class with other documented classes. Explicit enabling a collaboration graph,
# when COLLABORATION_GRAPH is set to NO, can be accomplished by means of the
# command \collaborationgraph. Disabling a collaboration graph can be
# accomplished by means of the command \hidecollaborationgraph.
# The default value is: YES.
# This tag requires that the tag HAVE_DOT is set to YES.

# 如果将 COLLABORATION_GRAPH 标记设置为 YES，则 Doxygen 将为每个已记录的类生成一个图表，显示该类与其他已记录的类之间的直接和间接实现依赖关系（继承、包含和类引用变量）。当将 COLLABORATION_GRAPH 设置为 NO 时，可以通过命令 \collaborationgraph 显式启用协作图。可以通过命令 \hidecollaborationgraph 禁用协作图。
# 默认值为：YES。
# 此标记要求将标记 HAVE_DOT 设置为 YES。
COLLABORATION_GRAPH    = YES

# If the GROUP_GRAPHS tag is set to YES then Doxygen will generate a graph for
# groups, showing the direct groups dependencies. Explicit enabling a group
# dependency graph, when GROUP_GRAPHS is set to NO, can be accomplished by means
# of the command \groupgraph. Disabling a directory graph can be accomplished by
# means of the command \hidegroupgraph. See also the chapter Grouping in the
# manual.
# The default value is: YES.
# This tag requires that the tag HAVE_DOT is set to YES.

# 如果 GROUP_GRAPHS 标记设置为 YES，则 Doxygen 将生成一个组图，显示直接组依赖关系。当 GROUP_GRAPHS 设置为 NO 时，可以通过命令 \groupgraph 显式启用组依赖关系图。可以通过命令 \hidegroupgraph 禁用目录图。另请参阅手册中的分组一章。
# 默认值为：YES。
# 此标记要求将标记 HAVE_DOT 设置为 YES。
GROUP_GRAPHS           = YES

# If the UML_LOOK tag is set to YES, Doxygen will generate inheritance and
# collaboration diagrams in a style similar to the OMG's Unified Modeling
# Language.
# The default value is: NO.
# This tag requires that the tag HAVE_DOT is set to YES.

# 如果将 UML_LOOK 标签设置为 YES，Doxygen 将生成类似于 OMG 统一建模语言风格的继承和协作图。
# 默认值为：NO。
# 此标签要求将标签 HAVE_DOT 设置为 YES。
UML_LOOK               = NO

# If the UML_LOOK tag is enabled, the fields and methods are shown inside the
# class node. If there are many fields or methods and many nodes the graph may
# become too big to be useful. The UML_LIMIT_NUM_FIELDS threshold limits the
# number of items for each type to make the size more manageable. Set this to 0
# for no limit. Note that the threshold may be exceeded by 50% before the limit
# is enforced. So when you set the threshold to 10, up to 15 fields may appear,
# but if the number exceeds 15, the total amount of fields shown is limited to
# 10.
# Minimum value: 0, maximum value: 100, default value: 10.
# This tag requires that the tag UML_LOOK is set to YES.

# 如果启用了 UML_LOOK 标记，则字段和方法将显示在类节点内。如果有许多字段或方法以及许多节点，则图表可能会变得太大而无法使用。UML_LIMIT_NUM_FIELDS 阈值限制每种类型的项目数量，以使大小更易于管理。将其设置为 0 表示无限制。请注意，在强制执行限制之前，阈值可能会超过 50%。因此，当您将阈值设置为 10 时，最多可能会出现 15 个字段，但如果数量超过 15，则显示的字段总数限制为 10。
# 最小值：0，最大值：100，默认值：10。
# 此标记要求将标记 UML_LOOK 设置为 YES。
UML_LIMIT_NUM_FIELDS   = 10

# If the DOT_UML_DETAILS tag is set to NO, Doxygen will show attributes and
# methods without types and arguments in the UML graphs. If the DOT_UML_DETAILS
# tag is set to YES, Doxygen will add type and arguments for attributes and
# methods in the UML graphs. If the DOT_UML_DETAILS tag is set to NONE, Doxygen
# will not generate fields with class member information in the UML graphs. The
# class diagrams will look similar to the default class diagrams but using UML
# notation for the relationships.
# Possible values are: NO, YES and NONE.
# The default value is: NO.
# This tag requires that the tag UML_LOOK is set to YES.

# 如果 DOT_UML_DETAILS 标记设置为 NO，Doxygen 将在 UML 图中显示没有类型和参数的属性和方法。如果 DOT_UML_DETAILS 标记设置为 YES，Doxygen 将在 UML 图中为属性和方法添加类型和参数。如果 DOT_UML_DETAILS 标记设置为 NONE，Doxygen 将不会在 UML 图中生成带有类成员信息的字段。类图将类似于默认类图，但使用 UML 符号表示关系。
# 可能的值包括：NO、YES 和 NONE。
# 默认值为：NO。
# 此标记要求将标记 UML_LOOK 设置为 YES。
DOT_UML_DETAILS        = NO

# The DOT_WRAP_THRESHOLD tag can be used to set the maximum number of characters
# to display on a single line. If the actual line length exceeds this threshold
# significantly it will be wrapped across multiple lines. Some heuristics are
# applied to avoid ugly line breaks.
# Minimum value: 0, maximum value: 1000, default value: 17.
# This tag requires that the tag HAVE_DOT is set to YES.

# DOT_WRAP_THRESHOLD 标签可用于设置一行上显示的最大字符数。如果实际行长明显超出此阈值，则会将其换行到多行。应用了一些启发式方法以避免难看的换行符。
# 最小值：0，最大值：1000，默认值：17。
# 此标签要求将标签 HAVE_DOT 设置为 YES。
DOT_WRAP_THRESHOLD     = 17

# If the TEMPLATE_RELATIONS tag is set to YES then the inheritance and
# collaboration graphs will show the relations between templates and their
# instances.
# The default value is: NO.
# This tag requires that the tag HAVE_DOT is set to YES.

# 如果 TEMPLATE_RELATIONS 标签设置为 YES，则继承和协作图将显示模板与其实例之间的关系。
# 默认值为：NO。
# 此标签要求将标签 HAVE_DOT 设置为 YES。
TEMPLATE_RELATIONS     = NO

# If the INCLUDE_GRAPH, ENABLE_PREPROCESSING and SEARCH_INCLUDES tags are set to
# YES then Doxygen will generate a graph for each documented file showing the
# direct and indirect include dependencies of the file with other documented
# files. Explicit enabling an include graph, when INCLUDE_GRAPH is is set to NO,
# can be accomplished by means of the command \includegraph. Disabling an
# include graph can be accomplished by means of the command \hideincludegraph.
# The default value is: YES.
# This tag requires that the tag HAVE_DOT is set to YES.

# 如果 INCLUDE_GRAPH、ENABLE_PREPROCESSING 和 SEARCH_INCLUDES 标记设置为 YES，则 Doxygen 将为每个文档文件生成一个图表，显示该文件与其他文档文件的直接和间接包含依赖关系。当 INCLUDE_GRAPH 设置为 NO 时，可以通过命令 \includegraph 显式启用包含图。可以通过命令 \hideincludegraph 禁用包含图。
# 默认值为：YES。
# 此标记要求将标记 HAVE_DOT 设置为 YES。
INCLUDE_GRAPH          = YES

# If the INCLUDED_BY_GRAPH, ENABLE_PREPROCESSING and SEARCH_INCLUDES tags are
# set to YES then Doxygen will generate a graph for each documented file showing
# the direct and indirect include dependencies of the file with other documented
# files. Explicit enabling an included by graph, when INCLUDED_BY_GRAPH is set
# to NO, can be accomplished by means of the command \includedbygraph. Disabling
# an included by graph can be accomplished by means of the command
# \hideincludedbygraph.
# The default value is: YES.
# This tag requires that the tag HAVE_DOT is set to YES.

# 如果 INCLUDED_BY_GRAPH、ENABLE_PREPROCESSING 和 SEARCH_INCLUDES 标记设置为 YES，则 Doxygen 将为每个文档文件生成一个图表，显示该文件与其他文档文件的直接和间接包含依赖关系。当 INCLUDED_BY_GRAPH 设置为 NO 时，可以通过命令 \includedbygraph 显式启用包含图表。可以通过命令
# \hideincludedbygraph 禁用包含图表。
# 默认值为：YES。
# 此标记要求将标记 HAVE_DOT 设置为 YES。
INCLUDED_BY_GRAPH      = YES

# If the CALL_GRAPH tag is set to YES then Doxygen will generate a call
# dependency graph for every global function or class method.
#
# Note that enabling this option will significantly increase the time of a run.
# So in most cases it will be better to enable call graphs for selected
# functions only using the \callgraph command. Disabling a call graph can be
# accomplished by means of the command \hidecallgraph.
# The default value is: NO.
# This tag requires that the tag HAVE_DOT is set to YES.

# 如果将 CALL_GRAPH 标记设置为 YES，则 Doxygen 将为每个全局函数或类方法生成一个调用依赖关系图。
#
# 请注意，启用此选项将显著增加运行时间。因此，在大多数情况下，最好仅使用 \callgraph 命令为选定函数启用调用图。禁用调用图可以通过命令 \hidecallgraph 来完成。
# 默认值为：NO。
# 此标记要求将标记 HAVE_DOT 设置为 YES。
CALL_GRAPH             = NO

# If the CALLER_GRAPH tag is set to YES then Doxygen will generate a caller
# dependency graph for every global function or class method.
#
# Note that enabling this option will significantly increase the time of a run.
# So in most cases it will be better to enable caller graphs for selected
# functions only using the \callergraph command. Disabling a caller graph can be
# accomplished by means of the command \hidecallergraph.
# The default value is: NO.
# This tag requires that the tag HAVE_DOT is set to YES.

# 如果将 CALLER_GRAPH 标记设置为 YES，则 Doxygen 将为每个全局函数或类方法生成一个调用者依赖关系图。
#
# 请注意，启用此选项将显著增加运行时间。因此，在大多数情况下，最好仅使用 \callergraph 命令为选定函数启用调用者图。禁用调用者图可以通过命令 \hidecallergraph 来完成。
# 默认值为：NO。
# 此标记要求将标记 HAVE_DOT 设置为 YES。
CALLER_GRAPH           = NO

# If the GRAPHICAL_HIERARCHY tag is set to YES then Doxygen will graphical
# hierarchy of all classes instead of a textual one.
# The default value is: YES.
# This tag requires that the tag HAVE_DOT is set to YES.

# 如果将 GRAPHICAL_HIERARCHY 标记设置为 YES，则 Doxygen 将以图形方式显示所有类的层次结构，而不是文本层次结构。
# 默认值为：YES。
# 此标记要求将 HAVE_DOT 标记设置为 YES。
GRAPHICAL_HIERARCHY    = YES

# If the DIRECTORY_GRAPH tag is set to YES then Doxygen will show the
# dependencies a directory has on other directories in a graphical way. The
# dependency relations are determined by the #include relations between the
# files in the directories. Explicit enabling a directory graph, when
# DIRECTORY_GRAPH is set to NO, can be accomplished by means of the command
# \directorygraph. Disabling a directory graph can be accomplished by means of
# the command \hidedirectorygraph.
# The default value is: YES.
# This tag requires that the tag HAVE_DOT is set to YES.

# 如果将 DIRECTORY_GRAPH 标记设置为 YES，则 Doxygen 将以图形方式显示目录对其他目录的依赖关系。依赖关系由目录中文件之间的 #include 关系决定。当 DIRECTORY_GRAPH 设置为 NO 时，可以通过命令 \directorygraph 显式启用目录图。可以通过
# 命令 \hidedirectorygraph 禁用目录图。
# 默认值为：YES。
# 此标记要求将标记 HAVE_DOT 设置为 YES。
DIRECTORY_GRAPH        = YES

# The DIR_GRAPH_MAX_DEPTH tag can be used to limit the maximum number of levels
# of child directories generated in directory dependency graphs by dot.
# Minimum value: 1, maximum value: 25, default value: 1.
# This tag requires that the tag DIRECTORY_GRAPH is set to YES.

# DIR_GRAPH_MAX_DEPTH 标签可用于通过点来限制目录依赖关系图中生成的子目录的最大层数。
# 最小值：1，最大值：25，默认值：1。
# 此标签要求将标签 DIRECTORY_GRAPH 设置为 YES。
DIR_GRAPH_MAX_DEPTH    = 1

# The DOT_IMAGE_FORMAT tag can be used to set the image format of the images
# generated by dot. For an explanation of the image formats see the section
# output formats in the documentation of the dot tool (Graphviz (see:
# https://www.graphviz.org/)).
# Note: If you choose svg you need to set HTML_FILE_EXTENSION to xhtml in order
# to make the SVG files visible in IE 9+ (other browsers do not have this
# requirement).
# Possible values are: png, jpg, gif, svg, png:gd, png:gd:gd, png:cairo,
# png:cairo:gd, png:cairo:cairo, png:cairo:gdiplus, png:gdiplus and
# png:gdiplus:gdiplus.
# The default value is: png.
# This tag requires that the tag HAVE_DOT is set to YES.

# DOT_IMAGE_FORMAT 标签可用于设置 dot 生成的图像的图像格式。有关图像格式的说明，请参阅 dot 工具文档中的输出格式部分（Graphviz（参见：https://www.graphviz.org/））。
# 注意：如果选择 svg，则需要将 HTML_FILE_EXTENSION 设置为 xhtml，以使 SVG 文件在 IE 9+ 中可见（其他浏览器没有此要求）。
# 可能的值包括：png、jpg、gif、svg、png:gd、png:gd:gd、png:cairo、png:cairo:gd、png:cairo:cairo、png:cairo:gdiplus、png:gdiplus 和 png:gdiplus:gdiplus。
# 默认值为：png。
# 此标签要求将标签 HAVE_DOT 设置为 YES。
DOT_IMAGE_FORMAT       = png

# If DOT_IMAGE_FORMAT is set to svg, then this option can be set to YES to
# enable generation of interactive SVG images that allow zooming and panning.
#
# Note that this requires a modern browser other than Internet Explorer. Tested
# and working are Firefox, Chrome, Safari, and Opera.
# Note: For IE 9+ you need to set HTML_FILE_EXTENSION to xhtml in order to make
# the SVG files visible. Older versions of IE do not have SVG support.
# The default value is: NO.
# This tag requires that the tag HAVE_DOT is set to YES.

# 如果 DOT_IMAGE_FORMAT 设置为 svg，则可将此选项设置为 YES，以启用允许缩放和平移的交互式 SVG 图像生成。
#
# 请注意，这需要 Internet Explorer 以外的现代浏览器。经过测试并可正常运行的是 Firefox、Chrome、Safari 和 Opera。
# 注意：对于 IE 9+，您需要将 HTML_FILE_EXTENSION 设置为 xhtml 才能使
# SVG 文件可见。旧版本的 IE 不支持 SVG。
# 默认值为：NO。
# 此标记要求将标记 HAVE_DOT 设置为 YES。
INTERACTIVE_SVG        = NO

# The DOT_PATH tag can be used to specify the path where the dot tool can be
# found. If left blank, it is assumed the dot tool can be found in the path.
# This tag requires that the tag HAVE_DOT is set to YES.

# DOT_PATH 标签可用于指定可以找到点工具的路径。如果留空，则假定可以在路径中找到点工具。
# 此标签要求将标签 HAVE_DOT 设置为 YES。
DOT_PATH               =

# The DOTFILE_DIRS tag can be used to specify one or more directories that
# contain dot files that are included in the documentation (see the \dotfile
# command).
# This tag requires that the tag HAVE_DOT is set to YES.

# DOTFILE_DIRS 标签可用于指定一个或多个包含文档中包含的点文件的目录（请参阅 \dotfile 命令）。
# 此标签要求将标签 HAVE_DOT 设置为 YES。
DOTFILE_DIRS           =

# You can include diagrams made with dia in Doxygen documentation. Doxygen will
# then run dia to produce the diagram and insert it in the documentation. The
# DIA_PATH tag allows you to specify the directory where the dia binary resides.
# If left empty dia is assumed to be found in the default search path.

# 您可以在 Doxygen 文档中包含使用 dia 制作的图表。然后，Doxygen 将运行 dia 来生成图表并将其插入文档中。DIA_PATH 标记允许您指定 dia 二进制文件所在的目录。
# 如果留空，则假定在默认搜索路径中找到 dia。
DIA_PATH               =

# The DIAFILE_DIRS tag can be used to specify one or more directories that
# contain dia files that are included in the documentation (see the \diafile
# command).

# DIAFILE_DIRS 标签可用于指定一个或多个包含文档中包含的 dia 文件的目录（参见 \diafile 命令）。
DIAFILE_DIRS           =

# When using PlantUML, the PLANTUML_JAR_PATH tag should be used to specify the
# path where java can find the plantuml.jar file or to the filename of jar file
# to be used. If left blank, it is assumed PlantUML is not used or called during
# a preprocessing step. Doxygen will generate a warning when it encounters a
# \startuml command in this case and will not generate output for the diagram.

# 使用 PlantUML 时，应使用 PLANTUML_JAR_PATH 标记来指定 java 可以找到 plantuml.jar 文件的路径或要使用的 jar 文件的文件名。如果留空，则假定在预处理步骤中未使用或调用 PlantUML。在这种情况下，Doxygen 遇到 \startuml 命令时会生成警告，并且不会为图表生成输出。
PLANTUML_JAR_PATH      =

# When using PlantUML, the PLANTUML_CFG_FILE tag can be used to specify a
# configuration file for PlantUML.

# 当使用PlantUML时，可以使用PLANTUML_CFG_FILE标签来指定PlantUML的配置文件。
PLANTUML_CFG_FILE      =

# When using PlantUML, the specified paths are searched for files specified by
# the !include statement in a PlantUML block.

# 当使用 PlantUML 时，会在指定的路径中搜索由 PlantUML 块中的 !include 语句指定的文件。
PLANTUML_INCLUDE_PATH  =

# The DOT_GRAPH_MAX_NODES tag can be used to set the maximum number of nodes
# that will be shown in the graph. If the number of nodes in a graph becomes
# larger than this value, Doxygen will truncate the graph, which is visualized
# by representing a node as a red box. Note that if the number of direct
# children of the root node in a graph is already larger than
# DOT_GRAPH_MAX_NODES then the graph will not be shown at all. Also note that
# the size of a graph can be further restricted by MAX_DOT_GRAPH_DEPTH.
# Minimum value: 0, maximum value: 10000, default value: 50.
# This tag requires that the tag HAVE_DOT is set to YES.

# DOT_GRAPH_MAX_NODES 标签可用于设置图中显示的最大节点数。如果图中的节点数大于此值，Doxygen 将截断图，通过将节点表示为红色框来可视化。请注意，如果图中根节点的直接子节点数已经大于 DOT_GRAPH_MAX_NODES，则根本不会显示该图。还请注意，MAX_DOT_GRAPH_DEPTH 可以进一步限制图的大小。
# 最小值：0，最大值：10000，默认值：50。
# 此标签要求将标签 HAVE_DOT 设置为 YES。
DOT_GRAPH_MAX_NODES    = 50

# The MAX_DOT_GRAPH_DEPTH tag can be used to set the maximum depth of the graphs
# generated by dot. A depth value of 3 means that only nodes reachable from the
# root by following a path via at most 3 edges will be shown. Nodes that lay
# further from the root node will be omitted. Note that setting this option to 1
# or 2 may greatly reduce the computation time needed for large code bases. Also
# note that the size of a graph can be further restricted by
# DOT_GRAPH_MAX_NODES. Using a depth of 0 means no depth restriction.
# Minimum value: 0, maximum value: 1000, default value: 0.
# This tag requires that the tag HAVE_DOT is set to YES.

# MAX_DOT_GRAPH_DEPTH 标签可用于设置由点生成的图的最大深度。深度值为 3 表示仅显示通过最多 3 条边的路径从根节点可到达的节点。距离根节点较远的节点将被忽略。请注意，将此选项设置为 1 或 2 可能会大大减少大型代码库所需的计算时间。另请注意，DOT_GRAPH_MAX_NODES 可以进一步限制图的大小。使用深度 0 表示没有深度限制。
# 最小值：0，最大值：1000，默认值：0。
# 此标签要求将标签 HAVE_DOT 设置为 YES。
MAX_DOT_GRAPH_DEPTH    = 0

# Set the DOT_MULTI_TARGETS tag to YES to allow dot to generate multiple output
# files in one run (i.e. multiple -o and -T options on the command line). This
# makes dot run faster, but since only newer versions of dot (>1.8.10) support
# this, this feature is disabled by default.
# The default value is: NO.
# This tag requires that the tag HAVE_DOT is set to YES.

# 将 DOT_MULTI_TARGETS 标记设置为 YES，以允许 dot 在一次运行中生成多个输出文件（即命令行上的多个 -o 和 -T 选项）。这会使 dot 运行得更快，但由于只有较新版本的 dot（>1.8.10）支持此功能，因此默认情况下禁用此功能。
# 默认值为：NO。
# 此标记要求将标记 HAVE_DOT 设置为 YES。
DOT_MULTI_TARGETS      = NO

# If the GENERATE_LEGEND tag is set to YES Doxygen will generate a legend page
# explaining the meaning of the various boxes and arrows in the dot generated
# graphs.
# Note: This tag requires that UML_LOOK isn't set, i.e. the Doxygen internal
# graphical representation for inheritance and collaboration diagrams is used.
# The default value is: YES.
# This tag requires that the tag HAVE_DOT is set to YES.

# 如果 GENERATE_LEGEND 标记设置为 YES，Doxygen 将生成一个图例页面，解释点生成的图形中各种框和箭头的含义。
# 注意：此标记要求未设置 UML_LOOK，即使用 Doxygen 内部继承和协作图的图形表示。
# 默认值为：YES。
# 此标记要求将标记 HAVE_DOT 设置为 YES。
GENERATE_LEGEND        = YES

# If the DOT_CLEANUP tag is set to YES, Doxygen will remove the intermediate
# files that are used to generate the various graphs.
#
# Note: This setting is not only used for dot files but also for msc temporary
# files.
# The default value is: YES.

# 如果 DOT_CLEANUP 标签设置为 YES，Doxygen 将删除用于生成各种图形的中间文件。
#
# 注意：此设置不仅适用于点文件，还适用于 msc 临时文件。
# 默认值为：YES。
DOT_CLEANUP            = YES

# You can define message sequence charts within Doxygen comments using the \msc
# command. If the MSCGEN_TOOL tag is left empty (the default), then Doxygen will
# use a built-in version of mscgen tool to produce the charts. Alternatively,
# the MSCGEN_TOOL tag can also specify the name an external tool. For instance,
# specifying prog as the value, Doxygen will call the tool as prog -T
# <outfile_format> -o <outputfile> <inputfile>. The external tool should support
# output file formats "png", "eps", "svg", and "ismap".

# 您可以使用 \msc 命令在 Doxygen 注释中定义消息序列图表。如果 MSCGEN_TOOL 标记留空（默认），则 Doxygen 将使用内置版本的 mscgen 工具来生成图表。或者，MSCGEN_TOOL 标记也可以指定外部工具的名称。例如，指定 prog 作为值，Doxygen 将以 prog -T <outfile_format> -o <outputfile> <inputfile> 的形式调用该工具。外部工具应支持输出文件格式“png”、“eps”、“svg”和“ismap”。
MSCGEN_TOOL            =

# The MSCFILE_DIRS tag can be used to specify one or more directories that
# contain msc filesthat are included in the documentation (see the \mscfile
# command).

# MSCFILE_DIRS 标签可用于指定一个或多个包含文档中包含的 msc 文件的目录（参见 \mscfile 命令）。
MSCFILE_DIRS           =
```





附录

 