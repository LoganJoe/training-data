---
title: " C++ STL常用举隅\t\t"
url: 2712.html
id: 2712
categories:
  - Algorithm
date: 2019-02-08 15:28:24
tags:
---

老子终于要写这个大坑了23333

迭代器
---

迭代器是STL里的一个重要概念。几乎所有的STL都有迭代器。迭代器提供了一个类似于指针的元素，以指向STL中的某一元素。

要定义一个迭代器类型，可以在STL名后面加`::iterator it,it1`之类的。后面的就是定义出来的，仅针对前述STL的iterator类。例如

std::map<int,long long>::iterator it;

标明对`<pos,value>`键分别定义为int和long long的map定义的一个迭代器`it`。

迭代器支持很多操作。例如`it++`访问下一个元素的迭代器，`it--`访问上一个元素的迭代器等。

迭代器其实指向的是一个指针类型。因此，要取出迭代器所指向位置的值，要用取地址符，即`*it`来获取。

vector
------

vector其实说白了就是一个不定长数组。vector由如下定义：

std::vector<int> A;

其中，尖括号内可以填入一个参数，表示vector内类型。

在C++11里引入了vector的范围迭代，同时指示器也得到了更新。所以vector在开O2的情况下也不会比数组慢。范围迭代在另外一篇博客内有叙述。

vector在内存空间里是连续的一段，可以用`begin()`和`end()`取出头尾地址。因此，vector的sort得这样写：

std::sort(s.begin(),s.end());

vector有两种取元素的方法：迭代器与数组。注意，迭代器取到空地址会返回`end()+1`，而数组则会直接RE。因此，在向vector里面取元素的时候，一定要通过size判断这个位置是否存在。

向vector里插入元素，可以用`A.push_back(s)`向`A`中插入元素`s`。vector是连续表，不支持向前插入。但是，vector是支持`insert`和`delete`的。当然，这两个操作只是暴力移动后面所有的空间，效率$O(n)$。具体用法是

A.insert(A.begin()+pos,val);A.insert(it,val);
A.delete(A.begin()+pos);A.delete(it);

第一个参数要求为指针类型。

vector用`size()`返回其元素个数，用`empty()`判断是否为空，用`clear()`来清空。

map
---

map其实是一个映射，给定一个键，返回一个值。所以，map在定义的时候要同时填入`pos`和`value`的类型：

std::map<int,int> MAP;

map其实同时存储了键和值，因此，我们用迭代器，其取出来的是一个`<key,value>`对，也就是一个pair：pair的`first`存储了`key`，`second`存储了`value`。

在迭代器中，map默认是按照`key`即键值排序的。向下迭代会取到键值更大的位置。

map可以用三种方法取值：数组，迭代器和函数：

int c = MAP\[2\]
int c = MAP.find(2)
std::map<int,int>::iterator it = MAP.begin(); int c = *it;

同样，map也有`size(),clear(),empty()`函数。注意，`vector`中的`size`是$O(1)$的。而map，set，priority_queue…里面的`size()`是$O(\\log n)$的。事实上，他们的插入，删除，访问均是$O(\\log n)$的。

对于某个键值，我们同样也可以用`MAP.insert(key,value),MAP.delete(key)`来插入和删除元素。

set
---

set其实就是一个平衡树。set内元素自带有序。定义：

std::set<int> S;
std::multiset<int> S;

其中，普通set中元素不可重复。multiset中元素可重复。

**操作**

**效果**

`set c`

产生一个空的set/multiset，不含任何元素

`set c(op)`

以op为排序准则，产生一个空的set/multiset

`set c1(c2)`

产生某个set/multiset的副本，所有元素都被拷贝

`set c(beg,end)`

以区间\[beg,end)内的所有元素产生一个set/multiset

`set c(beg,end, op)`

以op为排序准则，区间\[beg,end)内的元素产生一个set/multiset

`c.~set()`

销毁所有元素，释放内存

`set<Elem>`

产生一个set，以(operator <)为排序准则

`set<Elem,0p>`

产生一个set，以op为排序准则

`c.size()`

返回当前的元素数量，$O(\\log n)$

`c.empty ()`

判断大小是否为零，等同于0 == size()，效率更高

`c.max_size()`

返回能容纳的元素最大数量

`count (elem)`

返回元素值为elem的个数

`find(elem)`

返回元素值为elem的**第一个**元素，如果没有**返回end()**

`lower _bound(elem)`

返回元素值为elem的第一个可安插位置，也就是元素值 >= elem的第一个元素位置

`upper _bound (elem)`

返回元素值为elem的最后一个可安插位置，也就是元素值 > elem 的第一个元素位置

`equal_range (elem)`

返回elem可安插的第一个位置和最后一个位置，也就是元素值==elem的区间

`c.begin()`

返回一个随机存取迭代器，指向第一个元素

`c.end()`

返回一个随机存取迭代器，指向**最后一个元素的下一个位置**

`c.rbegin()`

返回一个逆向迭代器，指向逆向迭代的第一个元素

`c.rend()`

返回一个逆向迭代器，指向逆向迭代的最后一个元素的下一个位置

`c.insert(elem)`

插入一个elem副本，返回新元素位置，无论插入成功与否。

`c.insert(pos, elem)`

安插一个elem元素副本，返回新元素位置，pos为收索起点，提升插入速度。

`c.insert(beg,end)`

将区间\[beg,end)所有的元素安插到c，无返回值。

`c.erase(elem)`

删除**与elem相等**的所有元素，返回被移除的元素个数。

`c.erase(pos)`

移除迭代器pos**所指位置**元素，无返回值。

`c.erase(beg,end)`

移除区间\[beg,end)所有元素，无返回值。

`c.clear()`

移除所有元素，将容器清空

注意，mulitset不能随意用`erase`删除。

set中的删除操作是不进行任何的错误检查的，比如定位器的是否合法等等，所以用的时候自己一定要注意。

queue
-----

队列是很简单的数据结构。队列的参数表仅填入一个参数表示类型。除了拥有迭代器，上述的`size(),empty(),clear()`外，还满足队列的性质：用`push()`加入一个元素到队尾，用`front()`取队头，用`pop()`弹出队头。

deque
-----

双端队列。双端队列本质是用链表实现的：除了拥有迭代器，上述的`size(),empty(),clear()`外，还满足双端队列的性质：用`push_back()`加入一个元素到队尾，用`push_front()`加入一个元素到队头，用`front()`取队头，用`back()`取队尾。用`pop_front()`弹出队头。用`pop_back()`弹出队尾。

priority_queue
--------------

　`priority_queue`的模板申明带3个参数：`priority_queue<Type, Container, Functional>`，其中Type 为数据类型，Container为保存数据的容器，Functional 为元素比较方式。

　　Container必须是用数组实现的容器，比如`vector,deque`等等，但不能用 `list`。STL里面默认用的是`vector`。

`priority_queue`默认申明一个大根堆。若要声明一个小根堆，可以用STL自带的彷函数：

priority_queue<int, vector<int>, greater<int> > q;

此外，还可以通过重载运算符的方式重新声明优先级。

`priority_queue`作为一个堆，支持`push(value)`插入元素，`top()`取堆顶，`pop()`弹出堆顶。所以叫优先队列。

bitset
------

bitset是系统自带的压位。bitset的STL有四百多行。作为一个位运算集合，它的实现方式是将32位压成一个int（或者64位压成一个longlong）,然后集中维护。由于用的是整数来维护，因此其比按位操作要快上不少，一般效率是$O(n/32)$的。$n$为位数。同样的，其空间占用也是$O(n/32)$个int的级别的。

bitset的定义带有一个参数，表示位数。例如

std::bitset<10000> S;<code></code>

定义了一个10000位的bitset。

bitset支持所有的位运算操作。

// bitset operators
#include <iostream> // std::cout
#include <string> // std::string
#include <bitset> // std::bitset

int main ()
{
std::bitset<4> foo (std::string("1001"));
std::bitset<4> bar (std::string("0011"));

std::cout << (foo^=bar) << '\\n'; // 1010 (XOR,assign)
std::cout << (foo&=bar) << '\\n'; // 0010 (AND,assign)
std::cout << (foo|=bar) << '\\n'; // 0011 (OR,assign)

std::cout << (foo<<=2) << '\\n'; // 1100 (SHL,assign)
std::cout << (foo>>=1) << '\\n'; // 0110 (SHR,assign)

std::cout << (~bar) << '\\n'; // 1100 (NOT)
std::cout << (bar<<1) << '\\n'; // 0110 (SHL)
std::cout << (bar>>1) << '\\n'; // 0001 (SHR)

std::cout << (foo==bar) << '\\n'; // false (0110==0011)
std::cout << (foo!=bar) << '\\n'; // true (0110!=0011)

std::cout << (foo&bar) << '\\n'; // 0010
std::cout << (foo|bar) << '\\n'; // 0111
std::cout << (foo^bar) << '\\n'; // 0101

return 0;
}

此外：

操作

效果

`size()`

返回大小（位数）

`count()`

返回1的个数

`any()`

返回是否有1

`none()`

返回是否没有1

`set()`

全都变成1

`set(p)`

将第p + 1位变成1

`set(p, x)`

将第p + 1位变成x

`reset()`

全都变成0

`reset(p)`

将第p + 1位变成0

`flip()`

全都取反

`flip(p)`

将第p + 1位取反

`to_ulong()`

返回它转换为unsigned long的结果，如果超出范围则报错

`to_ullong()`

返回它转换为unsigned long long的结果，如果超出范围则报错

`to_string()`

返回它转换为string的结果