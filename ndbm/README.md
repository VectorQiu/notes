# 数据库函数库

> 第三版UNIX环境高级编程 第20章 数据库函数库
>
> 1. C语言函数库 键-值存储数据库
> 2. dbm(3) UNIX系统流行的数据函数库 Ken Thompson开发（动态散列结构）
> 3. 编码风格 John Lions解释UNIX V6操作系统源代码的书的影响，源代码简易

## 1.数据结构

![](\\image\\idx&dat_struct.png)

## 2.函数库接口

```c
#include "apue_db.h"

DBHANDLE db_open(const char *pathname, int oflag, ... /* int mode */);
void db_close(DBHANDLE db);
int db_store(DBHANDLE db, const char *key, const char *data, int flag);
char *fetch(DBHANDLE db, const char *key);
int db_delete(DBHANDLE db, const char *key);
void db_rewind(DBHANDLE db);
char *db_nextrec(DBHANDLE db, char *key);
```

## 3.系统函数

### 3.1 文件操作(系统调用)

```c
#include <fcntl.h>

int open(const char *pathname, int flags);
int open(const char *pathname, int flags, mode_t mode);
```

其中，`pathname` 是要打开的文件的路径名，`flags` 是打开文件的方式和选项，`mode` 是文件权限（仅在创建新文件时有效）。

`flags` 参数可以是以下标志的一个或多个的组合：

- `O_RDONLY`: 只读方式打开文件。
- `O_WRONLY`: 只写方式打开文件。
- `O_RDWR`: 读写方式打开文件。
- `O_CREAT`: 如果文件不存在则创建文件。
- `O_EXCL`: 与 `O_CREAT` 一起使用时，如果文件存在则返回错误。
- `O_TRUNC`: 如果文件存在并且以写入方式打开，则清空文件内容。
- `O_APPEND`: 以追加方式打开文件。
- `O_NONBLOCK` 或 `O_NDELAY`: 非阻塞模式打开文件。
- `O_SYNC`: 同步写入方式打开文件，每次写操作都会立即写入到磁盘。
- `O_DIRECT`: 直接 I/O 操作方式打开文件，跳过缓冲区。

`mode` 参数是一个八进制数，指定了创建新文件时的权限，它与 UNIX/Linux 文件权限掩码相同。

```c
#include <fcntl.h>

int fcntl(int fd, int cmd, ... /* arg */ );
```

- `fd`：文件描述符，表示要进行操作的文件。
- `cmd`：命令，表示要执行的操作。
- `arg`：可选参数，根据不同的命令可能需要提供。

`fcntl` 函数可以执行各种操作，如获取/设置文件描述符标志、获取/设置文件状态标志、获取/设置文件锁等。它通过 `cmd` 参数来指定要执行的操作，根据不同的命令可能需要提供额外的参数。

以下是一些常用的 `fcntl` 命令：

- **F_DUPFD**：复制文件描述符。可能需要一个整数参数，表示新的文件描述符。
- **F_GETFD**：获取文件描述符标志。不需要额外参数。
- **F_SETFD**：设置文件描述符标志。可能需要一个整数参数，表示要设置的文件描述符标志。
- **F_GETFL**：获取文件状态标志。不需要额外参数。
- **F_SETFL**：设置文件状态标志。可能需要一个整数参数，表示要设置的文件状态标志。
- **F_GETLK**：获取文件锁。可能需要一个 `struct flock` 结构体参数，表示锁的信息。
- **F_SETLK**：设置文件锁。可能需要一个 `struct flock` 结构体参数，表示要设置的锁信息。
- **F_SETLKW**：设置文件锁，并等待锁。可能需要一个 `struct flock` 结构体参数，表示要设置的锁信息。。



```c
#include <unistd.h>
int close(int fd);
ssize_t read(int fd, void *buf, size_t count);
ssize_t write(int fd, const void *buf, size_t count);
off_t lseek(int fd, off_t offset, int whence);
int unlink(const char *pathname);
int rmdir(const char *pathname);
```



```c
#include <sys/uio.h>

ssize_t readv(int fd, const struct iovec *iov, int iovcnt);
ssize_t writev(int fd, const struct iovec *iov, int iovcnt);
```

- `fd`：文件描述符，表示要读取数据的文件。
- `iov`：一个指向 `struct iovec` 数组的指针，每个 `struct iovec` 结构体表示一个缓冲区的起始地址和长度。
- `iovcnt`：`iov` 数组中元素的数量。

### 3.2 字符串处理函数

```c
#include <string.h>

char *strcpy(char *dest, const char *src);
char *strncpy(char *dest, const char *src, size_t n);
char *strcat(char *dest, const char *src);
char *strncat(char *dest, const char *src, size_t n);
size_t strlen(const char *s);
```

```c
int strcmp(const char *s1, const char *s2);
int strncmp(const char *s1, const char *s2, size_t n);
```

字符串比较

- 如果 `s1` 字符串大于 `s2` 字符串，则返回一个正整数。
- 如果 `s1` 字符串小于 `s2` 字符串，则返回一个负整数。
- 如果 `s1` 字符串等于 `s2` 字符串，则返回 0。

```c
char *strstr(const char *haystack, const char *needle);
```

字符串中查找另一个字符串的第一次出现，并返回第一次出现的位置

该函数接受两个参数 `haystack` 和 `needle`，分别指向要搜索的主字符串和要搜索的子字符串。函数返回一个指向主字符串中第一次出现子字符串的指针，如果子字符串未找到，则返回 NULL。

具体的搜索方式是，`strstr` 函数会从主字符串 `haystack` 的开头开始逐个比较子字符串 `needle` 的每个字符，直到找到与子字符串相匹配的位置或者主字符串结束为止。如果找到了匹配的位置，则返回该位置的指针；如果未找到，则返回 NULL。

```c
#include <stdio.h>
#include <string.h>

int main() {
    const char *haystack = "Hello, world!";
    const char *needle = "world";

    char *result = strstr(haystack, needle);
    if (result != NULL) {
        printf("'%s' was found in '%s' at position %ld\n", needle, haystack, result - haystack);
    } else {
        printf("'%s' was not found in '%s'\n", needle, haystack);
    }

    return 0;
}
```



```c
char *strchr(const char *s, int c);
```

字符串中查找指定字符的第一次出现，并返回该字符在字符串中的位置

该函数接受两个参数 `s` 和 `c`，其中 `s` 是要搜索的字符串，`c` 是要查找的字符。函数返回一个指向字符串中第一次出现指定字符的指针，如果未找到指定字符，则返回 NULL。

具体的搜索方式是，`strchr` 函数会从字符串 `s` 的开头开始逐个比较每个字符，直到找到与指定字符 `c` 相匹配的位置或者字符串结束为止。如果找到了匹配的位置，则返回该位置的指针；如果未找到，则返回 NULL。

```c
#include <stdio.h>
#include <string.h>

int main() {
    const char *str = "Hello, world!";
    char ch = 'o';

    char *result = strchr(str, ch);
    if (result != NULL) {
        printf("'%c' was found in '%s' at position %ld\n", ch, str, result - str);
    } else {
        printf("'%c' was not found in '%s'\n", ch, str);
    }

    return 0;
}
```



```c
char *strtok(char *str, const char *delim);
```

`strtok` 函数用于将字符串分解成一系列子字符串，其中每个子字符串都以分隔符字符为界

函数接受两个参数：

- `str`：要分解的字符串。
- `delim`：包含分隔符字符的字符串。

第一次调用时，`str` 参数指向要分解的字符串，之后的调用中，`str` 参数为 NULL，函数会继续从上一次调用的位置继续分解。

函数返回值为分解出的子字符串的指针，如果没有更多的子字符串可以分解，则返回 NULL。

在使用 `strtok` 函数时，需要注意以下几点：

- 每次调用 `strtok` 函数都会改变原始字符串，将分隔符替换为 NULL 字符。
- 如果要在不同的字符串上进行分解，需要在每次调用 `strtok` 时传入原始字符串的副本。
- 当分解结束时，函数返回 NULL。

### 3.3 动态内存分配函数

```c
#include <stdlib.h>

void *malloc(size_t size);
void *calloc(size_t num, size_t size);
void *realloc(void *ptr, size_t size);
void free(void *ptr);
```

- **malloc**: 接受一个 `size_t` 类型的参数，表示要分配的内存块的字节数。如果分配成功，则返回指向分配内存块的指针；如果分配失败，则返回 NULL。
- **calloc**: 接受两个 `size_t` 类型的参数，分别表示要分配的内存块的数量和每个内存块的字节数。如果分配成功，则返回指向分配内存块的指针；如果分配失败，则返回 NULL。分配的内存块会被初始化为 0。
- **realloc**: 接受一个指向之前分配的内存块的指针和一个 `size_t` 类型的参数，表示要重新分配的内存块的大小。如果分配成功，则返回指向新分配内存块的指针；如果分配失败，则返回 NULL。原内存块的内容会被保留到新内存块中。
- **free**: 接受一个指向之前分配的内存块的指针，用于释放之前分配的内存块。被释放的内存块会被操作系统回收，可以被后续的内存分配函数再次使用。

### 3.4 可变参数

1. **va_list**: 声明一个可变参数列表对象。
   - `va_list` 是一个类型，用于声明可变参数列表的对象。通常在函数参数列表中使用 `va_list` 来表示可变参数。
2. **va_start**: 开始处理可变参数列表。
   - `va_start` 宏用于初始化可变参数列表的访问，它接受两个参数：可变参数列表对象和最后一个固定参数的地址。这个宏将可变参数列表对象设置为指向第一个可变参数的位置。
3. **va_arg**: 获取可变参数列表中的下一个参数。
   - `va_arg` 宏用于获取可变参数列表中的下一个参数，它接受两个参数：可变参数列表对象和要获取参数的类型。每次调用 `va_arg` 都会返回可变参数列表中的下一个参数，并将列表对象移动到下一个参数的位置。
4. **va_end**: 结束处理可变参数列表。
   - `va_end` 宏用于结束对可变参数列表的访问，它接受一个参数：可变参数列表对象。调用 `va_end` 后，不能再使用对应的可变参数列表对象。

```
#include <stdio.h>
#include <stdarg.h>

void print_integers(int num, ...) {
    va_list args;
    va_start(args, num); // 开始处理可变参数列表

    for (int i = 0; i < num; i++) {
        int value = va_arg(args, int); // 获取下一个参数
        printf("%d ", value);
    }

    va_end(args); // 结束处理可变参数列表
    printf("\n");
}

int main() {
    print_integers(5, 1, 2, 3, 4, 5);
    return 0;
}
```

### 3.5 标准输入输出函数

#### 3.5.1 格式化输入输出

```c
#inclued <stdio.h>

int scanf(const char *format, ...);
int fscanf(FILE *stream, const char *format, ...);
int sscanf(const char *str, const char *format, ...);

int printf(const char *format, ...);
int fprintf(FILE *stream, const char *format, ...);
int sprintf(char *str, const char *format, ...);
```

#### 3.5.2 字符输入输出流

```C
#inclued <stdio.h>

int putc(int c, FILE *stream);
int putchar(int c);
int getc(FILE *stream);
int getchar(void);
char *fgets(char *str, int n, FILE *stream); /* 从指定文件流读取一行字符串。 */
int fputs(const char *str, FILE *stream); /* 将字符串写入指定文件流 */
```



#### 3.5.3 标准库文件输入输出

```c
#inclued <stdio.h>

FILE *fopen(const char *filename, const char *mode);
int fclose(FILE *stream);
size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);
int fseek(FILE *stream, long offset, int whence);
long ftell(FILE *stream);
void rewind(FILE *stream);
int feof(FILE *stream);
```

- `ptr`：要读取或写入的数据块的指针。
- `size`：每个数据项的大小（以字节为单位）。
- `nmemb`：要读取或写入的数据项的数量。
- `stream`：要读取或写入的文件流指针
- `offset`：偏移量，可以是正数（向后移动）或负数（向前移动）。
- `whence`：指定偏移量的起始位置，可以是 `SEEK_SET`（从文件起始位置开始）、`SEEK_CUR`（从当前位置开始）或 `SEEK_END`（从文件末尾开始）



## 4.GDB调试

GDB（GNU Debugger）是一种功能强大的调试工具，用于调试 C、C++、Fortran 等编程语言的程序。以下是一些常用的 GDB 命令和用法：

1. **启动程序**: 在命令行中输入 `gdb` 后跟着要调试的程序的名称，然后按回车键启动 GDB。例如：`gdb myprogram`。
2. **设置断点**：
   - `break <function>`: 在指定函数入口处设置断点。
   - `break <file>:<line>`: 在指定文件的特定行上设置断点。
   - `break <line>`: 在当前文件的特定行上设置断点。
   - `break if <condition>`: 设置条件断点。
3. **运行程序**:
   - `run`: 运行程序。
   - `run <args>`: 运行程序并传递参数。
4. **单步执行**:
   - `next`: 单步执行一行源代码。
   - `step`: 单步执行，如果当前行是函数调用，进入函数内部执行。
   - `finish`: 执行完当前函数，并返回到函数的调用点。
5. **显示变量**:
   - `print <variable>`: 打印变量的值。
   - `info locals`: 显示当前函数的局部变量。
   - `info args`: 显示当前函数的参数。
6. **查看堆栈**:
   - `backtrace` 或 `bt`: 显示当前的函数调用栈。
7. **查看源代码**:
   - `list`: 显示当前执行的源代码。
   - `list <function>`: 显示指定函数的源代码。
8. **跳转**:
   - `jump <line>`: 跳转到指定行继续执行。
9. **查看内存**:
   - `x/<n><format> <address>`: 显示内存内容。
10. **退出 GDB**:
    - `quit`: 退出 GDB 调试器。

## 5.测试

```c
#include "apue.h"
#include "apue_db.h"
#include <fcntl.h>

int
main(void)
{
	DBHANDLE	db;

	if ((db = db_open("db4", O_RDWR | O_CREAT | O_TRUNC,
	  FILE_MODE)) == NULL)
		err_sys("db_open error");

	if (db_store(db, "Alpha", "data1", DB_INSERT) != 0)
		err_quit("db_store error for alpha");
	if (db_store(db, "beta", "Data for beta", DB_INSERT) != 0)
		err_quit("db_store error for beta");
	if (db_store(db, "gamma", "record3", DB_INSERT) != 0)
		err_quit("db_store error for gamma");

	db_close(db);
	exit(0);
}
```



```shell
$ gcc -g main.c db.c error.c lockreg.c -o main
$ ./main 
$ cat db4.idx 
      0     71     50      0
      0  10Alpha:0:6
      0  10beta:6:14
     29  11gamma:20:8
$ cat db4.dat 
data1
Data for beta
record3
```



