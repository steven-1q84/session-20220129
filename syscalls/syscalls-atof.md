# Linux系统调用：*atof*

[TOC]

## 1. 概要

```c
#include <stdlib.h>

double atof(const char *nptr);
int atoi(const char *nptr);
long atol(const char *nptr);
long long atoll(const char *nptr);

double strtod(const char *restrict nptr, char **restrict endptr);
float strtof(const char *restrict nptr, char **restrict endptr);
long double strtold(const char *restrict nptr, char **restrict endptr);

long strtol(const char *restrict nptr, char **restrict endptr, int base);
long long strtoll(const char *restrict nptr, char **restrict endptr, int base);

unsigned long strtoul(const char *restrict nptr, char **restrict endptr, int base);
unsigned long long strtoull(const char *restrict nptr, char **restrict endptr, int base);
```



## 2. 描述

将字符串转换为数值

- `atof()` 将字符串 **nptr* 转换为双精度浮点型数值返回
- `atoi()`、`atol()`、`atoll()` 将字符串 **nptr* 转换为整形数值
  - 转换出错时返回 0

- `strtod()`、`strtof`、`strtold` 将字符串 **nptr* 转换为 *double*、*float*、*long double*类型数值
  - 如果转换未发生，函数返回 0，*nptr* 保存在 **endptr* 中
  - 由于 ‘0’ 是合法返回值，因此应通过检查 *errno* 判断是否出错

- `strtol`、`strtoll`、`strtoul`、`strtoull` 将字符串 **nptr* 转换为 *long*、*long long*、*unsinged long*、*unsinged  long long* 类型数值返回

## 3. 参数

### 3.1. *nptr* `const char *`

表示数值的字符串

### 3.2. *endptr* `char **` 

第一个不能转换的非法字符：

- 函数返回后，若 *endptr* 指针非 *NULL*，指向最后一个使用的字符的指针将保存在 *endptr* 指向的内存中

### 3.3. *base* `int`

字符串所表示数值的基底：

- 当 *base* 为 0 时：
  - 数字字符串前若出现“0x”或“0X”，字符串按16进制数处理
  - 数字字符串前若出现“0”，字符串按8进制数处理
  - 数字字符串前若没有特殊字符，字符串按10进制数处理
- 当 *base* 为 *n* 且 *n* ∈ [2, 36] 时：
  - 数字字符串按 *n* 进制数处理
  - 字符串一直处理到某个超出基底大小的字符为止
  - 当 *9 < n* 时，*{ 'A', 'B', ..., 'Z' }* 对应 *{10, 11, ..., 35}*



## 4. 返回值

...



## 4. 参考

[atof(3) — Linux manual page](https://man7.org/linux/man-pages/man3/atof.3.html)

[atoi(3) — Linux manual page](https://man7.org/linux/man-pages/man3/atoi.3.html)

[strtod(3) — Linux manual page](https://man7.org/linux/man-pages/man3/strtod.3.html)

[strtol(3) — Linux manual page](https://man7.org/linux/man-pages/man3/strtol.3.html)

[strtoul(3) — Linux manual page](https://man7.org/linux/man-pages/man3/strtoul.3.html)
