/*
 * Copyright (c) 2023-2024
 *
 * Change Logs:
 * Date          Author       Notes
 * 2024-07-05    liwei.qiu    first version
 */

/* includes ----------------------------------------------------------------- */
#include <stdio.h>

/* private config ----------------------------------------------------------- */

/* private define ----------------------------------------------------------- */
#define MAX(a, b)        ((a) > (b) ? (a) : (b))
#define SHORT_NAME       42
#define LONGER_NAME      0x007f
#define EVEN_LONGER_NAME (2)
#define foo(x)           (x * x)
#define bar(y, z)        (y + z)

/* private typedef ---------------------------------------------------------- */
typedef enum { COLOR_RED, COLOR_GREEN, COLOR_BLUE } Color;

union Data {
    int i;
    float f;
    char str[20];
};

typedef struct {
    int x;
    int y;
} point_t;

/* private variables -------------------------------------------------------- */
static const int kMaxValue = 100;
int a = 1;
int somelongname = 2;
double c = 3;

// 字符串
char site[7] = {'R', 'U', 'N', 'O', 'O', 'B', '\0'};
char *str = "RUNOOB";

// 数组
int myArray[5] = {10, 20, 30, 40, 50};

// 指针
int *p;

// 函数指针
int (*f)();

/* private function prototypes ---------------------------------------------- */
static void print_helloworld();
static int add_two_numbers(int a, int b);
static int factorial(int n);
static void print_color(Color color);
static void print_point(const point_t *p);

/* public functions --------------------------------------------------------- */
int main() {
    // if
    int score;

    // 1.提示输入成绩
    printf("请输入学生成绩: \n");

    // 2.获取用户输入
    scanf("%d", &score);

    // 3.判断成绩
    if (score >= 90) {
        printf("优秀\n");
    } else if (75 <= score && score < 90) {
        printf("良好\n");
    } else if (60 <= score && score < 75) {
        printf("及格\n");
    } else if (40 <= score && score < 60) {
        printf("不及格\n");
    } else {
        printf("差劲\n");
    }

    // switch-case
    int week;
    printf("input integer number: ");
    scanf("%d", &week);
    switch (week) {
    case 1:
        printf("Monday\n");
        break;
    case 2:
        printf("Tuesday\n");
        break;
    case 3:
        printf("Wednesday\n");
        break;
    case 4:
        printf("Thursday\n");
        break;
    case 5:
        printf("Friday\n");
        break;
    case 6:
        printf("Saturday\n");
        break;
    case 7:
        printf("Sunday\n");
        break;
    default:
        printf("error\n");
    }

    // for
    for (int i = 0; i < 10; i++) {
        if (i == 5) {
            continue;
        }

        if (i == 9) {
            break;
        }
        printf("index:[%2d] \n", i);
    }

    // do-while
    do {
        printf("do-while");
    } while (0);

    int while_count = 10;
    while (while_count >= 0) {
        printf("while:%d \n", while_count);
        while_count--;
    }

    // 函数调用
    print_helloworld();
    add_two_numbers(1, 2);
    factorial(10);
    print_color(COLOR_RED);
    point_t point = {1, 2};
    print_point(&point);
    return 0;
}

/* private functions -------------------------------------------------------- */
static void print_helloworld() {
    printf("Hello, World!\n");
}

// 函数定义：返回两个整数之和
static int add_two_numbers(int a, int b) {
    return a + b;
}

// 函数定义：返回一个整数的阶乘
static int factorial(int n) {
    if (n == 0) {
        return 1;
    }
    return n * factorial(n - 1);
}

// 函数定义：打印颜色
static void print_color(Color color) {
    switch (color) {
    case COLOR_RED:
        printf("Color is Red\n");
        break;
    case COLOR_GREEN:
        printf("Color is Green\n");
        break;
    case COLOR_BLUE:
        printf("Color is Blue\n");
        break;
    default:
        printf("Unknown Color\n");
    }
}

// 函数定义：打印点的坐标
void print_point(const point_t *p) {
    printf("point_t coordinates: (%d, %d)\n", p->x, p->y);
}
/* ----------------------------- end of file -------------------------------- */
