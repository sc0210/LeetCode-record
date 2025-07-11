# 📘 解法總覽：右左規則（Clockwise/Spiral Rule）

## 這是 C 程式指標解析的經典法則，由 David Anderson 提出

> 以變數名稱為中心，往右讀一個 token，再往左，再往右，再往左…，直到結束。

## 快速理解步驟

1. 找到**變數名稱**（如 ptr2Array）

2. 以名稱為中心：

    - 優先處理 ()：函式
    - 然後處理 []：陣列
    - 然後處理 *：指標

3. 每讀一層，往更外層理解意思

## 輔助工具

1. `cdecl`
2. 安裝方式：`sudo apt-get install cdecl`
3. 用法說明：
    - 講解一段敘述 `explain  char *(*fptab[])(int)`
    - 寫出對應的宣告 `declare a as array of pointer to function returning pointer to function returning pointer to char`

## 練習題目

```c
int a
int *p
int **p
int a[10]
int *p[10]
int (*p)[10]
int (*p)(int)
int (*p[10])(int)
```

## 說明

1. a as int
2. p as pointer to int
3. p as pointer to a pointer to int
4. a as array 10 of int
5. p as pointer to array 10 of int
6. p as pointer to function (int) returning int
7. p as array 10 of pointer to function (int) returning int

## Quiz

```c
int *arr[5]; 
int (*ptr)[5];
int *(*ptr)(int);
int (*fptr[3])(char);
int **p;
int (*x[10])(int, int);
int *f(int, float);
int (*const p)[10];
void (*signal(int, void (*)(int)))(int);
char *(*arr[4])(char *);
```

## Ans

1. arr as array 5 of pointer to int
2. ptr as pointer to array 5 of int
3. ptr as pointer to function (int) returning pointer to int
4. fptr as array 3 of pointer to function (char) returning int
5. p as pointer to pointer to int
6. x as array 10 of pointer to function (int, int) returning int
7. f as function (int, float) returning pointer to int
8. p as const pointer to array 10 of int
9. signal as function (int, pointer to function (int) returning void) returning pointer to function (int) returning void
10. arr as array 4 of pointer to function (pointer to char) returning pointer to char