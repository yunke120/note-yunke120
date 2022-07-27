# C++学习

## 引用

- 语法：数据类型 &别名 = 原名;

- 示例：

  ```C++
  int a = 10;
  int &b = a;
  ```

- 本质：指针常量

  示例代码本质为：`int * const b = &a`

- 注意事项：

  1. 引用必须要初始化
  2. 引用一旦初始化后，不允许改变

- 示例代码

  ```C++
  #include <iostream>
  
  int main() {
  
      int a = 10;
      int &b = a;
      std::cout << "a : " << a << std::endl;
      std::cout << "b : " << b << std::endl;
  
      b = 20;
      std::cout << "a : " << a << std::endl;
      std::cout << "b : " << b << std::endl;
  
      return 0;
  }
  ```

### 引用作函数入口参数

```c++
#include <iostream>

// 值传递
void mySwap01(int a, int b)
{
    int temp = a;
    a = b;
    b = temp;
}

// 指针传递
void mySwap02(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 引用
void mySwap03(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}


int main() {
    int a = 10;
    int b = 20;
    mySwap01(a, b); /* 形参不修饰实参 */
    std::cout << "a : " << a << std::endl;
    std::cout << "b : " << b << std::endl;
    mySwap02(&a, &b); /* 形参修饰实参 */
    std::cout << "a : " << a << std::endl;
    std::cout << "b : " << b << std::endl;
    mySwap03(a, b); /* 形参修饰实参 */
    std::cout << "a : " << a << std::endl;
    std::cout << "b : " << b << std::endl;
    return 0;
}
/* 输出：
a : 10
b : 20
a : 20
b : 10
a : 10
b : 20
*/
```

### 引用作函数返回值

> 1. 不要返回局部变量的引用
>
> 2. 函数的调用可以作为左值

```c++
#include <iostream>

int& test01()
{
    int a = 10; // 局部变量，栈区
    return a; // 编译器会有警告
}

int& test02()
{
    static int a = 10; // 静态变量，全局区
    return a;
}
int main() {
    int &ref = test02(); //
    std::cout << "ref:" << ref << std::endl;
    test02() = 1000; // 左值
    std::cout << "ref:" << ref << std::endl;
    return 0;
}
/* 输出：
ref:10
ref:1000
*/
```

## 函数高级

### 函数默认参数

1. 如果函数声明有默认参数，函数定义就不能有默认参数
2. 如果某个位置参数有默认值，那么从这个位置往后，都要有默认值

### 函数重载

1. 作用：函数名可以相同，提高复用性

2. 满足条件：

   1. 同一个作用域下
   2. 函数名称相同
   3. 函数参数类型不同 或 个数不同 或 顺序不同

3. 注意事项：

   1. 函数返回值不能作为函数重载的条件

   2. 引用作为重载条件

      ```c++
      #include <iostream>
      void fun(int &a)
      {
          std::cout << "fun(int &a)" << std::endl;
      }
      
      void fun(const int &a)
      {
          std::cout << "fun(const int &a)" << std::endl;
      }
      int main() {
          int a = 10;
          const int b = 10;
          fun(a);
          fun(b);
          return 0;
      }
      ```

   3. 函数重载碰到默认参数

      ![1658891929610](figures/1658891929610.png)

