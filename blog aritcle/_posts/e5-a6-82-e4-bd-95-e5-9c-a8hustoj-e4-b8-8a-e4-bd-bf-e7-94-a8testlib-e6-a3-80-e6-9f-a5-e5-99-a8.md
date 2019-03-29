---
title: " 如何在HUSTOJ上使用testlib检查器\t\t"
url: 3532.html
id: 3532
categories:
  - Other
date: 2018-08-24 15:32:27
tags:
---

### 安利一波 testlib！

[testlib](http://codeforces.com/testlib) 或许是 Codeforces 在数百场比赛中有效控制出锅率并保持长久不衰的最大武器。如果你有幸连续体验了 #420 和 #421…… emmmmm 似乎是个声名狼籍的巧合呢……

testlib 可以用来实现健壮性极佳的 checker（答案检查器，即 Special Judge）、generator（数据生成器）、validator（数据校验器）和 interactor（交互器），不过在现有的环境下大家关注最多的应该还是 checker。手写的 checker 在选手的奇妙输出上 RE 或给出错误结果的可能性极高（例如声名狼籍的 HNOI 2017 D2T2，以及 NOI 2017 D2T1 的小锅（逃，没 A 题还在这吐槽怕是要被吃掉哦）），于是乎有了 testlib 这个伟大的存在。

testlib checker 的大致思想是避免通过 `scanf`/`iostream` 直接读取程序的输出，转而使用一套完善的 API 按照特定格式读取对应类型的数据。一切**不符合格式要求**的输出、**超出范围**的数据，甚至文件末尾多余的非空白内容都会导致 testlib 直接给出 Presentation Error 的判断。这样一来，checker 读取到的数据有了合法性的保证，也就可以轻松地避免不少  Judgement Failed 了。

（注：不少 OJ 并不区分 Presentation Error 和 Wrong Answer。）

### （超简陋的） testlib 入门指南

#### Setup

testlib可以实现一些健壮性极佳的checker。

请先下载（经过魔改的）testlib.h：

[testlib](http://www.dtenomde.com/wp-content/uploads/2018/08/testlib.h)[Download](http://www.dtenomde.com/wp-content/uploads/2018/08/testlib.h)

使用方式：在开头#include "testlib.h"，然后在main函数开头加上

> register\_DTOJ\_Checker(argc,argv,point_score);

其中，point\_score请填入本测试点评分。使用argv\[4\]传入的测试点，请用atoi取出后传入。已知bug：spj开头必须refresh \_message。

#### Hello world

CF 对于 checker 的完整说明在 [这里](http://codeforces.com/blog/entry/18431)。如果语言障碍不大的话还是读一遍比较好吧。

下面的例子取自官方说明，实现了一个 checker 用于检查只包含一个 \[−2000,2000\]\[-2000, 2000\]\[−2000,2000\] 范围内整数的输出。直观感受一下大概是能搞清楚这个框架的吧 ← ←

#include "testlib.h"

// main 需要接收命令行参数
int main(int argc, char *argv\[\])
{
    register\_DTOJ\_Checker(argc,argv,10.0);
    int pans = ouf.readInt(-2000, 2000);
    int jans = ans.readInt();

    if (pans == jans)
        quitf(_ok, "The sum is correct.");
    else
        quitf(_wa, "The sum is wrong: expected = %d, found = %d", jans, pans);

    return 0;
}

将 `testlib.h` 复制到同一目录后直接编译即可。运行的方式是 `./checker <input-file> <output-file> <answer-file>`。看到 "ok" 出现的瞬间是不是整个人都兴奋了呢 (///u///)

#### Cheatsheet

一些最最常用的函数。更多功能可以浏览 testlib.h 头文件，并善用 Ctrl-F。

定义

说明

`InStream inf;`  
`InStream ouf;`  
`InStream ans;`

← 输入文件  
← 选手输出  
← 参考输出

`int InStream::readInt(int minv, int maxv)`

读取一个 \[minv, maxv\] 范围内的 32 位整数（忽略空白字符）

`long long InStream::readLong(long long minv, long long maxv)`

读取一个 \[minv, maxv\] 范围内的 64 位整数（忽略空白字符）

`double InStream::readDouble(double minv, double maxv)`

读取一个 \[minv, maxv\] 范围内的实数（忽略空白字符）

`std::string InStream::readToken()`

读取一个不包含空白字符的连续字符串（忽略空白字符）

`std::string InStream::readToken(const std::string& ptrn)`

读取一个匹配给定模式的不包含空白字符的连续字符串（忽略空白字符）  
模式串的格式戳[这里](https://github.com/MikeMirzayanov/testlib/blob/master/testlib.h#L439)

`char InStream::readChar()`

读取单个字符

`char InStream::readSpace()`

读取一个空格

`void InStream::readEoln()`

读取一个换行符

`void InStream::readEof()`

读取一个文末符

**另外，[这里](https://github.com/MikeMirzayanov/testlib/tree/master/checkers) 是几个常见 checker（整数序列、实数序列、大小写不敏感 Yes/No 等）的实现。**

#### Good practices & Shameless self promotion

*   给所有读入的数据一个限制范围
*   将「读入答案」的操作分离为一个单独的子程序，并对 `ouf` 和 `ans` 分别调用它
*   PE 或 WA 时给出一些详细的信息（例如违反了哪一项限制、出错在第几行）

总之参考几份 checker 之后还是不难写出一个超级健壮的 checker 的。