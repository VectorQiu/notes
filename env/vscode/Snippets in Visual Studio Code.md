# Visual Studio 代码中的代码片段

> https://code.visualstudio.com/docs/editor/userdefinedsnippets

代码片段是一种模板，可以更方便地输入重复的代码模式，如循环或条件语句。

在 Visual Studio 代码中，片段会与其他建议一起出现在智能提示（Ctrl+Space）中，也会出现在专门的片段选择器（命令面板中的**插入片段**）中。此外，还支持制表符补全：使用`"editor.tabCompletion"："on"`启用，键入**片段前缀**（触发文本），然后按 Tab 键插入片段。

片段语法遵循 [TextMate 片段语法](https://manual.macromates.com/en/snippets)，但 "插值外壳代码 "和使用 `\u`除外；两者都不支持。

![ajax snippet](https://code.visualstudio.com/assets/docs/editor/userdefinedsnippets/ajax-snippet.gif)

## [内置片段](https://code.visualstudio.com/docs/editor/userdefinedsnippets#_builtin-snippets)

VS Code 内置了多种语言的片段，如 JavaScript、TypeScript、Markdown 和 PHP：JavaScript、TypeScript、Markdown 和 PHP。

![builtin javascript snippet](https://code.visualstudio.com/assets/docs/editor/userdefinedsnippets/builtin-javascript-snippets.png)

您可以在命令面板上运行**插入片段**命令来查看语言的可用片段，从而获得当前文件语言的片段列表。不过请注意，该列表还包括您定义的用户片段，以及您安装的扩展程序提供的任何片段。

## [从市场安装片段](https://code.visualstudio.com/docs/editor/userdefinedsnippets#_install-snippets-from-the-marketplace)

VS Code Marketplace 上的许多扩展都包含片段。你可以使用 @category: "snippets" 过滤器在扩展视图（Ctrl+Shift+X）中搜索包含片段的扩展。

![Searching for extensions with snippets](https://code.visualstudio.com/assets/docs/editor/userdefinedsnippets/category-snippets.png)

如果找到想要使用的扩展，请安装它，然后重启 VS Code，新片段就可以使用了。

## [创建自己的片段](https://code.visualstudio.com/docs/editor/userdefinedsnippets#_create-your-own-snippets)

您可以轻松定义自己的片段，无需任何扩展。要创建或编辑自己的片段，请在**文件** > **首选项**下选择**配置用户片段**，然后选择要显示片段的语言（通过[语言标识符](https://code.visualstudio.com/docs/languages/identifiers)），如果要显示所有语言的片段，则选择**新建全局片段文件**选项。VS Code 会为你管理底层片段文件的创建和刷新。

![snippet dropdown](https://code.visualstudio.com/assets/docs/editor/userdefinedsnippets/snippet-dropdown.png)

片段文件以 JSON 格式编写，支持 C 风格注释，可定义无限数量的片段。Snippets 支持大多数 TextMate 语法的动态行为，可根据插入上下文智能格式化空白，并允许轻松进行多行编辑。

下面是一个 JavaScript `for` 循环片段示例：

```
// in file 'Code/User/snippets/javascript.json'
{
  "For Loop": {
    "prefix": ["for", "for-const"],
    "body": ["for (const ${2:element} of ${1:array}) {", "\t$0", "}"],
    "description": "A for loop."
  }
}
```

在上面的例子中

- "For Loop "是代码段名称。如果没有提供说明，则通过 IntelliSense 显示。
- `prefix` 定义一个或多个触发词，用于在 IntelliSense 中显示代码段。子串匹配在前缀上执行，因此在本例中，"fc "可以匹配 "for-const"。
- `body`是一行或多行内容，插入时将以多行形式连接。换行符和嵌入的制表符将根据插入片段的上下文进行格式化。
- `description`是 IntelliSense 显示的片段的可选描述。

此外，上述示例的正文中有三个占位符（按遍历顺序排列）：${1:array}、${2:element} 和 $0：您可以使用 Tab 键快速跳转到下一个占位符，此时您可以编辑占位符或跳转到下一个占位符。冒号 : 后面的字符串（如果有）是默认文本，例如 ${2:element} 中的 element。占位符的遍历顺序是按数字升序排列，从 1 开始；0 是一种可选的特殊情况，总是排在最后，并在光标位于指定位置时退出代码段模式。

### [文件模板片段](https://code.visualstudio.com/docs/editor/userdefinedsnippets#_file-template-snippets)

如果片段的目的是填充或替换文件内容，则可以在片段定义中添加 isFileTemplate 属性。运行 "片段 "命令时，文件模板片段会显示在下拉菜单中：从片段填充文件 "命令时，文件模板片段会显示在下拉菜单中。

## [片段范围](https://code.visualstudio.com/docs/editor/userdefinedsnippets#_snippet-scope)

片段有范围限制，因此只会推荐相关的片段。片段的范围可以由以下两种方式之一确定：

1. the **language(s)** 片段的作用域（可能是全部）
2. the **project(s)** 片段的作用域（可能是全部）

### [语言片段范围](https://code.visualstudio.com/docs/editor/userdefinedsnippets#_language-snippet-scope)

每个片段的作用域是一种语言、几种语言或所有（"全局"）语言，取决于它是否在以下语言中定义：

1. a **language** snippet file
2. a **global** snippet file

单语言用户自定义片段定义在特定语言的片段文件（如 javascript.json）中，你可以通过片段的语言标识符访问该文件：配置用户片段。只有在编辑定义该片段的语言时才能访问该片段。

多语言和全局用户定义的片段都在 "全局 "片段文件（文件后缀为".code-snippets "的 JSON）中定义，也可通过**片段访问：配置用户片段**。在全局片段文件中，片段定义可能有一个额外的 `scope` 属性，该属性包含一个或多个[语言标识符](https://code.visualstudio.com/docs/languages/identifiers)，使片段仅适用于指定的语言。如果没有给出 `scope` 属性，则全局片段适用于***所有语言。

大多数用户定义的片段只适用于一种语言，因此定义在特定语言的片段文件中。

### [项目片段范围](https://code.visualstudio.com/docs/editor/userdefinedsnippets#_project-snippet-scope)

您也可以为项目创建全局片段文件（文件后缀为 .code-snippets 的 JSON 文件）。项目文件夹下的片段是通过片段 "配置用户片段 "下拉菜单中的 "为''...新建片段文件 "选项创建的：配置用户代码片段 "下拉菜单中的 "为''...新建代码片段文件 "选项创建，并位于项目根目录下的 .vscode 文件夹中。项目片段文件用于与在该项目中工作的所有用户共享片段。项目文件夹中的片段与全局片段类似，可通过作用域属性作用于特定语言。

## [片段语法](https://code.visualstudio.com/docs/editor/userdefinedsnippets#_snippet-syntax)

片段的 `body`可以使用特殊结构来控制游标和插入的文本。以下是支持的功能及其语法：

### [Tabstops](https://code.visualstudio.com/docs/editor/userdefinedsnippets#_tabstops)

使用制表符，可以让编辑器光标在代码段内移动。使用 $1 和 $2 指定光标位置。数字表示访问制表符的顺序，而 0 表示光标的最终位置。同一制表符的多次出现会被链接并同步更新。

### [Placeholders](https://code.visualstudio.com/docs/editor/userdefinedsnippets#_placeholders)

占位符是带有值的制表符，如 ${1:foo}。占位符文本将被插入和选中，以便于更改。占位符可以嵌套，如 `${1:another ${2:placeholder}}`.

### [Choice](https://code.visualstudio.com/docs/editor/userdefinedsnippets#_choice)

占位符的值可以是选项。语法是以逗号分隔的数值枚举，并用管道字符括起来，例如 ${1|one,two,three|}。插入代码段并选择占位符后，"选择 "将提示用户选择其中一个值。

### [Variables](https://code.visualstudio.com/docs/editor/userdefinedsnippets#_variables)

使用 $name 或 ${name:default}，可以插入变量的值。如果变量未设置，则插入其默认值或空字符串。如果变量未知（即变量名未定义），则插入变量名并将其转换为占位符。

可以使用以下变量

- `TM_SELECTED_TEXT` 当前选中的文本或空字符串
- `TM_CURRENT_LINE` 当前行的内容
- `TM_CURRENT_WORD` 光标下单词的内容或空字符串
- `TM_LINE_INDEX` 基于零索引的行号
- `TM_LINE_NUMBER` 基于单索引的行号
- `TM_FILENAME` 当前文件的文件名
- `TM_FILENAME_BASE` 当前文件的文件名（不含扩展名
- `TM_DIRECTORY` 当前文件的目录
- `TM_FILEPATH` 当前文件的完整文件路径
- `RELATIVE_FILEPATH` 当前文档的相对（打开的工作区或文件夹）文件路径
- `CLIPBOARD` 剪贴板内容
- `WORKSPACE_NAME` 打开的工作区或文件夹的名称
- `WORKSPACE_FOLDER` 打开的工作区或文件夹的路径
- `CURSOR_INDEX` 基于零指数的游标编号
- `CURSOR_NUMBER` 基于一个索引的游标编号

用于插入当前日期和时间：

- `CURRENT_YEAR` The current year
- `CURRENT_YEAR_SHORT` 当年的最后两位数
- `CURRENT_MONTH` The month as two digits (example '02')
- `CURRENT_MONTH_NAME` The full name of the month (example 'July')
- `CURRENT_MONTH_NAME_SHORT` The short name of the month (example 'Jul')
- `CURRENT_DATE` The day of the month as two digits (example '08')
- `CURRENT_DAY_NAME` The name of day (example 'Monday')
- `CURRENT_DAY_NAME_SHORT` The short name of the day (example 'Mon')
- `CURRENT_HOUR` The current hour in 24-hour clock format
- `CURRENT_MINUTE` The current minute as two digits
- `CURRENT_SECOND` The current second as two digits
- `CURRENT_SECONDS_UNIX` The number of seconds since the Unix epoch
- `CURRENT_TIMEZONE_OFFSET` The current UTC time zone offset as `+HH:MM` or `-HH:MM` (example `-07:00`).

用于插入随机值：

- `RANDOM` 6 random Base-10 digits
- `RANDOM_HEX` 6 random Base-16 digits
- `UUID` A Version 4 UUID

用于插入行或块注释，尊重当前语言：

- `BLOCK_COMMENT_START` Example output: in PHP `/*` or in HTML `<!--`
- `BLOCK_COMMENT_END` Example output: in PHP `*/` or in HTML `-->`
- `LINE_COMMENT` Example output: in PHP `//`

下面的代码段在 JavaScript 文件中插入了`/* Hello World */`，在 HTML 文件中插入了`<!--Hello World-->`：

```
{
  "hello": {
    "scope": "javascript,html",
    "prefix": "hello",
    "body": "$BLOCK_COMMENT_START Hello World $BLOCK_COMMENT_END"
  }
}
```

### [变量变换](https://code.visualstudio.com/docs/editor/userdefinedsnippets#_variable-transforms)

转换允许你在插入变量之前修改其值。转换的定义由三部分组成：

1. 与变量值匹配的正则表达式，或在无法解析变量时使用空字符串。
2. 格式字符串"，用于引用正则表达式中的匹配组。格式字符串允许有条件插入和简单修改。
3. 传递给正则表达式的选项。

下面的示例插入了当前文件的名称，但没有结尾，因此从 `foo.txt` 变成了 `foo`。

```
${TM_FILENAME/(.*)\\..+$/$1/}
  |           |         |  |
  |           |         |  |-> no options
  |           |         |
  |           |         |-> references the contents of the first
  |           |             capture group
  |           |
  |           |-> regex to capture everything before
  |               the final `.suffix`
  |
  |-> resolves to the filename
```

### [占位符转换](https://code.visualstudio.com/docs/editor/userdefinedsnippets#_placeholdertransform)

与变量变换一样，占位符变换允许在移动到下一个制表符时更改占位符的插入文本。插入的文本会与正则表达式匹配，匹配的文本会被指定的替换格式文本替换（取决于选项）。每个占位符都可以使用第一个占位符的值独立定义自己的变换。占位符变换格式与变量变换格式相同。

### [转换示例](https://code.visualstudio.com/docs/editor/userdefinedsnippets#_transform-examples)

为了说明某些字符需要双引号转义，示例用双引号表示，就像它们会出现在代码段正文中一样。文件名 example-123.456-TEST.js 的转换示例和输出结果。

| Example                               | Output                    | Explanation                        |
| :------------------------------------ | :------------------------ | :--------------------------------- |
| `"${TM_FILENAME/[\\.]/_/}"`           | `example-123_456-TEST.js` | Replace the first `.` with `_`     |
| `"${TM_FILENAME/[\\.-]/_/g}"`         | `example_123_456_TEST_js` | Replace each `.` or `-` with `_`   |
| `"${TM_FILENAME/(.*)/${1:/upcase}/}"` | `EXAMPLE-123.456-TEST.JS` | Change to all uppercase            |
| `"${TM_FILENAME/[^0-9a-z]//gi}"`      | `example123456TESTjs`     | Remove non-alphanumeric characters |

### [语法](https://code.visualstudio.com/docs/editor/userdefinedsnippets#_grammar)

下面是片段的 EBNF（[扩展 Backus-Naur form](https://en.wikipedia.org/wiki/Extended_Backus-Naur_form)）。使用 `\`（反斜杠），可以转义 `$`、`}` 和 `\`。在选择元素中，反斜杠还可以转义逗号和管道字符。只有需要转义的字符才能被转义，因此在这些结构中不能转义 `$`，在选择结构中也不能转义 `$` 或 `}`。

```
any         ::= tabstop | placeholder | choice | variable | text
tabstop     ::= '$' int
                | '${' int '}'
                | '${' int  transform '}'
placeholder ::= '${' int ':' any '}'
choice      ::= '${' int '|' text (',' text)* '|}'
variable    ::= '$' var | '${' var '}'
                | '${' var ':' any '}'
                | '${' var transform '}'
transform   ::= '/' regex '/' (format | text)+ '/' options
format      ::= '$' int | '${' int '}'
                | '${' int ':' '/upcase' | '/downcase' | '/capitalize' | '/camelcase' | '/pascalcase' '}'
                | '${' int ':+' if '}'
                | '${' int ':?' if ':' else '}'
                | '${' int ':-' else '}' | '${' int ':' else '}'
regex       ::= JavaScript Regular Expression value (ctor-string)
options     ::= JavaScript Regular Expression option (ctor-options)
var         ::= [_a-zA-Z] [_a-zA-Z0-9]*
int         ::= [0-9]+
text        ::= .*
if          ::= text
else        ::= text
```

## [使用 TextMate 片段](https://code.visualstudio.com/docs/editor/userdefinedsnippets#_using-textmate-snippets)

Y你也可以在 VS 代码中使用现有的 TextMate 片段（.tmSnippets）。请参阅扩展 API 部分的 "使用 TextMate 片段 "主题了解更多信息。

## [为片段指定键钮](https://code.visualstudio.com/docs/editor/userdefinedsnippets#_assign-keybindings-to-snippets)

你可以创建自定义 [keybindings](https://code.visualstudio.com/docs/getstarted/keybindings) 来插入特定的代码段。打开 "keybindings.json"（**首选项：打开键盘快捷方式文件**），其中定义了你所有的按键绑定，然后添加一个按键绑定，将 "片段 "作为额外参数：

```
{
  "key": "cmd+k 1",
  "command": "editor.action.insertSnippet",
  "when": "editorTextFocus",
  "args": {
    "snippet": "console.log($1)$0"
  }
}
```

该键绑定将调用**插入片段**命令，但不是提示您选择片段，而是插入所提供的片段。您可以像往常一样定义自定义[按键绑定](https://code.visualstudio.com/docs/getstarted/keybindings)，其中包括键盘快捷方式、命令 ID 以及启用键盘快捷方式时的可选[当子句上下文时](https://code.visualstudio.com/docs/getstarted/keybindings#_when-clause-contexts)。

此外，你可以使用 langId 和 name 参数来引用现有的片段，而不是使用片段参数值来定义内联片段。langId 参数用于选择插入由 name 表示的片段的语言，例如下面的示例选择了适用于 csharp-files 的 myFavSnippet。

```
{
  "key": "cmd+k 1",
  "command": "editor.action.insertSnippet",
  "when": "editorTextFocus",
  "args": {
    "langId": "csharp",
    "name": "myFavSnippet"
  }
}
```

## [Next steps](https://code.visualstudio.com/docs/editor/userdefinedsnippets#_next-steps)

- [Command Line](https://code.visualstudio.com/docs/editor/command-line) - VS Code 具有丰富的命令行界面，可用于打开或扩展文件以及安装扩展程序。
- [Extension API](https://code.visualstudio.com/api) - 了解扩展 VS Code 的其他方法。
- [Snippet Guide](https://code.visualstudio.com/api/language-extensions/snippet-guide) - 您可以将片段打包，以便在 VS 代码中使用。

## [Common questions](https://code.visualstudio.com/docs/editor/userdefinedsnippets#_common-questions)

### [What if I want to use existing TextMate snippets from a .tmSnippet file?](https://code.visualstudio.com/docs/editor/userdefinedsnippets#_what-if-i-want-to-use-existing-textmate-snippets-from-a-tmsnippet-file)

您可以轻松打包 TextMate 片段文件，以便在 VS 代码中使用。请参阅我们的扩展 API 文档中的 "使用 TextMate 片段"。

### [How do I have a snippet place a variable in the pasted script?](https://code.visualstudio.com/docs/editor/userdefinedsnippets#_how-do-i-have-a-snippet-place-a-variable-in-the-pasted-script)

要在粘贴的脚本中使用变量，需要转义变量名中的"$"，这样就不会被片段扩展阶段解析。

```
"VariableSnippet":{
    "prefix": "_Var",
    "body": "\\$MyVar = 2",
    "description": "A basic snippet that places a variable into script with the $ prefix"
  }
```

This results in the pasted snippet as:

```
$MyVar = 2
```

### [Can I remove snippets from IntelliSense?](https://code.visualstudio.com/docs/editor/userdefinedsnippets#_can-i-remove-snippets-from-intellisense)

是的，您可以在插入片段命令下拉菜单中选择片段项目右侧的从 IntelliSense 隐藏按钮，从而隐藏特定片段，使其不显示在 IntelliSense（完成列表）中。

![Hide from IntelliSense button in Insert Snippet dropdown](https://code.visualstudio.com/assets/docs/editor/userdefinedsnippets/hide-from-intellisense.png)

您仍然可以使用插入片段命令选择片段，但隐藏的片段不会显示在 IntelliSense 中。