---
title: " AtCoder Regular Contest 092\t\t"
tags:
  - 二分图
  - 思路
url: 1210.html
id: 1210
categories:
  - AtCoder
  - Solution
date: 2018-03-22 22:34:23
---

Rank38！开心。

C:2D Plane 2N Points
--------------------

### 题意

二维平面上有$n$个红点和$n$个蓝点，若一个红点的$x$都比蓝点的$x$小，且红点的$y$也比蓝点的$y$小，那么它们匹配。 问最多能有多少匹配，一个点不能属于多个对。

### 题解

刚开始还以为就两重for上去，写完被样例卡了。 想了想发现有点不妥，觉得GG的时候突然想到：这不就是二分图最大匹配吗？！然后写完因数组开小WA了一次就过了。  

D:Two Sequences
---------------

### 题意

从长度为$n$的序列$A$和长度为$n$的序列$B$各选一个数加起来，得到$n^2$个数。问这$n^2$个数的异或。

### 题解

我觉得这个题不错。 从高到低考虑答案的每一二进制位虑，也就是计算$n^2$个数中某一二进制位上为$1$的数有多少个。 假设现在考虑$2^k$那一位。显然比这位高的位置对当前这位没有影响，也就是说所有数可以对$2^{k+1}$取模。 枚举序列$A$中选的是什么数，记为$a$，考虑序列$B$满足什么条件的数才是我们要找的，记找的数为$b$。 那么需要满足 $$2^k\\leqslant a+b<2^{k+1}$$ 或者 $$2^{k+1}+2^k\\leqslant a+b<2^{k+2}$$ 由于所有数已经对$2^{k+1}$取模了，那么两个数的和一定$<2^{k+2}$。 那么对于每个$a$，二分查找一下满足条件的$b$数量即可。  

E:Both Sides Merger
-------------------

### 题意

有一个长度为$n$的序列$A$。每次你可以选择开头或末尾的数，然后删掉。或者选择中间的数，将它换成它左右两侧的数之和。 一直操作到只剩一个数。最大化剩下的数，并输出方案。

### 题解

考虑最后的答案是有由最初哪些数的和得到的。 发现两个奇偶性不同的位置上的数是不可能加在一起的，两个位置之间的距离的奇偶性不会改变。 那么答案肯定由一串最初在奇数位的数或者最初在偶数位的数加起来得到的。 我们可以用$n^2$的dp求出答案，记$f\[i\]$贡献答案的最后一个数是第$i$个，然后找和$i$奇偶性相同的$j$转移，并且记录下转移路径。 假如贡献最优解的位置$i$是从位置$j$转移过来的，那么先把$\[i,j\]$中间的数两两合起来，然后把$i,j$合起来，最后把最优解开头前面的和结尾后面的删掉即可。 打完比赛后发现$n^2$的dp完全可以优化到$O(n)$，原本以为还要两个单调栈，后来发现只要记当前最优解位置就好… 那么问题来了，出题人为什么不卡$n^2$呢… 不过$n^2$也没多少人过，可能主要想考思路吧。