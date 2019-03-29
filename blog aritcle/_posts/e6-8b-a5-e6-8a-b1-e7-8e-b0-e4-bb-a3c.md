---
title: " 拥抱“现代C++”\t\t"
url: 5999.html
id: 5999
categories:
  - Other
date: 2019-01-06 12:31:36
tags:
---

引言
--

本文将介绍一部分在OI中常用的c++11/14/17新特性。 请务必注意每个特性所包含于的C++标准，并且一定要在相应的满足充分限制性的编译条件下编译运行，以免发生不必要的惨剧。需要注意的是，不要在NOI系列赛事中，尤其是未标明编译环境的场合使用这些特性。 目前，各大现代OJ都已经具备了对于这些新特性的支持。在此，我们推荐的编译环境配置如下： G++：**GCC 8.2.0** with GNU C++ support. -std=c++17 clang：**Clang 7.0.0** with =std=c++17 MSVC：Microsoft visual studio 2017 professional v.15.9.3 : **visual c++ 2017 0x0700** 其中，我们推荐使用对于新C++17支持最好的**MSVC**作为生产环境。除此，clang也是很好的轻量编译器选择。 关于各编译器对于c++特性的支持，可以参阅[https://zh.cppreference.com/w/cpp/compiler_support](https://zh.cppreference.com/w/cpp/compiler_support)。 ubuntu 18.04上预装的G++版本为**7.3**，目前最新版本为**8.2.0**。可以通过apt-get手动升级G++版本。 下面特性主要整理自[迈向C++11/14/17](https://changkun.de/modern-cpp/book/01-intro/index.html)，收入了算法竞赛中常用的新特性。这遵循了[知识共享署名-非商业性使用-禁止演绎 4.0 国际许可协议许可](http://creativecommons.org/licenses/by-nc-nd/4.0/)。

弃用功能
----

**注意**：弃用并非彻底不能用，只是用于暗示程序员这些特性将从未来的标准中消失，应该尽量避免使用。但是，已弃用的特性依然是标准库的一部分，并且出于兼容性的考虑，大部分特性其实会『永久』保留。

*   **不再允许字符串字面值常量赋值给一个 char *。如果需要用字符串字面值常量赋值和初始化一个 char *，应该使用 const char * 或者 auto。**
    
        char *str = "hello world!"; // 将出现弃用警告
        
    
*   **C++98 异常说明、 unexpected\_handler、set\_unexpected() 等相关特性被弃用，应该使用 noexcept。**
    
*   **auto\_ptr 被弃用，应使用 unique\_ptr。**
    
*   **register 关键字被弃用，可以使用但不再具备任何实际含义。**
    
*   **bool 类型的 ++ 操作被弃用。**
    
*   **如果一个类有析构函数，为其生成拷贝构造函数和拷贝赋值运算符的特性被弃用了。**
    
*   **C 语言风格的类型转换被弃用（即在变量前使用 (convert\_type)），应该使用 static\_cast、reinterpret\_cast、const\_cast 来进行类型转换。**
    
*   **特别地，在最新的 C++17 标准中弃用了一些可以使用的 C 标准库，例如 、、 与 等**
    
*   ……等等
    

还有一些其他诸如参数绑定（C++11 提供了 `std::bind` 和 `std::function`）、`export`等特性也均被弃用。前面提到的这些特性**如果你从未使用或者听说过，也请不要尝试去了解他们，应该向新标准靠拢**，直接学习新特性。毕竟，技术是向前发展的。

语言强化
----

### if/switch 变量声明强化

在传统 C++ 中，变量的声明在虽然能够位于任何位置，甚至于 `for` 语句内能够声明一个临时变量 `int`，但始终没有办法在 `if` 和 `switch` 语句中声明一个临时的变量。例如：

    #include <iostream>
    #include <vector>
    #include <algorithm>
    
    int main() {
        std::vector<int> vec = {1, 2, 3, 4};
    
        // 在 c++17 之前
        const std::vector<int>::iterator itr = std::find(vec.begin(), vec.end(), 2);
        if (itr != vec.end()) {
            *itr = 3;
        }
    
        // 需要重新定义一个新的变量
        const std::vector<int>::iterator itr2 = std::find(vec.begin(), vec.end(), 3);
        if (itr2 != vec.end()) {
            *itr2 = 4;
        }
    
        // 将输出 1, 4, 3, 4
        for (std::vector<int>::iterator element = vec.begin(); element != vec.end(); ++element)
            std::cout << *element << std::endl;
    }
    

在上面的代码中，我们可以看到 `itr` 这一变量是定义在整个 `main()` 的作用域内的，这导致当我们需要再次遍历整个 `std::vectors` 时，需要重新命名另一个变量。C++17 消除了这一限制，使得我们可以在 if（或 switch）中完成这一操作：

    // 将临时变量放到 if 语句内
    if (const std::vector<int>::iterator itr = std::find(vec.begin(), vec.end(), 3);
        itr != vec.end()) {
        *itr = 4;
    }
    

### 初始化列表

初始化是一个非常重要的语言特性，最常见的就是在对象进行初始化时进行使用。在传统 C++ 中，不同的对象有着不同的初始化方法，例如普通数组、POD （**P**lain **O**ld **D**ata，即没有构造、析构和虚函数的类或结构体）类型都可以使用 `{}` 进行初始化，也就是我们所说的初始化列表。而对于类对象的初始化，要么需要通过拷贝构造、要么就需要使用 `()` 进行。这些不同方法都针对各自对象，不能通用。例如：

    #include <iostream>
    #include <vector>
    
    class Foo {
    public:
        int value_a;
        int value_b;
        Foo(int a, int b) : value_a(a), value_b(b) {}
    };
    
    int main() {
        // before C++11
        int arr[3] = {1, 2, 3};
        Foo foo(1, 2);
        std::vector<int> vec = {1, 2, 3, 4, 5};
    
        std::cout << "arr[0]: " << arr[0] << std::endl;
        std::cout << "foo:" << foo.value_a << ", " << foo.value_b << std::endl;
        for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it) {
            std::cout << *it << std::endl;
        }
        return 0;
    }
    

为了解决这个问题，C++11 首先把初始化列表的概念绑定到了类型上，并将其称之为 `std::initializer_list`，允许构造函数或其他函数像参数一样使用初始化列表，这就为类对象的初始化与普通数组和 POD 的初始化方法提供了统一的桥梁，例如：

    #include <initializer_list>
    class MagicFoo {
    public:
        std::vector<int> vec;
        MagicFoo(std::initializer_list<int> list) {
            for (std::initializer_list<int>::iterator it = list.begin(); 
                 it != list.end(); ++it)
                vec.push_back(*it);
        }
    };
    int main() {
        // after C++11
        MagicFoo magicFoo = {1, 2, 3, 4, 5};
    
        std::cout << "magicFoo: ";
        for (std::vector<int>::iterator it = magicFoo.vec.begin(); it != magicFoo.vec.end(); ++it) std::cout << *it << std::endl;
    }
    

这种构造函数被叫做初始化列表构造函数，具有这种构造函数的类型将在初始化时被特殊关照。 初始化列表除了用在对象构造上，还能将其作为普通函数的形参，例如：

    public: 
        void foo(std::initializer_list<int> list) {
                for (std::initializer_list<int>::iterator it = list.begin(); it != list.end(); ++it) vec.push_back(*it);
        }
    
    magicFoo.foo({6,7,8,9});
    

其次，C++11 还提供了统一的语法来初始化任意的对象，例如：

    Foo foo2 {3, 4};
    

### 结构化绑定

结构化绑定提供了类似其他语言中提供的多返回值的功能。在\[标准库扩充：容器\]中，我们会了解 C++11 新增了 `std::tuple` 容器用于构造一个元组，进而囊括多个返回值。但缺陷是，C++11/14 并没有提供一种简单的方法直接从元组中拿到并定义元组中的元素，尽管我们可以使用 `std::tie` 对元组进行拆包，但我们依然必须非常清楚这个元组包含多少个对象，各个对象是什么类型，非常麻烦。 C++17 完善了这一设定，给出的结构化绑定可以让我们写出这样的代码：

    #include <iostream>
    
    std::tuple<int, double, std::string> f() {
        return std::make_tuple(1, 2.3, "456");
    }
    
    int main() {
        auto [x, y, z] = f();
        std::cout << x << ", " << y << ", " << z << std::endl;
        return 0;
    }
    

### auto

`auto` 在很早以前就已经进入了 C++，但是他始终作为一个存储类型的指示符存在，与 `register` 并存。在传统 C++ 中，如果一个变量没有声明为 `register` 变量，将自动被视为一个 `auto` 变量。而随着 `register` 被弃用（在 C++17 中作为保留关键字，以后使用，目前不具备实际意义），对 `auto` 的语义变更也就非常自然了。 使用 `auto` 进行类型推导的一个最为常见而且显著的例子就是迭代器。你应该在前面的小节里看到了传统 C++ 中冗长的迭代写法：

    // 在 C++11 之前
    // 由于 cbegin() 将返回 vector<int>::const_iterator
    // 所以 itr 也应该是 vector<int>::const_iterator 类型
    for(vector<int>::const_iterator it = vec.cbegin(); itr != vec.cend(); ++it)
    

而有了 `auto` 之后可以：

    #include <initializer_list>
    #include <vector>
    #include <iostream>
    
    class MagicFoo {
    public:
        std::vector<int> vec;
        MagicFoo(std::initializer_list<int> list) {
            // 从 C++11 起, 使用 auto 关键字进行类型推导
            for (auto it = list.begin(); it != list.end(); ++it) {
                vec.push_back(*it);
            }
        }
    };
    int main() {
        MagicFoo magicFoo = {1, 2, 3, 4, 5};
        std::cout << "magicFoo: ";
        for (auto it = magicFoo.vec.begin(); it != magicFoo.vec.end(); ++it) {
            std::cout << *it << ", ";
        }
        std::cout << std::endl;
        return 0;
    }
    

一些其他的常见用法：

    auto i = 5;              // i 被推导为 int
    auto arr = new auto(10); // arr 被推导为 int *
    

> **注意**：`auto` 不能用于函数传参，因此下面的做法是无法通过编译的（考虑重载的问题，我们应该使用模板）：
> 
>     > int add(auto x, auto y);
>     >
>     > 2.6.auto.cpp:16:9: error: 'auto' not allowed in function prototype
>     > int add(auto x, auto y) {
>     >         ^~~~
>     >
>     
> 
> 此外，`auto` 还不能用于推导数组类型：
> 
>     > auto auto_arr2[10] = arr;   // 错误,  无法推导数组元素类型
>     >
>     > 2.6.auto.cpp:30:19: error: 'auto_arr2' declared as array of 'auto'
>     >     auto auto_arr2[10] = arr;
>     >
>     
>     

### 区间 for 迭代

C++11 引入了基于范围的迭代写法，我们拥有了能够写出像 Python 一样简洁的循环语句，我们可以进一步简化前面的例子：

    #include <iostream>
    #include <vector>
    #include <algorithm>
    
    int main() {
        std::vector<int> vec = {1, 2, 3, 4};
        if (auto itr = std::find(vec.begin(), vec.end(), 3); itr != vec.end()) *itr = 4;
        for (auto element : vec)
            std::cout << element << std::endl; // read only
        for (auto &element : vec) {
            element += 1;                      // writeable
        }
        for (auto element : vec)
            std::cout << element << std::endl; // read only
    }
    

### 尖括号 “>”

在传统 C++ 的编译器中，`>>`一律被当做右移运算符来进行处理。但实际上我们很容易就写出了嵌套模板的代码：

    std::vector<std::vector<int>> matrix;
    

这在传统C++编译器下是不能够被编译的，而 C++11 开始，连续的右尖括号将变得合法，并且能够顺利通过编译。甚至于下下面这种写法都能够通过编译：

    template<bool T>
    class MagicType {
        bool magic = T;
    };
    
    // in main function:
    std::vector<MagicType<(1>2)>> magic; // 合法, 但不建议写出这样的代码
    

### 类型别名模板

在了解类型别名模板之前，需要理解『模板』和『类型』之间的不同。仔细体会这句话：**模板是用来产生类型的。**在传统 C++ 中，`typedef` 可以为类型定义一个新的名称，但是却没有办法为模板定义一个新的名称。因为，模板不是类型。例如：

    template<typename T, typename U>
    class MagicType {
    public:
        T dark;
        U magic;
    };
    
    // 不合法
    template<typename T>
    typedef MagicType<std::vector<T>, std::string> FakeDarkMagic;
    

C++11 使用 `using` 引入了下面这种形式的写法，并且同时支持对传统 `typedef` 相同的功效：

> 通常我们使用 `typedef` 定义别名的语法是：`typedef 原名称 新名称;`，但是对函数指针等别名的定义语法却不相同，这通常给直接阅读造成了一定程度的困难。

    typedef int (*process)(void *);
    using NewProcess = int(*)(void *);
    template<typename T>
    using TrueDarkMagic = MagicType<std::vector<T>, std::string>;
    
    int main() {
        TrueDarkMagic<bool> you;
    }
    

### 默认模板参数

我们可能定义了一个加法函数：

    template<typename T, typename U>
    auto add(T x, U y) -> decltype(x+y) {
        return x+y;
    }
    

但在使用时发现，要使用 add，就必须每次都指定其模板参数的类型。 在 C++11 中提供了一种便利，可以指定模板的默认参数：

    template<typename T = int, typename U = int>
    auto add(T x, U y) -> decltype(x+y) {
        return x+y;
    }
    

运行强化
----

### Lambda 表达式基础

Lambda 表达式是 C++11 中最重要的新特性之一，而 Lambda 表达式，实际上就是提供了一个类似匿名函数的特性，而匿名函数则是在需要一个函数，但是又不想费力去命名一个函数的情况下去使用的。这样的场景其实有很多很多，所以匿名函数几乎是现代编程语言的标配。 Lambda 表达式的基本语法如下：

    [捕获列表](参数列表) mutable(可选) 异常属性 -> 返回类型 {
    // 函数体
    }
    

上面的语法规则除了 `[捕获列表]` 内的东西外，其他部分都很好理解，只是一般函数的函数名被略去，返回值使用了一个 `->` 的形式进行（我们在上一节前面的尾返回类型已经提到过这种写法了）。 所谓捕获列表，其实可以理解为参数的一种类型，lambda 表达式内部函数体在默认情况下是不能够使用函数体外部的变量的，这时候捕获列表可以起到传递外部数据的作用。根据传递的行为，捕获列表也分为以下几种： **1\. 值捕获** 与参数传值类似，值捕获的前提是变量可以拷贝，不同之处则在于，被捕获的变量在 lambda 表达式被创建时拷贝，而非调用时才拷贝：

    void learn_lambda_func_1() {
        int value_1 = 1;
        auto copy_value_1 = [value_1] {
            return value_1;
        };
        value_1 = 100;
        auto stored_value_1 = copy_value_1();
        // 这时, stored_value_1 == 1, 而 value_1 == 100.
        // 因为 copy_value_1 在创建时就保存了一份 value_1 的拷贝
    }
    

**2\. 引用捕获** 与引用传参类似，引用捕获保存的是引用，值会发生变化。

    void learn_lambda_func_2() {
        int value_2 = 1;
        auto copy_value_2 = [&value_2] {
            return value_2;
        };
        value_2 = 100;
        auto stored_value_2 = copy_value_2();
        // 这时, stored_value_2 == 100, value_1 == 100.
        // 因为 copy_value_2 保存的是引用
    }
    

**3\. 隐式捕获** 手动书写捕获列表有时候是非常复杂的，这种机械性的工作可以交给编译器来处理，这时候可以在捕获列表中写一个 `&` 或 `=` 向编译器声明采用 引用捕获或者值捕获. 总结一下，捕获提供了lambda 表达式对外部值进行使用的功能，捕获列表的最常用的四种形式可以是：

*   \[\] 空捕获列表
*   \[name1, name2, …\] 捕获一系列变量
*   \[&\] 引用捕获, 让编译器自行推导捕获列表
*   \[=\] 值捕获, 让编译器执行推导应用列表

**4\. 表达式捕获(C++14)**

> 这部分内容需要了解后面马上要提到的右值引用以及智能指针

上面提到的值捕获、引用捕获都是已经在外层作用域声明的变量，因此这些捕获方式捕获的均为左值，而不能捕获右值。 C++14 给与了我们方便，允许捕获的成员用任意的表达式进行初始化，这就允许了右值的捕获，被声明的捕获变量类型会根据表达式进行判断，判断方式与使用 `auto` 本质上是相同的：

    #include <iostream>
    #include <utility>
    
    int main() {
        auto important = std::make_unique<int>(1);
        auto add = [v1 = 1, v2 = std::move(important)](int x, int y) -> int {
            return x+y+v1+(*v2);
        };
        std::cout << add(3,4) << std::endl;
        return 0;
    }
    

在上面的代码中，`important` 是一个独占指针，是不能够被捕获到的，这时候我们需要将其转移为右值，在表达式中初始化。

### 泛型 Lambda

上一节中我们提到了 `auto` 关键字不能够用在参数表里，这是因为这样的写法会与模板的功能产生冲突。但是 Lambda 表达式并不是普通函数，所以 Lambda 表达式并不能够模板化。这就为我们造成了一定程度上的麻烦：参数表不能够泛化，必须明确参数表类型。 幸运的是，这种麻烦只存在于 C++11 中，从 C++14 开始，Lambda 函数的形式参数可以使用 `auto` 关键字来产生意义上的泛型：

    auto add = [](auto x, auto y) {
        return x+y;
    };
    
    add(1, 2);
    add(1.1, 2.2);
    

3.3 右值引用 右值引用是 C++11 引入的与 Lambda 表达式齐名的重要特性之一。它的引入解决了 C++ 中大量的历史遗留问题，消除了诸如 `std::vector`、`std::string` 之类的额外开销，也才使得函数对象容器 `std::function` 成为了可能。

### 左值、右值的纯右值、将亡值、右值

要弄明白右值引用到底是怎么一回事，必须要对左值和右值做一个明确的理解。 **左值(lvalue, left value)**，顾名思义就是赋值符号左边的值。准确来说，左值是表达式（不一定是赋值表达式）后依然存在的持久对象。 **右值(rvalue, right value)**，右边的值，是指表达式结束后就不再存在的临时对象。 而 C++11 中为了引入强大的右值引用，将右值的概念进行了进一步的划分，分为：纯右值、将亡值。 **纯右值(prvalue, pure rvalue)**，纯粹的右值，要么是纯粹的字面量，例如 `10`, `true`；要么是求值结果相当于字面量或匿名临时对象，例如 `1+2`。非引用返回的临时变量、运算表达式产生的临时变量、原始字面量、Lambda 表达式都属于纯右值。 **将亡值(xvalue, expiring value)**，是 C++11 为了引入右值引用而提出的概念（因此在传统 C++中，纯右值和右值是统一个概念），也就是即将被销毁、却能够被移动的值。 将亡值可能稍有些难以理解，我们来看这样的代码：

    std::vector<int> foo() {
        std::vector<int> temp = {1, 2, 3, 4};
        return temp;
    }
    
    std::vector<int> v = foo();
    

在这样的代码中，函数 `foo` 的返回值 `temp` 在内部创建然后被赋值给 `v`，然而 `v` 获得这个对象时，会将整个 temp 拷贝一份，然后把 `temp` 销毁，如果这个 `temp` 非常大，这将造成大量额外的开销（这也就是传统 C++ 一直被诟病的问题）。在最后一行中，`v` 是左值、`foo()` 返回的值就是右值（也是纯右值）。 但是，`v` 可以被别的变量捕获到，而 `foo()` 产生的那个返回值作为一个临时值，一旦被 `v` 复制后，将立即被销毁，无法获取、也不能修改。 将亡值就定义了这样一种行为：临时的值能够被识别、同时又能够被移动。

### 右值引用和左值引用

需要拿到一个将亡值，就需要用到右值引用的申明：`T &&`，其中 `T` 是类型。右值引用的声明让这个临时值的生命周期得以延长、只要变量还活着，那么将亡值将继续存活。 C++11 提供了 `std::move` 这个方法将左值参数无条件的转换为右值，有了它我们就能够方便的获得一个右值临时对象，例如：

    #include <iostream>
    #include <string>
    
    void reference(std::string& str) {
        std::cout << "左值" << std::endl;
    }
    void reference(std::string&& str) {
        std::cout << "右值" << std::endl;
    }
    
    int main()
    {
        std::string lv1 = "string,"; // lv1 是一个左值
        // std::string&& r1 = s1; // 非法, 右值引用不能引用左值
        std::string&& rv1 = std::move(lv1); // 合法, std::move可以将左值转移为右值
        std::cout << rv1 << std::endl; // string,
    
        const std::string& lv2 = lv1 + lv1; // 合法, 常量左值引用能够延长临时变量的生命周期
        // lv2 += "Test"; // 非法, 引用的右值无法被修改
        std::cout << lv2 << std::endl; // string,string
    
        std::string&& rv2 = lv1 + lv2; // 合法, 右值引用延长临时对象生命周期
        rv2 += "Test"; // 合法, 非常量引用能够修改临时变量
        std::cout << rv2 << std::endl; // string,string,string,Test
    
        reference(rv2); // 输出左值
    
        return 0;
    }
    

容器
--

### std::array

看到这个容器的时候肯定会出现这样的问题：

1.  为什么要引入 `std::array` 而不是直接使用 `std::vector`？
2.  已经有了传统数组，为什么要用 `std::array`?

先回答第一个问题，`std::vector` 太强大了，以至于我们没有必要为了去敲碎一个鸡蛋而用一个钉锤。使用 `std::array` 保存在栈内存中，相比堆内存中的 `std::vector`，我们就能够灵活的访问这里面的元素，从而获得更高的性能；同时正式由于其堆内存存储的特性，有些时候我们还需要自己负责释放这些资源。 而第二个问题就更加简单，使用`std::array`能够让代码变得更加现代，且封装了一些操作函数，同时还能够友好的使用标准库中的容器算法等等，比如 `std::sort`。 `std::array` 会在编译时创建一个固定大小的数组，`std::array` 不能够被隐式的转换成指针，使用 `std::array` 很简单，只需指定其类型和大小即可：

    std::array<int, 4> arr= {1,2,3,4};
    
    int len = 4;
    std::array<int, len> arr = {1,2,3,4}; // 非法, 数组大小参数必须是常量表达式
    

当我们开始用上了 `std::array` 时，难免会遇到要将其兼容 C 风格的接口，这里有三种做法：

    void foo(int *p, int len) {
        return;
    }
    
    std::array<int, 4> arr = {1,2,3,4};
    
    // C 风格接口传参
    // foo(arr, arr.size()); // 非法, 无法隐式转换
    foo(&arr[0], arr.size());
    foo(arr.data(), arr.size());
    
    // 使用 `std::sort`
    std::sort(arr.begin(), arr.end());
    

### std::forward_list

`std::forward_list` 是一个列表容器，使用方法和 `std::list` 基本类似，因此我们就不花费篇幅进行介绍了。 需要知道的是，和 `std::list` 的双向链表的实现不同，`std::forward_list` 使用单向链表进行实现，提供了 `O(1)` 复杂度的元素插入，不支持快速随机访问（这也是链表的特点），也是标准库容器中唯一一个不提供 `size()` 方法的容器。当不需要双向迭代时，具有比 `std::list` 更高的空间利用率。

### 无序容器

我们已经熟知了传统 C++ 中的有序容器 `std::map`/`std::set`，这些元素内部通过红黑树进行实现，插入和搜索的平均复杂度均为 `O(log(size))`。在插入元素时候，会根据 `<`操作符比较元素大小并判断元素是否相同，并选择合适的位置插入到容器中。当对这个容器中的元素进行遍历时，输出结果会按照 `<` 操作符的顺序来逐个遍历。 而无序容器中的元素是不进行排序的，内部通过 Hash 表实现，插入和搜索元素的平均复杂度为 `O(constant)`，在不关心容器内部元素顺序时，能够获得显著的性能提升。 C++11 引入了两组无序容器：`std::unordered_map`/`std::unordered_multimap` 和 `std::unordered_set`/`std::unordered_multiset`。 它们的用法和原有的 `std::map`/`std::multimap`/`std::set`/`set::multiset` 基本类似，由于这些容器我们已经很熟悉了，便不一一举例，我们直接来比较一下`std::map`和`std::unordered_map`：

    #include <iostream>
    #include <string>
    #include <unordered_map>
    #include <map>
    
    int main() {
        // 两组结构按同样的顺序初始化
        std::unordered_map<int, std::string> u = {
            {1, "1"},
            {3, "3"},
            {2, "2"}
        };
        std::map<int, std::string> v = {
            {1, "1"},
            {3, "3"},
            {2, "2"}
        };
    
        // 分别对两组结构进行遍历
        std::cout << "std::unordered_map" << std::endl;
        for( const auto & n : u)
            std::cout << "Key:[" << n.first << "] Value:[" << n.second << "]\n";
    
        std::cout << std::endl;
        std::cout << "std::map" << std::endl;
        for( const auto & n : v)
            std::cout << "Key:[" << n.first << "] Value:[" << n.second << "]\n";
    }
    

最终的输出结果为：

    std::unordered_map
    Key:[2] Value:[2]
    Key:[3] Value:[3]
    Key:[1] Value:[1]
    
    std::map
    Key:[1] Value:[1]
    Key:[2] Value:[2]
    Key:[3] Value:[3]
    

### std::tuple

了解过 Python 的程序员应该知道元组的概念，纵观传统 C++ 中的容器，除了 `std::pair`外，似乎没有现成的结构能够用来存放不同类型的数据（通常我们会自己定义结构）。但 `std::pair` 的缺陷是显而易见的，只能保存两个元素。

#### 元组基本操作

关于元组的使用有三个核心的函数：

1.  `std::make_tuple`: 构造元组
2.  `std::get`: 获得元组某个位置的值
3.  `std::tie`: 元组拆包

    #include <tuple>
    #include <iostream>
    
    auto get_student(int id)
    {
    // 返回类型被推断为 std::tuple<double, char, std::string>
    
    if (id == 0)
        return std::make_tuple(3.8, 'A', "张三");
    if (id == 1)
        return std::make_tuple(2.9, 'C', "李四");
    if (id == 2)
        return std::make_tuple(1.7, 'D', "王五");
        return std::make_tuple(0.0, 'D', "null");
        // 如果只写 0 会出现推断错误, 编译失败
    }
    
    int main()
    {
        auto student = get_student(0);
        std::cout << "ID: 0, "
        << "GPA: " << std::get<0>(student) << ", "
        << "成绩: " << std::get<1>(student) << ", "
        << "姓名: " << std::get<2>(student) << '\n';
    
        double gpa;
        char grade;
        std::string name;
    
        // 元组进行拆包
        std::tie(gpa, grade, name) = get_student(1);
        std::cout << "ID: 1, "
        << "GPA: " << gpa << ", "
        << "成绩: " << grade << ", "
        << "姓名: " << name << '\n';
    }
    

`std::get` 除了使用常量获取元组对象外，C++14 增加了使用类型来获取元组中的对象：

    std::tuple<std::string, double, double, int> t("123", 4.5, 6.7, 8);
    std::cout << std::get<std::string>(t) << std::endl;
    std::cout << std::get<double>(t) << std::endl; // 非法, 引发编译期错误
    std::cout << std::get<3>(t) << std::endl;
    

#### 运行期索引

如果你仔细思考一下可能就会发现上面代码的问题，`std::get<>` 依赖一个编译期的常量，所以下面的方式是不合法的：

    int index = 1;
    std::get<index>(t);
    

那么要怎么处理？答案是，**标准库做不到**。这里介绍一个使用 `boost::variant` 配合变长模板参数的黑魔法：

    #include <boost/variant.hpp>
    template <size_t n, typename... T>
    boost::variant<T...> _tuple_index(size_t i, const std::tuple<T...>& tpl) {
    if (i == n)
        return std::get<n>(tpl);
    else if (n == sizeof...(T) - 1)
        throw std::out_of_range("越界.");
    else
        return _tuple_index<(n < sizeof...(T)-1 ? n+1 : 0)>(i, tpl);
    }
    template <typename... T>
    boost::variant<T...> tuple_index(size_t i, const std::tuple<T...>& tpl) {
        return _tuple_index<0>(i, tpl);
    }
    

这样我们就能：

    int i = 1;
    std::cout << tuple_index(i, t) << std::endl;
    

#### 元组合并与遍历

还有一个常见的需求就是合并两个元组，这可以通过 `std::tuple_cat` 来实现：

    auto new_tuple = std::tuple_cat(get_student(1), std::move(t));
    

马上就能够发现，应该如何快速遍历一个元组？但是我们刚才介绍了如何在运行期通过非常数索引一个 `tuple` 那么遍历就变得简单了，首先我们需要知道一个元组的长度，可以：

    template <typename T>
    auto tuple_len(T &tpl) {
        return std::tuple_size<T>::value;
    }
    

这样就能够对元组进行迭代了：

    // 迭代
    for(int i = 0; i != tuple_len(new_tuple); ++i)
        // 运行期索引
        std::cout << tuple_index(i, new_tuple) << std::endl;
    

结语
--

以上是一些主要的，可以应用的C++11/14/17新特性的简要叙述。 其中还有一些复杂的，不太实用的应用方法，这里不再赘述。