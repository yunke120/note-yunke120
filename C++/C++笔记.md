1. 虚函数在运行时绑定，非虚函数在编译时绑定
2. 虚函数不能时静态的
3. 虚函数可以是另一个类的友元函数
4. 应该使用基类类型的指针或引用来访问虚函数，以实现运行时的多态性
5. 虚函数的原型在基类和派生类中应该是相同的
6. 虚函数始终在基类中定义，在派生类中重写；派生类可以不重写或重新定义虚函数，在这种情况下将使用函数的基类版本。
7. 类可以有虚析构函数，但不能有虚构造函数

C++早期绑定和晚期绑定示例：

```c++
// CPP program to illustrate
// working of Virtual Functions
#include<iostream>
using namespace std;

class base {
public:
	void fun_1() { cout << "base-1\n"; }
	virtual void fun_2() { cout << "base-2\n"; }
	virtual void fun_3() { cout << "base-3\n"; }
	virtual void fun_4() { cout << "base-4\n"; }
};

class derived : public base {
public:
	void fun_1() { cout << "derived-1\n"; }
	void fun_2() { cout << "derived-2\n"; }
	void fun_4(int x) { cout << "derived-4\n"; }
};

int main()
{
	base *p;
	derived obj1;
	p = &obj1;

	// Early binding because fun1() is non-virtual
	// in base
	p->fun_1();

	// Late binding (RTP)
	p->fun_2();

	// Late binding (RTP)
	p->fun_3();

	// Late binding (RTP)
	p->fun_4();

	// Early binding but this function call is
	// illegal (produces error) because pointer
	// is of base type and function is of
	// derived class
	// p->fun_4(5);
	
	return 0;
}

```

output:

```
base-1
derived-2
base-3
base-4
```

说明：

​		最初，我们创建一个类型为基类的指针，并使用派生类对象的地址对其进行初始化。当我们创建派生类的一个对象时，编译器创建一个指针作为包含派生类的 VTABLE 地址的类的数据成员。

在上面的例子中使用了类似的晚期和早期绑定的概念。对于 `fun _ 1()`函数调用，调用函数的基类版本，`fun _ 2()`在派生类中被重写，因此调用派生类版本，`fun _3()`在派生类中不被重写，而且是虚函数，因此调用基类版本，同样 `fun _ 4()`也不被重写，因此调用基类版本。

注意: 派生类中的 `fun _ 4(int)`不同于基类中的虚函数 `fun _ 4()` ，因为两个函数的原型不同。