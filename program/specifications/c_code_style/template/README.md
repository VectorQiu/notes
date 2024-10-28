# C style and coding rules template

> ref: [c-code-style](https://github.com/MaJerle/c-code-style)
>
> 
>
> The single most important rule when writing code is this: *check the surrounding code and try to imitate it*.
>
> As a maintainer it is dismaying to receive a patch that is obviously in a different coding style to the surrounding code. This is disrespectful, like someone tromping into a spotlessly-clean house with muddy shoes.
>
> So, whatever this document recommends, if there is already written code and you are patching it, keep its current style consistent even if it is not your favorite style.

## Integration with VSCode

VScode comes with pre-installed `clang-format` tool (part of LLVM package) that has been design to help developers with auto-format tool during code development.

As such, it allows users to format code on file change (and save). When file is saved, vscode will try to invoke the clang-format and format the code. Rules to use are in `.clang-format` file. If clang-format cannot find the rules in the path of current file, it will go all the way up to the root, until one is found. If still none is available, default rules are then being used.

This repository contains always up-to-date `.clang-format` file with rules matching explained ones. You can place the folder in the root or your project or even in the root of your software development projects -> use one file for all!

Some configurations shall be enabled:

![VSCode configuration](https://github.com/MaJerle/c-code-style/raw/main/images/vscode-settings.png)

## Conventions used

The keywords *MUST*, *MUST NOT*, *REQUIRED*, *SHALL*, *SHALL NOT*, *SHOULD*, *SHOULD NOT*, *RECOMMENDED*, *NOT RECOMMENDED*, *MAY*, and *OPTIONAL* in this document are to be interpreted as described in BCP 14 [RFC2119] [RFC8174]

## Clang format integration

Repository comes with always-up-to-date `.clang-format` file, an input configuration for `clang-format` tool. It can be seamlessly integrated with most of latest techno IDEs, including VSCode. Formatting then happens on the spot on each file save.

https://code.visualstudio.com/docs/cpp/cpp-ide#_code-formatting

```sh
python .\scripts\run-clang-format-from-config.py
```



## Artistic style configuration

[AStyle](http://astyle.sourceforge.net/) is a great piece of software that can help with formatting the code based on input configuration.

This repository contains `astyle-code-format.cfg` file which can be used with `AStyle` software.

```
astyle --options="astyle-code-format.cfg" "input_path/*.c,*.h" "input_path2/*.c,*.h"
```



> Artistic style configuration is obsolete and no longer updated

## Eclipse formatter

Repository contains `eclipse-ext-kr-format.xml` file that can be used with eclipse-based toolchains to set formatter options.

It is based on K&R formatter with modifications to respect above rules. You can import it within eclipse settings, `Preferences -> LANGUAGE -> Code Style -> Formatter` tab.